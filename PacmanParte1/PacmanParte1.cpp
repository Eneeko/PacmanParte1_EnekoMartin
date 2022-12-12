#include <iostream>
#include <conio.h>

using namespace std;
#define CONSOLE_HEIGHT 29
#define CONSOLE_WIDTH 119
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27


void RellenarMapa();
void ImprimirPantalla();
void Inputs();
void Logica();
void PonerScore();
void FinPartida();

//Cada tipo de ENUM define una parte del mapa
enum MAP_TILES { EMPTY = ' ', WALL = '#', POINT = '.' };

//Cada tipo de ENUM define una dirección de movimiento del jugador
enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };

MAP_TILES ConsoleScreen[CONSOLE_HEIGHT][CONSOLE_WIDTH];
int map_points = 0;
char personaje = 'o';
int personaje_x = 10;
int personaje_y = 5;
int personaje_puntos = 5;
USER_INPUTS input = USER_INPUTS::NONE;
bool run = true;
int score = 0;
int pacman_win = 17;




int main()//Se desarrolla el programa principal
{
	RellenarMapa();
	ImprimirPantalla();
	while (run) {

		Inputs();
		Logica();
		ImprimirPantalla();
		PonerScore();
		FinPartida();

	}

}

void RellenarMapa() {
	//En esta función se rellena el mapa mediante un for anidado utilizando los enums de tipo MAP_TILES. Con el for, se colocan las paredes a los lados del mapa
	//y se deja un espacio vacío en el interior de éstas. Además, coloco los puntos que el jugador va a recoger, a mi gusto, repartidos por el mapa.

	for (size_t i = 0; i < CONSOLE_HEIGHT; i++)//size_t puede ser un int por ejemplo
	{
		for (size_t j = 0; j < CONSOLE_WIDTH; j++)
		{
			if (i == 0 || i == CONSOLE_HEIGHT - 1 || j == 0 || j == CONSOLE_WIDTH - 1) {
				ConsoleScreen[i][j] = MAP_TILES::WALL;
			}
			else {
				ConsoleScreen[i][j] = MAP_TILES::EMPTY;
			}
		}
	}
	ConsoleScreen[2][4] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[4][2] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[17][73] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[20][70] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[11][18] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[1][5] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[2][110] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[3][36] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[7][41] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[8][88] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[25][8] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[18][21] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[4][14] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[12][16] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[13][17] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[20][28] = MAP_TILES::POINT;
	map_points++;
	ConsoleScreen[5][33] = MAP_TILES::POINT;
	map_points++;

	ConsoleScreen[6][0] = MAP_TILES::EMPTY;
	ConsoleScreen[7][0] = MAP_TILES::EMPTY;

	ConsoleScreen[6][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;
	ConsoleScreen[7][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;

	ConsoleScreen[6][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;
	ConsoleScreen[7][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;

}

void Inputs() {

	//En esta función asigno el movimiento del jugador mediante los enums del tipo USER_INPUTS. La función _getch() me permite introducir estos inputs sin 
	//la necesidad de pulsar enter, y dependiendo de la tecla que pulse asignare un valor u otro al input. En este caso, al ser movimiento, utilizo
	//las teclas W A S D, las flechas direccionales y la tecla ESC.

	char input_raw = ' ';
	input_raw = _getch();

	switch (input_raw)
	{
	case 'W':
	case 'w':
	case KEY_UP:
		input = USER_INPUTS::UP;
		cout << input_raw;
		break;
	case 'A':
	case 'a':
	case KEY_LEFT:
		input = USER_INPUTS::LEFT;
		break;
	case 'S':
	case 's':
	case KEY_DOWN:
		input = USER_INPUTS::DOWN;
		break;
	case 'D':
	case 'd':
	case KEY_RIGHT:
		input = USER_INPUTS::RIGHT;
		break;
	case 'Q':
	case 'q':
	case ESC:
		input = USER_INPUTS::QUIT;
		break;
	default:
		input = USER_INPUTS::NONE;
		break;
	}
}

void Logica()
{
	//En esta función decreto lo que va a hacer el personaje una vez implementados los inputs, mediante un switch. Al ser movimiento, el personaje se va
	//a mover hacia arriba, abajo, izquierda o derecha una unidad, dependiendo del input que he introduido por teclado anteriormente (UP, DOWN, RIGHT, LEFT)
	//Además, también implemento el sistema de "teletransporte" cuando el personaje se encuentra un hueco en la pared, que funciona mediante los límites de
	//la consola. Si el personaje alcanza una posición menor a 0 se instancia en el otro lado del mapa, y viceversa. Por último, también implemento la
	//recolección de puntos. Si el jugador pasa por encima de un punto, se cambia el punto por el MAP_TILES empty y se incrementa en uno los puntos del jugador,
	//así como la puntuación.

	int personaje_y_new = personaje_y;
	int personaje_x_new = personaje_x;
	switch (input)
	{
	case UP:
		personaje_y_new--;
		break;
	case DOWN:
		personaje_y_new++;
		break;
	case RIGHT:
		personaje_x_new++;
		break;
	case LEFT:
		personaje_x_new--;
		break;
	case QUIT:
		run = false;
		break;
	}
	if (personaje_x_new < 0) {
		personaje_x_new = CONSOLE_WIDTH - 1;
	}
	personaje_x_new %= CONSOLE_WIDTH;

	if (ConsoleScreen[personaje_y_new][personaje_x_new] == MAP_TILES::WALL) {
		personaje_y_new = personaje_y;
		personaje_x_new = personaje_x;
	}
	else if (ConsoleScreen[personaje_y_new][personaje_x_new] == MAP_TILES::POINT)
	{
		score++;
		personaje_puntos++;
		ConsoleScreen[personaje_y_new][personaje_x_new] = MAP_TILES::EMPTY;
	}
	personaje_y = personaje_y_new;
	personaje_x = personaje_x_new;
}

void PonerScore()//En esta función simplemente se imprime por pantalla la puntuación del jugador respecto a la puntuación total. 
{

	cout << "Score: " << score << "/" << pacman_win;

}

void FinPartida()
{
	//En esta función se gestiona el final de la partida mediante un if, donde comprobamos si la puntuación del jugador es igual a la puntuación total.
	//Si es así, se imprime por pantalla un mensaje informandome de que he ganado y se pausa el sistema hasta que pulse una tecla para salir de la consola.

	if (score == pacman_win)
	{
		cout << endl;
		cout << "Has ganado la partida   ";
		system("pause");
		exit(EXIT_SUCCESS);

	}
}


void ImprimirPantalla()
{
	//En esta función imprimo por pantalla toda la información que contiene el mapa mediante un for anidado.

	system("CLS");
	for (size_t i = 0; i < CONSOLE_HEIGHT; i++)//size_t puede ser un int por ejemplo
	{
		for (size_t j = 0; j < CONSOLE_WIDTH; j++)
		{
			if (personaje_x == j && personaje_y == i) {
				cout << personaje;

			}
			else {
				cout << (char)ConsoleScreen[i][j];
			}
		}
		cout << endl;
	}
}