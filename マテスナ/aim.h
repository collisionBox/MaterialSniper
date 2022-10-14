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
	//�^�[�Q�b�g�Ɏg�p
	float GetExRate() const { return ExRate; }
	int GetMouseX()const { return mouseX; }
	int GetMouseY()const { return mouseY; }
	bool GetIsLeftClick()const { return isLeftClick; }
	//�e���Ɏg�p
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
	float ExRate;//�g�嗦
	int prevMousePosX;
	int prevMousePosY;
	const float  magnificationRate = 3.0f;//�Y�[���{��
};

