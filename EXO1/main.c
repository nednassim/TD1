#include <stdio.h>
#include <stdlib.h>

int main () {
	FILE *file;
	char name[20], c;
	printf("Entrer le nom du fichier : \n");
	scanf("%s", name);

	file = fopen(name, "r");
	if (file == NULL) {
		printf("Fichier introuvable");
		exit(0);
	}
	c = fgetc(file);
	while (c != EOF) {
		printf("%c", c);
		c = fgetc(file);
	}
	fclose(file);
	return 0;
}
