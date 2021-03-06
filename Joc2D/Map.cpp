#include "Map.h"

Map::Map() {

}


void Map::init(ShaderProgram &shaderProgram, glm::ivec2 &size) {
	floor_size = size;
	
}

void Map::render() {
	list<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) (*it)->render();
}

void Map::update(int deltaTime) {
	list<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) (*it)->update(deltaTime);
}

int Map::collisionDown(glm::ivec2 Pos, glm::ivec2 size) {
	if ((Pos.y + size.y) - 1 > 480) return 0;
	list<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		glm::ivec2 p = (*it)->getPos();
		if ((Pos.y + size.y - 1) >(p.y - 1) && (p.x < (Pos.x + size.x)) && ((p.x + 32) > Pos.x) && ((p.y + 28) > Pos.y)) {
			return  (*it)->damage();
		}
	}
	return -1;
}
int Map::collisionUp(glm::ivec2 Pos, glm::ivec2 size) {
	if (Pos.y - size.y < 480 - floor_size.y - 1) return 0;
	list<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		glm::ivec2 p = (*it)->getPos();
		if (Pos.y < (p.y + 28) && (p.x < (Pos.x + size.x)) && ((p.x + 32) > Pos.x) && (p.y < (Pos.y + size.y))) {
			return  (*it)->damage();
		}
	}
	return -1;
}
int Map::collisionLeft(glm::ivec2 Pos, glm::ivec2 size) {
	if (Pos.x - size.x < c_x) return 0;
	list<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		glm::ivec2 p = (*it)->getPos();
		if ((Pos.x < (p.x + 32)) && ((Pos.y) < (p.y + 28)) && ((Pos.y + size.y) > p.y) && (Pos.x  > p.x) && ((Pos.x + size.x) > p.x)) {
			return  (*it)->damage();
		}
	}
	return -1;
}
int Map::collisionRight(glm::ivec2 Pos, glm::ivec2 size) {
	if ((Pos.x + size.x) - 1 > c_x + 640 - 1) return 0;
	list<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		glm::ivec2 p = (*it)->getPos();
		if ((Pos.x + size.x) >(p.x) && ((Pos.y) < (p.y + 28)) && ((Pos.y + size.y) > p.y) && ((Pos.x + size.x) < (p.x + 32))) {
			return  (*it)->damage();
		}
	}
	return -1;
}



void Map::SetCx(int cx) { c_x = cx; }

void Map::LoadObject(char* spr, const glm::ivec2 &Pos, int d, ShaderProgram &shaderProgram) {
	Object* o = new Object;
	o->init(spr, Pos, d, shaderProgram);
	objects.push_back(o);
}

/*void Map::playerdoDMG(glm::vec2 PosPlayer, int dmg, glm::vec2 hb, int dist) {
	glm::vec2 hbc;
	hbc.x = PosPlayer.x + dist;
	hbc.y = PosPlayer.y;
	int s = Enemys.size();
	for (int i = 0; i < s; ++i){
		Enemys[i].hitted(hbc,hb,dmg);
	}
}*/

bool Map::ObjectDamage(glm::vec2 hbc, glm::vec2 hb, int dmg) {
	vector<list<Object*>::iterator> its;
	bool m = false;
	for (list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			m = (*it)->getDamage(hbc, hb, dmg);
			if ((*it)->Destroyed()) its.push_back(it);
	}
	for (int i = 0; i < its.size(); ++i) {
		int h = (*its[i])->getHealth();
		objects.erase(its[i]);
	}
	return m;
}
