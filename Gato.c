#include "gato.h"
#include <stdio.h>
#include <stdlib.h>

struct GameState
{
  char currentPlayer; // esto sera 'x' o 'o' dependiendo del jugador
  char board[3][3];
};

void displayBoard(struct GameState *g)
{
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
      printf("[%c]", g->board[i][j]);
    printf("\n");
  }
}

Game* newGame()
{
  Game *g = malloc(sizeof(Game));

  g->currentPlayer = 'o';

  int counter = 0;

  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      g->board[i][j] = '0' + counter++;

  return g;
}

int contador = 0;
char getWinner(struct GameState *g)
{
  contador++;
  int b = 0;
  for(int i=0; i< 3; i++)
    for(int j=0; j< 3; j++)
      if(g->board[i][j] != 'x' && g->board[i][j] != 'o')
        b++;

  
  if(b==0 && contador > 1){
    displayBoard(g);
    int counter = 0;

    for(int i=0; i<3; i++)
      for(int j=0; j<3; j++)
        g->board[i][j] = '0' + counter++;

    switchPlayer(g);
    printf("No hay ganador\n\n");
    contador = 0;
    return 0;
  }

    // revisar filas
  for(int i=0; i< 3; i++)
  {
    if(g->board[i][0] == g->currentPlayer &&
       g->board[i][1] == g->currentPlayer &&
       g->board[i][2] == g->currentPlayer
    )
      return g->currentPlayer;
  }
  // revisamos las columnas
  for(int i=0; i< 3; i++)
  {
    if(g->board[0][i] == g->currentPlayer &&
    g->board[1][i] == g->currentPlayer &&
    g->board[2][i] == g->currentPlayer
    )
      return g->currentPlayer;
  }

  // revisamos las diagonales (esto quedara de tarea hjejejejeje )
  if(g->board[0][0] == g->currentPlayer &&
  g->board[1][1] == g->currentPlayer &&
  g->board[2][2] == g->currentPlayer
  )
    return g->currentPlayer;

  if(g->board[0][2] == g->currentPlayer &&
  g->board[1][1] == g->currentPlayer &&
  g->board[2][0] == g->currentPlayer
  )
    return g->currentPlayer;

  
  return 0;
}

char getCurrentPlayer(Game *g)
{
  return g->currentPlayer;
}

void makeMove(Game *g, int place)
{
  // como ponemos la ficha en place?
  int row = place / 3;
  int col = place % 3;

  if(place == 9){
    saveGame(g);
    return;
  }
  
  if(g->board[row][col] != 'x' && g->board[row][col] != 'o')
    g->board[row][col] = g->currentPlayer;
  else{
    printf("El lugar ya estaba ocupado. Jugador %c elige otro lugar:", g->currentPlayer);
    fscanf(stdin, "%d", &place);
    makeMove(g, place);
  }
    
}

void switchPlayer(Game *g)
{
  if(g->currentPlayer == 'o')
    g->currentPlayer = 'x';
  else
    g->currentPlayer = 'o';

}

Game* loadGame(const char* pathToSave){
  //si existe un juego guardado se carga desde él
  Game *carga = newGame();
  
  FILE *savedGame = fopen(pathToSave, "r+b");
  
  if (savedGame != NULL)
  {
    //aqui tenemos un juego previamente guardado
    
    //carga->currentPlayer = a[0];
    /*int counter = 1;
    for(int i=0; i<3; i++)
      for(int j=0; j<3; j++){
        carga->board[i][j] = a[counter]; 
        counter++;
        }*/
    carga = savedGame;
    return carga;
  }
  return newGame();
}

void saveGame(Game *g){
  FILE *game = fopen("NuevoJuego.game", "w+b");
  fwrite(g, sizeof(Game), 1, game);
  fclose(game);
}