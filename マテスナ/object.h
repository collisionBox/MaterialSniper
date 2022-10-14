#pragma once
enum ObjType
{
	STOP,
	MOVE
};
class Target
{
public:
	Target();
	~Target();
	void Init(ObjType type);
	void Update();
	void Draw(int& mouseX, int& mouseY, float& exRate, bool& flag);
	void Behavior();
	void HitTest(int& mouseX, int& mouseY, bool& flag);
	int GetAlpha() const { return alpha; }
	bool getIsHit() const { return isHit; }
private:
	int handle;
	int alpha;
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
	
	
};