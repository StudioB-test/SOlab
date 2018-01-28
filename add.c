/*
* ESERCIZIO ESAME LAB
* SOMMA PARALLELA CON DUE THREAD (PROCESSI IN CASO DI PIPE)
* Scrivere un programma che computa la somma di n nuerm interi utilizzando due processi.
* il programmma deve creare 3 diversi thread: un generatpre e due sommatori.
* ###---GENERATORE---###
* Genera una sewuenza di n numeri casuali, attendere i risultati e stamparne la somma-:
* per  N volte  scegli un n casuale tra 1 e 100
*   	1.invia n. alternativamente. a uno dei procsssi seguenti
*   	2. attente le due somme s1 e s2 e stampa s1+s2
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
#define N 4

int main() {
	int fd, fr, i, s, p, n, j=0;
	char leggi;
	char message[20];

	srand(time(NULL));

	mkfifo(PNAME1,0666);	// crea la pipe con nome, se esiste gia' non fa nulla
  mkfifo(PNAME2,0666);

	if ( (fd = open(PNAME1,O_WRONLY)) < 0 ) {	// apre la pipe in scrittura
		perror("errore apertura pipe");
		exit(1);
	}

	if ( (fr = open(PNAME2,O_WRONLY)) < 0 ) {	// apre la pipe in scrittura
		perror("errore apertura pipe");
		exit(1);
	}

	for (j=0; j<N; j++){		// invia N volte il numero casuale
		if( (j % 2)==0 ){
			sprintf(message, "%d", j);
			write (fd,message,strlen(message));
		} else {
			sprintf(message, "%d", j);
			write (fr,message,strlen(message));
		}
	}

	close(fd);
	close(fr);

	if ( (fd = open (PNAME1,O_RDONLY)) < 0 ) { // apre la pipe in lettura
		perror("errore apertura pipe");
		exit(1);
	}
	if ( (fr = open (PNAME2,O_RDONLY)) < 0 ) { // apre la pipe in lettura
		perror("errore apertura pipe");
		exit(1);
	}

	while (read(fd,&leggi,1)) {	// legge un carattere alla volta fino a EOF
		n = leggi - '0';
	}

	close(fd);

	while (read(fr,&leggi,1)) {	// legge un carattere alla volta fino a EOF
		p = leggi - '0';
	}

	close(fr);	// chiude il descrittore

	s = n + p;
	printf("questo è p: %d \n",p);
	printf("questo è n: %d \n",n);
	printf("questo è s: %d \n",s);


	return 0;
}
