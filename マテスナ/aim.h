#pragma once
class Target;
class Bullet;
class Director;
class Aim
{
public:
	static Aim& GetInstance() { static Aim aim; return aim; }

	Aim();
	~Aim();
	void Init();
	void Update(Director director, Target& tag, Bullet& bullet, float& gameTime, float& deltaTime);
	//ターゲットに使用
	float GetExRate() const { return ExRate; }
	float GetMouseX()const { return x; }
	float GetMouseY()const { return y; }
	bool GetIsLeftClick()const { return isLeftClick; }
	//弾痕に使用
	bool GetIsClick() const { return isRightClick; }
	//監督に使用
	int GetMagazin() const { return magazin; }
	int GetCarriedNum() const { return carriedNum; }
	float GetBreath() { return breath; }
private:
	void Draw(Target& tag, Bullet& bullet);
	void MouseBehavior(Director director, Target& tag, float& gameTime, float& deltaTime);
	void MagazinDirector(float& gameTime);
	void FireFlagBehavior();
	void O2gauge(Director director, float& gameTIme, float& delatTime);
	int handle;
	int scorpHandle;
	int lectilHandle;
	int aimming;
	int TempScreen;
	float Angle;
	int magazin;//装弾数
	int carriedNum;//弾薬携行数
	int maxMagazin = 5;//マガジンサイズ
	const int carriedNumMax = maxMagazin * 7;
	const float reloadTime = 1.7f;
	float nowTime;
	float cameraShake;
	float bleathStop = 10.0f;
	float omega;
	float v;
	const float nomalCameraShake = 0.012f;//通常時のブレ
	const float stopBreathCameraShake = 0.008f;//息止め時のブレ
	const float onPantingCameraShake = 0.04f;//息切れ時のブレ
	float stopBreathTime = 3.0f;//息を止めていられる時間
	const float recoverO2 = 20.0f;//酸素回復量(1秒で20消費)
	float breath;
	bool LShiftFlag;
	bool pantingFlag;//息切れフラグ
	bool fireFlag;
	bool reloadFlag;
	int mouseX, mouseY;
	float x, y;
	bool isRightClick;
	bool isLeftClick;
	float ExRate;//拡大率
	float prevMousePosX;
	float prevMousePosY;
	const float  magnificationRate = 3.0f;//ズーム倍率
	float variableTime;//試験運用　時間をいろいろなところで代入できる変数
	class TextBitmap text;
};

