#include "shared.h"
#include "Chessboard.h"
#include "Piece.h"

const int dim = 8;
const Vector2 cell_size = Vector2(80, 80);

Chessboard::Chessboard() : _view(nullptr), _selected(nullptr)
{

}

void Chessboard::init()
{
	_view = new Sprite;

	_view->setSize(cell_size.x * dim, cell_size.y * dim);
	_cells.resize(dim * dim);

	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			//initializing cells' vector
			_cells[i * dim + j].pos = Point(j, i);

			//rendering chessboard via ColorRectSprite
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

	//putting pieces on the table
	resetPieces();

	//adding callbacks to board
	_view->addClickListener(CLOSURE(this, &Chessboard::clicked));
	_view->setTouchChildrenEnabled(false);

	//----temporary anchor for board rotation
	_view->setAnchor(0.5f, 0.5f);
}


void Chessboard::resetPieces()
{
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			//removing piece if it is standing on current cell
			if (_cells[i * dim + j].piece)
			{
				_cells[i * dim + j].piece->detach();
				_cells[i * dim + j].piece = nullptr;
			}

			//putting pieces on board according to standard chess configuration
			if (i < 2 || i > 5)
			{
				spPiece piece = new Piece;

				std::string name;

				name += (i < 2) ? "black_" : "white_";

				if (i == 1 || i == 6)
				{
					name += "pawn";
				}
				else
				{
					switch (j)
					{
						case 0:
						case 7:
							name += "rook";
							break;
						case 1:
						case 6:
							name += "knight";
							break;
						case 2:
						case 5:
							name += "bishop";
							break;
						case 3:
							name += "queen";
							break;
						case 4:
							name += "king";
							break;
					}
				}
				//P.S. all those numbers look very ugly, but i dunno yet how to rewrite it more pretty

				piece->setResAnim(res.getResAnim(name));
				piece->setAnchor(0.5f, 0.5f);
				Vector2 pos = Vector2(j * cell_size.x, i * cell_size.y) + cell_size / 2;
				piece->setPosition(pos);
				piece->attachTo(_view);

				_cells[i * dim + j].piece = piece;
			}
		}
	}
}


void Chessboard::clicked(Event* event)
{
	TouchEvent* te = safeCast<TouchEvent*>(event);
	Vector2 pos = te->localPosition;
	//log::messageln("%d - %d: %.2f, %.2f", event->target->getObjectID(), event->currentTarget->getObjectID(), pos.x, pos.y);

	Point cellPos;
	cellPos.x = (int)(pos.x / cell_size.x);
	cellPos.y = (int)(pos.y / cell_size.y);

	log::messageln("(%d, %d) clicked", cellPos.x, cellPos.y);

	Cell* cell_p = getCell(cellPos);

	log::messageln("(%d, %d) got", cell_p->pos.x, cell_p->pos.y);


	if (_selected)
	{
		_selected->piece->unselect();
		if (cell_p)
		{
			//--------temporary----------------------------------------
			//tweens are declared in case i need to add done-callbacks
			//look carefully what tweens are returned
			spTween move_tween = _selected->piece->moveTo(cellPos);
			

			if (cell_p->piece)
			{
				spTween remove_tween = cell_p->piece->remove();
			}

			//Possible memory leak? 
			cell_p->piece = _selected->piece;
			_selected->piece = nullptr;
			//--------------------------------------------------------
		}

		_selected = nullptr;
	}
	else
	{
		//!!!!!!!!!!!! Bug: allows clicking on empty cell
		_selected = cell_p;
		if (cell_p)
			cell_p->piece->select();
	}

	//---temp rotation---
	//_view->setRotationDegrees(_view->getRotationDegrees() + 180);
	//-------------------

	return;
}


Cell* Chessboard::getCell(const Point& pos)
{
	if (pos.x < 0 || pos.x >= dim ||
		pos.y < 0 || pos.y >= dim)
		return nullptr;

	Cell& cell = _cells[pos.y * dim + pos.x];
	return &cell;
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