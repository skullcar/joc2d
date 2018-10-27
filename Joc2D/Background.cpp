#include "Background.h"


Background::Background(){

}

void Background::init(char* back,glm::ivec2 size,ShaderProgram &shaderProgram){
	text.loadFromFile(back, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(1.0f,1.0f), &text, &shaderProgram);
	sprite->setPosition(glm::vec2(0, 0));
	bg_size = size;
}

void Background::render(){
	sprite->render();
}

glm::ivec2 Background::getSize() { return bg_size; }