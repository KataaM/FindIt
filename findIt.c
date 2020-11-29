// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
//#include "findIt.h"
#include <regex.h>
#define BIG 20

typedef enum {false, true} bool;

typedef struct
{
	char pseudo[BIG];
	char nom[BIG];
	char prenom[BIG];
	char jeu[BIG];
	char rank[BIG];
	char email[BIG];
	char password[BIG];
	char kda[BIG];
	bool isAdmin;
	int honneur;
}User;


typedef struct
{
	char emetteur[BIG];
	char destinataire[BIG];
	char obnjet[BIG];
	char message[BIG];
}Mail;

/*
* Lance findIt et permet à l'utilisateur de choisir entre trois possibiliés (login,register,quitter)
*/
User lancerFindIt(FILE *findItDb);

/*
* Permet de savoir en regardant dans la base de donneé si l'utilisateur existe ou non.
*/
void checkUserExist();

/*
* Permet d'afficher toutes les possibilités d'actions pour un utilisateur lambda
*/
Mail menuUser(int choix);

/*
* Permet à l'utilisateur de se login (Vérifiera si le login existe et si le mdp correspond au login).
*/
User login(FILE *findItDb);


/*
* Permet à l'utilisateur de s'enregistrer (Vérifiera si l'utilisateur n'existe pas déjà et si les informations sont correctes)
*/
User registerr(FILE *findItDb);

/*
* Permet d'afficher toutes les possibilités d'actions pour un administrateur
*/
void menuAdmin(FILE *findItDb);

/* Cette fonction permet à l'utilisateur d'écrire un "mail" de recherche de groupe
* En fonction du mail on traitera l'objet / le message pour voir s'il y a des correspondances avec notre base de donnée
* Si l'utilisateur ne possède pas de groupe on lui proposera une multitude de choix de groupe
* S'il en possède un alors on lui demande d'abord de le quitter avec la méthode quitterGroupe ou alors on le fera avec un oui/non.
*/
void findGroup(FILE *findItDb);

/* Permet de connaître le niveau d'honneur du joueur qui le demande
*   
* => Lire base de donnée en fonction du pseudo pour savoir le niveau d'honneur
*
*/
void showHonnorLevel(FILE *findItDb, int *honneur);

/*  Permet de report un joueur (pseudo nécessaire dans le message)
*
*   Si on repère plusieurs joueurs dans le message/objet alors on les reports tous.
*   => Lire BDD => Honneur -1 sur le pseudo lu dans le message
*/
void reportPlayer(FILE *findItDb, int *honneur);

/*  Permet d'effectuer une recommandation d'un joueur (pseudo nécessaire dans le message)
*
*   Si on repère plusieurs joueurs dans le message/objet  alors on les recommandes tous.
*   => Lire BDD => Honneur +1 sur le(s) pseudo(s) lu dans le message
*/
void recommandPlayer(FILE *findItD, int *honneur);

/* Permet d'afficher les statistiques d'un joueurs (K/D/A) sur un jeu donner en paramètre
*
*
* Lire dans la base de donnée en fonction du jeu donner en paramètre les statistiques qui sont associé au joueur
*
*/ 
void showStats(FILE *findItDb, char *kda);


/* Montre tous les choix possible pour l'utilisateur
*
*
*
*/ 
void aideUser();

/* 
*   Montre tous les choix possible pour l'administrateur
*/ 
void aideAdmin();


/*
* Créer un utilisateur dans la base de donnée
*/
void createAccount();

/*
* Permet de lister tout les utilisateurs de la base de donnée
*/
void listAllUsers(FILE *findItDb);

/*
* Permet de rechercher un utilisateur dans la base de donnée et d'afficher toutes ses informations
*/
void searchUser(FILE *findItDb);

/*
* Permet de rechercher et supprimer un utilisateur dans la base de donnée lorsque l'on fournit son Pseudo
*/
void deleteUser(FILE *findItDb);

/*
* Permet d'ajouter un mot clé ainsi que sa réponse associée dans la base de donnée
*/
void addKeyword();

/*
* Permet de rechercher un mot clé dans la base de donnée et d'afficher sa réponse associée
*/
void searchKeyWord();

/*
* Permet de supprimer un mot clé dans la base de donnée
*/
void deleteKeyWord();

/*
* Permet de lister tout mots clés ainsi que leur réponse associée
*/
void listAllKeyWords();

Mail readMail(FILE *findItDb,Mail mail,int isAdmin);

Mail userWriteMail();

Mail adminWriteMail();


//Printf un utilisateur
void printUser(User user);

