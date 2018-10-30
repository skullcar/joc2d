#include "cSound.h"

cSound::cSound() {}

bool cSound::load(const string &filename) {
	buffer = new SoundBuffer;
	bool res = buffer->loadFromFile(filename);
	sound = new Sound;
	sound->setBuffer(*buffer);

	return res;
}

void cSound::play() {
	if (sound->getStatus() != Music::Playing) sound->play();
}

void cSound::stop() {
	sound->pause();
}