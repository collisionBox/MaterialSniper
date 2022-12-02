#include "DxLib.h"
#include "environment.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	// ��ʃ��[�h�̃Z�b�g
	//SetBackgroundColor(100, 100, 100);
	SetGraphMode(windowX, windowY, 32);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	//���Ԍv��
	float nowTime = 0;
	float prevTime = nowTime;
	float deltaTime;
	float startTime = (float)(GetNowCount());
	float gameTime;
	//�����V�[���ݒ�
	GAMEINSTANCE.SetScene(new Game);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		//FPS�v�Z
		nowTime = (float)(GetNowCount());
		deltaTime = (nowTime - prevTime) / 1000.0f;
		gameTime = (nowTime - startTime) / 1000.0f;
		
		//��ʏ�����
		ClearDrawScreen();
		// ����ʂ̓��e��\��ʂɔ��f
		//DrawFormatString(200, 200, white, "delta:%f\ntime:%f", deltaTime,gameTime);
		GAMEINSTANCE.Update(gameTime, deltaTime);
		GAMEINSTANCE.Draw();
		ScreenFlip();

		prevTime = nowTime;
	}
	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}