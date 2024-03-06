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
            for(int j=0;j<4;j++) {
                mySong.tickTab[i].note[j] = 0;
            }
        }
        mySong.title[0]='\0';
        return mySong;
    }
    for (int i=0;i<MAX_NUMBER_TICKS;i++){
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

    char line[MAX_SIZE_LINE];

    fgets(line,MAX_SIZE_TITLE,txt);
    printf("%s",line);
    fputs(line,ams);

    fgets(line,MAX_SIZE_TITLE,txt);
    printf("%s\n",line);
    fputs(line,ams);

    fgets(line,MAX_SIZE_TITLE,txt);
    fputs("\n",ams);
    fputs("    01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 \n", ams);

    char tableau_ticks[MAX_NUMBER_TICKS][60];
    for (int i=0;i<MAX_NUMBER_TICKS;i++){
        for (int j=0;j<60;j++){
            tableau_ticks[i][j]=' ';
        }
    }
    int nb_ligne=0;

    char *delim =",";
    char *token;
    int valeur[]={10,12,1,3,5,6,8}; //tableau des valeurs des notes
    while ( ! feof( txt ) ) {
        fgets(line, MAX_SIZE_LINE, txt);

        token = strtok(line, delim);

        while (token != NULL) {
            int compt = 0;
            int decalage = 0;

            if (token[0] == ' ') {
                decalage += 1;
            }
            compt = valeur[token[0 + decalage] - 'A'] + ((token[1+decalage]-48)-1)*12;
            if (token[2 + decalage] == '#') {
                compt+=1;
                decalage+=1;
            }
            printf("%d | ", compt);

            int nb_tick=0;
            switch (token[3+decalage]) {
                case 'R':
                    nb_tick=8;
                    break;
                case 'B':
                    nb_tick=4;
                    break;
                case 'N':
                    nb_tick=2;
                    break;
                case 'C':
                    nb_tick=1;
                    break;
            }

            for (int i=0;i<nb_tick;i++){
                if (i==0){
                    tableau_ticks[nb_ligne + i][compt - 1] = '^';
                }
                else {
                    tableau_ticks[nb_ligne + i][compt - 1] = 'x';
                }
            }


            /*for i in ticktab[i]
             * if i == la ou j'en suis, j'affiche x (ou ^ xdddddd)
             */
            
            token = strtok(NULL, delim);
        }
        printf("\n");
        nb_ligne++;
    }
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
            sprintf(ligne + strlen(ligne), "\n");
        }
        fputs(ligne,ams);

    }

    fclose(txt);
    fclose(ams);
}