#include <stdio.h>
#include <stdlib.h>

# define ELEMENTSIZE 32
# define NUMELEMENTS 1024*1024*128 // 4 Gigabyte

int main ( void ) {
	char ** bufferPointers = malloc ( NUMELEMENTS * sizeof ( char *) ) ;
	for ( u_int64_t i = 0 ; i < NUMELEMENTS ; i ++ )
	bufferPointers [ i] = g_slice_alloc ( ELEMENTSIZE ) ;
	for ( u_int64_t i = 0 ; i < NUMELEMENTS ; i ++ )
	g_slice_free1 ( ELEMENTSIZE , bufferPointers [i] ) ;
	free ( bufferPointers ) ;

return 0;
}
