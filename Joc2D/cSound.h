#ifndef _CSOUND_INCLUDE
#define _CSOUND_INCLUDE

#include "General.h"

class cSound {
public:
	cSound();

	bool load(const std::string & filename);
	void play();
	void stop();

private:
	SoundBuffer* buffer;
	Sound* sound;
};

#endif
