#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "General.h"
#include "Map.h"
#include "Sprite.h"
#include "cSound.h"


class Enemy {
public:
	Enemy();

	void init(const glm::ivec2 &size, int h);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::vec2 &pos);
	void setMap(Map *mapn);

	glm::ivec2 getPosition();
	glm::ivec2 getSize();

	bool IsDead();
	bool IsInvisible();
	void Invisible(bool inv);
	void ChangeSprite(char* spr);
	void AddSounds();

private:
	int health;
	bool bJumping;
	bool invisible;
	glm::vec2 posEnemy, sizeEnemy;
	int jumpAngle, startY;

	Texture spritesheet;
	Sprite *sprite;
	Map *map;
	vector<cSound*> Sounds;
};
#endif