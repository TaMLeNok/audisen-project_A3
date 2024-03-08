/**
 * @authors Lelievre Tom Bellenger Maxime GroupePJ2 Caen
 */

#ifndef AUDISEN2024_AMP_H
#define AUDISEN2024_AMP_H

#include "define.h"



void string_tolower(char * song_filename);
void string_replace(char *song_filename);

FILE* initAMP(char* filename);

void readAMP(FILE* pf, char * song_filename);

void closeAMP(FILE* pf);




#endif //AUDISEN2024_AMP_H