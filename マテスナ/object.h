#pragma once

class Target
{
public:
	Target();
	~Target();
	void Init();
	void Update();
	void Draw(int mouseX, int mouseY, float exRate, bool flag);
	void Behavior();
	void HitTest(int mouseX, int mouseY);
	int GetAlpha() const { return alpha; }
	bool getIsHit() const { return isHit; }
private:
	int handle;
	int alpha;
	bool isAlive;
	bool fadeFlag;
	const int deltaAlphaNum = 30;
	int x, y, z;
	int rx, ry, lx, ly;
	int speed;
	int vx, vy;
	const float defaultExRate = 0.2;
	bool isHit;
	const int imgHalfSize = 150 / 2;
};