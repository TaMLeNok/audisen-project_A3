#include "define.h"

void string_tolower(char * song_filename){

    for (int i = 0; i < strlen(song_filename); i++){
        song_filename[i] = (char)tolower((int)song_filename[i]);
    }

}