int main() {
    
    printf("------Starting findIt program------- \n");
    
    FILE *findItDb;
    
    findItDb = fopen("findItDb.txt", "a");
    fclose(findItDb);
    
    findItDb = fopen("findItDb.txt", "r+");
    
    //Lancement du register/login
    User userLoggedIn;
    userLoggedIn = lancerFindIt(findItDb);
   
   
	
    //Mail mailToRead;
    
    
    if (userLoggedIn.isAdmin){
        printf(" \n \n L'utilisateur est un administrateur. \n \n ");
        //Si l'utilisateur est administrateur..
        
        menuAdmin(findItDb);
    } else {
        //Si l'utilisateur est "lambda".
        //Lui faire écrire un mail
        //mailToRead = userWriteMail();
    }
    
    //readMail();
    
    
    //DisplayMail();
    //Faire une boucle pour redemmander à l'utilisateur de saisir un mail
    
    return 0;
}


User lancerFindIt(FILE *findItDb){
    int choix;
    
    User joueur;
    
    
    //Choix entre register et login puis appel des fonctions en fonction du choix
    
    
	printf("----- LancerFindIt() -----\n(1) Se connecter ?\n(2)S'inscrire ?\n (3) Quitter ? \n");
	scanf("%d", &choix);

	while( (choix < 1) && (choix > 4) ){

		printf("----- LancerFindIt() -----\n(1) Se connecter ?\n(2)S'inscrire ?\n (3) Quitter ? \n");
		scanf("%d", &choix);
	}
   
	do {
		switch(choix){
				case 1 : 
						joueur = login(findItDb); //on rentre dans la fonction de connexion
						return joueur;
						break;
				case 2 : 
						joueur = registerr(findItDb); //on rentre dans la fonction d'inscription
						return joueur;
						break;
				case 3 :
						return joueur;
						break;
				default : 
						printf("\nMauvais choix petit hackeur, recommence.");
						break;
		}
		
		printf(" \n \n \n Retour au menu principal \n ... \n ----- LancerFindIt() -----\n(1) Se connecter ?\n(2)S'inscrire ?\n (3) Afficher tous les utilisateurs ? \n  (4) Quitter ? \n");
		scanf("%d", &choix);
		
    } while (choix != 3);
    return joueur;
}

User login(FILE *findItDb)
{
    User joueur;
    bool cherche = true;
    bool continuee = true;
    char userName[BIG];
    char password[BIG];
    findItDb = fopen("findItDb.txt", "r");
   
    //mdp OU pseudo est incorrect OU mdp ET pseudo incorrect)
    while(continuee)
    {
        printf(" \nNom d'utilisateur : ");
        scanf("%s",userName);
        printf(" \nmot de passe : ");
		scanf("%s",password);
        
        while(cherche)
        {
            fread(&joueur, sizeof(User), 1, findItDb);
    		
    		if(strcmp(userName, joueur.pseudo) == 0)
    		{
    			if(strcmp(password, joueur.password) == 0)
    			{
    			    cherche = false;
    			    continuee =false;
    			}
    		}
    		else if(fread(&joueur, sizeof(User), 1, findItDb) == 0)
    		{
    			printf("L'utilisateur recherché n'existe pas, ressayer\n\n");
    			cherche = false;
    		}
    		
        }
    }
    return joueur;
}


User registerr(FILE *findItDb)
{
	

	User user;
	
	//TODO Vérification à effectuer pour tout les trucs
	
	printf("Veuillez entrez votre pseudo : ");
	scanf("%s",user.pseudo);
	printf("Veuillez entrez votre mot de passe : ");
	scanf("%s",user.password);
	printf("Veuillez entrez votre prénom : ");
	scanf("%s",user.prenom);
	printf("Veuillez entrez votre nom : ");
	scanf("%s",user.nom);
	printf("Veuillez entrez votre jeu préféré : ");
	scanf("%s",user.jeu);
	printf("Veuillez entrez votre rang actuel sur ce jeu : ");
	scanf("%s",user.rank);
	printf("Veuillez entrez votre kda sur ce jeu : ");
	scanf("%s",user.kda);
	printf("Veuillez entrez votre email : ");
	scanf("%s",user.email);
	
	int intIsAdmin;
	printf("Êtes-vous un administrateur ? (1) or (0) ");
	scanf("%d",&intIsAdmin);
	
	
	if (intIsAdmin == 1) {
		user.isAdmin = true;
	}else {
		user.isAdmin = false;
	}
	
	//Par défaut
	
	user.honneur = 0;

	fseek(findItDb, 0, SEEK_END);
	
	
	fwrite(&user, sizeof(User), 1, findItDb);
    
    return user;
}

