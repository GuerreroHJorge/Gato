#ifndef GATO_GATO_H
#define GATO_GATO_H

typedef struct GameState Game;

void displayBoard(Game *g);
Game* newGame();
char getWinner(Game *g);
char getCurrentPlayer(Game *g);
void makeMove(Game *g, int place);
void switchPlayer(Game *g);

Game* loadGame(const char* pathToSave); //cargar un juego previo
void saveGame(Game *g); // guardar un juego en curso

#endif //GATO_GATO_H
