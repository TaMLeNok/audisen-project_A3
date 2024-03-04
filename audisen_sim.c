/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdio.h>
#include "amp.h"


int main(){
    printf("Demarrage du projet AUDISEN\n");
    FILE * playlist = NULL;
    char * title;
    playlist = initAMP("ma_playlist.amp");
    readAMP(playlist,title);
    closeAMP(playlist);


    return 0;
}