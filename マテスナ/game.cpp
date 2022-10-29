#include "game.h"

void Game::game(float& gameTime, float& deltaTime)
{
	Update(gameTime, deltaTime);
	
}

void Game::Update(float& gameTime, float& deltaTime)
{
	aim.Update(target, bullet, gameTime, deltaTime);
	target.Update(bullet, gameTime);
	bullet.Update(aim, target, gameTime);
	director.Update(target, bullet, aim, gameTime);
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
