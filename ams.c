/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "ams.h"


s_song readAMS(char* fileName){

    s_song mySong;

    FILE * songFile;
    songFile=fopen(fileName,"r");
    if ( songFile == NULL ) {
        printf( "Cannot open file\n");
        mySong.nTicks=0;
        mySong.tpm=0;
        for (int i=0;i<MAX_NUMBER_TICKS;i++){
            mySong.tickTab[i].accent=0;
            for(int j=0;j<4;j++) {
                mySong.tickTab[i].note[j] = 0;
            }
        }
        mySong.title[0]='\0';
        return mySong;
    }
    for (int i=0;i<MAX_NUMBER_TICKS;i++){
        mySong.tickTab[i].accent=0;
        for(int j=0;j<4;j++) {
            mySong.tickTab[i].note[j] = 0;
        }
    }

    char line[MAX_SIZE_LINE]; // buffer de lecture

    fgets(mySong.title, MAX_SONGNAME_SIZE, songFile);
    mySong.title[strlen(mySong.title)-1] = '\0';

    fgets(line, MAX_SIZE_LINE, songFile);
    mySong.tpm=atoi(line)*2;

    fgets(line, MAX_SIZE_LINE, songFile); //saute la ligne
    fgets(line, MAX_SIZE_LINE, songFile); //saute la ligne

    int compt_ligne=0;
    char *delim ="|\n";
    char *token;

    while ( ! feof( songFile ) ) {

        fgets(line, MAX_SIZE_LINE, songFile);
        int compt_colonne = 0;
        int compt_note = 0;

        token = strtok(line, delim);

        while (token != NULL) {

            if (token[0] == '^' || token[0] == 'x') {
                mySong.tickTab[compt_ligne].note[compt_note] = compt_colonne;
                compt_note++;
            }
            if (token[0] == '^') {
                mySong.tickTab[compt_ligne].accent = 1;
            }if(token[0] =='x'){
                mySong.tickTab[compt_ligne].accent = 0;
            }

            token = strtok(NULL, delim);
            compt_colonne++;
        }
        compt_ligne++;
    }
    mySong.nTicks=compt_ligne;
    return mySong;
}


void createAMS(char* txtFileName, char* amsFileName){
    FILE * txt = NULL;
    txt = fopen(txtFileName,"r");
    if (txt == NULL){
        printf("Error file not found !\n");
        exit(0);
    }

    FILE * ams = NULL;
    ams = fopen(amsFileName,"w");
    if (ams == NULL){
        printf("Error file not found !\n");
        exit(0);
    }
    //fonction
    char line[MAX_SIZE_LINE];

    fgets(line,MAX_SIZE_TITLE,txt);
    printf("%s",line);
    fputs(line,ams);

    fgets(line,MAX_SIZE_TITLE,txt);
    printf("%s\n",line);
    fputs(line,ams);

    fgets(line,MAX_SIZE_TITLE,txt);
    fputs("\r\n",ams);

    char numeros[MAX_SIZE_LINE];
    sprintf(numeros,"    ");
    for (int i=1;i<=60;i++){
        sprintf(numeros+strlen(numeros), "%02d ",i);
    }
    sprintf(numeros+strlen(numeros),"\r\n");
    fputs(numeros,ams);
    //fin fonction
    char tableau_ticks[MAX_NUMBER_TICKS][60];
    for (int i=0;i<MAX_NUMBER_TICKS;i++){
        for (int j=0;j<60;j++){
            tableau_ticks[i][j]=' ';
        }
    }

    int nb_ligne=0;
    //cree tableau(nb_ligne, tableau_ticks, txt)
    char *delim =",";
    char *token;
    int valeur[]={10,12,1,3,5,6,8}; //tableau des valeurs des notes
    while ( ! feof( txt ) ) {
        fgets(line, MAX_SIZE_LINE, txt);
        if (line[0] != '\n' && line[0] != '\r' && line[0] != '\0') {

            token = strtok(line, delim);

            while (token != NULL) {
                int compt;
                int decalage = 0;

                if (token[0] == ' ') {
                    decalage += 1;
                }
                compt = valeur[token[0 + decalage] - 'A'] + ((token[1 + decalage] - 48) - 1) * 12;
                if (token[2 + decalage] == '#') {
                    compt += 1;
                    decalage += 1;
                }
                printf("%d | ", compt);

                int nb_tick = 0;
                switch (token[3 + decalage]) {
                    case 'R':
                        nb_tick = 8;
                        break;
                    case 'B':
                        nb_tick = 4;
                        break;
                    case 'N':
                        nb_tick = 2;
                        break;
                    case 'C':
                        nb_tick = 1;
                        break;
                }

                for (int i = 0; i < nb_tick; i++) {
                    if (i == 0) {
                        tableau_ticks[nb_ligne + i][compt - 1] = '^';
                    } else {
                        tableau_ticks[nb_ligne + i][compt - 1] = 'x';
                    }
                }
                token = strtok(NULL, delim);
            }
        }
        printf("\n");
        nb_ligne++;
    }
    //fin cree tableau

    //ecrit tableau(nb_ligne, tableau_ticks, ams)
    for(int i=0;i<nb_ligne;i++){
        char ligne[MAX_SIZE_LINE];
        sprintf(ligne,"%03d|",i+1);
        printf("%s",ligne);
        for (int j=0;j<60;j++){
            printf("%c |",tableau_ticks[i][j]);
            sprintf(ligne + strlen(ligne),"%c |",tableau_ticks[i][j]);
        }
        if (i!=nb_ligne-1) {
            printf("\n");
            sprintf(ligne + strlen(ligne), "\r\n");
        }
        fputs(ligne,ams);

    }
    //fin ecrit tableau

    fclose(txt);
    fclose(ams);
}