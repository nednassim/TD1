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
	char fichier[20];
	scanf("%s", fichier);
	printf("La liste des options disponibles :\n");
	printf("		1) Ecrire le fichier\n");
	printf("		2) Lire le fichier\n");
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
			FILE *file = fopen(fichier, "rb");
			if (file == NULL) {
				perror("Impossible d'ouvrir ce fichier\n");
				exit(0);
			}
			enregistrement enreg;
			int i = 1;
			char ch = '0';
			while (ch != EOF) {  // afficher le contenu du fichier
				fread(&enreg, sizeof(enregistrement), 1, file);
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
				printf("|      		 |              | 	       | 	       |\n");
				printf("|     %s       |    %s    |  %s  |      %s      |\n", nb, ville, date, temperature);
				printf("| 		 |		|     	       |	       |\n");
				printf("%s", str);
				i++;
/*
				printf("L'enregistremt : %d\n", i++);
				printf("La ville : %s   ", enreg.ville);
				printf("La date :  %s   ",  enreg.date);
				printf("La temperature : %i\n", enreg.temperature);
				printf("******************************************************************\n");
*/				
				ch = fgetc(file);                                                       
				fseek(file, (i - 1) * sizeof(enregistrement) , SEEK_SET);   
			}   
			fclose(file);
			break;
		}
	}
  return 0;
}


