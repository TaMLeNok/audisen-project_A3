/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "ams.h"


s_song readAMS(char* fileName){
	
	s_song mySong;

	FILE * songFile;
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

		return mySong;
	}
	char line[MAX_SIZE_LINE]; // buffer de lecture
	char titre[MAX_SONGNAME_SIZE];
	int tempo;

	fgets(mySong.title, MAX_SONGNAME_SIZE, songFile);
	char new_title[MAX_SONGNAME_SIZE];


	fgets(line, MAX_SIZE_LINE, songFile);
	mySong.tpm=atoi(line)*2;

	fgets(line, MAX_SIZE_LINE, songFile); //saute la ligne
	fgets(line, MAX_SIZE_LINE, songFile); //saute la ligne

	int compt_ligne=0;

	char *delim ="|\n";
	char *token;

	while ( ! feof( songFile ) ) {

		fgets(line, MAX_SIZE_LINE, songFile);
		int compt_colonne = 0;
		int compt_note = 0;

		token = strtok(line, delim);

		while (token != NULL) {

			if (token[0] == '^' || token[0] == 'x') {
				mySong.tickTab[compt_ligne].note[compt_note] = compt_colonne;
				compt_note++;
			}
			if (token[0] == '^') {
				mySong.tickTab[compt_ligne].accent = 1;
			}

			token = strtok(NULL, delim);
			compt_colonne++;
		}
		compt_ligne++;
	}
	mySong.nTicks=compt_ligne;

	return mySong;


}


void createAMS(char* txtFileName, char* amsFileName){



}