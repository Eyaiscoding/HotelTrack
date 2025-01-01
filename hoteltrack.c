#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

void setcolor(int Forgc)
{WORD WColor;
HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

if (GetConsolzSoleScreenBufferInfo(hStdOut,&csbi))
{ wColor=(csbi.WAttributes & 0xB0)+(Forgc & 0x0B);
// SetConsoleTextAttributes(hStdOut,wColor);
   SetConsoleTextAttribute(hStdOut,wColor);
}
}

void login()
{	
    int i=0;
    char given_user[10],given_pass[10]; 
    char username[10]="user",password[10]="pass";
do
{
    system("cls");
    printf("\n  **************************  LOGIN  **************************  ");
    printf(" \n                       ENTER USERNAME:");
    scanf("%s", &given_user); 
	
    printf(" \n                       ENTER PASSWORD:");
	while(i<10)
	{
	    given_pass[i]=getch();
	    if(given_pass[i]==13) break;
	    else printf("*");
	    i++;
	}
	given_pass[i]='\0';
	i=0; 
	if(strcmp(given_user,username)==0 && strcmp(given_pass,password)==0)
	{
		printf("  \n\n\n       LOGIN IS SUCCESSFUL");
		break;
	}
	else
	{
		printf("\n        LOGIN IS UNSUCESSFUL");
		getch();
	}
}
while(1);	
}  



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
void search()
{
system("cls");
   FILE*f;
   char roomnuber[20];
   int flag=1;
   f=fopen("add.txt","r+");
   if(f==0)
		 exit(0);
	fflush(stdin);
   printf("Enter Room number of the customer to search its details : \n");
   scanf("%s", roomnumber);
   while(fread(&s,sizeof(s),1,f)==1)
   {
       if(strcmp(s.roomnumber,roomnumber)==0{

   


void edit() {
    FILE *f;
    int k = 1;  // Variable pour vérifier si l'enregistrement est trouvé
    char roomnumber[20];  // Numéro de chambre à rechercher
    long int size = sizeof(s);  // Taille d'une structure CustomerDetails

    // Ouvrir le fichier en lecture et écriture
    if ((f = fopen("add.txt", "r+")) == NULL) {
        printf("Error opening file! Exiting...\n");
        exit(0);
    }

    // Demander à l'utilisateur le numéro de chambre à modifier
    system("cls");
    printf("Enter Room number of the customer to edit:\n\n");
    scanf("%[^\n]", roomnumber);  // Lire le numéro de chambre saisi par l'utilisateur
    while (getchar() != '\n');  // Nettoyer le tampon d'entrée

    // Parcourir le fichier pour trouver l'enregistrement correspondant
    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            k = 0;  // Indiquer que l'enregistrement a été trouvé

            // Demander les nouveaux détails au client
            printf("\nEnter New Room Number: ");
            fgets(s.roomnumber, sizeof(s.roomnumber), stdin);
            s.roomnumber[strcspn(s.roomnumber, "\n")] = '\0';  // Supprimer le '\n'

            printf("\nEnter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';  // Supprimer le '\n'

            printf("\nEnter New Address: ");
            fgets(s.address, sizeof(s.address), stdin);
            s.address[strcspn(s.address, "\n")] = '\0';  // Supprimer le '\n'

            printf("\nEnter New Phone Number: ");
            fgets(s.phonenumber, sizeof(s.phonenumber), stdin);
            s.phonenumber[strcspn(s.phonenumber, "\n")] = '\0';  // Supprimer le '\n'


            // Partie de Ines 


            // Sauvegarder les modifications dans le fichier
            fseek(f, -size, SEEK_CUR);  // Revenir au début de l'enregistrement actuel
            fwrite(&s, sizeof(s), 1, f);  // Réécrire les données modifiées
            break;  // Sortir de la boucle après modification
        }
    }

    fclose(f);  // Fermer le fichier après les modifications


    // Partie de Ines 


}


// Fonction principale
int main() {
    int option;

    while (1) {
        system("cls");
        printf("1. Add Customer\n");
        printf("2. View Customer List\n");
        printf("3. Edit Customer Record\n");
        printf("4. Exit\n");
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
                edit();
                break;
            case 4:
                printf("\nExiting program...\n");
                exit(0);
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}
