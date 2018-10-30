#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE



#include "General.h"
#include "ShaderProgram.h"
#include "Player.h"
#include "Background.h"
#include "Map.h"
#include "cSound.h"
#include "cMusic.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void GameOver();
	void ChangeLevel(int l);

private:
	Map *map;
	Player *player;
	Background *background;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection,view;
	int c_x, max_c_x;
	int level;
	char * spr;
	vector<Map> Maps;
	vector<Object> Objects;
	vector<glm::ivec2> Posplayer;
	vector<cSound> Sounds;
	vector<Background> Backgrounds;
	vector<char *> Musics;
	cMusic *music;
};


#endif // _SCENE_INCLUDE

