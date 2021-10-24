#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define BUFFER_SIZE 128

typedef struct enregistrement {
	char ville[16];	// 16 bytes
	char date[12];		// 12 bytes 
	int temperature;	// 4 bytes
}enregistrement;

int main () {
	printf("Entrer le nom du fichier : ");
	char name[6];
	scanf("%s", name);
	printf("La liste des options disponibles :\n");
	printf("		1) Ecrire le fichier\n");
	printf("		2) Lire le fichier\n");
	printf("Entrer une option : ");
	int option;
	scanf("%i", &option);
	switch(option) {
		case 1: {
			FILE *file = fopen(name, "wb");
			if (file == NULL) {
				perror("Impossible d'ouvrir ce fichier\n");
				exit(0);
			}
			enregistrement enreg;
			memset(&enreg, 0, sizeof(enregistrement));
			int n;
			printf("Entrer le nombre d'enregistrements: ");
			scanf("%i", &n);
			for (int i = 0; i < n; i++) {
				printf("L'enregistremt : %d\n", i + 1);
				printf("La ville : ");
				scanf("%s", enreg.ville);
				printf("La date : ");
				scanf("%s",  enreg.date);
				printf("La temperature : ");
				scanf("%d", &enreg.temperature);
				printf("******************\n");
				fwrite(&enreg, sizeof(enregistrement), 1, file);
			}
			fclose(file);
			break;
		}
		case 2: {
			FILE *file1 = fopen(name, "rb");
			if (file1 == NULL) {
				perror("Impossible d'ouvrir ce fichier\n");
				exit(0);
			}
			enregistrement enreg1;
			int i = 1;
			char ch = '0';
			while (ch != EOF) {  // afficher le contenu du fichier
				fread(&enreg1, sizeof(enregistrement), 1, file1);
				printf("L'enregistremt : %d\n", i++);
				printf("La ville : %s   ", enreg1.ville);
				printf("La date :  %s   ",  enreg1.date);
				printf("La temperature : %i\n", enreg1.temperature);
				printf("******************\n");
				ch = fgetc(file1);                                                       
				fseek(file1, (i - 1) * sizeof(enregistrement) , SEEK_SET);   
			}   
			fclose(file1);
			break;
		}
	}
  return 0;
}