/*

void findGroup(FILE *findItDb){
    
    //TODO mais la plus compliquer je pense.
}

void showHonnorLevel(FILE *findItDb, int *honneur){
    User joueur;
	bool continuee = true;
	
	fseek(findItDb, 0, SEEK_SET);
	while(continuee)
	{
		fread(&joueur, sizeof(User), 1, findItDb);
		
		if(strcmp(pseudo, joueur.pseudo) == 0)
		{
			printf("Le niveau d'honneur de %s est de %d\n",joueur.pseudo, joueur.honneur);
		}
		else if(fread(&joueur, sizeof(User), 1, findItDb) == 0)
		{
			printf("L'utilisateur recherché n'existe pas, retour au menu\n\n");
			continuee = false;
		}
	}
}

void reportPlayer(FILE *findItDb, int *honneur){
    User joueur;
	bool continuee = true;
	fseek(findItDb, 0, SEEK_SET);
	while(continuee)
	{
		fread(&joueur, sizeof(User), 1, findItDb);
		
		if(strcmp(pseudo, joueur.pseudo) == 0)
		{
			int new_honor_level = joueur.honneur - 1;
			fseek(findItDb, - sizeof(User), SEEK_CUR);
			joueur.honneur = new_honor_level;
			fwrite(&joueur, sizeof(User), 1, findItDb);
		}
		else if(fread(&joueur, sizeof(User), 1, findItDb) == 0)
		{
			printf("L'utilisateur recherché n'existe pas, retour au menu\n\n");
			continuee = false;
		}
	}
}

void recommandPlayer(FILE *findItD, int *honneur){
    User joueur;
    bool continuee = true;
	fseek(findItDb, 0, SEEK_SET);
	while(continuee)
	{
		fread(&joueur, sizeof(User), 1, findItDb);
		
		if(strcmp(pseudo, joueur.pseudo) == 0)
		{
			int new_honor_level = joueur.honneur + 1;
			fseek(findItDb, - sizeof(User), SEEK_CUR);
			joueur.honneur = new_honor_level;
			fwrite(&joueur, sizeof(User), 1, findItDb);
		}
		else if(fread(&joueur, sizeof(User), 1, findItDb) == 0)
		{
			printf("L'utilisateur recherché n'existe pas, retour au menu\n\n");
			continuee = false;
		}
	}
}

void showStats(FILE *findItDb, char *kda){
    User joueur;
	bool continuee = true;
	
	fseek(findItDb, 0, SEEK_SET);
	while(continuee)
	{
		fread(&joueur, sizeof(User), 1, findItDb);
		
		if(strcmp(pseudo, joueur.pseudo) == 0)
		{
			printf("Les statistiques de %s sont %s\n",joueur.pseudo, joueur.kda);
		}
		else if(fread(&joueur, sizeof(User), 1, findItDb) == 0)
		{
			printf("L'utilisateur recherché n'existe pas, retour au menu\n\n");
			continuee = false;
		}
	}
}


Mail userWriteMail(){
    
    //Cette fonction permettra à l'utilisateur de saisir un mail avec DESTINATAIRE/OBJET/MESSAGE
    return NULL;
}

Mail adminWriteMail(){
    
    //Cette fonction permettra à l'administrateur de saisir un mail avec DESTINATAIRE/OBJET/MESSAGE
    return NULL.=;
}

Mail readMail(FILE *findItDb,Mail mail,int isAdmin){
    
    
    
    //TODO 
    // Lire dans le mail envoyer et repérer les éventuels mot clés
    // déteminer le "choix = 1/2/3/4/5..."
    int choix = 0
    Mail mailToReturn;
    if (isAdmin == 0){
        
        mailToReturn = menuUser(choix);
    } else {
        
        mailToReturn = menuAdmin(choix);
    }
    return mailToReturn;
    
}

Mail menuUser(int choix){
    //printf("Commandes : \n Trouver un groupe (1)\n Voir le niveau d'honneur d'un utilisateur (2)\n Signaler un utilisateur (3)\n Recommander un utilisateur (4)\n Voir les statistiques d'un utilisateur (5)\n Sortir (6)\n");
    
    
    Mail mailToReturn;
    bool continuee = true;
    
    do{
        switch(choix)
        case 1 : findGroup();
                break;
        case 2 : showHonnorLevel();
                break;
        case 3 : reportPlayer();
                break;
        case 4 : recommandPlayer();
                break;
        case 5 : showStats();
                break;
        case 6 : continuee = false;
                break;
        default : printf("Cette commande n'existe pas ! Veuillez réessayer.");
    }while(continuee);
    
    
    return mailToReturn;
}
*/

