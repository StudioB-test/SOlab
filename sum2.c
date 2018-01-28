/*
* ESERCIZIO ESAME LAB
* SOMMA PARALLELA CON DUE THREAD (PROCESSI IN CASO DI PIPE)
* Scrivere un programma che computa la somma di n nuerm interi utilizzando due processi.
* il programmma deve creare 3 diversi thread: un generatpre e due sommatori.
* ###---SOMMATORE 1---###
* I DUE PROCESSI COMPUTANO LA SOMMA
*/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define PNAME1 "/tmp/aPipe1"
#define PNAME2 "/tmp/aPipe2"
#define N 2

int main() {
	int fd, fr, n, s = 0, j;
	char leggi;
	char message[20];

	//mkfifo(PNAME1,0666);	// crea la pipe con nome, se esiste gia' non fa nulla
  mkfifo(PNAME2,0666);



	if ( (fr = open (PNAME2,O_RDONLY)) < 0 ) { // apre la pipe in lettura
		perror("errore apertura pipe");
		exit(1);
	}

	while (read(fr,&leggi,1)) {	// legge un carattere alla volta fino a EOF
		n = leggi - '0';
		s = s + n;
	}

	printf("questo è s: %d \n",s);

	close(fr);

	if ( (fr = open(PNAME2,O_WRONLY)) < 0 ) {	// apre la pipe in scrittura
		perror("errore apertura pipe");
		exit(1);
	}
	sprintf(message, "%d", s);
	write (fr,message,strlen(message));

	close(fr);	// chiude il descrittore
	return 0;
}
