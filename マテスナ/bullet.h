#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();
	void Init();
	void Update(bool& flag, int& posX, int& posY);
	void Draw();
	void DrawBulletMark(bool& flag, int& X, int& Y);
	void OnClicBehavior(int& posX, int& posY);

private:
	int handle;
	int x, y, z;
	bool isClic;
	bool drawFlag;
};