#pragma once
class Target;
class Bullet;
class Aim
{
public:
	Aim();
	~Aim();
	void Init();
	void Update(Target& tag, Bullet& bullet, float& gameTime, float& deltaTime);
	//�^�[�Q�b�g�Ɏg�p
	float GetExRate() const { return ExRate; }
	float GetMouseX()const { return x; }
	float GetMouseY()const { return y; }
	bool GetIsLeftClick()const { return isLeftClick; }
	//�e���Ɏg�p
	bool GetIsClick() const { return isRightClick; }
	//�ēɎg�p
	int GetMagazin() const { return magazin; }
	int GetCarriedNum() const { return carriedNum; }
private:
	void Draw(Target& tag, Bullet& bullet);
	void MouseBehavior(Target& tag, float& gameTime, float& deltaTime);
	void MagazinDirector(float& gameTime);
	void FireFlagBehavior();
	void O2gauge(float& gameTIme, float& delatTime);

	int handle;
	int scorpHandle;
	int lectilHandle;
	int aimming;
	int TempScreen;
	float Angle;
	int magazin;//���e��
	int carriedNum;//�e��g�s��
	int maxMagazin = 5;//�}�K�W���T�C�Y
	const int carriedNumMax = maxMagazin * 7;
	const float reloadTime = 1.7f;
	float nowTime;
	float cameraShake;
	float bleathStop = 10.0f;
	float omega;
	float v;
	const float nomalCameraShake = 1.012f;//�ʏ펞�̃u��
	const float stopBreathCameraShake = 0.008f;//���~�ߎ��̃u��
	const float onPantingCameraShake = 0.02f;//���؂ꎞ�̃u��
	float stopBreathTime = 5.0f;//�����~�߂Ă����鎞��
	const float recoverO2 = 20.0f;//�_�f�񕜗�(1�b��20����)
	float breath;
	bool LShiftFlag;
	bool pantingFlag;//���؂�t���O
	bool fireFlag;
	bool reloadFlag;
	int mouseX, mouseY;
	float x, y;
	bool isRightClick;
	bool isLeftClick;
	float ExRate;//�g�嗦
	float prevMousePosX;
	float prevMousePosY;
	const float  magnificationRate = 3.0f;//�Y�[���{��
};

