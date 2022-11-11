#include "DxLib.h"
#include "Sequence.h"
#include "mapManager.h"
#include "player.h"
#include "input.h"
#include "bitmapText.h"

#ifndef __GAME_H__
#define __GAME_H__

// �R�����g�ɂ���ƃE�B���h�E�̂݃��[�h��
#define DEBUG_CONSOLE

#ifdef DEBUG_CONSOLE
#pragma comment(linker, "/SUBSYSTEM:CONSOLE" )
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS" )
#endif

class Sequence;    // �O�u����
class BitmapText;


// ��`�\����
typedef struct rectangle
{
	int sx, sy;
	int width, height; 
}rectangle;

bool isHitRect( rectangle *rect1, rectangle *rect2 ); 


// �Q�[���N���X
class Game
{
private:
	Game();      //�V���O���g��

	void      input();// ����
	void      draw(); // �`��
	int       move(); // �ړ�
	int       update();// ��ԑJ�ڂ̃A�b�v�f�[�g
	void      init(); // ������
	
	// �V�X�e�������ϐ�����
	Sequence *mNowState;  // ���݂̃X�e�[�g
	Sequence *mNextState; // ���̃X�e�[�g

	int       mMouseX, mMouseY;         // �}�E�X���W
	int       mMouseButton;
	int       mScreenWidth, mScreenHeight ;// �E�B���h�E���E����
	bool      mFullScreen ;
	bool      mIsGameQuit ;
	SHELLEXECUTEINFO *mAppInfo;                //�Q�[���I�����A�v���N�����
	// ���\�[�X��`



public:
	static Game& GameInstance()
	{
		static Game GameSys;
		return GameSys;
	}

	~Game();

	BitmapText systemText;

	void Run();  // �Q�[�����s
	void setScreen( int width, int height, bool Fullscreen );
	int  getScreenWidth() { return mScreenWidth ;}
	int  getScreenHeight(){ return mScreenHeight;}
	int  getMouseX()      { return mMouseX ; }
	int  getMouseY()      { return mMouseY ; }
	int  getMouseButton() { return mMouseButton ; } 
	
	void ResourceInit();
	void setFirstSequence( Sequence *Seq ) { mNowState = mNextState = Seq; }

	void      callQuit( char *nextappPath, char* nextexename );


};

// �N�����v�֐�
float clamp(float clampMax, float clampMin, float val);
// �l�惉���_���֐�
float getRandom(float min, float max);


#define GAMEINSTANCE Game::GameInstance()

#endif __GAME_H__