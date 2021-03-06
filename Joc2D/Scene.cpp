
#include "Scene.h"
#include "Game.h"
#include "Object.h"




#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 15

enum Levels {
	MENU,LEVEL1,LEVEL2,SELECT
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

	sel = new Select;
	sel->init(texProgram);

	
	level = 0;

	Maps = vector<Map>(4);
	Maps[MENU].init(texProgram, glm::ivec2(0,0));
	Maps[LEVEL1].init(texProgram, glm::ivec2(2800, 180));
	Maps[LEVEL2].init(texProgram, glm::ivec2(2800, 180));
	Maps[SELECT].init(texProgram, glm::ivec2(0, 0));

	Backgrounds = vector<Background>(4);
	Backgrounds[MENU].init("images/menu.png", glm::ivec2(640, 960), glm::vec2(1.0f, 0.5f),texProgram);
	Backgrounds[MENU].addAnimation();
	Backgrounds[LEVEL1].init("images/FondoDesierto.png", glm::ivec2(3430, 480), glm::vec2(1.0f, 1.0f), texProgram);
	Backgrounds[LEVEL2].init("images/background2.png", glm::ivec2(1090, 480), glm::vec2(1.0f, 1.0f), texProgram);
	Backgrounds[SELECT].init("images/select.png", glm::ivec2(640, 480), glm::vec2(1.0f, 1.0f), texProgram);

	Maps[LEVEL1].LoadObject("images/fire.png", glm::ivec2(320, 380), 10, texProgram);

	Posplayer = vector<glm::ivec2>(3);
	Posplayer[MENU] = glm::ivec2(0, 0);
	Posplayer[LEVEL1] = glm::ivec2(100, 320);
	Posplayer[LEVEL2] = glm::ivec2(100, 320);

	Musics = vector<char *>(3);
	Musics[MENU] = "music/Menu.ogg";
	Musics[LEVEL1] = "music/getout.ogg";
	Musics[LEVEL2] = "";


	music = new cMusic;

	view = glm::lookAt(glm::vec3(c_x, 0, 0.f), glm::vec3(c_x, 0, -1.f), glm::vec3(0.f, 1.f, 0.f));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	ChangeLevel(MENU);
}

void Scene::update(int deltaTime, int frame)
{
	currentTime += deltaTime;
	glm::ivec2 p;
	glm::ivec2 s;
	if (player != NULL) {
		p = player->getPosition();
		s = player->getSize();
	}
	else {
		p = glm::ivec2(0, 0);
		s = glm::ivec2(0, 0);
	}
	glm::vec2 b = Backgrounds[level].getSize();
	Backgrounds[level].update(deltaTime);
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
	if (player != NULL && player->IsDead()) {
		if (frame_death == 30) GameOver();
		else ++frame_death;
	}
	if (player != NULL) {
		player->update(deltaTime);
		if (player->DoDamage()) {
			int dmg = player->GetDamage();
			glm::vec2 hb = player->GetHitBoxDist();
			glm::vec2 hbc = player->GetHitBox();
			Maps[level].ObjectDamage(hbc, hb, dmg);
		}
	}
	Maps[level].update(deltaTime);
	if (level == SELECT) {
		idP = sel->update(deltaTime,frame);
		if (idP > -1) ChangeLevel(LEVEL1);
	}
	if (level == MENU && (Game::instance().getKey(97))) {
		ChangeLevel(SELECT);
		Game::instance().keyReleased(97);
	}
	if (Game::instance().getKey(98)) ChangeLevel(LEVEL2);
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
	if (player != NULL) {
		player->render();
	}
	if (level == SELECT) sel->render();
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
	if (level == MENU) {
		frame_death = 0;
		if (player != NULL) {
			delete player;
			player = NULL;
		}
		c_x = 0;
	}
	else if (level == SELECT) {
		c_x = 0;
	}
	else {
		if (player != NULL) {
			player->setPosition(Posplayer[l]);
			player->setMap(&Maps[level]);
		}
		if (player == NULL) {
			player = new Player();
			player->init(idP, Posplayer[level], texProgram);
			player->setMap(&Maps[level]);
		}
		c_x = (player->getPosition()).x - (SCREEN_WIDTH / 2);
		if (c_x < 0) c_x = 0;
		
	}
	max_c_x = Backgrounds[level].getSize().x - SCREEN_WIDTH;
	if (c_x > max_c_x + (float(SCREEN_WIDTH) / 2)) c_x = max_c_x;
	Maps[level].SetCx(c_x);

	if (level != SELECT) {
		if(music->loaded()) music->stop();
		music->load(Musics[l]);
		music->play();
	}
}


