#pragma once

class Piece;

struct Cell
{
	Point pos;
	Piece* piece;
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

	void putPieces();

	spSprite			_view;
	std::vector<Cell>	_cells;
};