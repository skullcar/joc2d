#ifndef _MAP_INCLUDE
#define _MAP_INCLUDE

#include "General.h"
#include "Background.h"
#include "Object.h"

class Map {
public:
	Map();

	void init(ShaderProgram &shaderProgram, glm::ivec2 &size);
	void render();
	void update(int deltaTime);
	int collisionDown(glm::ivec2 Pos, glm::ivec2 size);
	int collisionUp(glm::ivec2 Pos, glm::ivec2 size);
	int collisionLeft(glm::ivec2 Pos, glm::ivec2 size);
	int collisionRight(glm::ivec2 Pos, glm::ivec2 size);
	void SetCx(int cx);
	void LoadObject(char* spr, const glm::ivec2 &Pos, int d, ShaderProgram &shaderProgram);

private:
	Background back;
	glm::ivec2 floor_size;
	int c_x;
	vector<Object*> objects;
	vector<int> Enemys;
};

#endif
