#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debug(...) 42
#endif

#define SIZE 256

#define PBSTR "############################################################"
#define PBWIDTH 60

void Progress(double percentage) {
   int val = (int) (percentage * 100);
   int lpad = (int) (percentage * PBWIDTH);
   int rpad = PBWIDTH - lpad;
   printf("\r%3d%% [%.*s%*s]\n", val, lpad, PBSTR, rpad, "");
   fflush(stdout);
}


int main () {
	FILE *file = NULL;
	char name[20];
	printf("Entrer le nom du fichier : ");
	scanf("%s", name);

	file = fopen(name, "r");
	if (file == NULL) {
		printf("Fichier introuvable");
		exit(0);
	}

	fseek(file, 0L, SEEK_END);
	int size  = ftell(file);
	rewind(file);
	int option;

	printf("Les options disponibles : \n");	
	printf("	1) lecture en mode caracteres\n");
	printf("	2) lecture en mode lignes\n");
	printf("Choisissez une option : ");
	scanf("%d", &option);
	switch(option) {
		case 1: {
			char c;
			while ((c = fgetc(file)) != EOF) {
				printf("%c", c);
			}
			break;
		}
		case 2: {
			int count = 0;
			char buf[SIZE];
			while (fgets(buf, SIZE, file) != NULL) {
				printf("%s", buf);
				count += strlen(buf);
				Progress((double) (count / (double) size)); 
			}
			printf("Traitement termine avec succes!\n");
			break;
		}
	}
	fclose(file);
	return 0;
}
