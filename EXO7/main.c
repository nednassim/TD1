#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main () {
	char fichier1[20];
	printf("Entrer le nom du fichier : ");
	scanf("%s", fichier1);
	char fichier2[20];
	printf("Entrer le nom du fichier : ");
	scanf("%s", fichier2);

	FILE *file1 = fopen(fichier1, "r");
	FILE *file2 = fopen(fichier2, "r");

	int diff;
	int line, col;

	if (file1 == NULL || file2 == NULL) {
		perror("Impossible d'ouvrir les fichiers.\n");
		exit(0);
	}
	line = 1;
	col = 0;
	char ch1, ch2;
	int count = 0;
	while ((ch1 = fgetc(file1)) != EOF && (ch2 = fgetc(file2)) != EOF) {
//		ch1 = fgetc(file1);
//		ch2 = fgetc(file2);
		if (ch1 != ch2) {
			printf("Ligne : %d  Col : %d \n", line, col);
			++count;
		}

		if (ch1 == '\n') {
			++line;
			col = 0;
		}
		++col;
	}
	if (!count) printf("Les fichiers in1 et in2 sont identiques.\n");
	return 0;
}

