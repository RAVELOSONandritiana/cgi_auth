#ifndef LIB_H
#define LIB_H
int nb_ligne(char *chaine){
	char chemin[200];
	strcpy(chemin,"cat ");
	strcat(chemin,chaine);
	strcat(chemin," | wc -l");
	FILE *fichier = popen(chemin,"r");
	char ch[256];
	while(fgets(ch,256,fichier));	
	pclose(fichier);
	return atoi(ch);
}
void modif_mois(char *mois){
	if(strcmp(mois,"Sept")==0){
		strcpy(mois,"Septambra");
	}
	if(strcmp(mois,"Oct")==0){
		strcpy(mois,"Octobra");
	}
	if(strcmp(mois,"Nov")==0){
		strcpy(mois,"Novambra");
	}
	if(strcmp(mois,"Dec")==0){
		strcpy(mois,"Decambra");
	}
}
void css(){
	printf("<style>");
	printf(""
		"td{"
			"width:20vw;"
		"}"
	"");
	printf("</style>");
}
void modif_week_day(char *mois,char *jour,char *week_day){
	int k = 23;
	int j = 20;
	int m = 0;
	if(strcmp(mois,"Septambra")==0){
		m = 9;
	}
	else if(strcmp(mois,"Octobra")==0){
		m = 10;
	}
	int p = 0;
	sscanf(jour,"%d",&p);
	
	int day = (p+13*(m+1)/5+k+k/4+j/4+5*j)%7;
	
	if(day==0){
		strcpy(week_day,"Asabotsy");
	}
	else if(day==1){
		strcpy(week_day,"Alahady");
	}
	else if(day==2){
		strcpy(week_day,"Alatsinainy");
	}
	else if(day==3){
		strcpy(week_day,"Talata");
	}
	else if(day==4){
		strcpy(week_day,"Alarobia");
	}
	else if(day==5){
		strcpy(week_day,"Alakamisy");
	}
	else if(day==6){
		strcpy(week_day,"Zoma");
	}
}
char **stock_ligne(int taille){
	
	FILE *fichier = NULL;
	
	fichier = fopen("/var/log/auth.log","r");
	char **fichier_total;
	fichier_total = (char **)malloc(sizeof(char *)*taille);
	for(int i = 0;i<taille;i++){
		fichier_total[i] = (char *)malloc(256);
	}
	for(int i = 0;i<taille;i++){
		char line[256];
		fgets(line,256,fichier);
		strcpy(fichier_total[i],line);
	}
	fclose(fichier);
	return fichier_total;
}

void affiche_tab(char **chaine,int debut,int fin,char *user1){
	printf("<table border=\"1\">");
	printf("<tr><th>Date</th><th>Session</th><th>Utilisateur</th></tr>");
	char mois[100],jour[100],heure[100],user[100],type[100],day[100];
		
	for(int i = debut;i<fin;i++)
	{
		if(strstr(chaine[i],"closed") || strstr(chaine[i],"opened")){
			sscanf(chaine[i],"%[^ ] %[^ ] %[^ ] %*[^:]: %*[^ ] session %[^ ] for user %[^ ] ",mois,jour,heure,type,user);
			//Modification des valeurs
			strcpy(user,strtok(user,"("));
			modif_mois(mois);
			if(strcmp(user1,user)==0){
				modif_week_day(mois,jour,day);
			  	
				printf("<tr>");
				printf("<td>");
				printf("%s %s %s %s",day,jour,mois,heure);
				printf("</td>");
				if(strstr(type,"opened")){
					printf("<td style=\"color:green\">");
					printf("%s",type);
				}
				else if(strstr(type,"closed")){
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
	
	printf("</table>");
}

void st_tout(int debut,int fin,char *user1,char **chaine){
	char mois[100],jour[100],heure[100],user[100],type[100],day[100];
	FILE *fichier = NULL;
	fichier = fopen("doc.txt","w");
	if(fichier==NULL){
		printf("Erreur");
	}
	for(int i = debut;i<fin;i++)
	{
		if(strstr(chaine[i],"closed") || strstr(chaine[i],"opened")){
			sscanf(chaine[i],"%[^ ] %[^ ] %[^ ] %*[^:]: %*[^ ] session %[^ ] for user %[^ ] ",mois,jour,heure,type,user);
			//Modification des valeurs
			strcpy(user,strtok(user,"("));
			modif_mois(mois);
			if(strcmp(user1,user)==0){
				fprintf(fichier,"%s %s %s %s %s\n",day,mois,heure,type,user);
			}
		}
	}
	fclose(fichier);
}
#endif
