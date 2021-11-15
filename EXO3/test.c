#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debug(...) 42
#endif


#define BUFFER_SIZE 128
int main () {
	FILE *file = fopen("in", "r");
  	
	char str[BUFFER_SIZE];
	const char delim[2] = " ";
	char *pos;
	int index, count = 0;
	char word[10];
	printf("Entrer le mot a rechercher : ");
	scanf("%s", word);
	while ((fgets(str, BUFFER_SIZE, file)) != NULL) {	// lire ligne par ligne jusqu'a la fin
		index = 0;
		while ((pos = strstr(str + index, word)) != NULL) {	// trouver la prochaine occurence du mot str
			// l'indexe du mot en str et (l'@ de pos - l'@ str)
			index = (pos - str) + 1;
			count ++;
			debug("%s %i %i", pos, index, count);
		}
	}

	printf("Le nombre d'occurences du mot %s dans le fichier 'in' est : %d\n", word, count);
	return 0;
}
