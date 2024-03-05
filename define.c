#include "define.h"

void string_tolower(char * song_filename){

    for (int i = 0; i < strlen(song_filename); i++){
        song_filename[i] = (char)tolower((int)song_filename[i]);
    }
}

void string_replace(char * song_filename){

    char new_song_filename[MAX_SIZE_TITLE];
    int j=0;
    for(int i=0;i< strlen(song_filename); i++) {
        if (isalnum((int) song_filename[i])) {
            new_song_filename[i - j] = song_filename[i];
        } else {
            if (new_song_filename[i - 1 - j] != '_') {
                new_song_filename[i - j] = '_';
            }else{
                j++;
            }

        }
    }
    strcpy(song_filename,new_song_filename);
}

void repr_song(s_song song){
    printf("titre : %s\n",song.title);
    printf("tpm : %d\n",song.tpm);
    printf("nTicks : %d\n",song.nTicks);
    printf("ticks tab : ");
    for(int i=0;i<song.nTicks;i++){
        for(int j=0;j<4;j++){
            printf("%d | ", song.tickTab[i].note[j]);
        }
        printf(" accent : %d\n",song.tickTab[i].accent);
    }
}