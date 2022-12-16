#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>


// WARNING !  ce code lit les fichier json qui ne depass pas TAILLE_MAX caractere que vous pouvez bien sur modifier ici
#define TAILLE_MAX 100000 // CARACTERE A LIRE DU FICHIER 1000

#define OBJET_MAX 400   // le nombre maximale d objet situer dans le fichier json
#define CHAMPS_MAX 1000  // c est la taille maximale d une chaine represenatnt un objet json
#define ITEM_MAX 100   // chaque item de chqua champs peut pas depaser 100 caractere 

#define distance_min 5 // la distance maximal accepter  entre deux chaine



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
		int dist(int i, int j) {
			if(d[i][j]>=0){
				return d[i][j];
			}
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
				if ((y = dist(i, j + 1)) < x) x = y;
				if ((y = dist(i + 1, j)) < x) x = y;
				x++;
			}
			return d[i][j] = x;
		}
return dist(0, 0);
}


int comparaison(char s[], char t[]){
	int dis=levenshtein(s,t);
	int test;
	test =(dis<=distance_min);
	if(test==1){
		return 1;
	}
	
	return 0;	
}




struct Personne {
	char nom[ITEM_MAX];
  	char prenom[ITEM_MAX];
  	char adresse_email[ITEM_MAX];
  	char ville[ITEM_MAX];
  	char pays[ITEM_MAX];
}Personne;

char* f( char* s){
	int i;
	char* t;
	for(i=0; i<strlen(s)-1; i++) t[i]=s[i];
	return t;
}

struct Personne initPersonne( char json_objet[]){

 		struct Personne A;
 		
 		char S[5][100]; 
   
   	   int i=0;
		char * token = strtok(json_objet, ",");
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



int main(){
	
//mapping 	
// on import le fichier json dans une chaine	
	FILE* fichier = NULL;
	long Size=taille("fichiertest9.json");
    fichier = fopen("fichiertest9.json", "r");
    int caractereActuel = 0;
    char chaine[TAILLE_MAX] = ""; // Cha�ne vide de taille TAILLE_MAX
    int i=0;
	 if (fichier != NULL)
    {
        do {
        caractereActuel = fgetc(fichier); // On lit le caract�re
        chaine[i]=caractereActuel;
        i++;
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourn� EOF (fin de fichier)
       
        fclose(fichier); // On ferme le fichier qui a �t� ouvert
    }
    else{
    	printf("%s","le fichier n est pas lu");
	}


int w=0;
char *liste_objets[OBJET_MAX]; 
char  *token = strtok(chaine,"{"); 
	   	while( token != NULL  && w<OBJET_MAX ) {
	   		liste_objets[w] = (char *) malloc(CHAMPS_MAX);
	      	strcat(liste_objets[w],token);
	      	w++;
	      	token = strtok(NULL,"{");
	   }
int nombre_objet = w;

struct Personne A;
int k;

// Recherche
printf("%s"," \n - - - - -  Recherche dans la base JSON    - - - - - \n");
char nom[ITEM_MAX],prenom[ITEM_MAX],ville[ITEM_MAX],pays[ITEM_MAX];
printf("%s","Nom :");
scanf("%s",nom);
printf("%s","Prenom :");
scanf("%s",prenom);
printf("%s","Ville :");
scanf("%s",ville);
printf("%s","Pays :");
scanf("%s",pays);


long clk_tck = CLOCKS_PER_SEC;
clock_t  Time,t1, t2;
t1 = clock();

for(k=1;k<nombre_objet;k++){
	A=initPersonne(liste_objets[k]);
	if( comparaison(A.nom,nom) || comparaison(A.prenom,prenom)  || comparaison(A.ville,ville) || comparaison(A.pays,pays)){
		printf("%s","\n--------*******-------\n");
		printf("%s\n",A.nom);
		printf("%s\n",A.prenom);
		printf("%s\n",A.adresse_email);
		printf("%s\n",A.ville);
		printf("%s\n",A.pays);
		printf("%s","\n");

	}
}

	t2 = clock();
	Time=t2-t1;

printf(" \n Temps consomme  dans la recherche (s) : %lf  \n  La taille du fichier json (byte):  %ld \n",1000*(double)(t2-t1)/(double)clk_tck,Size);

}


