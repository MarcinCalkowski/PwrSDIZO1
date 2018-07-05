#pragma once

class Board
{
	int *board;
	int size;

public:
	Board();
	~Board();
	int Board::Menu();
	int Board::LoadFromFile(std::string filename);
	int Board::AddElementZero(int var);
	int Board::AddElementFirst(int var);
	int Board::AddElementLast(int var);
	int Board::AddElement(int var, int position);
	int Board::DeleteBoard();
	int Board::DeleteElementFirst();
	int Board::DeleteElementLast();
	int Board::DeleteElement(int position);
	int DeleteElementFound(int var);
	int DeleteElementFirst(int var);
	int Board::ShowBoard(int n);
	int FindElement(int var);
};

