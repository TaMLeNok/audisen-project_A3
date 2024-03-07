/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */
#define _WIN32
#include <stdio.h>
#include "ftd2xx.h"
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "usb.h"

void sent_frame(char * name_playlist,FT_HANDLE ftHandle){
    FILE * playlist = NULL;

    s_song song;
    char frame_title[INIT_FRAME_MAX_SIZE];
    char frame_tick[TICK_FRAME_SIZE];
    char title[MAX_SONGNAME_SIZE];
    playlist = initAMP(name_playlist);
    while (!feof(playlist)) {
        readAMP(playlist, title);
        song = readAMS(title);
        repr_song(song);
        if (strlen(song.title) != 0) {
            song.title[strlen(song.title)]='\0';
            createInitFrame(song, frame_title);
            printf("%s",frame_title);
            writeUSB(frame_title,ftHandle);
            for (int i = 0; i < song.nTicks; ++i) {
                createTickFrame(song.tickTab[i],frame_tick);
                printf("%s",frame_tick);
                writeUSB(frame_tick,ftHandle);
            }
            Sleep(1000);
        }else{
            printf("File doesnt exist ! No trame for this file");
        }

    }
}

int main(){
    printf("Demarrage du projet AUDISEN USB\n");
    FT_HANDLE ft_handle;
    ft_handle = initUSB();
    sent_frame("Playlist.amp",ft_handle);
    closeUSB(ft_handle);

    return 0;
}