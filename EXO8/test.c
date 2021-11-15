#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debug(...) 42
#endif


#define BUFFER_SIZE 18 

typedef struct compte_ccp {
   char num[12]; // numero du compte CCP (12 bytes)
   int solde; // solde du compte CCP (4 bytes)
   // taille de compte_CCP : 16 bytes
} compte_ccp;


int main () {
	printf("Entrer le nom du fichier : ");
	char fichier[20];
	scanf("%s", fichier);
	printf("La liste des options disponibles :\n");
	printf("    1) Ecrire le fichier\n");
	printf("    2) Lire le fichier\n");
	printf("Entrer une option : ");

	int option;
	scanf("%i", &option);
	switch(option) {
		case 1: {
			FILE *file = fopen(fichier, "wb");
			if (file == NULL) {
				perror("Impossible d'ouvrir ce fichier\n");
				exit(0);
			}
			compte_ccp compte;
			memset(&compte, 0, sizeof(compte));
			int n;
			printf("Entrer le nombre de comptes : ");
			scanf("%d", &n);
			for (int i = 0; i < n; i++) {
				printf("Le compte : %d\n", i + 1);
				printf("Le numero de compte : ");
				int num;
				scanf("%d", &num);
				sprintf(compte.num, "%010d", num);
				printf("Le solde du compte : ");
				scanf("%d", &compte.solde);
				debug("%d", compte.solde);
				printf("*********************\n");
				fwrite(&compte, sizeof(compte_ccp), 1, file);
			}
			fclose(file);
			break;
		}
		case 2: {
		   FILE *file = fopen(fichier, "rb");
         if (file == NULL) {
            perror("Impossible d'ouvrir ce fichier\n");
            exit(0);
         }
         compte_ccp compte;
         int i = 1;
         char ch = '0';
         while (ch != EOF) {  // afficher le contenu du fichier
 			 	fread(&compte, sizeof(compte_ccp), 1, file);
			   printf("Le compte : %d\n", i++);
				printf("Le numero de compte: %s \n", compte.num);
   	      printf("Le solde du compte:  %d \n",  compte.solde);
            printf("#******************************#\n");
				ch = fgetc(file);
            fseek(file, (i - 1) * sizeof(compte) , SEEK_SET);
			}
			fclose(file);
			break;
		}
	}
	return 0;
}
