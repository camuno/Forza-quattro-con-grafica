#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

tabella[6][7] = { 0 };

// Controllo vittoria
int controlloVittoria(int riga, int col) {
	// Dichiaro variabili
	int cont = 0;

	// Controllo riga
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

	// Controllo colonna
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

	// Controllo diagonali
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
		for (int j = 0; j < 7; j++) {
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

int main(void) {
	SetTraceLogLevel(LOG_NONE);

	int screenWidth = 1200;
	int screenHeight = 1040;

	// Inizializzo la finestra
	InitWindow(screenWidth - 1, screenHeight - 2, "Forza Quattro");

	// Inizializzo l'audio
	InitAudioDevice();

	// Carico i suoni
	Sound buttonSound1 = LoadSound("src/assets/button-1.mp3");
	Sound buttonSound2 = LoadSound("src/assets/button-2.mp3");

	// Carico le texture
	Texture2D boardTexture = LoadTexture("src/assets/quadris-board.png");
	Texture2D yellowCoinTexture = LoadTexture("src/assets/yellow-coin.png");
	Texture2D redCoinTexture = LoadTexture("src/assets/red-coin.png");

	// Dichiarazione variabili
	Vector2 boardVector2 = { 0.0f, -1.0f };

	float coinPositionX[7] = {
		boardVector2.x + 28,
		boardVector2.x + 195,
		boardVector2.x + 363,
		boardVector2.x + 530,
		boardVector2.x + 698,
		boardVector2.x + 866,
		boardVector2.x + 1033
	};

	float coinPositionY[6] = {
		boardVector2.y + 16,
		boardVector2.y + 185,
		boardVector2.y + 354,
		boardVector2.y + 522,
		boardVector2.y + 691,
		boardVector2.y + 860,
	};

	Rectangle areaBoard[7] = {
		{0.0f, 0.0f, (boardTexture.width - 25) / 7 + 15, boardTexture.height},
		{areaBoard[0].x + areaBoard[0].width, 0.0f, (boardTexture.width - 25) / 7, boardTexture.height},
		{areaBoard[1].x + areaBoard[1].width, 0.0f, (boardTexture.width - 25) / 7, boardTexture.height},
		{areaBoard[2].x + areaBoard[2].width, 0.0f, (boardTexture.width - 25) / 7, boardTexture.height},
		{areaBoard[3].x + areaBoard[3].width, 0.0f, (boardTexture.width - 25) / 7, boardTexture.height},
		{areaBoard[4].x + areaBoard[4].width, 0.0f, (boardTexture.width - 25) / 7, boardTexture.height},
		{areaBoard[5].x + areaBoard[5].width, 0.0f, (boardTexture.width - 25) / 7 + 10, boardTexture.height}
	};

	int turno = 0, vittoria = 0;
	Vector2 mousePoint = { 0.0f, 0.0f };
	Rectangle againButton = { 450.0f, 457.0f, 300.0f, 50.0f };
	Rectangle exitButton = { 500.0f, 517.0f, 200.0f, 50.0f };

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// Trovo la posizione del mouse
		mousePoint = GetMousePosition();

		// Inizializzo i canvas
		BeginDrawing();

		// Cambio il colore di sfondo
		ClearBackground(RAYWHITE);

		// Stampo la tabella di forza quattro
		DrawTextureEx(boardTexture, boardVector2, 0.0f, 1.0f, RAYWHITE);

		// Stampo le monete nella tabella
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (tabella[i][j] == 1) {
					DrawTexture(yellowCoinTexture, coinPositionX[j], coinPositionY[i], RAYWHITE);
				}
				else if (tabella[i][j] == 2) {
					DrawTexture(redCoinTexture, coinPositionX[j], coinPositionY[i], RAYWHITE);
				}
			}
		}

		if (vittoria != 0) {
			// Cambio il colore di sfondo
			ClearBackground(BLACK);

			// Rendo più scura la tabella
			DrawRectangle(0, 0, 1200, 1040, (Color) { 0, 0, 0, 100 });

			if (turno == 1) {
				DrawText("Ha vinto il primo giocatore", boardTexture.width / 4 - 30, exitButton.y - 200, exitButton.height, WHITE);
			}
			else {
				DrawText("Ha vinto il secondo giocatore", boardTexture.width / 4 - 35, exitButton.y - 200, exitButton.height, WHITE);
			}

			if (CheckCollisionPointRec(mousePoint, exitButton)) {
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
					DrawRectangle(exitButton.x, exitButton.y, exitButton.width, exitButton.height, BEIGE);
				}
				else {
					DrawRectangle(exitButton.x, exitButton.y, exitButton.width, exitButton.height, BROWN);
				}

				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
					break;
				}
			}
			else {
				DrawRectangle(exitButton.x, exitButton.y, exitButton.width, exitButton.height, MAROON);
			}
			DrawText("Exit", exitButton.x + 53, exitButton.y + 2, exitButton.height, BLACK);

			if (CheckCollisionPointRec(mousePoint, againButton)) {
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
					DrawRectangle(againButton.x, againButton.y, againButton.width, againButton.height, BEIGE);
				}
				else {
					DrawRectangle(againButton.x, againButton.y, againButton.width, againButton.height, BROWN);
				}

				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
					for (int i = 0; i < 6; i++) {
						for (int j = 0; j < 7; j++) {
							tabella[i][j] = 0;
						}
					}
					vittoria = 0;
					PlaySound(buttonSound1);
				}
			}
			else {
				DrawRectangle(againButton.x, againButton.y, againButton.width, againButton.height, MAROON);
			}
			DrawText("Play Again", againButton.x + 20, againButton.y, againButton.height, BLACK);
		}
		else {
			// Controllo dove i giocatori inseriscono la moneta
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
				for (int i = 0; i < 7; i++) {
					if (CheckCollisionPointRec(mousePoint, areaBoard[i])) {
						for (int j = 5; j >= 0; j--) {
							if (tabella[j][i] == 0) {
								if (turno == 0) {
									tabella[j][i] = 1;

									// Controllo vittoria
									vittoria = controlloVittoria(j, i);

									// Cambio turno giocatore
									turno = 1;
								}
								else {
									tabella[j][i] = 2;

									// Controllo vittoria
									vittoria = controlloVittoria(j, i);

									// Cambio turno giocatore
									turno = 0;
								}
								break;
							}
						}
					}
				}
			}
		}

		// De-inizializzo i canvas
		EndDrawing();
	}

	// Chiudo la finestra
	CloseWindow();
}