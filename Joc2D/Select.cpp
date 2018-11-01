
#include "Select.h"
#include "Game.h"
#include <SFML/System/Time.hpp>


enum actions {
	STAND,MOVE
};

Select::Select(){}

void Select::init(ShaderProgram &shaderProgram) {
	sprites = vector<Sprite*>(3);
	
	t1.loadFromFile("images/AvalancheDouble.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprites[0] = Sprite::createSprite(glm::ivec2(340, 212), glm::vec2(0.125f, 0.05f), &t1, &shaderProgram);
	sprites[0]->setNumberAnimations(2);
	sprites[0]->setAnimationSpeed(STAND, 8);
	sprites[0]->addKeyframe(STAND, glm::vec2(0.125f, 0.3f));
	sprites[0]->setAnimationSpeed(MOVE, 8);
	for (int x = 0; x < 6; x++) {
		sprites[0]->addKeyframe(MOVE, glm::vec2(x*0.125f, 0.3f));
	}
	sprites[0]->changeAnimation(STAND);
	sprites[0]->setPosition(glm::vec2(-70, 60));

	t2.loadFromFile("images/AvalancheDouble.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprites[1] = Sprite::createSprite(glm::ivec2(340, 212), glm::vec2(0.125f, 0.05f), &t2, &shaderProgram);
	sprites[1]->setNumberAnimations(2);
	sprites[1]->setAnimationSpeed(STAND, 8);
	sprites[1]->addKeyframe(STAND, glm::vec2(0.125f, 0.3f));
	sprites[1]->setAnimationSpeed(MOVE, 8);
	for (int x = 0; x < 6; x++) {
		sprites[1]->addKeyframe(MOVE, glm::vec2(x*0.125f, 0.3f));
	}
	sprites[1]->changeAnimation(STAND);
	sprites[1]->setPosition(glm::vec2(140, 60));

	t1.loadFromFile("images/AvalancheDouble.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprites[2] = Sprite::createSprite(glm::ivec2(340, 212), glm::vec2(0.125f, 0.05f), &t1, &shaderProgram);
	sprites[2]->setNumberAnimations(2);
	sprites[2]->setAnimationSpeed(STAND, 8);
	sprites[2]->addKeyframe(STAND, glm::vec2(0.125f, 0.3f));
	sprites[2]->setAnimationSpeed(MOVE, 8);
	for (int x = 0; x < 6; x++) {
		sprites[2]->addKeyframe(MOVE, glm::vec2(x*0.125f, 0.3f));
	}
	sprites[2]->changeAnimation(STAND);
	sprites[2]->setPosition(glm::vec2(350, 60));

	select = 0;

	sprites[select]->changeAnimation(MOVE);
}

int Select::update(int deltaTime, int frame) {
	sprites[select]->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		Game::instance().specialKeyReleased(GLUT_KEY_LEFT);
		sprites[select]->changeAnimation(STAND);
		--select;
		if (select < 0) select = 2;
		sprites[select]->changeAnimation(MOVE);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		Game::instance().specialKeyReleased(GLUT_KEY_RIGHT);
		sprites[select]->changeAnimation(STAND);
		++select;
		if (select > 2) select = 0;
		sprites[select]->changeAnimation(MOVE);
	}
	if (Game::instance().getKey(97)) return select;
	return -1;
}

void Select::render() {
	sprites[0]->render();
	sprites[1]->render();
	sprites[2]->render();
}