#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour stocker les détails des clients
struct CustomerDetails {
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
void add() {
    FILE *f;
    char choice;

    // Ouvrir ou créer le fichier
    f = fopen("add.txt", "a+");
    if (f == NULL) {
        printf("Error opening file! Exiting...\n");
        exit(1);
    }

    // Boucle pour ajouter plusieurs clients
    while (1) {
        system("cls");
        printf("Enter Customer Details:\n");
        printf("**************************\n");

        // Lecture des détails avec fgets
        printf("Enter Room number: ");
        fgets(s.roomnumber, sizeof(s.roomnumber), stdin);
        s.roomnumber[strcspn(s.roomnumber, "\n")] = '\0';

        printf("Enter Name: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0';

        printf("Enter Address: ");
        fgets(s.address, sizeof(s.address), stdin);
        s.address[strcspn(s.address, "\n")] = '\0';

        printf("Enter Phone Number: ");
        fgets(s.phonenumber, sizeof(s.phonenumber), stdin);
        s.phonenumber[strcspn(s.phonenumber, "\n")] = '\0';

        printf("Enter Nationality: ");
        fgets(s.nationality, sizeof(s.nationality), stdin);
        s.nationality[strcspn(s.nationality, "\n")] = '\0';

        printf("Enter Email: ");
        fgets(s.email, sizeof(s.email), stdin);
        s.email[strcspn(s.email, "\n")] = '\0';

        printf("Enter Period ('x' days): ");
        fgets(s.period, sizeof(s.period), stdin);
        s.period[strcspn(s.period, "\n")] = '\0';

        printf("Enter Arrival date (dd/mm/yyyy): ");
        fgets(s.arrivaldate, sizeof(s.arrivaldate), stdin);
        s.arrivaldate[strcspn(s.arrivaldate, "\n")] = '\0';

        // Écriture des données dans le fichier
        fwrite(&s, sizeof(s), 1, f);
        printf("\nCustomer details successfully added!\n");

        // Demander à l'utilisateur s'il veut continuer ou quitter
        printf("Press '0' to exit, or any other key to add another customer: ");
        choice = getchar();

        // Nettoyer le tampon après la lecture
        while (getchar() != '\n');

        // Sortir si l'utilisateur appuie sur '0'
        if (choice == '0') {
            printf("\nExiting...\n");
            break;
        }
    }

    fclose(f);
}

// Fonction pour afficher la liste des clients
void list() {
    FILE *f;
    int i;

    // Ouvrir le fichier en lecture
    f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("No records found. Exiting...\n");
        exit(1);
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
    while (fread(&s, sizeof(s), 1, f) == 1) {
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
int main() {
    int option;

    while (1) {
        system("cls");
        printf("1. Add Customer\n");
        printf("2. View Customer List\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        // Nettoyage du tampon
        while (getchar() != '\n');

        switch (option) {
            case 1:
                add();
                break;
            case 2:
                list();
                break;
            case 3:
                printf("\nExiting program...\n");
                exit(0);
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}
