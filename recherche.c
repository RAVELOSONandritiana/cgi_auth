#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOMBRE_INITIAL 100
int main(){
	
	printf("Content-Type:Text/html\n\n");
	FILE *fichier = NULL;
	printf("<head>");
		printf("<style>");
			printf("table{transform:translateX(30%);}");
			printf("td{width:20vw;height:4vw;align:center}");
			printf("tr{width:20vw;height:4vw}");
		printf("</style>");
	
	printf("</head>");
	
	printf("<body>");
	
	fichier = fopen("/var/log/auth.log","r");
	char line[256];
	int c=0;
	FILE *chaine = NULL;
	chaine = popen("cat /var/log/auth.log | wc -l","r");
	
	while(fgets(line,255,chaine))
	{
		c=atoi(line);
	}
	char *nom_input = getenv("QUERY_STRING");
	char nom_user[100];
	sscanf(nom_input,"%[^=]=%s",line,nom_user);
	
	fichier = fopen("/var/log/auth.log","r");
	printf("<table border=\"1\">");
	int cpt = 0;
	printf("<tr><th>Date</th><th>Session</th><th>Utilisateur</th></tr>");
	char mois[100],jour[100],heure[100],user[100],inutile[100],inutile2[100],type[100];
	for(int i = 0;i<=c;i++){
		fgets(line,256,fichier);
		if(i>=c-NOMBRE_INITIAL){
			sscanf(line,"%[^ ] %[^ ] %[^ ] %[^:]: %[^ ] session %[^ ] for user %[^ ] ",mois,jour,heure,inutile,inutile2,type,user);
				
					if(strstr(type,"opened") || strstr(type,"closed")){
						strcpy(user,strtok(user,"("));
						if(strcmp(user,nom_user)==0)
						{
							cpt++;
							printf("<tr>");
								printf("<td>");
									printf("%s %s %s",mois,jour,heure);
								printf("</td>");
								
								if(strstr(type,"opened")){
									printf("<td style=\"color:green\">");
									printf("%s",type);
								}
								if(strstr(type,"closed")){
									printf("<td style=\"color:red\">");
									printf("%s",type);
								}
								
								printf("</td>");
								printf("<td>");
									printf("%s",user);
								printf("</td>");
							printf("</tr>");
						}
					}
		}
	}
	
	printf("</table>");
				if(cpt==0){
						printf("<h1 style=\"color:red\">Aucune Correspondance</h1>");
				}
	fclose(fichier);
	printf("</body>");
		
	return 0;
}
