#include "Player.h"
#include "Game.h"
#include "cSound.h"

#define SPACEBAR 32
#define A 97
#define D 100
#define S 115
//AVALANCHE
#define A_JUMP_ANGLE_STEP 4
#define A_INIT_HEALTH 200
#define A_INIT_SPEED 3
#define A_HITBOX_X 25
#define A_HITBOX_Y 15
#define A_SPRITE_X 126
#define A_SPRITE_Y 90
#define A_COLISION_X 30
#define A_COLISION_Y 10

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT,
	ATTACK_1_LEFT, ATTACK_1_RIGHT, DEAD
};

enum PlayerSounds
{
	WALK, DAMAGE, HIT
};

enum PLayerFacing
{
	RIGHT, LEFT
};


void Player::init(int type, const glm::ivec2 &Pos, ShaderProgram &shaderProgram)
{
	if (type == 1) Player::createAvalanche(Pos, shaderProgram);
	bJumping = false;
	bar = new Health;
	bar->init(shaderProgram);
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (IsDead()) {
		if(sprite->animation() != DEAD) sprite->changeAnimation(DEAD);
		else ++deltaTime;
	}
	else {
		if (Game::instance().getKey(A)) {
			if (facing == LEFT && sprite->animation() != ATTACK_1_LEFT)
				sprite->changeAnimation(ATTACK_1_LEFT);
			else if (facing == RIGHT && sprite->animation() != ATTACK_1_RIGHT)
				sprite->changeAnimation(ATTACK_1_RIGHT);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			facing = LEFT;
			if (!bJumping && sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= speed;
			posPlayer.y -= speed;
			int dmg1 = map->collisionLeft(posPlayer, colisionSize);
			if (dmg1 == 0) {
				posPlayer.x += speed;
			}
			if (dmg1 > 0)
			{
				posPlayer.x += 2 * speed;
				health -= dmg1;
				Sounds[DAMAGE]->play();
			}
			int dmg2 = map->collisionUp(posPlayer, colisionSize);
			if (dmg2 == 0) posPlayer.y += speed;
			else if (dmg2 > 0) {
				posPlayer.y += 2 * speed;
				if (dmg1 == 0) {
					health -= dmg1;
					Sounds[DAMAGE]->play();
				}
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			facing = RIGHT;
			if (!bJumping && sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += speed;
			posPlayer.y -= speed;
			int dmg1 = map->collisionRight(posPlayer, colisionSize);
			if (dmg1 == 0) {
				posPlayer.x -= speed;
			}
			if (dmg1 > 0)
			{
				posPlayer.x -= 2 * speed;
				health -= dmg1;
				Sounds[DAMAGE]->play();
			}
			int dmg2 = map->collisionUp(posPlayer, colisionSize);
			if (dmg2 == 0) posPlayer.y += speed;
			else if (dmg2 > 0) {
				posPlayer.y += 2 * speed;
				if (dmg1 == 0) {
					health -= dmg1;
					Sounds[DAMAGE]->play();
				}
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			facing = LEFT;
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= speed;
			posPlayer.y += speed;
			int dmg1 = map->collisionLeft(posPlayer, colisionSize);
			if (dmg1 == 0) {
				posPlayer.x += speed;
			}
			if (dmg1 > 0)
			{
				posPlayer.x += 2 * speed;
				health -= dmg1;
				Sounds[DAMAGE]->play();
			}
			int dmg2 = map->collisionDown(posPlayer, colisionSize);
			if (dmg2 == 0) posPlayer.y -= speed;
			else if (dmg2 > 0) {
				posPlayer.y -= 2 * speed;
				if (dmg1 == 0) {
					health -= dmg1;
					Sounds[DAMAGE]->play();
				}
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			facing = RIGHT;
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += speed;
			posPlayer.y += speed;
			int dmg1 = map->collisionRight(posPlayer, colisionSize);
			if (dmg1 == 0) {
				posPlayer.x -= speed;
			}
			if (dmg1 > 0)
			{
				posPlayer.x -= 2 * speed;
				health -= dmg1;
				Sounds[DAMAGE]->play();
			}
			int dmg2 = map->collisionDown(posPlayer, colisionSize);
			if (dmg2 == 0) posPlayer.y -= speed;
			else if (dmg2 > 0) {
				posPlayer.y -= 2 * speed;
				if (dmg1 == 0) {
					health -= dmg1;
					Sounds[DAMAGE]->play();
				}
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			facing = LEFT;
			if (!bJumping && sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= speed;
			int dmg = map->collisionLeft(posPlayer, colisionSize);
			if (dmg == 0) {
				posPlayer.x += speed;
			}
			if (dmg > 0)
			{
				posPlayer.x += 2 * speed;
				health -= dmg;
				Sounds[DAMAGE]->play();
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			facing = RIGHT;
			if (!bJumping && sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += speed;
			int dmg = map->collisionRight(posPlayer, colisionSize);
			if (dmg == 0) {
				posPlayer.x -= speed;
			}
			if (dmg > 0)
			{
				posPlayer.x -= 2 * speed;
				health -= dmg;
				Sounds[DAMAGE]->play();
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			if (!bJumping) {
				if (facing == RIGHT && sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
				else if (facing == LEFT && sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			}
			posPlayer.y -= speed;
			int dmg = map->collisionUp(posPlayer, colisionSize);
			if (dmg == 0) posPlayer.y += speed;
			else if (dmg > 0) {
				posPlayer.y += 2 * speed;
				health -= dmg;
				Sounds[DAMAGE]->play();
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (!bJumping) {
				if (facing == RIGHT && sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
				else if (facing == LEFT && sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			}
			posPlayer.y += speed;
			int dmg = map->collisionDown(posPlayer, colisionSize);
			if (dmg == 0) posPlayer.y -= speed;
			else if (dmg > 0) {
				posPlayer.y -= 2 * speed;
				health -= dmg;
				Sounds[DAMAGE]->play();
			}
		}
		else {
			if (!bJumping) {
				if (facing == LEFT && sprite->animation() != STAND_LEFT)
					sprite->changeAnimation(STAND_LEFT);
				else if (facing == RIGHT && sprite->animation() != STAND_RIGHT) sprite->changeAnimation(STAND_RIGHT);
			}
		}
		if (bJumping) {
			if (facing == RIGHT && (sprite->animation() != JUMP_RIGHT)) sprite->changeAnimation(JUMP_RIGHT);
			else if (facing == LEFT && (sprite->animation() != JUMP_LEFT)) sprite->changeAnimation(JUMP_LEFT);
			jumpAngle += A_JUMP_ANGLE_STEP;
			if (jumpAngle >= 180) {
				bJumping = false;
				posPlayer.y = startY;
			}
			else {
				if (map->collisionDown(posPlayer, colisionSize) >= 0) posPlayer.x -= speed;
				posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			}
		}
		else if (Game::instance().getKey(S)) {
			if (facing == RIGHT && (sprite->animation() != JUMP_RIGHT)) sprite->changeAnimation(JUMP_RIGHT);
			else if (facing == LEFT && (sprite->animation() != JUMP_LEFT)) sprite->changeAnimation(JUMP_LEFT);
			bJumping = true;
			jumpAngle = 0;
			startY = posPlayer.y;
		}
	}

	sprite->setPosition(glm::vec2(posPlayer.x - spriteMove.x, posPlayer.y - spriteMove.y));
	if (sprite->animation() == MOVE_LEFT || sprite->animation() == MOVE_RIGHT && !bJumping) Sounds[WALK]->play();
	else  Sounds[WALK]->stop();
	bar->update(float(health)/mhealth);
}

void Player::setMap(Map *mapn) {
	map = mapn;
}

void Player::render()
{
	sprite->render();
	bar->render();
}

void Player::setSize(const glm::ivec2 &size){
	colisionSize.x = size.x;
	//colisionSize.y = size.y - A_COLISION_Y;
	colisionSize.y = size.y;
}

void Player::setPosition(const glm::ivec2 &pos)
{
	posPlayer.x = pos.x;
	//posPlayer.y = pos.y + A_COLISION_Y;
	posPlayer.y = pos.y;
}

void Player::AddSounds() {
	cSound* s = new cSound;
	s->load("music/Walk.wav");
	Sounds.push_back(s);
	s = new cSound;
	s->load("music/Damage.wav");
	Sounds.push_back(s);
	s = new cSound;
	s->load("music/Rockhit.wav");
	Sounds.push_back(s);
}

glm::ivec2 Player::getPosition() { return posPlayer; }

glm::ivec2 Player::getSize() { return colisionSize; }

bool Player::IsDead() { return health <= 0; }

void Player::createAvalanche(const glm::ivec2 &Pos, ShaderProgram &shaderProgram) {
	bJumping = false;
	facing = RIGHT;
	health = A_INIT_HEALTH;
	mhealth = health;
	speed = A_INIT_SPEED;
	AddSounds();
	spritesheet.loadFromFile("images/AvalancheDouble.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(256, 128), glm::vec2(0.125f, 0.05f), &spritesheet, &shaderProgram);
	posPlayer = Pos;
	colisionSize = glm::ivec2(A_COLISION_X, A_COLISION_Y);
	hitboxSize = glm::ivec2(A_HITBOX_X, A_HITBOX_Y);
	spriteMove = glm::ivec2(A_SPRITE_X, A_SPRITE_Y);
	sprite->setNumberAnimations(9);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	for (int x = 0; x < 6; x++) {
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(x*0.125f, 0.3f));
	}

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	for (int x = 0; x < 6; x++) {
		sprite->addKeyframe(STAND_LEFT, glm::vec2(x*0.125f, 0.8f));
	}

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	for (int x = 0; x < 8; x++) {
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x*0.125f, 0.4f));
	}

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	for (int x = 0; x < 8; x++) {
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x*0.125f, 0.9f));
	}

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	for (int x = 0; x < 6; x++) {
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x*0.125f, 0.35f));
	}

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	for (int x = 0; x < 6; x++) {
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(x*0.125f, 0.85f));
	}

	sprite->setAnimationSpeed(ATTACK_1_RIGHT, 8);
	for (int x = 0; x < 5; x++) {
		if (x == 3) {
			sprite->addKeyframeWithDmg(ATTACK_1_RIGHT, glm::vec2(x*0.125f, 0.0f), 4, glm::vec2(30, 30), 45);
			sprite->damageKeyframe(x);
		}
		else sprite->addKeyframe(ATTACK_1_RIGHT, glm::vec2(x*0.125f, 0.0f));
	}
	for (int x = 0; x < 5; x++) {
		if (x == 4) {
			sprite->addKeyframeWithDmg(ATTACK_1_RIGHT, glm::vec2(x*0.125f, 0.05f), 6, glm::vec2(30, 40), 45);
			sprite->damageKeyframe(x);
		}
		else sprite->addKeyframe(ATTACK_1_RIGHT, glm::vec2(x*0.125f, 0.05f));
	}
	for (int x = 0; x < 5; x++) {
		if (x == 3) {
			sprite->addKeyframeWithDmg(ATTACK_1_RIGHT, glm::vec2(x*0.125f, 0.1f), 4, glm::vec2(30, 30), 45);
			sprite->damageKeyframe(x);
		}
		else sprite->addKeyframe(ATTACK_1_RIGHT, glm::vec2(x*0.125f, 0.1f));
	}
	for (int x = 0; x < 7; x++) {
		if (x == 4) {
			sprite->addKeyframeWithDmg(ATTACK_1_RIGHT, glm::vec2(x*0.125f, 0.15f), 6, glm::vec2(60, 60), 45);
			sprite->damageKeyframe(x);
		}
		else sprite->addKeyframe(ATTACK_1_RIGHT, glm::vec2(x*0.125f, 0.15f));
	}

	sprite->setAnimationSpeed(ATTACK_1_LEFT, 9);
	for (int x = 0; x < 5; x++) {
		if (x == 3) {
			sprite->addKeyframeWithDmg(ATTACK_1_LEFT, glm::vec2(x*0.125f, 0.5f), 30, glm::vec2(30, 30), -45);
			sprite->damageKeyframe(x);
		}
		else sprite->addKeyframe(ATTACK_1_LEFT, glm::vec2(x*0.125f, 0.5f));
	}
	for (int x = 0; x < 5; x++) {
		if (x == 4) {
			sprite->addKeyframeWithDmg(ATTACK_1_LEFT, glm::vec2(x*0.125f, 0.55f), 50, glm::vec2(30, 40), -45);
			sprite->damageKeyframe(x);
		}
		else sprite->addKeyframe(ATTACK_1_LEFT, glm::vec2(x*0.125f, 0.55f));
	}
	for (int x = 0; x < 5; x++) {
		if (x == 3) {
			sprite->addKeyframeWithDmg(ATTACK_1_LEFT, glm::vec2(x*0.125f, 0.6f), 30, glm::vec2(30, 30), -45);
			sprite->damageKeyframe(x);
		}
		else sprite->addKeyframe(ATTACK_1_LEFT, glm::vec2(x*0.125f, 0.6f));
	}
	for (int x = 0; x < 7; x++) {
		if (x == 4) {
			sprite->addKeyframeWithDmg(ATTACK_1_LEFT, glm::vec2(x*0.125f, 0.65f), 80, glm::vec2(60, 60), -45);
			sprite->damageKeyframe(x);
		}
		else sprite->addKeyframe(ATTACK_1_LEFT, glm::vec2(x*0.125f, 0.65f));
	}

	sprite->setAnimationSpeed(DEAD, 8);
	for (int x = 0; x < 4; x++) {
		sprite->addKeyframe(DEAD, glm::vec2(x*0.125f, 0.20f));
	}

	sprite->changeAnimation(0);
	//sprite->setPosition(glm::vec2(posPlayer.x - 59, posPlayer.y - A_COLISION_Y));
	sprite->setPosition(glm::vec2(posPlayer.x - spriteMove.x, posPlayer.y - spriteMove.y));
}

bool Player::DoDamage() {
	return sprite->damage();
}

int Player::GetDamage() {
	return sprite->getDamage();
}

glm::vec2 Player::GetHitBoxDist() {
	return sprite->getHitBox();
}

glm::vec2 Player::GetHitBox() {
	int d = sprite->getDistance();
	glm::vec2 hb;
	hb.x = posPlayer.x + d;
	hb.y = posPlayer.y;
	return hb;
}

void createBlizzard(const glm::ivec2 &Pos, ShaderProgram &shaderProgram) {}
void createFlurry(const glm::ivec2 &Pos, ShaderProgram &shaderProgram) {}