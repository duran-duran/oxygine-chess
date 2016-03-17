#include "shared.h"
#include "Piece.h"

//shouldn't I make it global?
const Vector2 cell_size = Vector2(80, 80);

Piece::Piece()
{

}

void Piece::select()
{
	//let piece pulse when it is selected
	addTween(Actor::TweenScale(1.2f), 300, -1, true);
	
	return;
}

void Piece::unselect()
{
	//stop pulsing and get back to normal size
	removeTweens();
	setScale(1.0f);

	return;
}

spTween Piece::moveTo(const Point& pos)
{
	Vector2 dest = Vector2(pos.x * cell_size.x, pos.y * cell_size.y) + cell_size / 2;

	spTween tween = addTween(Actor::TweenPosition(dest), 500);

	return tween;
}

spTween Piece::remove()
{
	spTween tween = addTween(Actor::TweenAlpha(0), 500);
	tween->setDetachActor(true);

	//should i return it? dunno yet
	return tween;
}