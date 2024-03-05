/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "ams.h"


s_song readAMS(char* fileName){
	
	s_song mySong;

	FILE *songFile;
	songFile=fopen(fileName,"r");
	if ( songFile == NULL ) {
		printf( "Cannot open file\n");
		mySong.nTicks=0;
		mySong.tpm=0;
		for (int i=0;i<MAX_NUMBER_TICKS;i++){
			for(int j=0;j<4;j++) {
				mySong.tickTab[i].note[j] = 0;
			}
		}
		mySong.title[0]='\0';

		repr_song(mySong);
		return mySong;
	}
	char line[MAX_SIZE_LINE]; // buffer de lecture
	char titre[MAX_SONGNAME_SIZE];
	int tempo;

	fgets(mySong.title, MAX_SONGNAME_SIZE, songFile);

	fgets(line, MAX_SIZE_LINE, songFile);
	mySong.tpm=atoi(line);

	printf("%s",mySong.title);
	printf("%d\n",mySong.tpm);

	fgets(line, MAX_SIZE_LINE, songFile); //saute la ligne
	fgets(line, MAX_SIZE_LINE, songFile); //saute la ligne
	int compt_ligne=0;
	int compt_note=0;

	while ( ! feof( songFile ) ) {

		fgets(line, MAX_SIZE_LINE, songFile);
		printf("%s", line);
	}


	return mySong;


}


void createAMS(char* txtFileName, char* amsFileName){


}