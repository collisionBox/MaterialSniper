#pragma once

class Target
{
public:
	Target();
	~Target();
	void Init();
	void Update();
	void Draw(float exRate);
	void Behavior();
	void HitTest();
private:
	int handle;
	int x, y, z;
	int rx, ry, lx, ly;
	int speed;
	int vx, vy;
	const float defaultExRate = 0.2;
	bool isHit;
	const int imgHalfSize = 640 / 2;
};