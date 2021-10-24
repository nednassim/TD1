#include <stdio.h>
#include <stdlib.h>

int main () {
	FILE *file1 = fopen("in1", "r");
	FILE *file2 = fopen("in2", "r");
	FILE *file3 = fopen("out", "w");
	
	if (file1 == NULL || file2 == NULL || file3 == NULL) {
		printf("Impossible d'ouvrir les fichiers\n");
		exit(0);
	}
	
	char c;
	while ((c = fgetc(file1)) != EOF) {
		fputc(c, file3);
	}
	while ((c = fgetc(file2)) != EOF) {
		fputc(c, file3);
	}
	
	printf("Les deux fichiers fusionnes en out\n");

	fclose(file1);
	fclose(file2);
	fclose(file3);

	return 0;
}
