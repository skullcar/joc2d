#pragma once

#ifndef _HEALTH_INCLUDE
#define _HEALTH_INCLUDE

#include "General.h"
#include "Texture.h"
#include "Sprite.h"

class Health {
public:
	Health();
	void init(ShaderProgram &shaderProgram);
	void render();
	void update(float health);
private:
	Texture g, r, f;
	Sprite* gs, *rs, *fs;
	ShaderProgram *sp;
}; 
#endif
