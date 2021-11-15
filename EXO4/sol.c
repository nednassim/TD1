#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   char fichier[20];
   printf("Entrer le nom du fichier : ");
   scanf("%s", fichier);

	FILE *file = fopen(fichier, "r"); // ouverture du fichier

	if (file == NULL) {
		printf("Impossible d'ouvrir ce fichier\n");
		exit(0);	
	}

	char c;
	int count = 0;
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			count++;
		}
	}

	printf("Le nombre de lignes est : %d\n", count);
	fclose(file);	// fermeture du fichier
	return 0;
}
