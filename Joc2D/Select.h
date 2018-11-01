#pragma once

#ifndef _SELECT_INCLUDE
#define _SELECT_INCLUDE

#include "General.h"
#include "Sprite.h"
#include "Texture.h"

class Select {
public:
	Select();
	void init(ShaderProgram &shaderProgram);
	void render();
	int update(int deltaTime,int frame);
private:
	vector<Sprite*> sprites;
	Texture t1, t2, t3;
	int select;
};
#endif;