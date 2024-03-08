/**
 * @authors Lelievre Tom Bellenger Maxime GroupePJ2 Caen
 */

#include <ctype.h>
#include "define.h"
#include "amp.h"


/**Replace the special char in the song name in our amp file
 *
 * @param song_filename
 */
void string_replace(char *song_filename) {
    char new_song_filename[MAX_SONGNAME_SIZE];
    // Init a tab with '\0' everywhere
    for (int i = 0; i < MAX_SIZE_TITLE; i++) {
        new_song_filename[i] = '\0';
    }

    int decalage = 0;
    for(int i = 0; i < strlen(song_filename); i++) {
        // Skip the \r and \n char
        if (song_filename[i] != '\n' && song_filename[i] != '\r') {

            // If we have an alpha we write it in our new tab
            if (isalpha(song_filename[i])) {
                new_song_filename[i - decalage] = song_filename[i];
            } else {
            // else we replace it by a underscore if the previous one wasnt a underscore
                if (new_song_filename[i - 1 - decalage] != '_') {
                    new_song_filename[i - decalage] = '_';
                } else {
                    // if the previous one was an underscore we just increment for continue our search in our tab
                    decalage++;
                }
            }
        }
    }

    // we copy this new string in our actual string
    strcpy(song_filename, new_song_filename);
    strcat(song_filename, ".ams"); // and we add the file ext '.ams'
}

/**Lower all the alpha
 *
 * @param song_filename
 */
void string_tolower(char * song_filename){

    for (int i = 0; i < strlen(song_filename); i++){
        song_filename[i] = (char)tolower((int)song_filename[i]);
    }
}

/**This function open an amp file and return it if the file exist
 *
 * @param filename
 * @return amp file
 */

/**Open a amp file if he exists
 *
 * @param filename
 * @return
 */
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

/** This function will read the amp file and format the string in it
 *
 * @param pf
 * @param song_filename
 */
void readAMP(FILE* pf, char * song_filename){

        fgets(song_filename, MAX_SONGNAME_SIZE, pf);
        string_tolower(song_filename);
        string_replace(song_filename);
}


/** Close the amp file
 *
 * @param pf
 */
void closeAMP(FILE* pf){
    if (pf){
        fclose(pf);
        printf("File found and closed !\n");
    }
    else{
        printf("File not found and not closed !\n");
    }
}