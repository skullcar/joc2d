#include "Enemy.h"
#include "Game.h"
#include "cSound.h"

Enemy::Enemy() {};

void Enemy::init(const glm::ivec2 &size, int h) {
	bJumping = false;
	health = h;
	AddSounds();
	sizeEnemy = size;
	invisible = true;
}

void Enemy::update(int deltatime) {

}

void Enemy::render() {
	sprite->render();
}

void Enemy::setPosition(const glm::vec2 &pos) { posEnemy = pos; }
void Enemy::setMap(Map *mapn) { map = mapn; }

void Enemy::ChangeSprite(char* spr) { spritesheet.loadFromFile(spr, TEXTURE_PIXEL_FORMAT_RGBA); }

glm::ivec2 Enemy::getPosition() { return posEnemy; }
glm::ivec2 Enemy::getSize() { return sizeEnemy;  }

void Enemy::Invisible(bool inv) { invisible = inv; }
bool Enemy::IsInvisible() { return invisible; }
bool Enemy::IsDead() { return health <= 0; }

void Enemy::AddSounds() {
	cSound* s = new cSound;
	s->load("music/Walk.wav");
	Sounds.push_back(s);
	s = new cSound;
	s->load("music/Damage.wav");
	Sounds.push_back(s);
}


