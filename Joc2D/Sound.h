#ifndef _SOUND_INCLUDE
#define _SOUND_INCLUDE

#pragma comment(lib, "irrKlang.lib")

#include <stdio.h>
#include <vector>
#include <irrKlang.h>

using namespace std;

class Sound {
public:
	Sound();
	void Play();
	void Stop();
private:
	char* path;
};



class SoundManager {
public:
	SoundManager();
	void LoadSound(char* path);
	void Play(int id);
private:
	void Load(int id);
	void Relase(int id);

	vector<Sound> sounds;
};



#endif