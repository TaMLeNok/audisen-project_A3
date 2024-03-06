#include "define.h"

void string_tolower(char * song_filename){

    for (int i = 0; i < strlen(song_filename); i++){
        song_filename[i] = (char)tolower((int)song_filename[i]);
    }
}

void string_replace(char *song_filename) {
    char new_song_filename[MAX_SONGNAME_SIZE];
    for (int i = 0; i < MAX_SIZE_TITLE; i++) {
        new_song_filename[i] = '\0';
    }

    int decalage = 0;
    for(int i = 0; i < strlen(song_filename); i++) {
        if (song_filename[i] != '\n' && song_filename[i] != '\r') {
            if (isalpha(song_filename[i])) {
                new_song_filename[i - decalage] = song_filename[i];
            } else {
                if (new_song_filename[i - 1 - decalage] != '_') {
                    new_song_filename[i - decalage] = '_';
                } else {
                    decalage++;
                }
            }
        }
    }
    strcpy(song_filename, new_song_filename);
    strcat(song_filename, ".ams");
}

void repr_song(s_song song){
    printf("titre : %s\n",song.title);
    printf("tpm : %d\n",song.tpm);
    printf("nTicks : %d\n",song.nTicks);
    printf("ticks tab : \n");
    for(int i=0;i<song.nTicks;i++){
        for(int j=0;j<4;j++){
            printf("%d | ", song.tickTab[i].note[j]);
        }
        printf(" accent : %d\n",song.tickTab[i].accent);
    }
}

int calculate_checksum(const char * content){
    int checksum =0;
    int i = 0;
    while(content[i]!='*'){
        checksum^=content[i];
        i++;
    }
    return checksum;
}

int get_note(char* token){
    int compt=0;

    return compt;


}


