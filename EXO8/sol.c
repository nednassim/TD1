#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debug(...) 42
#endif

#define BUFFER_SIZE 16

typedef struct compte_ccp {
	char num[12];	// numero du compte CCP (12 bytes)
	int solde; // solde du compte CCP (4 bytes)
	// taille de compte_CCP : 16 bytes
} compte_ccp;

int main () {
	FILE *F1 = fopen("in1", "rb+");	// ouverture du premier fichier
	FILE *F2 = fopen("in2", "r");		// ouverture du deuxieme fichier
	
	if (F1 == NULL || F2 == NULL) {
		perror("Impossible d'ouvrir les fichiers! \n");
		exit(0);		
	}

	compte_ccp compte;
   memset(&compte, 0, sizeof(compte_ccp));
	const char delim[2] = " ";
	int i = 0;
	char ch = '0';
	char buffer[BUFFER_SIZE];
	char num[12], montant[8];
	while (fread(&compte, sizeof(compte_ccp), 1, F1) == 1)  {	// lecture d'un compte_ccp de fichier F1
		rewind(F2);	// repositionnement sur le debut du fichier F2
		while (fgets(buffer, BUFFER_SIZE, F2) != NULL) { // parcours du fichier F2
			strcpy(num, strtok(buffer, delim));	
			debug("%s %d %s", compte.num, compte.solde, num);
			if (!strcmp(compte.num, num)) {
				strcpy(montant, strtok(NULL, delim));				
				compte.solde += atoi(montant);
				debug("%d", compte.solde);
				fseek(F1, i * sizeof(compte_ccp), SEEK_SET);	// positionnement sur le compte cible
				debug("%ld", ftell(F1));
				fwrite(&compte, sizeof(compte_ccp), 1, F1);	// ecriture de l'enregistrement dans le fichier F1
				break;
			}
		}
		i++;
		debug("%d", i);
	}

	fclose(F1); // fermeture du premier fichier
	fclose(F2); // fermeture du deuxieme fichier
	return 0;
}

