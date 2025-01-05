#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //pour manipuler les attributs de couleur du terminal
#include <conio.h>

// Fonction pour définir la couleur du texte
void setcolor(int Forgc) {
    WORD WColor; // Variable pour stocker les informations de couleur
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Obtenir la poignée du terminal
    CONSOLE_SCREEN_BUFFER_INFO csbi; // Structure pour les informations sur le tampon de l'écran
 
    // Vérifier les informations sur le tampon de l'écran
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        // Calculer les nouveaux attributs de couleur
        WColor = (csbi.wAttributes & 0xF0) + (Forgc & 0x0F);
        // Définir les nouveaux attributs de couleur pour l'affichage
        SetConsoleTextAttribute(hStdOut, WColor);
    }
}

void login()
{	
    int i = 0;
    char given_user[10], given_pass[10]; // Variables pour les entrées utilisateur
    char username[10] = "user", password[10] = "pass"; // Identifiants prédéfinis
    do
    {
        system("cls"); // Efface l'écran
        printf("\n  **************************  LOGIN  **************************  ");
        printf(" \n                       ENTER USERNAME:"); 
        scanf("%s", &given_user); 
		
        printf(" \n                       ENTER PASSWORD:");
        while (i < 10) // Boucle pour la saisie du mot de passe
        {
            given_pass[i] = getch(); // Lit un caractère sans l'afficher
            if (given_pass[i] == 13) break; // Arrête sur "Entrée"
            else printf("*"); // Masque le mot de passe
            i++;
        }
        given_pass[i] = '\0'; // Termine la chaîne de caractères
        i = 0; // Réinitialise le compteur

        // Vérifie si les identifiants correspondent
        if (strcmp(given_user, username) == 0 && strcmp(given_pass, password) == 0)
        {
            printf("  \n\n\n       LOGIN IS SUCCESSFUL");
            break; // Quitte la boucle en cas de succès
        }
        else
        {
            printf("\n        LOGIN IS UNSUCCESSFUL");
            getch(); // Attend une touche avant de réessayer
        }
    }
    while (1); // Boucle infinie pour les tentatives
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

        // Nettoyer le tampon avant fgets
        while (getchar() != '\n');

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

    // Affichage des en-têtes alignés
    printf("%-10s %-20s %-25s %-15s %-15s %-30s %-10s %-15s\n",
           "ROOM", "NAME", "ADDRESS", "PHONE", "NATIONALITY", "EMAIL", "PERIOD", "ARRIVAL DATE");

    for (i = 0; i < 150; i++)  // Ligne séparatrice
        printf("-");

    printf("\n");

    // Lire et afficher chaque enregistrement avec alignement
    while (fread(&s, sizeof(s), 1, f) == 1) {
        printf("%-10s %-20s %-25s %-15s %-15s %-30s %-10s %-15s\n",
               s.roomnumber, s.name, s.address, s.phonenumber,
               s.nationality, s.email, s.period, s.arrivaldate);
    }

    for (i = 0; i < 150; i++)  // Ligne séparatrice
        printf("-");

    printf("\n");

    fclose(f);
    printf("\nPress any key to exit");
    getchar();  // Attend une touche pour quitter
}



void delete()
{
	FILE *f, *t;
	int i = 1; 
	char roomnumber[20]; 

	if ((t = fopen("temp.txt", "w")) == NULL) // Crée un fichier temporaire
		exit(0);
	if ((f = fopen("add.txt", "r")) == NULL) // Ouvre le fichier principal
		exit(0);

	system("cls"); // Efface l'écran
    printf("Enter Room number of the customer to be deleted from the database: \n");
	scanf("%s", roomnumber); // Lit le numéro de chambre
	while (fread(&s, sizeof(s), 1, f) == 1) // Parcourt les enregistrements
	{
		if (strcmp(s.roomnumber, roomnumber) == 0) // Si l'enregistrement correspond
		{      
			i = 0; // Enregistrement trouvé
		}
		else
		{
			fwrite(&s, sizeof(s), 1, t); // Copie les enregistrements restants
		}
	}
	if (i == 1) // Si aucun enregistrement trouvé
	{       
        printf("\n\n Records of Customer are not found");
		getch(); // Attend une touche
		fclose(f);
		fclose(t);
		main(); // Retourne au menu principal
	}
	fclose(f); // Ferme le fichier principal
	fclose(t); // Ferme le fichier temporaire
	remove("add.txt"); // Supprime le fichier principal
	rename("temp.txt", "add.txt"); // Renomme le fichier temporaire en principal
    printf("\n\nThe Customer is successfully removed");
	getch(); // Attend une touche
}

