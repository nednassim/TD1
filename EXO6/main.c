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

int main () {
	menu();
	int option;
	scanf("%i", &option);
	switch(option) {
		// connaitre la temperature min, max, moy pour une ville donnee
		case 1: {
			FILE *file0 = fopen("in", "rb");
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
			while (ch != EOF) {
				fread(&enreg0, sizeof(enregistrement), 1, file0);	
				if (!strcmp(enreg0.ville, ville)) {
					assert(p);
					*(p + (count++)) = enreg0.temperature;
					printf("La temperature : %i\n", *(p + count - 1));
//					printf("p[%i] = %i\n", count - 1, *(p + count - 1));				
					moy += enreg0.temperature;	
				}
				ch = fgetc(file0);
				fseek(file0, (i++) * sizeof(enregistrement) , SEEK_SET);
			}
			p = (int*) realloc (p, count * sizeof(int));
			int min = *(p), max = *(p);
			for (int i = 0; i < count; i++) {
				printf("p[%i] = %i\n", i, *(p + i));
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
			FILE *file1 = fopen("in", "ab+");
			enregistrement enreg1;
			memset(&enreg1, 0, sizeof(enregistrement));
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
			FILE *file2 = fopen("in", "rb+");
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
			while (ch != EOF) {
				fread(&enreg2, sizeof(enregistrement), 1, file2);	
				if (!strcmp(enreg2.ville, ville) && !strcmp(enreg2.date, date)) {
					enreg2.temperature = temperature;
					fwrite(&enreg2, sizeof(enregistrement), 1, file2);	
					afficher(enreg2, 0);
					break;
				}
				ch = fgetc(file2);
				fseek(file2, (i++) * sizeof(enregistrement) , SEEK_SET);
			}
			fclose(file2);
			break;
		}
		// supprimer tous les enregistrements relatifs a une ville donnee
		case 4: {
			FILE *file3 = fopen("in", "rb");
			FILE *file4 = fopen("out", "wb");
			if (file3 == NULL) {
				perror("Impossible d'ouvrir ce fichier\n");
				exit(0);
			}
			enregistrement enreg3;
//			memset(&enreg3, 0, sizeof(enregistrement));
			int i = 1;
			char ch = '0';
			char ville[16];
			printf("Entrer la ville : ");
			scanf("%s", ville);
			while (ch != EOF) {
				fread(&enreg3, sizeof(enregistrement), 1, file3);	
				if (strcmp(enreg3.ville, ville)) {
					fwrite(&enreg3, sizeof(enregistrement), 1, file4);
				}
				ch = fgetc(file3);
				fseek(file3, (i++) * sizeof(enregistrement) , SEEK_SET);
			}
			break;
			// la deuxieme solution est une suppression logique
			// en ajoutant un champ booleen "supprime 0 1"
			// 1 si l'enregistrement est supprime et 0 sinon
		}
		default : {
			printf("Cette option n'est pas disponible\n");
			menu();
		}
	}
	return 0;
}


