/**
 * @authors Lelievre Tom Bellenger Maxime GroupePJ2 Caen
 */

#include "define.h"
#include "ams.h"

/**
 * Read an ams file
 * @param fileName name of the file
 * @return a s_song with attributes of the song
 */
s_song readAMS(char* fileName){

    s_song mySong; //song that will be returned

    FILE * songFile;
    songFile=fopen(fileName,"r");   //opening the ams file of the song
    if ( songFile == NULL ) {   //if no file with this name, return a struc with empty attributes
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

    char line[MAX_SIZE_LINE]; // buffer that will get a line from the file

    fgets(mySong.title, MAX_SONGNAME_SIZE, songFile); //get title in first line
    mySong.title[strlen(mySong.title)-1] = '\0';   //to finish the string

    fgets(line, MAX_SIZE_LINE, songFile);   //get tpm in second line
    mySong.tpm=atoi(line)*2;    //convert string to int

    fgets(line, MAX_SIZE_LINE, songFile); //skip empty line
    fgets(line, MAX_SIZE_LINE, songFile); // skip Index line 1 2 3 4 5 6 7 .....

    int compt_ligne=0;  //counter that will give the number of ticks of the song
    char *delim ="|\n"; //use '|' and '\n' as a delimiter for strtok, to browse every box one by one (box separated by '|')
    char *token;

    while ( ! feof( songFile ) ) {  //while it's not the end of the file

        fgets(line, MAX_SIZE_LINE, songFile);   //get the line and put it in line
        int compt_colonne = 0; //value of the box
        int compt_note = 0; //counter that counts where we are in the array of note of a line of the ticktab of the song

        token = strtok(line, delim);    //take the first token

        while (token != NULL) { //while it's not the end of the line, browse the line box by box

            if (token[0] == '^' || token[0] == 'x') {   //if there is a note
                mySong.tickTab[compt_ligne].note[compt_note] = compt_colonne;
                //add the value of the note in the array of note of tickTab at the right line
                compt_note++; //so we go to the next index of the array of note
            }
            if (token[0] == '^') { //if it is an accentuated note
                mySong.tickTab[compt_ligne].accent = 1; //put the accent of the line at 1
            }

            token = strtok(NULL, delim);    //goes to the next token (so next box)
            compt_colonne++;
        }
        compt_ligne++;  //line is finished, goes to the next
    }
    mySong.nTicks=compt_ligne;
    return mySong;
}

/**
 * Read a txt file to fill an ams file
 * @param txtFileName name of the txt file
 * @param amsFileName name of the ams file
 */
void createAMS(char* txtFileName, char* amsFileName){
    //opening the txt file
    FILE * txt = NULL;
    txt = fopen(txtFileName,"r");
    if (txt == NULL){
        printf("Error file not found !\n");
        exit(0);
    }
    //opening the ams file
    FILE * ams = NULL;
    ams = fopen(amsFileName,"w");
    if (ams == NULL){
        printf("Error file not found !\n");
        exit(0);
    }

    createHeader(txt,ams);

    //initializing the array of note, filling it all with empty note at first
    char tableau_ticks[MAX_NUMBER_TICKS][60];
    for (int i=0;i<MAX_NUMBER_TICKS;i++){
        for (int j=0;j<60;j++){
            tableau_ticks[i][j]=' ';
        }
    }

    int nb_ligne=0;
    createTab(&nb_ligne, txt, tableau_ticks);
    writeTab(&nb_ligne,ams,tableau_ticks);

    fclose(txt);
    fclose(ams);
}

/**
 * Create the "header" of the ams file thanks to the header of the txt file
 * @param txt name of the txt file
 * @param ams name of the ams file
 */
void createHeader(FILE* txt, FILE* ams){
    char line[MAX_SIZE_LINE];   //buffer that will stock a line

    //get the title and put it in the ams
    fgets(line,MAX_SIZE_TITLE,txt);
    printf("%s",line);
    fputs(line,ams);

    //get the tempo and put it in the ams
    fgets(line,MAX_SIZE_TITLE,txt);
    printf("%s\n",line);
    fputs(line,ams);

    fgets(line,MAX_SIZE_TITLE,txt);
    fputs("\r\n",ams);

    //creating first line of the tab
    char numeros[MAX_SIZE_LINE];
    sprintf(numeros,"    ");
    for (int i=1;i<=60;i++){
        sprintf(numeros+strlen(numeros), "%02d ",i);
    }
    sprintf(numeros+strlen(numeros),"\r\n");
    fputs(numeros,ams);
}

/**
 * Create an array of note by reading the txt file
 * @param nb_ligne get the number of tick of the file, that will be used in funcion writeTab
 * @param txt name of the txt file
 * @param tableau_ticks the array of note of the file
 */
void createTab(int *nb_ligne, FILE* txt, char tableau_ticks[MAX_NUMBER_TICKS][60]){
    char line[MAX_SIZE_LINE];
    char *delim =","; //use ',' as a delimiter for strtok, to browse every note of the line one by one (box separated by '|')
    char *token;
    int valeur[]={10,12,1,3,5,6,8}; //Array of values of note, from A to G
    while ( ! feof( txt ) ) {   //we browse to the end of the file
        fgets(line, MAX_SIZE_LINE, txt);    //get the actual line
        if (line[0] != '\n' && line[0] != '\r' && line[0] != '\0') {    //to not crash when the is an empty line

            token = strtok(line, delim); //take the first token of the line

            while (token != NULL) { //while there's still a note (it's not the end of the line)
                int compt;  //value of the note
                int decalage = 0;  //counts the number of shifts in the line

                if (token[0] == ' ') {  //if token starts by a space, one more shift to get the duration of the note
                    decalage += 1;
                }
                char letter = token[0 + decalage];  //get the letter of the note
                int index = letter-'A'; //get the index of the letter in the array valeur

                char number_char=token[1 + decalage];   //get the number of the note
                int number=number_char-48;  //put the number to int (ASCII)

                compt = valeur[index] + (number - 1) * 12;  //value of C2 = 1 + 12*(2-1) = 13 (1 is the value of C in the array)
                if (token[2 + decalage] == '#') {   //if it's a dieze note
                    compt += 1;    //add 1 to the value of the note
                    decalage += 1;  //one more shift to get the duration of the note
                }
                printf("%d | ", compt);

                int nb_tick = 0;    //count number of tick the note will last depending on the letter
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

                ///put the note for x tick in the tab, starting at our line, on the column of the value of the note
                for (int i = 0; i < nb_tick; i++) {
                    if (i == 0) { //first tick of the note is accentuated
                        tableau_ticks[*nb_ligne + i][compt - 1] = '^';
                    } else {    //the others are not
                        tableau_ticks[*nb_ligne + i][compt - 1] = 'x';
                    }
                }
                token = strtok(NULL, delim);    //goes to the next token
            }
        }
        printf("\n");
        *nb_ligne+=1;   //when no more token, goes to next line
    }
}

/**
 * Write the array of note on the ams file reading the array of note
 * @param nb_ligne
 * @param ams name of the ams file
 * @param tableau_ticks the array of note
 */
void writeTab(int *nb_ligne, FILE* ams, char tableau_ticks[MAX_NUMBER_TICKS][60]){
    for(int i=0;i<*nb_ligne;i++){ //searching the tab line by line
        char line[MAX_SIZE_LINE];   //buffer in which we will fill the line to put in the file
        sprintf(line,"%03d|",i+1);  //puting the actual number of the line
        printf("%s",line);
        for (int j=0;j<60;j++){ //searching every box of the line
            printf("%c |",tableau_ticks[i][j]);
            sprintf(line + strlen(line),"%c |",tableau_ticks[i][j]);    //add to the line the actual note
        }
        if (i!= (*nb_ligne)-1) {    //if it's not last line
            printf("\n");
            sprintf(line + strlen(line), "\r\n");   //goes to next line
        }
        fputs(line,ams);    //put the line in the ams
    }
}
