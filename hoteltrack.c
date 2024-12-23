#include <stdio.h>
#include <stdlib.h> // Pour exit()
#include <string.h> // Pour strcspn()

// Structure pour stocker les détails des clients
struct CustomerDetails
{
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[15];
    char nationality[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
} s;

// Fonction pour ajouter un client
void add()
{
    FILE *f;
    char test;

    // Ouvrir le fichier en mode ajout ou création
    f = fopen("add.txt", "a+");
    if (f == NULL)
    {
        f = fopen("add.txt", "w+");
        system("cls");
        printf("Please hold on while we set our database in your computer!!");
        printf("\nProcess completed, press any key to continue!!");
        getchar(); // Pause utilisateur
    }

    // Boucle pour ajouter plusieurs clients
    while (1)
    {
        system("cls");
        printf("\nEnter Customer Details:");
        printf("\n**************************");

        // Lecture des détails du client avec fgets
        printf("\nEnter Room number:\n");
        fgets(s.roomnumber, sizeof(s.roomnumber), stdin);
        s.roomnumber[strcspn(s.roomnumber, "\n")] = '\0';

        printf("Enter Name:\n");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0';

        printf("Enter Address:\n");
        fgets(s.address, sizeof(s.address), stdin);
        s.address[strcspn(s.address, "\n")] = '\0';

        printf("Enter Phone Number:\n");
        fgets(s.phonenumber, sizeof(s.phonenumber), stdin);
        s.phonenumber[strcspn(s.phonenumber, "\n")] = '\0';

        printf("Enter Nationality:\n");
        fgets(s.nationality, sizeof(s.nationality), stdin);
        s.nationality[strcspn(s.nationality, "\n")] = '\0';

        printf("Enter Email:\n");
        fgets(s.email, sizeof(s.email), stdin);
        s.email[strcspn(s.email, "\n")] = '\0';

        printf("Enter Period ('x' days):\n");
        fgets(s.period, sizeof(s.period), stdin);
        s.period[strcspn(s.period, "\n")] = '\0';

        printf("Enter Arrival date (dd\\mm\\yyyy):\n");
        fgets(s.arrivaldate, sizeof(s.arrivaldate), stdin);
        s.arrivaldate[strcspn(s.arrivaldate, "\n")] = '\0';

        // Écriture des données dans le fichier
        fwrite(&s, sizeof(s), 1, f);

        // Vider le tampon pour éviter les interférences
        while ((test = getchar()) != '\n' && test != EOF)
            ;

        // Message et attente de la touche
        printf("\n\n1 Room is successfully booked!!");
        printf("\nPress ESC key to exit, or any other key to add another customer detail:");
        test = getchar(); // Lire la touche actuelle

        // Vérification de la touche ESC
        if (test == 27)
        { // Code ASCII pour ESC
            printf("\nExiting...\n");
            break;
        }

        // Consommer les résidus après lecture
        while ((test = getchar()) != '\n' && test != EOF)
            ;
    }

    fclose(f);
}

// Fonction pour afficher la liste des clients
void list()
{
    FILE *f;
    int i;

    // Ouvrir le fichier en mode lecture
    f = fopen("add.txt", "r");
    if (f == NULL)
    {
        printf("\nNo records found. Exiting...\n");
        exit(0);
    }

    system("cls");
    printf("ROOM    ");
    printf("NAME\t ");
    printf("\tADDRESS ");
    printf("\tPHONENUMBER ");
    printf("\tNATIONALITY ");
    printf("\tEMAIL ");
    printf("\t\t  PERIOD ");
    printf("\t ARRIVALDATE \n");

    for (i = 0; i < 118; i++)
        printf("-");

    // Lire et afficher chaque enregistrement
    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        printf("\n%s \t%s \t\t%s \t\t%s \t%s  \t%s  \t     %s  \t  %s",
               s.roomnumber, s.name, s.address, s.phonenumber,
               s.nationality, s.email, s.period, s.arrivaldate);
    }
    printf("\n");

    for (i = 0; i < 118; i++)
        printf("-");

    fclose(f);
    printf("\nPress any key to exit");
    getchar();
}

// Fonction principale
int main()
{
    add();  // Appel de la fonction pour ajouter un client
    list(); // Appel de la fonction pour afficher les clients
    return 0;
}
