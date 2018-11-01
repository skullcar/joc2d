
#include "Health.h"

Health::Health(){

}

void Health::init(ShaderProgram &shaderProgram) {
	g.loadFromFile("images/green.png", TEXTURE_PIXEL_FORMAT_RGBA);
	r.loadFromFile("images/red.png", TEXTURE_PIXEL_FORMAT_RGBA);
	gs = Sprite::createSprite(glm::vec2(290,40), glm::vec2(1.f,1.f), &g, &shaderProgram);
	rs = Sprite::createSprite(glm::vec2(290, 40), glm::vec2(1.f, 1.f), &r, &shaderProgram);
	gs->setPosition(glm::vec2(42, 41));
	rs->setPosition(glm::vec2(42, 41));
	sp = &shaderProgram;
}

void Health::update(float health) {
	Sprite *aux = gs;
	gs = Sprite::createSprite(glm::vec2(290 * health, 40), glm::vec2(1.f, 1.f), &g, sp);
	gs->setPosition(glm::vec2(42, 41));
	delete aux;
}

void Health::render() {
	rs->render();
	gs->render();
}