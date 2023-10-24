#ifndef LIB_REC_H
#define LIB_REC_H
void obtenir_nom(char *nom){
	char chaine[200];
	strcpy(chaine,getenv("QUERY_STRING"));
	sscanf(chaine,"%*[^=]=%[^=]=",nom);
	printf("%s",nom);
}
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

void enregistrer_fichier(){
	FILE *fichier = NULL;
	FILE *fichier_log = NULL;
	fichier_log = fopen("/var/log/auth.log","r");
	fichier = fopen("doc.txt","w");
	char mois[100],jour[100],heure[100],user[100],type[100];
	int taille = nb_ligne("/var/log/auth.log");
	for(int i = 0;i<taille;i++)
	{
		char line[256];
		fgets(line,255,fichier_log);
		if(strstr(line,"opened")||strstr(line,"closed"))
		{
			char *week_day = NULL;
			sscanf(line,"%[^ ] %[^ ] %[^ ] %*[^:]: %*[^ ] session %[^ ] for user %[^ ] ",mois,jour,heure,type,user);
			modif_week_day(mois,jour,week_day);
			fprintf(fichier,"%s %s %s %s %s\n",week_day,jour,mois,type,user);
		}
	}
	fclose(fichier_log);
	fclose(fichier);
}

#endif
