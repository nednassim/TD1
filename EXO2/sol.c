#include <stdio.h>
#include <stdlib.h>

int main () {
	FILE *file1 = fopen("in1", "a");
	FILE *file2 = fopen("in2", "r");
	
	if (file1 == NULL || file2 == NULL) {
		printf("Impossible d'ouvrir les fichiers\n");
		exit(0);
	}
	
	char c;
	while ((c = fgetc(file2)) != EOF) {
		fputc(c, file1);
	}
	
	fclose(file1);
	fclose(file2);
	return 0;
}
