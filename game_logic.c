#include <stdio.h>
#include <stdlib.h>
#include <termios.h> /* per usare il terminale linux x input */
#include "game_logic.h"

#define START_STR 81
#define SIDE 9

/* this refreshes the console and displays it */
void drawBoard(int numbers[][9]) {
	
	int i, j;

	system("clear"); /* per pulire la console. Se esegui su windows è cls, non clear */

	for(i = 0; i < SIDE; i++) {

		/* print horizontal lines */
		if(i % 3 == 0) {

			printf("+-------+-------+-------+ \n");
		}
		
 
		for(j = 0; j < SIDE; j++) {

			/* print vertical lines */
			if(j % 3 == 0) {

				printf("| ");
			}

			if(numbers[i][j] != 0) {

				printf("%d ", numbers[i][j]);
			} else {

				printf("· ");
			}
		}

		printf("|\n");
	}

	printf("+-------+-------+-------+ \n");
	printf("\n---------------------------------------\n\n");
}


/* main game loop: mostra il menu di scelta e gestisce l'input */
void displayMenu() {
	
	int scelta, mat[SIDE][SIDE];
	char startingString[START_STR + 1], outGameString[START_STR + 1];

	int x, y, val;
	
	do {
		
		printf("1 - avvia una nuova partita\n");
		printf("2 - inserisci valore\n");
		printf("3 - cancella valore\n");
		printf("4 - verifica la soluzione attuale\n");
		printf("5 - carica una soluzione e verificala\n");
		printf("6 - riavvia partita attuale\n"); /* QUESTO LO FAI CHE QUANDO LO FAI PARTIRE SCRIVI SU UN FILE E QUANDO CHIAMI QUESTO LEGGI */
		printf("0 - esci\n");

		
		scanf("%d", &scelta);

		switch(scelta) {
		
			case 1: {
				
				printf("Inserisci stringa iniziale:\n");
				scanf("%s", startingString);
				/* METTERE CHECK ERRORE */
				startGame(startingString, mat, outGameString);
				break;
			}
			case 2: {

				int isSceltaCorretta;

				do {

					system("clear");
					printf("Dimmi le coordinate (da 1 a 9):\nX: ");
					scanf("%d", &x);

					while(!(x >= 1 && x <= 9)) {

						system("clear");
						printf("Errore: La coordinata deve essere tra 1 e 9: Reinserire\n");
						scanf("%d", &x);
					}

					system("clear");
					printf("Dimmi le coordinate (da 1 a 9):\nY: ");

					scanf("%d", &y);

					while(!(y >= 1 && y <= 9)) {

						system("clear");
						printf("Errore: La coordinata deve essere tra 1 e 9: Reinserire\n");
						scanf("%d", &y);
					}

					printf("[ %d, %d ] è la scelta corretta (1: si, 0: no)?\n", x, y);
					scanf("%d", &isSceltaCorretta);


				} while(!isSceltaCorretta);

				system("clear");
				printf("Dimmi il valore da inserire (da 1 a 9): ");
				scanf("%d", &val);

				while(!(val >= 1 && val <= 9)) {

					system("clear");
					printf("Errore: Il valore deve essere tra 1 e 9: Reinserire\n");
					scanf("%d", &val);
				}

				/* aggiorna la matrice che contiene tutti i valori numerici */
				mat[x - 1][y - 1] = val;

				/* aggiorna la stringa di gioco (mi muovo di 9*y per la riga, poi aggiungo y per la colonna) */
				*(outGameString + SIDE*x + y) = val + '0'; /* converti val nel carattere corrispondente */

				/* refresho la board */
				drawBoard(mat);
				break;
			}
			case 3: {
				
				int isSceltaCorretta;

				do {

					system("clear");
					printf("Dimmi le coordinate (da 1 a 9):\nX: ");
					scanf("%d", &x);

					while(!(x >= 1 && x <= 9)) {

						system("clear");
						printf("Errore: La coordinata deve essere tra 1 e 9: Reinserire\n");
						scanf("%d", &x);
					}

					system("clear");
					printf("Dimmi le coordinate (da 1 a 9):\nY: ");

					scanf("%d", &y);

					while(!(y >= 1 && y <= 9)) {

						system("clear");
						printf("Errore: La coordinata deve essere tra 1 e 9: Reinserire\n");
						scanf("%d", &y);
					}

					printf("[ %d, %d ] è la scelta corretta (1: si, 0: no)?\n", x, y);
					scanf("%d", &isSceltaCorretta);


				} while(!isSceltaCorretta);

				/* aggiorna la matrice che contiene tutti i valori numerici */
				mat[x - 1][y - 1] = 0;

				/* aggiorna la stringa di gioco (mi muovo di 9*y per la riga, poi aggiungo y per la colonna) */
				*(outGameString + SIDE*x + y) = '_';

				/* refresho la board */
				drawBoard(mat);
				break;

			}
			case 4: {

				system("clear");

				if(isResolved(mat)) {

					printf("Risolto\n");
				} else {

					printf("Non risolto\n");
				}

				break;
			}
			case 5: {

				int i, j, pressed = 0;

				printf("Inserisci stringa da controllare:\n");
				scanf("%s", startingString);
				/* METTERE CHECK ERRORE */
				startGame(startingString, mat, outGameString);

				for(i = 0; startingString[i] != '\0'; i++) {

					/* la matrice è linearizzata e allineata con il puntatore quindi posso fare così e stica */
					/* Se il carattere è '_', ' ', o '-' metto 0, altrimenti metto il numero corrispondente al carattere */ 
					if(startingString[i] == '_' || startingString[i] == ' ' || startingString[i] == '-') {

						*(*mat + i) = 0;
					} else {
			
						*(*mat + i) = startingString[i] - '0';
					}

				}
				system("clear");

				if(isResolved(mat)) {

					printf("Risolto\n");
				} else {

					printf("Non risolto\n");
				}
				break;
			}
			case 6: {


				
			}
			case 0: {
				
				system("clear");
				printf("Grazie per aver giocato\n");
				
				break;
			}
			default: {
			
				printf("Scelta errata. Scegli un valore da 1 a 6");
			}
		}	
	} while(scelta != 0);
}

