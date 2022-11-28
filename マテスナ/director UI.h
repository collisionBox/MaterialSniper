#pragma once
class Target;
class Bullet;
class Aim;
class TextBitmap;

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
	static Director& directorInstance() { static Director director; return director; }
	Director();
	~Director();
	void Init();
	void Update(Target& tag, Bullet& bullet, Aim& aim, float& gameTime);
	int BreakNum() { return breakNum++; }

private:
	TextBitmap text;
	void ReloadBlanking(Aim& aim);
	void O2Gauge(Aim& aim);
	int bulletHandle;
	int alpha;
	int reloadStringHandle;//
	int blankingSpeed = 6;
	const int x = 1700, y = 950;
	int prevTime;
	int red, green, blue;
	float min = 710.0f;
	float max = 1210.0f;
	float valiable;
	float gauge;
	unsigned int breakNum;//åÇîjêî
};