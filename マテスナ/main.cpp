#include "DxLib.h"
#include "environment.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	// ��ʃ��[�h�̃Z�b�g
	SetBackgroundColor(100, 100, 100);
	SetGraphMode(windowX, windowY, 32);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);

	float nowTime = 0;
	float prevTime = nowTime;
	float deltaTime;
	float startTime = GetNowCount();
	float gameTime;
	Aim aim;
	Target target;
	Bullet bullet;
	Director director;
	//������
	aim.Init();
	target.Init();
	bullet.Init();
	Game game;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		//FPS�v�Z
		nowTime = GetNowCount();
		deltaTime = (nowTime - prevTime) / 1000.0f;
		gameTime = (nowTime - startTime) / 1000.0f;

		//��ʏ�����
		ClearDrawScreen();
		game.game(gameTime, deltaTime);
		/*aim.Update(target,bullet,gameTime, deltaTime);
		target.Update(gameTime);
		bullet.Update(aim, target);
		director.Update(target, bullet, aim, gameTime);*/
		// ����ʂ̓��e��\��ʂɔ��f
		DrawFormatString(200, 200, white, "%f\n%f", deltaTime,gameTime);
		
		ScreenFlip();

		prevTime = nowTime;
	}
	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}