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
	void DrawBulletMark(float& mouseX, float&mouseY, int& objX, int& objY, float& exRate, bool& flag);
	bool GetImpactFlag() const{ return impactFlag; }
private:
	int Markhandle;
	int x, y;
	float z;
	const float initialV = 8.68f;//èâë¨

	bool aliveFlag;
	bool fireFlag;
	bool drawFlag;
	int prevX, prevY;
	bool impactFlag;
};

