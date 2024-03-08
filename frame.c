/**
 * @authors Lelievre Tom Bellenger Maxime GroupePJ2 Caen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"

/**This function is calculating the checksum of our frame
 *
 * @param content
 * @return
 */
int calculate_checksum(const char * content){
    int checksum =0;
    int i = 0;
    while(content[i]!='*'){ // Will stop the loop when there is a * in our frame
        checksum^=content[i];
        i++;
    }
    return checksum;
}

/** Create a frame for a title song name
 *
 * @param mySong
 * @param frame
 */
void createInitFrame(s_song mySong, char* frame){

    int checksum;
    sprintf(frame,"#%s,%d,%d*",mySong.title,mySong.tpm,mySong.nTicks);
    checksum = calculate_checksum(frame + 1); // Will start the cheksum after the "#"
    sprintf(frame + strlen(frame),"%02x\r\n",checksum); //Will convert into Hex the cheksum and add it to our frame

}


/**Create a frame for a tick
 *
 * @param myTick
 * @param frame
 */
void createTickFrame(s_tick myTick, char* frame){

    int checksum;
    int mode = 0; // 0  default mode
    sprintf(frame,"#%d,%d,%02d,%02d,%02d,%02d*",mode,myTick.accent,myTick.note[0],myTick.note[1],myTick.note[2],myTick.note[3]);
    checksum = calculate_checksum(frame + 1); // Will start the cheksum after the "#"
    sprintf(frame + strlen(frame),"%02x\r\n",checksum); //Will convert into Hex the cheksum and add it to our frame


}
