#pragma once

class Target
{
public:
	Target();
	~Target();
	void Init();
	void Update();
	void Draw();
	void Behavior();
	void HitTest();
private:
	int handle;
	int bulletMarkHandle;
	int x, y, z;
	int rx, ry, lx, ly;
	int speed;
	int vx, vy;
	float exRate;
	const float defaultExRate = 0.2;
	bool isHit;
	const int imgHalfSize = 640 / 2;
};