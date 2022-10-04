#pragma once

class Target;
class Aim
{
public:
	Aim();
	~Aim();
	void Init();
	void Update(Target tag);
	void Draw(Target tag);
	void Zoom();
	void MouseBehavior();
	//ターゲットに使用
	float GetExRate() const { return ExRate; }
	//弾痕に使用
	bool GetIsClick() const { return isRightClick; }
	int GetMousePosX() const { return mouseX; }
	int GetMousePosY() const { return mouseY; }

private:
	int handle;
	int bgHandle;
	int crosshairHandle;
	int TempScreen;
	float Angle;
	int mouseX, mouseY;
	int x, y;
	bool isRightClick;
	float ExRate;//拡大率
	int prevMousePosX;
	int prevMousePosY;

	const float  magnificationRate = 3.0f;//ズーム倍率
};

