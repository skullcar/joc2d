
#include "Scene.h"
#include "Game.h"
#include "Object.h"




#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 15

enum Levels {
	MENU,LEVEL1,LEVEL2
};


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(player != NULL)
		delete player;
}


void Scene::init() {
	initShaders();

	spr = "images/1.png";
	level = 0;

	Maps = vector<Map>(3);
	Maps[MENU].init(texProgram, glm::ivec2(0,0));
	Maps[LEVEL1].init(texProgram, glm::ivec2(2800, 180));
	Maps[LEVEL2].init(texProgram, glm::ivec2(2800, 180));

	Maps[LEVEL1].LoadObject("images/fire.png", glm::ivec2(320, 380), 10, texProgram);

	Backgrounds = vector<Background>(3);
	Backgrounds[MENU].init("images/menu.png", glm::ivec2(640, 480), texProgram);
	Backgrounds[LEVEL1].init("images/bg1.png", glm::ivec2(2800, 480), texProgram);
	Backgrounds[LEVEL2].init("images/bg1.png", glm::ivec2(2800, 480), texProgram);

	Posplayer = vector<glm::ivec2>(3);
	Posplayer[MENU] = glm::ivec2(0, 0);
	Posplayer[LEVEL1] = glm::ivec2(100, 320);
	Posplayer[LEVEL2] = glm::ivec2(100, 320);

	player = new Player();
	player->init(Posplayer[level], glm::ivec2(63, 70));
	player->setMap(&Maps[level]);

	c_x = (player->getPosition()).x - (SCREEN_WIDTH / 2);
	if (c_x < 0) c_x = 0;
	max_c_x = Backgrounds[level].getSize().x - SCREEN_WIDTH;
	if (c_x > max_c_x + (float(SCREEN_WIDTH) / 2)) c_x = max_c_x;
	Maps[level].SetCx(c_x);
	view = glm::lookAt(glm::vec3(c_x, 0, 0.f), glm::vec3(c_x, 0, -1.f), glm::vec3(0.f, 1.f, 0.f));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	glm::ivec2 p = player->getPosition();
	glm::ivec2 s = player->getSize();
	glm::vec2 b = Backgrounds[level].getSize();
	if ((p.x + s.x) >= (((2.f / 3.f) * SCREEN_WIDTH) + c_x) && (c_x + SCREEN_WIDTH < b.x)) {
		c_x += 1;
		if (c_x > max_c_x + (float(SCREEN_WIDTH) / 2)) c_x = max_c_x;
		Maps[level].SetCx(c_x);
	}
	else if (p.x <= ((SCREEN_WIDTH / 3.f)+ c_x) && (c_x >= 0)){
		c_x -= 1;
		if (c_x < 0) c_x = 0;
		Maps[level].SetCx(c_x);
	}
	view = glm::lookAt(glm::vec3(c_x, 0.f, 0.f), glm::vec3(c_x, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	if (player->IsDead()) GameOver();
	if (!(player->IsInvisible()))player->update(deltaTime);
	if ((Game::instance().getKey(98))) GameOver();
	Maps[level].update(deltaTime);
	if (level == MENU && (Game::instance().getKey(97))) ChangeLevel(level + 1);
}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("view", view);
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
    texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	Backgrounds[level].render();
	Maps[level].render();
	if (!(player->IsInvisible())) player->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::GameOver() {
	c_x = 0;
	view = glm::lookAt(glm::vec3(c_x, 0.f, 0.f), glm::vec3(c_x, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	ChangeLevel(MENU);
}

void Scene::ChangeLevel(int l) {
	level = l;
	player->setPosition(Posplayer[l]);
	player->setMap(&Maps[level]);
	if (player->IsInvisible()) player->setSprite(spr, texProgram);
	if (l == MENU) player->init(Posplayer[MENU], glm::ivec2(63, 70));
}


