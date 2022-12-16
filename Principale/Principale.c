#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>


// WARNING !  ce code lit les fichier json qui ne depass pas TAILLE_MAX caractere que vous pouvez bien sur modifier ici

#define TAILLE_MAX 1000000 // CARACTERE A LIRE DU FICHIER 100000
#define OBJET_MAX 10000  // le nombre maximale d objet situer dans le fichier json
#define CHAMPS_MAX 2000  // c est la taille maximale d une chaine represenatnt un objet json
#define ITEM_MAX 1000   // chaque item de chaque champs peut pas depaser 100 caractere 
#define distance_min 5 // la distance maximal accepter  entre deux chaine

//=======================================================================================================================
char** lire (char file_name[]){
	FILE* fichier = NULL;
    fichier = fopen(file_name, "r");
    int caractereActuel = 0;
    char* chaine=(char*)malloc(TAILLE_MAX);
    int i=0;
//----------------------------copier le contenue dans un tableau CHAINE---------------------------------//
	 if (fichier != NULL)
    {
        do {
        caractereActuel = fgetc(fichier); // On lit le caractère
        chaine[i]=caractereActuel;
        i++;
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
       
        fclose(fichier); // On ferme le fichier qui a été ouvert
    }
    else{
    	printf("%s","\nle fichier n\'est pas lu\n");
	}

//------------------------------mettre les objets dans une chaine des objet----------------------------//
int w=0;
char **liste_objets = calloc(OBJET_MAX, sizeof(char*));
   char  *token = strtok(chaine,"{"); 
	   	while( token != NULL  && w<OBJET_MAX ) 
		   {
	   		liste_objets[w] = (char*) malloc(CHAMPS_MAX);
	      	strcat(liste_objets[w],token);
	      	w++;
	      	token = strtok(NULL,"{");
	       }
return liste_objets;
}

//=======================================================================================================================
int levenshtein(char s[], char t[])
{
		int ls = strlen(s);
		int lt = strlen(t);
		int d[ls+1][lt+1];
		int i ,j;
		for (i= 0; i <= ls; i++){
			for (j=0; j <= lt; j++) {
			d[i][j] = -1;
			}
		} 
		//======================
		int dist(int i, int j) {
			if(d[i][j]>=0){
				return d[i][j];
			}
		//======================	
			int x;
			if (i == ls)
			x = lt - j;
			else if (j == lt)
			x = ls - i;
			else if (s[i] == t[j])
			x = dist(i + 1, j + 1);
			else {
				x=dist(i+1,j+1);
				int y;
				if ((y = dist(i, j + 1)) < x) 
				       x = y;
				if ((y = dist(i + 1, j)) < x) 
				       x = y;
				x++;
			}
		//=======================	
			return d[i][j] = x;
		}
return dist(0, 0);
}

//=======================================================================================================================
int comparaison(char s[], char t[])
{
	int dis=levenshtein(s,t);
	int test;
	test=(dis<=distance_min);
	if(test==1)
			return 1;
	return 0;	
}

//=======================================================================================================================
int NombreObjet(char file_name[]){
	char caractereActuel; 
	int i=0;
	FILE* fichier = fopen(file_name, "r");
     if (fichier != NULL)
    {
        do {
        caractereActuel = fgetc(fichier); 
            if(caractereActuel == '{')  
			        i++;
        } while (caractereActuel != EOF); 
        fclose(fichier);
    }
     return i;
}

//=======================================================================================================================
struct Personne 
{
	char nom[ITEM_MAX];
  	char prenom[ITEM_MAX];
  	char adresse_email[ITEM_MAX];
  	char ville[ITEM_MAX];
  	char pays[ITEM_MAX];
}Personne;

//=======================================================================================================================
char* f( char* s){
	int i;
	char* t;
	for(i=0; i<strlen(s)-1; i++) t[i]=s[i];
	return t;
}

//=======================================================================================================================
struct Personne initPersonne( char json_objet[]){
 		struct Personne A;
 		char S[5][100]; 
   	    int i=0;
		char * token = strtok(json_objet, ",");
	   	// loop through the string to extract all other tokens
	   	while( token != NULL ) {
	      strcpy(S[i],token);
	      i++;
	      token = strtok(NULL, ",");
	   }
 		char * token1 = strtok(S[0], ":");
 		token1 = strtok(NULL, ":");
 		char * token2 = strtok(S[1], ":");
 		token2 = strtok(NULL, ":");
 		char * token3 = strtok(S[2], ":");
 		token3 = strtok(NULL, ":");
 		char * token4 = strtok(S[3], ":");
 		token4 = strtok(NULL, ":");
 		char * token5 = strtok(S[4], ":");
 		token5 = strtok(NULL, ":"); 			
 		
	 	strcpy(A.nom,token1);
		strcpy(A.prenom,token2);
		strcpy(A.adresse_email,token3);
		strcpy(A.ville,token4);
		strcpy(A.pays,f(token5));
		return A;
}

//=======================================================================================================================
long taille(char *adress){
	FILE* fichier=NULL;
	long taille;
	fichier=fopen(adress,"rb");
	if(fichier){
		fseek(fichier,0,SEEK_END);
		taille=ftell(fichier);
		fclose(fichier);
	}
	return taille;
}

//=======================================================================================================================
void lower_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

//=======================================================================================================================
void research_function(int NbrObj, char** OurList, char nom[], char prenom[], char ville[], char pays[]){
int k;
struct Personne A;
struct Personne B;
int test=0;
for(k=1;k<(NbrObj+1);k++){
	A=initPersonne(OurList[k]);
	//-----------------------------
	B=A;
	lower_string(B.nom); lower_string(B.prenom); lower_string(B.ville); lower_string(B.pays); 
	//-----------------------------
	if( comparaison(B.nom,nom) || comparaison(B.prenom,prenom)  || comparaison(B.ville,ville) || comparaison(B.pays,pays)){
		printf("-----------ID: %d-------------\n", k);
		printf("%s\n",A.nom);
		printf("%s\n",A.prenom);
		printf("%s\n",A.adresse_email);
		printf("%s\n",A.ville);
		printf("%s\n",A.pays);

		test = 1;
	}
}
if(test==0)               
          { printf("\nIl n'y a aucune personne avec ces coordonnees\n"); }
      }
      
//=======================================================================================================================
void afficher_panneau()
{
	puts("\n");
	printf("-------------------------------------------------------------------------------------------------------\n");
    printf("****************************************|      BIENVENUE      |****************************************\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    puts("\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("                                    |     PROJET ALGORITHMIQUE     |                \n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    puts("\n");
    printf("===============================^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^===============================  \n ");
    printf("                   |         ALGORITHME DE RECHERCHE DANS UN FICHIER JSON          |        \n");
    printf("=======================================================================================================\n\n");
    printf("                               }---------{+}    Coded By    {+}---------{          \n");
    printf("                           }------------{+}   YASSER SOKRI   {+}-------------{      \n");
    printf("                           }------------{+} ABDELLAH OUBADOU {+}-------------{      \n\n");

}
//=======================================================================================================================
void PageDonnees()
{
     printf("%s","\n\n----------------------------------------------------------------------------------------------------------------\n");
     printf("%s","-----------------**********************|  RECHERCHE DANS LA BASE JSON : |**********************-----------------\n");
     printf("%s","----------------------------------------------------------------------------------------------------------------\n");
     puts("\n\n\n");
}
//=======================================================================================================================
void time_date(void){
		printf("\nLa date du jour : %s",__DATE__);
		printf("\nL'heure d'ouverture : %s\n",__TIME__);
}


/*------------------------------------------------fonction main--------------------------------------------------------*/
      
//=======================================================================================================================
int main(){
   system("color 0C"); time_date(); afficher_panneau();
   printf("\n\n\n- MERCI D\'APPUYER SUR UNE TOUCHE QUELCONQUE POUR COMMENCER (^_^) ....\n"); getch(); system("cls");time_date();
   
//=====================================Mapping- On import le fichier json dans une chaine================================

//La demande du nom du fichier JSON qu'on va lutiliser pour la recherche=================================================
    char file_name[30];
    printf("\n\nENTRER LE NOM DE LA BASE JSON (Exemple: name.json!) \t");
	scanf("%s", file_name);	
	printf("%s", file_name );
	
//Le calcul de la taille de notre fichier JSON===========================================================================
	long Size=taille(file_name);
	
//On met nos objet JSON dans une liste===================================================================================	
	char** NosObjets=lire(file_name);
	
// Le calcul de nombre des objets du fichier JSON=========================================================================
	int nombre_objet= NombreObjet(file_name);

// Demande des données à l'utilisateur====================================================================================
system("cls"); time_date();  system("color 5B"); printf("-Le nombre d 'objets dans cette base JSON est : %d \n ",nombre_objet); PageDonnees();
char nom[ITEM_MAX],prenom[ITEM_MAX],ville[ITEM_MAX],pays[ITEM_MAX];
printf("\t- SVP! ENTRER LES DONNEES QUE VOUS CONNAISEZ CONCERNANT LA PERSONNE : \n\n");
printf("%s","- NOM :\t");
scanf("%s",nom);
lower_string(nom);
printf("%s","- PRENOM :\t");
scanf("%s",prenom);
lower_string(prenom);
printf("%s","- VILLE :\t");
scanf("%s",ville);
lower_string(ville);
printf("%s","- PAYS :\t");
scanf("%s",pays);
lower_string(pays);
printf("--> RECHERCHER <--\t");
getch();

//=======================================================================================================================
    system("cls");time_date();system("color 3f"); printf("\n");

//=======================================================================================================================
    long clk_tck = CLOCKS_PER_SEC;
    clock_t  Time, t1, t2;
    srand(time(NULL));
    t1 = clock();
    
// La recherche des donnees des personnes correspondent aux informations entre===========================================
    research_function(nombre_objet, NosObjets, nom, prenom, ville, pays);
    
//=======================================================================================================================
	t2 = clock();
	Time=t2-t1;
	
//=======================================================================================================================
    printf("\n\t + LE TEMPS DE RECHERCHE EST (ms) : %lf  \n\t + LA TAILLE DU FICHIER JSON (byte):  %ld \n",((double)(t2-t1)/(double)clk_tck)*1000,Size);

//=======================================================================================================================
    puts("\n\n\n");
    puts("--> CLIQUER POUR FERMER LE PROGRAMME <--");

//=======================================================================================================================
    getch();
    system("cls");
    printf("\n\n\a Vous avez fermer le programme avec succes\n\n");
    system("exit");
	
}


