#pragma once
class Aim;
class Target;

class Bullet
{
public:
	Bullet();
	~Bullet();
	void Init();
	void Update(Aim& aim, Target& tag, float gameTime);
	void Draw();
	void DrawBulletMark(float& mouseX, float&mouseY, int& objX, int& objY, float& exRate, bool& flag);
	bool GetImpactFlag() const{ return impactFlag; }
	void SetImpactFlag() { impactFlag = false; }
private:
	int Markhandle;
	int x, y, z;
	bool fireFlag;
	bool drawFlag;
	int prevX, prevY;
	float impactTime;
	bool impactFlag;
};