void search()
{
system("cls"); //nettoyage de l'éran
   FILE*f;
   char roomnumber[20]; //variable pour stocker le numéro de chambre
   int flag=1; //variable de controle pour vérifier si le client est trouvé
   f=fopen("add.txt","r+"); //ouvertude du fichier pour lecture et écriture
   if(f==0) //si le fichier ne s'ouvre pas ,quitter le programme
	   exit(0);
   fflush(stdin); //nettoyage du tampon d'entrée standard
   printf("Enter Room number of the customer to search its details : \n");
   scanf("%s", roomnumber); //entrée du numéro de chambre à rechercher
   while(fread(&s,sizeof(s),1,f)==1) //lecture de chaque enregistrement dans le fichier
   {
       if(strcmp(s.roomnumber,roomnumber)==0)// comparaison du numéro de chambre avec celui entré
       {
           flag=0; // le client a été trouvé
           printf("\n\tRecord Found\n");
           printf("\nRoom Number: \t%s",s.roomnumber); //affichage des détals du client
           printf("\nName:\t%s",s.name);
           printf("\nAddress:\t%s",s.address);
           printf("\nPhone number:\t%s",s.phonenumber);
	       printf("\nNationality:\t%s",s.nationality);
           printf("\nEmail:\t%s",s.email);
           printf("\nPeriod:\t%s",s.period);
           printf("\nArrival date:\t%s",s.arrivaldate);
           break;
       }
   }

   if (flag==1)//si aucun client n'a été trouvé 
   {
        printf("\n\tRequested Customer could not be found!");
    
    } 
    getch(); //attente de la pression d'une touche pour continuer
    fclose(f); //fermeture du fichier
}

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

	        printf("\nEnter New Nationality:");
	        fgets(s.nationality,sizeof(s.nationality),stdin);
	        s.nationality[strcspn(s.nationality,"\n")]='\0';

	        printf("Enter New Email:");
	        fgets(s.email,sizeof(s.email),stdin);
	        s.email[strcspn(s.email,"\n")]='\0';

	        printf("Enter New Period:");
	        fgets(s.period,sizeof(s.period),stdin);
	        s.period[strcspn(s.period,"\n")]='\0';

	        printf("Enter New Arrival date:");
	        fgets(s.arrivaldate,sizeof(s.arrivaldate),stdin);
	        s.arrivaldate[strcspn(s.arrivaldate,"\n")]='\0';

            // Sauvegarder les modifications dans le fichier
            fseek(f, -size, SEEK_CUR);  // Revenir au début de l'enregistrement actuel
            fwrite(&s, sizeof(s), 1, f);  // Réécrire les données modifiées
            break;  // Sortir de la boucle après modification
        }
    }

    
// vérifier si l'enregistrement a été trouver ou non

   if(k==1){
	   printf("\n\nTHE RECORD DOESN'T EXIST!!!");
	   fclose(f);  // Fermer le fichier après les modifications
	   getch(); // attendre une entrée utilisateur
   }else {
	   fclose(f);
	   printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
           getch();
	   }
}


// Fonction principale
int main() {
    int i = 0; // Initialisation de la variable i pour les boucles
    char choice; // Variable pour stocker le choix du menu

    // Nettoyer l'écran et afficher l'introduction
    system("cls");
    setcolor(15); // Couleur par défaut (Blanc vif)
    printf(" -------------------------------------------------------------------------\n");
    printf("|                                                                         |\n");
    printf("|                                                                         |\n");
    printf("|  OOOOOO   OOOOOO OOOOOO OOOOOO OOOOOO OOOOOO O      O OOOOOOO  OOOOOO   |\n");
    printf("|  O        O    O O      O        O      O    O O    O O        O        |\n");
    printf("|  O  OOOOO OOOOOO OOOOO  OOOOO    O      O    O  O   O O  OOOOO OOOOOO   |\n");
    printf("|  O    O   O  O   O      O        O      O    O   O  O O    O        O   |\n");
    printf("|  OOOOOO   O   O  OOOOOO OOOOOO   O    OOOOOO O    O O OOOOOO   OOOOOO   |\n");
    printf("|                                                                         |\n");
    printf(" -------------------------------------------------------------------------\n");
    printf("\t\t*************************************************\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*       -----------------------------           *\n");
    printf("\t\t*            WELCOME TO HOTEL X                 *\n");
    printf("\t\t*       -----------------------------           *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*************************************************\n\n\n");
    printf("\n Press any key to continue:");
    getch();

    system("cls");
    login();  // Appel de la fonction de connexion
    system("cls");

    // Boucle principale
    while (1) {
        system("cls");
        setcolor(10); // Vert pour le menu principal
        for (i = 0; i < 80; i++) printf("-");
        printf("\n   ******************************  |MAIN MENU|  ***************************** \n");
        for (i = 0; i < 80; i++) printf("-");

        printf("\n");
        printf("\t\t  enter your choice for menu:\n");
        printf(" \n Enter 1 -> Book a room");
        printf("\n------------------------");
        printf(" \n Enter 2 -> View Customer Record");
        printf("\n----------------------------------");
        printf(" \n Enter 3 -> Delete Customer Record");
        printf("\n-----------------------------------");
        printf(" \n Enter 4 -> Search Customer Record");
        printf("\n-----------------------------------");
        printf(" \n Enter 5 -> Edit Record");
        printf("\n-----------------------");
        printf(" \n Enter 6 -> Exit");
        printf("\n-----------------");
        printf("\n");

        // Lecture du choix utilisateur
        choice = getche();
        choice = toupper(choice); // Convertir en majuscule

        switch (choice) {
            case '1':
                setcolor(14); // Jaune pour ajouter une réservation
                add();
                break;
            case '2':
                setcolor(11); // Cyan pour afficher les clients
                list();
                break;
            case '3':
                setcolor(12); // Rouge pour la suppression
                delete();
                break;
            case '4':
                setcolor(13); // Magenta pour la recherche
                search();
                break;
            case '5':
                setcolor(9); // Bleu pour la modification
                edit();
                break;
            case '6':
                setcolor(12); // Rouge pour le message de sortie
                system("cls");
                printf("\n\n\t *****THANK YOU*****");
                printf("\n\t FOR TRUSTING OUR SERVICE");
                exit(0);
            default:
                setcolor(14); // Jaune pour les erreurs
                system("cls");
                printf("Incorrect Input");
                printf("\n Press any key to continue");
                getch();
        }
    }
}
