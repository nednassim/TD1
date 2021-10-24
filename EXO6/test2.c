#include <stdio.h>                                                                                                    
#include <stdlib.h>                                                                                                   
#include <stdarg.h>                                                                                                   
#include <string.h>                                                                                                   
                                                                                                                      
#define BUFFER_SIZE 128                                                                                               
                                                                                                                      
typedef struct enregistrement {                                                                                       
   char ville[16];   // 16 bytes                                                                                      
   char date[17];    // 12 bytes                                                                                      
   int temperature;  // 4 bytes                                                                                       
}enregistrement;                                                                                                      
                                                                                                                      
int main () {     
	printf("%ld", sizeof(enregistrement));
	return 0;
}
