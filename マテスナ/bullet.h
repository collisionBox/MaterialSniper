#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();
	void Init();
	void Update(bool& flag, int& posX, int& posY, float& exRate);
	void Draw();
	void DrawBulletMark(bool& flag, float& exRate);

private:
	int Markhandle;
	int x, y, z;
	bool drawFlag;
};