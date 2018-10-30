#include "Background.h"


Background::Background(){

}

void Background::init(char* back,glm::ivec2 size, glm::vec2 frame,ShaderProgram &shaderProgram){
	text.loadFromFile(back, TEXTURE_PIXEL_FORMAT_RGBA);
	glm::vec2 aux;
	aux.x = size.x * frame.x;
	aux.y = size.y * frame.y;
	sprite = Sprite::createSprite(aux, frame, &text, &shaderProgram);
	sprite->setPosition(glm::vec2(0, 0));
	bg_size = size;
	bg_frame = frame;
}

void Background::render(){
	sprite->render();
}

void Background::update(int deltaTime) {
	sprite->update(deltaTime);
}

void Background::addAnimation() {
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 1);
	sprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(0, glm::vec2(0.0f, 0.5f));
	sprite->changeAnimation(0);
}
glm::ivec2 Background::getSize() { return bg_size; }