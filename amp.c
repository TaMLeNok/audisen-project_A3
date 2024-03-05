/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <ctype.h>
#include "define.h"
#include "amp.h"




FILE* initAMP(char* filename){

    FILE * pf = NULL;
    pf = fopen(filename,"r");
    if (pf == NULL){
        printf("Error file not found !\n");
        return pf;
    }
    else{
        printf("File found !\n");
        return pf;
    }
}

void readAMP(FILE* pf, char * song_filename){

    fgets(song_filename, MAX_SONGNAME_SIZE, pf);
    string_tolower(song_filename);
    string_replace(song_filename);
    printf("%s\n",song_filename);
}

void closeAMP(FILE* pf){
    if (pf){
        fclose(pf);
        printf("File found and closed !\n");
    }
    else{
        printf("File not found and not closed !\n");
    }
}