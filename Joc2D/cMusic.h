#pragma once
#ifndef _CMUSIC_INCLUDE
#define _CMUSIC_INCLUDE
#include "General.h"

class cMusic {
public:
	cMusic();
	void load(char * filename);
	void play();
	void stop();
	bool loaded();
private:
	Music *music;
	bool l;
};
#endif
