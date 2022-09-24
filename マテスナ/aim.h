#pragma once

class Aim
{
public:
	Aim();
	~Aim();
	void Init();
	void Update();
	void Draw();
	void Zoom();
	void MouseBehavior();

private:
	int handle;
	int bgHandle;
	int MaskScreen;
	int TempScreen;
	float Angle;
	int mouseX, mouseY;
	int i;
	float x, y;
	bool isRightClick;
	float ExRate;//Šg‘å—¦
	int prevMousePosX;
	int prevMousePosY;

	const float  magnificationRate = 3.0f;//ƒY[ƒ€”{—¦
};

