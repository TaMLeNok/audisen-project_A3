/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"

int main(){
    printf("Demarrage du projet AUDISEN\n");
    /*
    FILE * playlist = NULL;
    char * title;
    playlist = initAMP("ma_playlist.amp");
    readAMP(playlist,title);
    closeAMP(playlist);
     */
    s_song OE;
    OE = readAMS("bohemian_rhapsody.ams");
    char frame[INIT_FRAME_MAX_SIZE];
    char frame2[INIT_FRAME_MAX_SIZE];
    createInitFrame(OE,frame);
    printf("%s",frame);
    createTickFrame(OE.tickTab[1],frame2);
    printf("%s",frame2);





    return 0;
}