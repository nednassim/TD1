#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
	FILE *file = fopen("in", "r");

	if (file == NULL) {
		printf("Impossible d'ouvrir ce fichier\n");
		exit(0);	
	}

	char c = fgetc(file);
	int count = 0;
	while (c != EOF) {
		if (c == '\n') {
			count++;
		}
		c = fgetc(file);
	}

	printf("Le nombre de lignes est : %d\n", count);
	fclose(file);
	return 0;
}
