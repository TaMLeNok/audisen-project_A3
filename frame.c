/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"



void createInitFrame(s_song mySong, char* frame){
    int checksum;
    sprintf(frame,"#%s,%d,%d*",mySong.title,mySong.tpm,mySong.nTicks);
    checksum = calculate_checksum(frame + 1); // Commence le checksum après le #
    sprintf(frame + strlen(frame),"%02x\r\n",checksum); //convertie le checksum en hexa et le rajoute à la trame

}

void createTickFrame(s_tick myTick, char* frame){

    int checksum;
    int mode = 1; // 1 par défaut
    sprintf(frame,"#%d,%d,%02d,%02d,%02d,%02d*",mode,myTick.accent,myTick.note[0],myTick.note[1],myTick.note[2],myTick.note[3]);
    checksum = calculate_checksum(frame + 1); // Commence le checksum après le #
    sprintf(frame + strlen(frame),"%02x\r\n",checksum); //convertie le checksum en hexa et le rajoute à la trame


}
