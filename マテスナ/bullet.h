#pragma once
class Aim;
class Target;

class Bullet
{
public:
	Bullet();
	~Bullet();
	void Init();
	void Update(Aim& aim, Target& tag);
	void Draw();
	void DrawBulletMark(float& mouseX, float& mouseY, float& exRate, bool& flag);

private:
	int Markhandle;
	int x, y, z;
	bool fireFlag;
	bool drawFlag;
};