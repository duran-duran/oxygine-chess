#include "shared.h"
#include "Chessboard.h"
#include "Piece.h"

const int dim = 8;
const Vector2 cell_size = Vector2(80, 80);

Chessboard::Chessboard() 
{
}

void Chessboard::init()
{
	_view = new Sprite;

	_view->setSize(cell_size.x * dim, cell_size.y * dim);
	//_cells.resize(dim * dim);

	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			//initializing cells' vector
			//_cells[i * dim + j].pos = Point(j, i);
			

			spColorRectSprite cell = new ColorRectSprite;
			cell->setSize(cell_size);
			(i + j) % 2 ?
				cell->setColor(Color::Sienna) :
				cell->setColor(Color::Cornsilk);
			cell->attachTo(_view);
			cell->setPosition(j * cell_size.x, i * cell_size.y);
			//cell->setAnchor? to rotate around the center of the board at the end of the turn		
		}
	}

	putPieces();

	//adding callbacks to board
	_view->addClickListener(CLOSURE(this, &Chessboard::clicked));
	_view->setTouchChildrenEnabled(false);

	//----temporary anchor for board rotation
	_view->setAnchor(0.5f, 0.5f);
}


void Chessboard::putPieces()
{
	//---------temporary board filling----------------
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			if (i < 2 || i > 5)
			{
				spSprite piece = new Sprite;
				std::string name;
				name += (i < 2) ? "black_" : "white_";
				if (i == 1 || i == 6)
				{
					name += "pawn";
				}
				else if (j == 0 || j == 7)
				{
					name += "rook";
				}
				else if (j == 1 || j == 6)
				{
					name += "knight";
				}
				else if (j == 2 || j == 5)
				{
					name += "bishop";
				}
				else if (j == 3)
				{
					name += "queen";
				}
				else
				{
					name += "king";
				}
				piece->setResAnim(res.getResAnim(name));
				piece->setAnchor(0.5f, 0.5f);
				piece->setPosition(Vector2(j * cell_size.x, i * cell_size.y) + cell_size / 2);
				piece->attachTo(_view);
			}
		}
	}
	//----------------------------------------------
}


void Chessboard::clicked(Event* event)
{
	//---temp rotation---
	_view->setRotationDegrees(_view->getRotationDegrees() + 180);
	//-------------------

	return;
}

spActor Chessboard::getView()
{
	return _view;
}

void Chessboard::free()
{
	_cells.clear();
	_view->detach();

}