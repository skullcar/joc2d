#include "Player.h"
#include "Game.h"
#include "cSound.h"



#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define MAX_HEALTH 100
#define HITBOX_Y_SIZE 45

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

enum PlayerSounds
{
	WALK, DAMAGE
};


void Player::init(const glm::ivec2 &Pos,const glm::ivec2 &size)
{
	bJumping = false;
	health = MAX_HEALTH;
	bsprite = false;
	AddSounds();
	setPosition(Pos);
	setSize(size);
	invisible = true;
}

void Player::update(int deltaTime) {
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		posPlayer.y -= 2;
		int dmg1 = map->collisionLeft(posPlayer, sizePlayer);
		if (dmg1 == 0) {
			posPlayer.x += 2;
		}
		if (dmg1 > 0)
		{
			posPlayer.x += 16;
			health -= dmg1;
			Sounds[DAMAGE]->play();
		}
		int dmg2 = map->collisionUp(posPlayer, sizePlayer);
		if (dmg2 ==0) posPlayer.y += 2;
		else if (dmg2 > 0){
			posPlayer.y += 16;
			if (dmg1 == 0) {
				health -= dmg1;
				Sounds[DAMAGE]->play();
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP)){
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		posPlayer.y -= 2;
		int dmg1 = map->collisionRight(posPlayer, sizePlayer);
		if (dmg1 == 0) {
			posPlayer.x -= 2;
		}
		if (dmg1 > 0)
		{
			posPlayer.x -= 16;
			health -= dmg1;
			Sounds[DAMAGE]->play();
		}
		int dmg2 = map->collisionUp(posPlayer, sizePlayer);
		if (dmg2 == 0) posPlayer.y += 2;
		else if (dmg2 > 0) {
			posPlayer.y += 16;
			if (dmg1 == 0) {
				health -= dmg1;
				Sounds[DAMAGE]->play();
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		posPlayer.y += 2;
		int dmg1 = map->collisionLeft(posPlayer, sizePlayer);
		if (dmg1 == 0) {
			posPlayer.x += 2;
		}
		if (dmg1 > 0)
		{
			posPlayer.x += 16;
			health -= dmg1;
			Sounds[DAMAGE]->play();
		}
		int dmg2 = map->collisionDown(posPlayer, sizePlayer);
		if (dmg2 == 0) posPlayer.y -= 2;
		else if (dmg2 > 0) {
			posPlayer.y -= 16;
			if (dmg1 == 0) {
				health -= dmg1;
				Sounds[DAMAGE]->play();
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		posPlayer.y += 2;
		int dmg1 = map->collisionRight(posPlayer, sizePlayer);
		if (dmg1 == 0) {
			posPlayer.x -= 2;
		}
		if (dmg1 > 0)
		{
			posPlayer.x -= 16;
			health -= dmg1;
			Sounds[DAMAGE]->play();
		}
		int dmg2 = map->collisionDown(posPlayer, sizePlayer);
		if (dmg2 == 0) posPlayer.y -= 2;
		else if (dmg2 > 0) {
			posPlayer.y -= 16;
			if (dmg1 == 0) {
				health -= dmg1;
				Sounds[DAMAGE]->play();
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		int dmg = map->collisionLeft(posPlayer, sizePlayer);
		if (dmg == 0) {
			posPlayer.x += 2;
		}
		else if (dmg > 0)
		{
			posPlayer.x += 16;
			health -= dmg;
			Sounds[DAMAGE]->play();
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		int dmg = map->collisionRight(posPlayer, sizePlayer);
		if (dmg == 0) {
			posPlayer.x -= 2;
		}
		else if (dmg > 0)
		{
			posPlayer.x -= 16;
			health -= dmg;
			Sounds[DAMAGE]->play();
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {

		if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
		else if (sprite->animation() == STAND_LEFT) sprite->changeAnimation(MOVE_LEFT);
		posPlayer.y -= 2;
		int dmg = map->collisionUp(posPlayer, sizePlayer);
		if (dmg == 0) posPlayer.y += 2;
		else if (dmg > 0) {
			posPlayer.y += 16;
			health -= dmg;
			Sounds[DAMAGE]->play();
			}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
		else if (sprite->animation() == STAND_LEFT) sprite->changeAnimation(MOVE_LEFT);
		posPlayer.y += 2;
		int dmg = map->collisionDown(posPlayer, sizePlayer);
		if (dmg == 0) posPlayer.y -= 2;
		else if (dmg > 0) {
				posPlayer.y -= 16;
				health -= dmg;
				Sounds[DAMAGE]->play();
			}
	}
	else {
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	if (Game::instance().getKey(97) && !bJumping) {
		bJumping = true;
		jumpAngle = 0;
		startY = posPlayer.y;
	}
	if (bJumping) {
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle >= 180) {
			bJumping = false;
			posPlayer.y = startY;
		}
		else {
			if (map->collisionDown(posPlayer, sizePlayer) >= 0) posPlayer.x -= 2;
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
		}
	}
	sprite->setPosition(glm::vec2(posPlayer.x-59, posPlayer.y - HITBOX_Y_SIZE));
	if (sprite->animation() == MOVE_LEFT || sprite->animation() == MOVE_RIGHT && !bJumping) Sounds[WALK]->play();
	else  Sounds[WALK]->stop();
}

void Player::setMap(Map *mapn) {
	map= mapn;
}

void Player::render()
{
	sprite->render();
}

void Player::setSize(const glm::ivec2 &size){
	sizePlayer.x = size.x;
	sizePlayer.y = size.y - HITBOX_Y_SIZE;
}

void Player::setPosition(const glm::ivec2 &pos)
{
	posPlayer.x = pos.x;
	posPlayer.y = pos.y + HITBOX_Y_SIZE;
}

void Player::AddSounds() {
	cSound* s = new cSound;
	s->load("music/Walk.wav");
	Sounds.push_back(s);
	s = new cSound;
	s->load("music/Damage.wav");
	Sounds.push_back(s);
}

glm::ivec2 Player::getPosition() { return posPlayer; }

glm::ivec2 Player::getSize() { return sizePlayer; }

bool Player::IsDead() { return health <= 0; }

bool Player::IsInvisible() { return invisible; }

void Player::Invisible(bool inv) { invisible = inv; }

void Player::ChangeSprite(char* spr) { spritesheet.loadFromFile(spr, TEXTURE_PIXEL_FORMAT_RGBA); }

bool Player::haveSprite() { return bsprite; }

void Player::setSprite(char * spr, ShaderProgram &shaderProgram) {
	invisible = false;
	spritesheet.loadFromFile(spr, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(182, 70), glm::vec2(0.125f, 0.5f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	for (float y = 1.0f; y >= 0.0f; y = y - 0.125f) {
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(y, 0.5f));
	}

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	for (float y = 0.0f; y < 1.0f; y = y + 0.125f) {
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(y, 0.0f));
	}


	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(posPlayer.x - 59, posPlayer.y - HITBOX_Y_SIZE));
	bsprite = true;
}


