#include "DxLib.h"
#include "Game.h"
#include "Sequence.h"

#include "qSelector.h"
//#include "SoftBodyTest.h"

int		WINAPI		myWinMain( HINSTANCE hInstance	,HINSTANCE hPreInst	,LPSTR     CmdLine	,int CmdShow ,
							   int screen_x, int screen_y, bool FullScreen)
{

	// �X�N���[���Z�b�g
	GAMEINSTANCE.setScreen(screen_x, screen_y, FullScreen);

	// �J�n�V�[�P���X��ݒ�
	GAMEINSTANCE.setFirstSequence(new QuestSelector);

	// �Q�[���J�n
	GAMEINSTANCE.Run();

	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////
// �R���\�[����ʂ���Windows�̂���@�ɔ�Ԃ��߂̃R�[�h
////////////////////////////////////////////////////////////////////////////////////////
void windowOpen(int screen_x, int screen_y, bool FullScreen)
{
	HINSTANCE	hInstance	= GetModuleHandle(0);
	int			iCmdShow	= SW_SHOWDEFAULT ;

	myWinMain( hInstance, NULL, NULL, iCmdShow, screen_x, screen_y, FullScreen);
}

// DOS�����̃G���g���[�|�C���g
int main(void)
{
	windowOpen(800, 600, false);
	return 0;
}

// �E�B���h�E�V�X�e���̎��̃G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	main();
	return 0;
}