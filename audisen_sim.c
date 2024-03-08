/**
 * @authors Lelievre Tom Bellenger Maxime GroupePJ2 Caen
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "autotests.h"

/**Thsi function create an frm file
 *
 * @param name_playlist
 * @param playlist_filename
 */
void create_frm(char * name_playlist, char * playlist_filename){
    FILE * playlist = NULL; // Stock the playlist amp file
    FILE * frm = NULL; // Oour frm file
    frm = fopen(playlist_filename,"w"); // Open in write mode
    if (frm == NULL){
        printf("Error file not found !\n");
        exit(0);
    }
    s_song song; // Will stock the song struct (tick, tpm, note, name)
    char frame_title[INIT_FRAME_MAX_SIZE]; // Will stock the frame title
    char frame_tick[TICK_FRAME_SIZE]; // Will stock the frame tick
    char title[MAX_SONGNAME_SIZE]; // Stock the name song of read amp (Like bohemian_rhapsody.ams)
    playlist = initAMP(name_playlist);

    // While boucle to read all the playlist.amp file
    while (!feof(playlist)) {
        readAMP(playlist, title);
        song = readAMS(title);

        // Condition to pass the file that read ams cant open
        if (strlen(song.title) != 0) {
            // Delete the '\n' in the song title name
            song.title[strlen(song.title)-1]='\0';
            createInitFrame(song, frame_title);
            fprintf(frm,"%s",frame_title); // Write the title frame in the frm file
            for (int i = 0; i < song.nTicks; ++i) {
                createTickFrame(song.tickTab[i],frame_tick);
                fprintf(frm,"%s",frame_tick); // Write the tick frame in the frm file
            }
        }else{
            printf("File doesnt exist ! No trame for this file");
        }

    }
    closeAMP(playlist);
    fclose(frm);
}

/**
 * Main with all of the autotest
 * @return
 */
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
    //char txtFileName[] = "blue.txt";
    // char amsFileName[] = "blue.ams";

    //createAMS(txtFileName,amsFileName);
    create_frm("Playlist.amp","AAAA.frm");

    testCreateAMS();
    testReadAMP();
    testReadAMS();
    testFrame();

    return 0;
}