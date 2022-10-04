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
	//�^�[�Q�b�g�Ɏg�p
	float GetExRate() const { return ExRate; }
	//�e���Ɏg�p
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
	float ExRate;//�g�嗦
	int prevMousePosX;
	int prevMousePosY;

	const float  magnificationRate = 3.0f;//�Y�[���{��
};

