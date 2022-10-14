#pragma once
class Target;
class Bullet;
class Aim
{
public:
	Aim();
	~Aim();
	void Init();
	void Update(Target& tag, Bullet& bullet);
	void Draw(Target& tag, Bullet& bullet);
	void Zoom();
	void MouseBehavior();
	//ターゲットに使用
	float GetExRate() const { return ExRate; }
	int GetMouseX()const { return mouseX; }
	int GetMouseY()const { return mouseY; }
	bool GetIsLeftClick()const { return isLeftClick; }
	//弾痕に使用
	bool GetIsClick() const { return isRightClick; }

private:
	int handle;
	int bgHandle;
	int crosshairHandle;
	int TempScreen;
	float Angle;
	
	int mouseX, mouseY;
	int x, y;
	bool isRightClick;
	bool isLeftClick;
	float ExRate;//拡大率
	int prevMousePosX;
	int prevMousePosY;
	const float  magnificationRate = 3.0f;//ズーム倍率
};

