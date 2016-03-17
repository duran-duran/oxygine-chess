#pragma once

class Piece : public Sprite
{
public:
	Piece();

	void select();
	void unselect();

	spTween moveTo(const Point& pos);
	spTween remove();
private:

};

DECLARE_SMART(Piece, spPiece);