#include "game.h"
#if 0
void Init()
{

}

void Update(float& gameTimw, float& deltaTime)
{
	aim.Update(director, target, bullet, gameTime, deltaTime);
	target.Update(bullet, gameTime);
	bullet.Update(aim, target, gameTime, deltaTime);
	director.Update(target, bullet, aim, gameTime);
}



#else
Game::Game()
{
	Init();
}

Game::~Game()
{

}


SceneBase* Game::Update(float& gameTime, float& deltaTime)
{
	aim.Update(director, target, bullet, gameTime, deltaTime);
	target.Update(bullet, gameTime);
	bullet.Update(aim, target, gameTime, deltaTime);
	director.Update(target, bullet, aim, gameTime);
	return this;
}

void Game::Draw()
{

}

void Game::Init()
{
	director.Init();
	aim.Init();
	target.Init();
	bullet.Init();
}

#endif // 0

