#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Dichiaro tabella
char tabella[6][7] = { 0 };

// Stampo tabella gioco
void stampoTabella() {
	int riga = 0, col = 0;

	printf("%c", 201);

	for (int i = 0; i < 6; i++) {
		printf("%c%c%c%c", 205, 205, 205, 203);
	}

	printf("%c%c%c%c", 205, 205, 205, 187);

	for (int i = 0; i < 5; i++) {
		printf("\n%c", 186);

		// Stampo le monete nella tabella
		for (int j = 0; j < 7; j++) {
			printf(" ");

			if (tabella[riga][col] == 0) {
				printf(" ");
			}
			else {
				// Imposto il colore del primo giocatore
				if (tabella[riga][col] == '1') {
					// Imposto il colore giallo
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);

					printf(" ");
				}
				// Imposto il colore del secondo giocatore
				else if (tabella[riga][col] == '2') {
					// Imposto il colore giallo
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);

					printf(" ");
				}
				else {
					printf(" ");
				}

				// Imposto il colore di default
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}

			printf(" %c", 186);

			col++;
		}

		riga++;
		col = 0;

		printf("\n%c", 204);

		for (int j = 0; j < 6; j++) {
			printf("%c%c%c%c", 205, 205, 205, 206);
		}

		printf("%c%c%c%c", 205, 205, 205, 185);
	}

	printf("\n%c", 186);

	// Stampo le monete nella tabella
	for (int i = 0; i < 7; i++) {
		printf(" ");

		if (tabella[riga][col] == 0) {
			printf(" ");
		}
		else {
			// Imposto il colore del primo giocatore
			if (tabella[riga][col] == '1') {
				// Imposto il colore giallo
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);

				printf(" ");
			}
			// Imposto il colore del secondo giocatore
			else if (tabella[riga][col] == '2') {
				// Imposto il colore giallo
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);

				printf(" ");
			}
			else {
				printf(" ");
			}

			// Imposto il colore di default
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		col++;

		printf(" %c", 186);
	}

	printf("\n%c", 200);

	for (int i = 0; i < 6; i++) {
		printf("%c%c%c%c", 205, 205, 205, 202);
	}

	printf("%c%c%c%c\n", 205, 205, 205, 188);

	for (int i = 0; i < 7; i++) {
		printf("  %d ", i + 1);
	}
	printf("\n\n");
}

// Controllo vittoria
int controlloVittoria(int riga, int col) {
	// Dichiaro variabili
	int cont = 0;

	// Controllo riga ROWS
	for (int i = 0; i < 7; i++) {
		if (tabella[riga][col] == tabella[riga][i]) {
			cont++;
		}
		else {
			cont = 0;
		}

		if (cont == 4) {
			return 1;
		}
	}

	cont = 0;

	// Controllo colonna COLUMNS
	for (int i = 0; i < 6; i++) {
		if (tabella[riga][col] == tabella[i][col]) {
			cont++;
		}
		else {
			cont = 0;
		}

		if (cont == 4) {
			return 1;
		}
	}

	cont = 0;

	// Controllo diagonali DIAGONALS
	{
		for (int i = 0; i < 4; i++) {
			if (tabella[riga][col] == tabella[riga + i][col - i]) {
				cont++;
			}
			else {
				break;
			}

			if (cont == 4) {
				return 1;
			}
		}

		for (int i = 1; i < 4; i++) {
			if (tabella[riga][col] == tabella[riga - i][col + i]) {
				cont++;
			}
			else {
				break;
			}

			if (cont == 4) {
				return 1;
			}
		}

		cont = 0;

		for (int i = 0; i < 4; i++) {
			if (tabella[riga][col] == tabella[riga + i][col + i]) {
				cont++;
			}
			else {
				break;
			}

			if (cont == 4) {
				return 1;
			}
		}

		for (int i = 1; i < 4; i++) {
			if (tabella[riga][col] == tabella[riga - i][col - i]) {
				cont++;
			}
			else {
				break;
			}

			if (cont == 4) {
				return 1;
			}
		}
	}

	cont = 0;

	// Controllo parità
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (tabella[i][j] != 0) {
				cont++;
			}
			else {
				return 0;
			}

			if (cont == 42) {
				return 2;
			}
		}
	}

	return 0;
}

// Richiesta, controllo e stampa scelta
void inputUtente(int& turno, int& vittoria) {
	// Dichiarazione variabili
	int scelta;
	bool sbagliato = true;

	// Inserimento dati utente
	printf("Dove vuoi mettere la moneta: ");
	scanf("%d", &scelta);

	do {
		// Controllo che la scelta sia corretta
		if (scelta < 1 || scelta > 7) {
			printf("Posizione non valida\nRiprova: ");
			scanf("%d", &scelta);

			// Controllo che la casella non sia occupata
		}
		else {
			for (int i = 5; i >= 0; i--) {
				if (tabella[i][scelta - 1] == 0) {
					if (turno == 0) {
						tabella[i][scelta - 1] = '1';

						// Controllo vittoria
						vittoria = controlloVittoria(i, scelta - 1);

						// Cambio turno giocatore
						turno = 1;
					}
					else {
						tabella[i][scelta - 1] = '2';

						// Controllo vittoria
						vittoria = controlloVittoria(i, scelta - 1);

						// Cambio turno giocatore
						turno = 0;
					}
					sbagliato = false;
					break;
				}
			}

			if (sbagliato) {
				printf("Colonna piena\nRiprova: ");
				scanf("%d", &scelta);
			}
		}
	} while (sbagliato);
}

int main() {
	// Dichiarazione variabili
	int turno = 0;
	int vittoria = 0;
	char currentBoard[3][3];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			currentBoard[i][j] = tabella[i][j];

	do {
		// Stampo la tabella
		stampoTabella();

		// Richiesta, controllo ed stampa scelta
		inputUtente(turno, vittoria);

		// Pulisco la console
		system("cls");
	} while (vittoria == 0);

	// Stampo la tabella
	stampoTabella();

	// Controllo se è il turno del secondo giocatore
	if (turno == 1) {
		printf("Ha vinto il primo giocatore\n");
	}
	else {
		printf("Ha vinto il secondo giocatore\n");
	}

	// Chiudo il programma appena cliccano un tasto qualsiasi
	system("pause");
}