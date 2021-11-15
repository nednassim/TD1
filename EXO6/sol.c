#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 128

typedef struct enregistrement {
	char ville[16];	// 16 bytes
	char date[12];		// 12 bytes 
	int temperature;	// 4 bytes
	// taille de l'enregistrement : 32 bytes
} enregistrement;

// une procedure pour afficher le menu
void menu() {
	printf("Les options disponibles : \n");
	printf("		1) Connaitre la temperature min, max, moy pour une ville donnee :\n");
	printf("		2) Rajouter un nouveau enregistrement au fichier :\n");
	printf("		3) Modifier la temperature d'une ville donnee a une date donnee :\n");
	printf("		4) Supprimer tous les enregistrements d'une ville donne :\n");	
	printf("Choisissez une option : ");
}

void afficher(enregistrement enreg, int n) {
	printf("L'enregistremt : %d\n", n);
	printf("La ville : %s   ", enreg.ville);
	printf("La date :  %s   ",  enreg.date);
	printf("La temperature : %i\n", enreg.temperature);
	printf("******************\n");
}

void afficher_fichier(char *fichier) {
	FILE *file = fopen(fichier, "rb");
	enregistrement enreg;
   int i = 1;
   char ch = '0';
   while (fread(&enreg, sizeof(enregistrement), 1, file)) {  // afficher le contenu du fichier
      char nb[12];
      sprintf(nb, "% 4d", i);
      char ville[16];
      sprintf(ville, "% 6s", enreg.ville);
      char date[12];
      sprintf(date, "%s", enreg.date);
      char temperature[4];
      sprintf(temperature, "% 3d", enreg.temperature);
      char str[100] = "+----------------+--------------+--------------+---------------+\n";
      printf("%s", str);
      printf("| Enregistrement |    Ville     |     Date     |  Temperature  |\n");
      printf("%s", str);
      printf("|                |              |              |               |\n");
      printf("|     %s       |    %s    |  %s  |      %s      |\n", nb, ville, date, temperature);
      printf("|                |              |              |               |\n");
      printf("%s", str);
      i++;
   }
	fclose(file);
}

int main () {
	printf("Entrer le nom du fichier en entree : ");
	char fichier[20];
	scanf("%s", fichier);
	afficher_fichier(fichier);	// on affiche le fichier
	menu();	// on affiche le menu
	int option;
	scanf("%i", &option);
	switch(option) {
		// connaitre la temperature min, max, moy pour une ville donnee
		case 1: {
			FILE *file0 = fopen(fichier, "rb");
			if (file0 == NULL) {
				perror("Impossible d'ouvrir ce fichier\n");
				exit(0);
			}
			enregistrement enreg0;
			int i = 1;
			char ch = '0';
			int count = 0;
			double moy = 0;
			char ville[16];
			int *p;
			p = (int*) calloc (100, sizeof(int));
			printf("Entrer le nom de la ville : ");
			scanf("%s", ville);
			while (fread(&enreg0, sizeof(enregistrement), 1, file0) == 1) {
				if (!strcmp(enreg0.ville, ville)) {
					assert(p);
					*(p + (count++)) = enreg0.temperature;
					printf("La temperature : %i\n", *(p + count - 1));
					moy += enreg0.temperature;	
				}
			}
			p = (int*) realloc (p, count * sizeof(int));
			int min = *(p), max = *(p);	// initialiser le min et le max 
			for (int i = 0; i < count; i++) {
				if (*(p + i) >= max) {
					max = *(p + i);
				}
				if (*(p + i) <= min) {
					min = *(p + i);
				}
			}
			free(p);		
			if (count)	{
				moy /= count;
			}
			printf("La temperature minimale de la ville %s : %i\n", ville, min);
			printf("La temperature minimale de la ville %s : %i\n", ville, max);
			printf("La temperature moyenne de la ville %s : %.2f\n", ville, moy);	
			fclose(file0);
			break;
		}
		// rajouter un nouveau enregistrement au fichier
		case 2: {
			FILE *file1 = fopen(fichier, "ab+");
			enregistrement enreg1;
			printf("La ville : ");
			scanf("%s", enreg1.ville);
			printf("La date : ");
			scanf("%s",  enreg1.date);
			printf("La temperature : ");
			scanf("%i", &enreg1.temperature);
			fwrite(&enreg1, sizeof(enregistrement), 1, file1);	
			fclose(file1);
			break;
		}
		// modifier la temperature d'une ville donnee a une date donnee	
		case 3: {				
			FILE *file2 = fopen(fichier, "rb+");
			if (file2 == NULL) {
				perror("Impossible d'ouvrir ce fichier\n");
				exit(0);
			}
			enregistrement enreg2;
			int i = 1;
			char ch = '0';
			char ville[16], date[12];
			int temperature;
			printf("Entrer la ville : ");
			scanf("%s", ville);
			printf("Entrer la date : ");
			scanf("%s", date);
			printf("Entrer la temperature voulue: ");
			scanf("%i",&temperature);
			while (fread(&enreg2, sizeof(enregistrement), 1, file2) == 1) {
				if (!strcmp(enreg2.ville, ville) && !strcmp(enreg2.date, date)) {
					enreg2.temperature = temperature;
					fseek(file2, -sizeof(enregistrement), SEEK_CUR);
					fwrite(&enreg2, sizeof(enregistrement), 1, file2);	
					break;
				}
			}
			fclose(file2);
			break;
		}
		// supprimer tous les enregistrements relatifs a une ville donnee
		case 4: {
			FILE *file3 = fopen(fichier, "rb");
			printf("Entrer le nom du fichier en sortie:");
			char fichier1[20];
			scanf("%s", fichier1);
			FILE *file4 = fopen(fichier1, "wb");
			if (file3 == NULL) {
				perror("Impossible d'ouvrir ce fichier\n");
				exit(0);
			}
			enregistrement enreg3;
			int i = 1;
			char ch = '0';
			char ville[16];
			printf("Entrer la ville : ");
			scanf("%s", ville);
			while (fread(&enreg3, sizeof(enregistrement), 1, file3) == 1) {
				if (strcmp(enreg3.ville, ville)) {
					fwrite(&enreg3, sizeof(enregistrement), 1, file4);
				}
			}
			break;
			// la deuxieme solution est une suppression logique
			// en ajoutant un champ booleen "supprime 0 1"
			// 1 si l'enregistrement est supprime et 0 sinon
		}
		default : {
			printf("Cette option n'est pas disponible\n");
			menu();
			break;
		}
	}
	return 0;
}


