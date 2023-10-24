#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_rec.h"
int main(){
	
	printf("Content-type:text/html\n\n");
	printf("<html>");
	printf("<body>");
	
	char *nom;
	nom = (char*)malloc(50);
	obtenir_nom(nom);
	enregistrer_fichier();
	
	printf("</body>");
	printf("</html>");
	return 0;
}
