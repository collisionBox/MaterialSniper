#pragma once
enum ObjType
{
	STOP,
	MOVE
};
class Bullet;

class Target
{
public:
	Target();
	~Target();
	void Init(ObjType type);
	void Update();
	void Draw(int& mouseX, int& mouseY, float& exRate, bool& flag, Bullet& bullet);
	void Behavior();
	void HitTest(int& mouseX, int& mouseY, bool& flag);

	int GetAlpha() const { return alpha; }
	bool GetIsHit() const { return isHit; }
	int GetType() const { return type; }
	int GetSpeed() const { return speed; }

private:

	int handle;
	int filterHandle;
	int alpha;
	int r;
	const int minR = 12;
	const int maxR = minR + (5 * 9);
	bool isAlive;
	bool fadeFlag;
	const int deltaAlphaNum = 30;
	int x, y, z;
	int type;
	int zoomX, zoomY;
	int rx, ry, lx, ly;
	int speed;
	int vx, vy;
	const float defaultExRate = 0.2;
	bool isHit;
	const int imgSize = 150;
	const int imgHalfSize = imgSize / 2;
	const int zoomCalculation = imgSize / 6 * 3 + imgSize;
	
	
};