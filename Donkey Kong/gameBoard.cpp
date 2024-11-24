#include "gameBoard.h"
#include "general.h"
#include "platform.h"
#include <iostream>


void gameBoard::draw()
{
	//2 loops drawing ths borders of the game
	for (int col = this->MIN_X; col < this->GAME_WIDTH + this->MIN_X; col++)
	{
		gotoxy(col, this->MIN_Y);
		std::cout << '=';
		gotoxy(col, this->MIN_Y + this->GAME_HEIGHT);
		std::cout << '=';
	}
	for (int row = this->MIN_Y; row < this->GAME_HEIGHT + this->MIN_Y; row++)
	{
		gotoxy(this->MIN_X, row);
		std::cout << "||";
		gotoxy(this->MIN_X + this->GAME_WIDTH, row);
		std::cout << "||";
	}
	platform p;
	p.init('=', 7, 20);
	p.draw();

}