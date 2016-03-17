#include "shared.h"

#include "Chessboard.h"

Chessboard board;

void example_preinit() {}

//called from main.cpp
void example_init()
{
    //load xml file with resources definition
    res.loadXML("res.xml");

	board.init();

	spActor view = board.getView();
	view->setPosition(getStage()->getSize() / 2 /*- view->getSize() / 2*/);
	getStage()->addChild(view);
}


//called each frame from main.cpp
void example_update()
{
}

//called each frame from main.cpp
void example_destroy()
{
    //free previously loaded resources
    res.free();
	board.free();
}
