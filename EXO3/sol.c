#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128

int main () {
	char fichier[20];
	printf("Entrer le nom du fichier : ");
	scanf("%s", fichier);
	FILE *file = fopen(fichier, "r"); // ouverture du fichier
	char word[10];
	printf("Entrer le mot a rechercher : "); 
	scanf("%s", word);

	char buffer[BUFFER_SIZE];
	const char delim[] = " /!@#$%^&*()[]|{},'.;:<>?\n\\\t";
	char *str;
	int count = 0;
	

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
