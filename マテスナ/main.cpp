#include "DxLib.h"
#include "environment.h"
#include "aim.h"
#include "Bullet.h"
#include "object.h"

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
	float nowTime = 0;
	float prevTime = nowTime;
	float deltaTime;

	Aim aim;
	Target target;
	Bullet bullet;
	
	aim.Init();
	target.Init();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//FPS�v�Z
		nowTime = GetNowCount();
		deltaTime = (nowTime - prevTime) / 1000.0f;
		//��ʏ�����
		ClearDrawScreen();

		aim.Update(target);
		target.Update();

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
		DrawFormatString(200, 200, white, "%f", deltaTime);
		prevTime = nowTime;
	}
	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}