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
	const bool GetClick() { return isRightClick; }
	const int GetMousePos() { return mouseX, mouseY; }

private:
	int handle;
	int bgHandle;
	int crosshairHandle;
	int TempScreen;
	float Angle;
	int mouseX, mouseY;
	int x, y;
	bool isRightClick;
	float ExRate;//ägëÂó¶
	int prevMousePosX;
	int prevMousePosY;

	const float  magnificationRate = 3.0f;//ÉYÅ[ÉÄî{ó¶
};

