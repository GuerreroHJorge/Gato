#include <stdio.h>
#include <stdlib.h>
#include "gato.h"

int main()
{
  char *cargar;
  printf("Cargar juego:\n");
  fscanf(stdin, "%s", cargar);
  Game *juego = loadGame(cargar);

  while(!getWinner(juego))
  {
    switchPlayer(juego);
    displayBoard(juego);
    printf("Es el turno del jugador: %c \n", getCurrentPlayer(juego));

    int place;
    fscanf(stdin, "%d", &place);
    makeMove(juego, place);
  }
  displayBoard(juego);
  
  //if(getWinner(juego) == 1)
  //  printf("\nEmpate\n");
  //else
  printf("El ganador es: %c\n", getWinner(juego));
  
  
  return 0;
}
