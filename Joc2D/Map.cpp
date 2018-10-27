#include "Map.h"

Map::Map() {

}


void Map::init(ShaderProgram &shaderProgram, glm::ivec2 &size) {
	floor_size = size;
}

void Map::render() {
	int f = objects.size();
	for (int i = 0; i < f; ++i) objects[i]->render();
}

void Map::update(int deltaTime) {
	int f = objects.size();
	for (int i = 0; i < f; ++i) objects[i]->update(deltaTime);
}

int Map::collisionDown(glm::ivec2 Pos, glm::ivec2 size) {
	if ((Pos.y + size.y) - 1 > 480) return 0;
	int f = objects.size();
	for (int i = 0; i < f; ++i) {
		glm::ivec2 p = objects[i]->getPos();
		if ((Pos.y + size.y - 1) > (p.y - 1) && (p.x < (Pos.x + size.x)) && ((p.x + 32) > Pos.x) && ((p.y + 28) > Pos.y)) {
			return  objects[i]->damage();
		}
	}
	return -1;
}
int Map::collisionUp(glm::ivec2 Pos, glm::ivec2 size) {
	if (Pos.y - 1 < 480 - floor_size.y - 1) return 0;
	int f = objects.size();
	for (int i = 0; i < f; ++i) {
		glm::ivec2 p = objects[i]->getPos();
		if (Pos.y < (p.y + 28) && (p.x < (Pos.x + size.x)) && ((p.x + 32) > Pos.x) && (p.y < (Pos.y + size.y))) {
			return  objects[i]->damage();
		}
	}
	return -1;
}
int Map::collisionLeft(glm::ivec2 Pos, glm::ivec2 size) {
	if (Pos.x -1 < c_x - 1) return 0;
	int f = objects.size();
	for (int i = 0; i < f; ++i) {
		glm::ivec2 p = objects[i]->getPos();
		if ((Pos.x < (p.x + 32)) && ((Pos.y) < (p.y + 28)) && ((Pos.y + size.y) > p.y) && (Pos.x  > p.x) && ((Pos.x + size.x) > p.x)) {
			return  objects[i]->damage();
		}
	}
	return -1;
}
int Map::collisionRight(glm::ivec2 Pos, glm::ivec2 size) {
	if ((Pos.x + size.x) - 1 > c_x + 640 - 1) return 0;
	int f = objects.size();
	for (int i = 0; i < f; ++i) {
		glm::ivec2 p = objects[i]->getPos();
		if ((Pos.x + size.x) > (p.x) && ((Pos.y) < (p.y + 28)) && ((Pos.y + size.y) > p.y) && ((Pos.x + size.x) < (p.x + 32))) {
			return  objects[i]->damage();
		}
	}
	return -1;
}



void Map::SetCx(int cx) { c_x = cx; }

void Map::LoadObject(char* spr, const glm::ivec2 &Pos, int d, ShaderProgram &shaderProgram) {
	Object* o = new Object;
	o->init(spr,Pos,d,shaderProgram);
	objects.push_back(o);
}