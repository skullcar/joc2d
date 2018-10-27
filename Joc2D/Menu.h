#pragma once

#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "General.h"
#include "Level.h"


class Menu: Level{
public:
	Menu();
	void init();
	void render();
	void update();
	bool endlevel();
private:

};
#endif