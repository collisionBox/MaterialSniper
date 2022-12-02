#pragma once
class Aim;
class Target;

class Bullet
{
public:
	Bullet();
	~Bullet();
	void Init();
	void Update(Aim& aim, Target& tag, float& gameTime, float& deltaTime);
	void Draw();
	void DrawBulletMark(float& mouseX, float&mouseY, float& objX, float& objY, float& exRate, bool& flag);
private:
	int Markhandle;
	float x, y;
	float z;
	const float initialV = 8.68f;//èâë¨

	bool aliveFlag;
	bool fireFlag;
	bool drawFlag;
	float prevX, prevY;
};

