#include "DxLib.h"
#include "environment.h"
#include "aim.h"
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
	
	Aim aim;
	Target target;
	aim.Init();
	target.Init();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		aim.Update();
		target.Update();
		

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}