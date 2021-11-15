#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define BUFFER_SIZE 128
	
void coder(char *filename, char *new_filename, char format, int n, char cle[n]) {
	FILE *file_out = fopen(new_filename, "w"); // ouverture du fichier en sortie

	printf("Le codage : \n");
	switch (format) {
		// Le cas d'un fichier texte
		case 't' : {
			FILE *file_in = fopen(filename, "r");	// ouverture du fichier en mode textuel
			if (file_in == NULL) {
				perror("Impossible d'ouvrir "
			}	
			char ch = fgetc(file_in);
			int i = 0;
			while (ch != EOF) {
				ch = ch + cle[i] ;
				fputc(ch, file_out);
				ch = fgetc(file_in);
				if (i == n) {
					i = 0;
				}
			}
			break;
		}
		// Le cas d'un fichier binaire
		case 'b': {
			FILE *file_in = fopen(filename, "rb");	// ouverture du fichier en mode binaire
			int buffer[n];
			while (!feof(file_in)) {
				fread(&buffer, n, 1, file_in);
				for (int i = 0; i < n; i++) {
					buffer[i] += cle[i];
				}
			}
			break;
		}
	}
	printf("Fichier code en : %s\n", new_filename);
	fclose(file_in);
	fclose(file_out);
}

void decoder(char *filename, char *new_filename, char format, int n, char cle[n]) {
	FILE *file_out = fopen(new_filename, "w");
	
	if (file_in == NULL || file_out == NULL) {
		perror("Impossible d'ouvrir les fichiers.\n");
		exit(0);
	}
	printf("Le decodage : \n");
	switch (format) {
		// Le cas d'un fichier texte
		case 't' : {
			FILE *file_in = fopen(filename, "r");
			char ch = fgetc(file_in);
			int i = 0;
			while (ch != EOF) {
				ch = ch - cle[i] ;
				fputc(ch, file_out);
				ch = fgetc(file_in);
				if (i == n) {
					i = 0;
				}
			}
			break;
		}
		// Le cas d'un fichier binaire
		case 'b': {
			FILE *file_in = fopen(filename, "rb");
			int buffer[n];
			while (!feof(file_in)) {
				fread(&buffer, n, 1, file_in);
				for (int i = 0; i < n; i++) {
					buffer[i] -= cle[i];
				}
			}
			break;
		}
	}
	fclose(file_in);
	fclose(file_out);
	printf("Fichier decode en : %s\n", new_filename);
}

int main () {
	char cle[20];
	printf("Entrer la cle : ");	
	scanf("%s", cle);
	printf("Entrer l'option que vous voulez : \n");
	printf("		1) Coder le fichier :\n");
	printf("		2) Decoder le fichier :\n");
	int opt;
	scanf("%d", &opt);
	switch (opt) {
		case 1: {
   		char fichier1[20], fichier2[20];
	   	printf("Entrer le nom du fichier a encoder en entree : ");
		   scanf("%s", fichier);
	   	printf("Entrer le nom du fichier en sortie : ");
		   scanf("%s", fichier);		  
			coder(fichier1, fichier2, 't', n, cle);	
			break;
		}
		case 2: {
	  		char fichier1[20], fichier2[20];
	   	printf("Entrer le nom du fichier a decoder en entree : ");
		   scanf("%s", fichier);
	   	printf("Entrer le nom du fichier en sortie : ");
		   scanf("%s", fichier);		  
			decoder(fichier1, fichier2, 't', n, cle);		
			break;
		}
		default:
			perror("Option non disponible.\n");
			exit(0);
	}
	return 0;
}
