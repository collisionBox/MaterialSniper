#include "game.h"

Game::Game()
{
	
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
	aim.Init();
	target.Init();
	bullet.Init();
}