/* questa viene chiamata solo se la stringa iniziale è corretta quindi non fai controlli */
/* inizializza la matrice e la stampa */
void startGame(char startingString[], int mat[][SIDE], char outGameString[]) {
	
	int i, j;

	for(i = 0; startingString[i] != '\0'; i++) {

		/* la matrice è linearizzata e allineata con il puntatore quindi posso fare così e stica */
		/* Se il carattere è '_', ' ', o '-' metto 0, altrimenti metto il numero corrispondente al carattere */ 
		if(startingString[i] == '_' || startingString[i] == ' ' || startingString[i] == '-') {

			*(*mat + i) = 0;
		} else {
			
			*(*mat + i) = startingString[i] - '0';
		}

		/* copio la stringa di partenza in una stringa nuova. Questa viene usata per tenere traccia dello stato del sudoku */
		outGameString[i] = startingString[i];
	}

	/* aggiungo terminatore */
	outGameString[i] = '\0';

	drawBoard(mat);
}

int isResolved(int mat[][SIDE]) {

	int i, j, k, h, s, row, col;
	int sommaRiga, sommaCol;
	int sommaRC = 45;
	int risolvibile; /* flag che mi dice se è risolvibile */
	int used[10]; /* tiene dentro tutti i valori già apparsi nella sottomatrice */
	
	/*
		NOTA: L'ARRAY LO FACCIO DI 10 ELEMENTI PK È PIU' COMODO LAVORARCI SENZA SMAZZARE TROPPO CON GLI INDICI
		CON 10 ELEMENTI IL NUMERO 1 CORRISPONDE ALL'INDICE 1, IL 2 AL 2 E COSI' VIA
		MENTRE CON 9 IL NUMERO 1 CORRISPONDE ALL'INDICE 0, IL 2 ALL'1 E COSI' VIA
	*/
	
	
	/*
		controllo se ogni numero compare una sola volta in tutta la riga/colonna 
		questo funziona pk, se ogni numero compare una sola volta nella riga/colonna,
		allora la somma di tutti gli elementi (da 1 a 9) è sommaRC = 9*(9+1)/2 = 45
	*/
	
	/*
		per ogni riga, se un numero compare più di 1 volta, allora non è risolvibile
	*/
	for(i = 0, risolvibile = 1; i < SIDE; i++) {


		/* imposto a 0 tutto l'array */
		for(s = 0; s < 10; s++) {

			used[s] = 0;
		}

		
		for(j = 0; j < SIDE; j++) {
			
			if(used[mat[i][j]] == 1) {

				risolvibile = 0;
			} else {

				used[mat[i][j]] = 1;
			}
		}

		printf("Riga %d: Risolvibile: %d\n", i, risolvibile);
	}

	/*
		per ogni colonna, se un numero compare più di 1 volta, allora non è risolvibile
	*/
	for(j = 0; j < SIDE; j++) {


		/* imposto a 0 tutto l'array */
		for(s = 0; s < 10; s++) {

			used[s] = 0;
		}
		
		for(i = 0, sommaCol = 0; i < SIDE; i++) {
			
			if(used[mat[i][j]] == 1) {

				risolvibile = 0;
			} else {

				used[mat[i][j]] = 1;
			}
		}

		printf("Colonna %d: Risolvibile: %d\n", j, risolvibile);
	}

	/* C'E' UN ERRORE DA QUALCHE PARTE QUI DENTRO PK SUL CHECK RIGHE/COLONNE VA MA QUI NO. CONTROLLA */
	
	
	for(i = 0; i < SIDE/3; i++) {
		
		for(j = 0; j < SIDE/3; j++) {
			
			row = (SIDE/3)*i; /* riga su cui lavorare */
			col = (SIDE/3)*j; /* colonna su cui lavorare */
			
			/* resetto l'array con i contatori per lavorare sulla prossima sottomatrice */
			for(s = 0; s < 10; s++) {
				
				used[s] = 0;
			}
			
			for(k = row; k < row + (SIDE/3); k++) {
				
                for(h = col; h < col + (SIDE/3); h++) {

					//printf("%d ", mat[k][h]);
					
                    if(mat[k][h] == 0) { /* nel sudoku non ci possono essere celle con 0. Ridondante pk ho già fatto il controllo prima ma non si sa mai */
						
						risolvibile = 0;

					} else if(used[mat[k][h]] == 1) { /* questo controlla se alla cella numero mat[k][h] c'è 1, che significa che il valore è già apparso */
						
						risolvibile = 0;
					
					} else if(used[mat[k][h]]) {
						
						risolvibile = 0;
					
					} else {

					/*
						se tutti e 3 i controlli sono andati a buon fine, significa che questo numero non c'era prima
						a questo punto lo devo mettere in used
					*/
					//used[mat[k][h] - '0'] = 1; 
					used[mat[k][h]] = 1;
					}
				}
			}
		}
	}
	
	return risolvibile;
}