void menuAdmin(FILE *findItDb){
    
    
    int choix;
  
    
    
    
    
    bool continuee = true;
    
    do{
		
		printf(" \n \n Commandes : \n Créer un compte (1)\n Lister tout les utilisateurs (2)\n Rechercher un utilisateur (3)\n Supprimer un utilisateur (4)\n Ajout d'un mot clé et sa réponse associée (5)\n Lister les mots clés et leurs réponses associées (6)\n Rechercher un mot clé (connaître sa réponse) (7) \n Supression d'un mot clé et de sa réponse associée (8) \n Sortir (9)\n \n");
		scanf("%d", &choix);

		while( (choix < 1) && (choix > 9) ){

			printf(" \n \n Commandes : \n Créer un compte (1)\n Lister tout les utilisateurs (2)\n Rechercher un utilisateur (3)\n Supprimer un utilisateur (4)\n Ajout d'un mot clé et sa réponse associée (5)\n Lister les mots clés et leurs réponses associées (6)\n Rechercher un mot clé (connaître sa réponse) (7) \n Supression d'un mot clé et de sa réponse associée (8) \n Sortir (9)\n \n");
			scanf("%d", &choix);
		}
		
        switch(choix) {
			case 1 : //createAccount();
					break;
			case 2 : listAllUsers(findItDb);
					break;
			case 3 : searchUser(findItDb);
					break;
			case 4 : deleteUser(findItDb);
					break;
			case 5 : //addKeyword();
					break;
			case 6 : //listAllKeyWords();
					break;
			case 7 : //searchKeyWord();
					break;
			case 8 : //deleteKeyWord();
					break;
			case 9 : continuee = false;
					break;
			default : printf(" \n\n Faut se laver les yeux... Réessaye ! \n \n ");
		}
    }while(continuee);
    
}

//void createAccount();



void listAllUsers(FILE *findItDb) {

	User user;
	
	printf("---listAllUsers() --- Affichage de tous les utilisateurs --- \n");
	
	fseek(findItDb, 0, SEEK_SET);
	
	while(fread(&user, sizeof(User), 1, findItDb) != 0)
	{
		printUser(user);
	}
}

void printUser(User user) {
	
	printf("\n Pseudo : %s ", user.pseudo);
	printf("\n Nom : %s ", user.nom);
	printf("\n Prénom : %s ", user.prenom);
	printf("\n Password : %s ", user.password);
	printf("\n Jeu : %s ", user.jeu);
	printf("\n Rang : %s ", user.rank);
	printf("\n Kda : %s ", user.kda);
	printf("\n Email : %s ", user.email);
	printf("\n Honneur :  %d ", user.honneur);
	printf("\n Administrateur :  %d \n", user.isAdmin);
}

void searchUser(FILE *findItDb){
	User joueur;
	bool continuee = true;
	char pseudo[BIG];
	
	printf("\n Veuillez entrez le pseudo du joueur que vous voulez rechercher : ");
	scanf("%s",pseudo);
	
	fseek(findItDb, 0, SEEK_SET);
	
	while(continuee)
	{
		fread(&joueur, sizeof(User), 1, findItDb);
		
		if(strcmp(pseudo, joueur.pseudo) == 0)
		{
			//Print l'utilisateur;
			printUser(joueur);
			continuee = false;
		}
		else if(fread(&joueur, sizeof(User), 1, findItDb) == 0)
		{
			printf(" \n L'utilisateur recherché n'existe pas, retour au menu. \n\n");
			continuee = false;
		}
	}
}

void deleteUser(FILE *findItDb) {
	
	//TODO DELETE USERMHMH
	//C'est de la merde
	// Soit on rajoute une variable isDeleted à chaque utilisateur et on met 1
	// et du coup on vérifie quand on print que isDeleted = 0
	// Soit on supprime le fichier et on réecrit le fichier en supprimant l'utilisateur ( je pense que c'est plus propre ;) ) 
	
	
	/*
	User joueur;
	char vide[1] = "";
	bool continuee = true;
	char pseudo[BIG];
	
	printf("\n Veuillez entrez le pseudo du joueur que vous voulez supprimer : ");
	scanf("%s",pseudo);
	
	fseek(findItDb, 0, SEEK_SET);
	
	while(continuee)
	{
		fread(&joueur, sizeof(User), 1, findItDb);
		
		if(strcmp(pseudo, joueur.pseudo) == 0)
		{
			//Print l'utilisateur;
			//TODO DELETE USER
			
			
			fseek(findItDb, - sizeof(User), SEEK_CUR);
			fwrite(&vide,sizeof(User), 1, findItDb);
			
			continuee = false;
		}
		else if(fread(&joueur, sizeof(User), 1, findItDb) == 0)
		{
			printf(" \n L'utilisateur que vous voulez supprimer n'existe pas, retour au menu. \n\n");
			continuee = false;
		}
	}
	*/
}
	
