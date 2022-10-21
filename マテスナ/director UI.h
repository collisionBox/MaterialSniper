#pragma once
#include "DxLib.h"
class Target;
class Bullet;
class Aim;
enum Sean
{
	DEMO  ,
	TITLE ,
	PLAY  ,
	OVER  
};
class Director
{
public:
	Director();
	~Director();
	void Init();
	void Update(Target& tag, Bullet& bullet, Aim& aim, float& gameTime);
	void Draw(Target& tag, Bullet& bullet, Aim& aim, float& gameTime);
	void ReloadBlanking(Aim& aim);
	void Sean();
private:
	int bulletHandle;
	int alpha;
	int reloadStringHandle;//
	int blankingSpeed = 6;
	const int x = 1700, y = 950;
};