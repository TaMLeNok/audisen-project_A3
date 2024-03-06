/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "autotests.h"

int main(){
    printf("Demarrage du projet AUDISEN\n");
/*
    FILE * playlist = NULL;
    char title[MAX_SONGNAME_SIZE];
    playlist = initAMP("Playlist.amp");
    readAMP(playlist,title);
    closeAMP(playlist);*
    */

   /* s_song OE;
    OE = readAMS("bohemian_rhapsody.ams");
    char frame[INIT_FRAME_MAX_SIZE];
    char frame2[TICK_FRAME_SIZE];
    createInitFrame(OE,frame);
    printf("%s",frame);
    createTickFrame(OE.tickTab[0],frame2);
    printf("%s",frame2);*/

    /* Autotest*/

    testReadAMP();
    testReadAMS();
    testCreateAMS();
    testFrame();



    return 0;
}