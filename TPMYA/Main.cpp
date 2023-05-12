#include "Game.h" 
#include <Box2D/Box2D.h>

void main(int argc, char* argv[])
{

	Game juego(800, 600, "Ventana");
	juego.Go();

	return;
}