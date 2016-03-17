#include "shared.h"

#include "oxygine-chess.h"
#include "Chessboard.h"

Chessboard board;

void chess_preinit() {}

//called from main.cpp
void chess_init()
{
    //load xml file with resources definition
    res.loadXML("res.xml");

	board.init();

	spActor view = board.getView();
	view->setPosition(getStage()->getSize() / 2 /*- view->getSize() / 2*/);
	getStage()->addChild(view);
}


//called each frame from main.cpp
void chess_update()
{
}

//called each frame from main.cpp
void chess_destroy()
{
    //free previously loaded resources
    res.free();
	board.free();
}
