#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "General.h"
#include "Sprite.h"
#include "Map.h"
#include "cSound.h"
#include "Health.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(int type, const glm::ivec2 &Pos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setPosition(const glm::ivec2 &pos);
	void setSize(const glm::ivec2 &size);
	void setMap(Map *mapn);

	glm::ivec2 getPosition();
	glm::ivec2 getSize();

	bool IsDead();
	bool DoDamage();
	int GetDamage();
	glm::vec2 GetHitBoxDist();
	glm::vec2 GetHitBox();

	
private:

	int health, speed, mhealth;
	int combo;
	bool bJumping;
	glm::vec2 posPlayer, colisionSize, hitboxSize, spriteMove;
	int jumpAngle, startY;
	int facing;
	Texture spritesheet;
	Sprite *sprite;
	Map *map;
	vector<cSound*> Sounds;
	Health *bar;

	void createAvalanche(const glm::ivec2 &Pos, ShaderProgram &shaderProgram);
	void createBlizzard(const glm::ivec2 &Pos, ShaderProgram &shaderProgram);
	void createFlurry(const glm::ivec2 &Pos, ShaderProgram &shaderProgram);
	void AddSounds();

};


#endif // _PLAYER_INCLUDE


