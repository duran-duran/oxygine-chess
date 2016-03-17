#pragma once

#include "Piece.h"

struct Cell
{
	Point pos;
	spPiece piece;
};


class Chessboard 
{
public:
	Chessboard();

	void init();
	void free();

	spActor getView();

private:
	void clicked(Event* event);

	Cell* getCell(const Point& pos);

	void resetPieces();

	spSprite			_view;
	std::vector<Cell>	_cells;
	Cell*				_selected;
};