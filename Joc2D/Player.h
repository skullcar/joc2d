#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "General.h"
#include "Sprite.h"
#include "Map.h"
#include "cSound.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &Pos, const glm::ivec2 &size);
	void update(int deltaTime);
	void render();
	
	void setPosition(const glm::vec2 &pos);
	void setSize(const glm::vec2 &size);
	void setMap(Map *mapn);
	void setSprite(char* spr, ShaderProgram &shaderProgram);

	glm::ivec2 getPosition();
	glm::ivec2 getSize();

	bool IsDead();
	bool IsInvisible();
	bool haveSprite();
	void Invisible(bool inv);
	void ChangeSprite(char* spr);

	
private:

	void AddSounds();
	int health; 
	bool bJumping;
	bool invisible;
	bool bsprite;
	glm::vec2 posPlayer, sizePlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	Map *map;
	vector<cSound*> Sounds;

};


#endif // _PLAYER_INCLUDE


