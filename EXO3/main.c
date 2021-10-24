#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128

int main () {
	FILE *file = fopen("in", "r");
	
	char buffer[BUFFER_SIZE];
	const char delim[2] = " ";
	char *str;
	int count = 0;
	
	char word[10];
	printf("Entrer le mot a rechercher : ");
	scanf("%s", word);

	if (file == NULL) {
		perror("Impossible d'ouvrir le fichier\n");
		exit(0);
	}
	
	while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
		str = strtok(buffer, delim);
		while (str != NULL) {			
			if (!strcmp(str, word)) {
				count++;
			}
			printf("%s\n", str);
			str = strtok(NULL, delim);
		}
	}
	printf("Le nombre d'occurences du mot %s dans le fichier 'in' est : %d\n", word, count);
	fclose(file);

	return 0;
}
