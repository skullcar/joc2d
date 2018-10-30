#include "cMusic.h"

cMusic::cMusic() {
	l = false;
}

void cMusic::load(char* filename) {
	music = new Music;
	music->openFromFile(filename);
	music->setLoop(true);
	music->setVolume(12.0f);
	l = true;
}

void cMusic::play() {
	if (music->getStatus() != Music::Playing) music->play();
}

void cMusic::stop() {
	if (music->getStatus() == Music::Playing) music->stop();
}

bool cMusic::loaded() { return l; }