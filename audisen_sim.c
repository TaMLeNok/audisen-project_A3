/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "autotests.h"


void create_frm(char * name_playlist, char * playlist_filename){
    FILE * playlist = NULL;
    FILE * frm = NULL;
    frm = fopen(playlist_filename,"w");
    if (frm == NULL){
        printf("Error file not found !\n");
        exit(0);
    }
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
            song.title[strlen(song.title)-1]='\0';
            createInitFrame(song, frame_title);
            fprintf(frm,"%s",frame_title);
            for (int i = 0; i < song.nTicks; ++i) {
                createTickFrame(song.tickTab[i],frame_tick);
                fprintf(frm,"%s",frame_tick);
            }
        }else{
            printf("File doesnt exist ! No trame for this file");
        }

    }
}

int main(){
    printf("Demarrage du projet AUDISEN\n");

    //create_frm("Playlist.amp","Playlist.frm");

    //s_song OE;
    //OE = readAMS("bohemian_rhapsody.ams");
    /*
    closeAMP(playlist);*
    */

   /* s_song OE;
    OE = readAMS("bohemian_rhapsody.ams");
    char frame[INIT_FRAME_MAX_SIZE];
    char frame2[TICK_FRAME_SIZE];
    createInitFrame(OE,frame);
    printf("%s",frame);
    createTickFrame(OE.tickTab[0],frame2);
    printf("%s",frame2);
    */
    //testReadAMS();
    char txtFileName[] = "SlimShady.txt";
    char amsFileName[] = "slim_shady.ams";

    createAMS(txtFileName,amsFileName);

    //testCreateAMS();
    create_frm("oe.apm","oe.frm");

    return 0;
}