#include <stdio.h>
#include <stdlib.h>

int main () {
	printf("Choisissez une option : \n");
	printf("  1) Concatener dans un seul fichier\n");
	printf("  2) Concatener dans un troisieme fichier\n");
	int option;
	scanf("%d", &option);
	switch(option) {
		case 1: {
			char fichier1[20], fichier2[20], fichier3[20];
			printf("Entrer le nom du premier fichier : ");
			scanf("%s", fichier1);
			printf("Entrer le nom du deuxieme fichier : ");
			scanf("%s", fichier2);
			FILE *file1 = fopen(fichier1, "a");	// ouverture du premier fichier
			FILE *file2 = fopen(fichier2, "r");	// ouverture du deuxieme fichier
			
			if (file1 == NULL || file2 == NULL) {
				printf("Impossible d'ouvrir les fichiers\n");
				exit(0);
			}
			printf("Traitement du fichier en cours ... \n");
			char c;
			while ((c = fgetc(file2)) != EOF) {
				fputc(c, file1);
			}
			printf("Les deux fichiers sont fusiones dans le premier fichier\n");			
			fclose(file1);
			fclose(file2);
			break;
		}
		case 2: {
			char fichier1[20], fichier2[20], fichier3[20];
			printf("Entrer le nom du premier fichier : ");
			scanf("%s", fichier1);
			printf("Entrer le nom du deuxieme fichier : ");
			scanf("%s", fichier2);
			printf("Entrer le nom du fichier resultat : ");
			scanf("%s", fichier3);
			FILE *file1 = fopen(fichier1, "r");	// ouverture du premier fichier
			FILE *file2 = fopen(fichier2, "r");	// ouverture du deuxieme fichier
			FILE *file3 = fopen(fichier3, "w");	// ouverture du fichier resultat

			if (file1 == NULL || file2 == NULL || file3 == NULL) {
				printf("Impossible d'ouvrir les fichiers\n");
				exit(0);
			}
			printf("Traitement du fichier en cours ... \n");
			char c;
			while ((c = fgetc(file1)) != EOF) {	// parcours du premier fichier 
				fputc(c, file3);
			}
			while ((c = fgetc(file2)) != EOF) {	// parcours du deuxiene fichier
				fputc(c, file3);
			}

			printf("Les deux fichiers fusionnes en %s\n", fichier3);

			fclose(file1);	// fermeture du premier fichier
			fclose(file2);	// fermeture du deuxieme fichier
			fclose(file3);	// fermeture du fichier resultat
			break;
		}
	}
	return 0;
}
