#include "gameBoard.h"
#include "general.h"
#include <iostream>
void gameBoard::draw(point board[4])
{
	int topLeftX = board[(int)gameBoard::CORNER::TOP_LEFT].getX();
	int topLeftY = board[(int)gameBoard::CORNER::TOP_LEFT].getY();
	int topRightX = board[(int)gameBoard::CORNER::TOP_RIGHT].getX();
	int topRightY = board[(int)gameBoard::CORNER::TOP_RIGHT].getY();
	int bottomRightX = board[(int)gameBoard::CORNER::BOTTOM_RIGHT].getX();
	int bottomRightY = board[(int)gameBoard::CORNER::BOTTOM_RIGHT].getY();
	int bottomLeftX = board[(int)gameBoard::CORNER::BOTTOM_LEFT].getX();
	int bottomLeftY = board[(int)gameBoard::CORNER::BOTTOM_LEFT].getY();
	gotoxy(topLeftX, topLeftY-1);
	for (int i = topLeftX; i <= topRightX; i++)
	{
		std::cout << '=';
	}
	int currY = topRightY;
	gotoxy(topRightX, topRightY);
	for (int i = topRightY; i < bottomRightY; i++)
	{
		std::cout << "||";
		gotoxy(topRightX, ++currY);
	}
	gotoxy(bottomLeftX, bottomLeftY);
	for (int i = topLeftX; i <= topRightX; i++)
	{
		std::cout << '=';
	}
    currY = topLeftY;
	gotoxy(topLeftX, topLeftY);
	for (int i = topRightY; i < bottomRightY; i++)
	{
		std::cout << "||";
		gotoxy(topLeftX, ++currY);
	}
}
