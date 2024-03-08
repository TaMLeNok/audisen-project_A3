/**
 * @authors Lelievre Tom Bellenger Maxime GroupePJ2 Caen
 */

#ifndef AUDISEN2024_AMS_H
#define AUDISEN2024_AMS_H

#include "define.h"

struct song initSong();
struct song readAMS(char* fileName);
void createAMS(char* txtFileName, char* amsFileName);
void createHeader(FILE* txt, FILE* ams);
void createTab(int *nb_ligne, FILE* txt, char tableau_ticks[MAX_NUMBER_TICKS][60]);
void writeTab(int *nb_ligne, FILE* ams, char tableau_ticks[MAX_NUMBER_TICKS][60]);


#endif //AUDISEN2024
