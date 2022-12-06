#pragma once
enum ObjType
{
	ESCORT,
	VIRUS,
};
class Bullet;
class Director;

class Target
{
public:
	static Target& tagInstance() { static Target tag; return tag; }
	Target();
	~Target();
	void Init();
	void Update(Bullet& bul, float& gameTime);
	void Draw(float mouseX, float mouseY, float& exRate, bool& flag, Bullet& bullet);
	void HitTest(float& mouseX, float& mouseY, bool flag, float& gameTime);

	int GetAlpha() const { return alpha; }
	bool GetIsHit() const { return isHit; }
	void SetIsHit() { isHit = false; }
	int GetType() const { return type; }
	float GetSpeed() const { return speed; }
	bool GetAlive() const { return prevAlive; }
	void SetIsAlive() { isAlive = false; }
	float GetX() const { return zoomX; }
	float GetY() const { return zoomY; }
	float GetZ()const { return z; }
	int GetPoint() const { return point; }

private:
	Director* director = nullptr;
	void Behavior(Bullet& bul, float& gameTime);
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
	float x, y, z;
	int type;
	float zoomX, zoomY;
	float rx, ry, lx, ly;
	float speed;
	float vx, vy;
	const float onNozoomExRate = 0.4f;
	bool isHit;
	int imgSizeX;
	int imgSizeY;
	int imgHalfSizeX;
	int imgHalfSizeY;
	int zoomCalculation;
	
	int hitNum;
	int criticalNum;
	int point;
};