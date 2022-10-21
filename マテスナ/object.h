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
	void Init();
	void Update(float& gameTime);
	void Draw(float mouseX, float mouseY, float& exRate, bool& flag, Bullet& bullet);
	void Behavior(float& gameTime);
	void HitTest(int& mouseX, int& mouseY, bool& flag, float& gameTime);

	int GetAlpha() const { return alpha; }
	bool GetIsHit() const { return isHit; }
	void SetIsHit() { isHit = false; }
	int GetType() const { return type; }
	int GetSpeed() const { return speed; }
	bool GetAlive() const { return prevAlive; }

private:

	int handle;
	int filterHandle;
	int alpha;
	int r;
	const int minR = 12;
	const int maxR = minR + (5 * 9);
	bool isAlive;
	bool prevAlive;
	bool fadeFlag;
	const int deltaAlphaNum = 30;
	float deadTime;
	const float waitTime = 1.5f;
	int x, y, z;
	int type;
	int zoomX, zoomY;
	int rx, ry, lx, ly;
	int speed;
	int vx, vy;
	const float onNozoomExRate = 0.4;
	bool isHit;
	int imgSizeX;
	int imgSizeY;
	int imgHalfSizeX;
	int imgHalfSizeY;
	int zoomCalculation;
	
	
};