#include "Object.h"
#include "Game.h"



void Object::init(char* spr, const glm::ivec2 &Pos, int d, ShaderProgram &shaderProgram) {
	PosObject = Pos;
	dmg = d;
	LoadSprite(spr,shaderProgram);
	PosObject.y += 70/2;
	health = 73;
}

void Object::render() {
	sprite->render();
}

void Object::update(int deltaTime) {
	sprite->update(deltaTime);
}

int Object::damage() { return dmg; }

glm::ivec2 Object::getPos() { return PosObject; }

void Object::LoadSprite(char* spr, ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile(spr, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 56), glm::vec2(0.25f, 1.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	for (float y = 0.0f; y < 1.0f; y = y + 0.25f) {
		sprite->addKeyframe(0, glm::vec2(y, 0.0f));
	}
	sprite->changeAnimation(0);
	sprite->setPosition(PosObject);
}

bool  Object::getDamage(glm::vec2 hbc, glm::vec2 hb, int dmg) {
	int cox = PosObject.x + 16;
	int coy = PosObject.y + 14;
	if ((abs(hbc.x - cox) < ((hb.x/2) + 16)) &&
		(abs(hbc.y - coy) < ((hb.y/2) + 14))) {
		health -= dmg;
		return true;
	}
	return false;
}

bool Object::Destroyed() {
	return health <= 0;
}

int Object::getHealth() { return health; }