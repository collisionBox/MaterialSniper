#include "Game.h"


bool isHitRect( rectangle *rect1, rectangle *rect2 )
{
	// �����蔻�������� 
	// (mx1 <= ex2 && 
	//  ex1 <= mx2 &&
	//  my1 <= ey2 &&
	//  ey1 <= my2)

	return (rect1->sx <= rect2->sx + rect2->width  &&
		    rect2->sx <= rect1->sx + rect1->width  &&
			rect1->sy <= rect2->sy + rect2->height &&
			rect2->sy <= rect1->sy + rect1->height);
}

Game::Game()
{
	mMouseX = mMouseY = 0     ;
	mScreenWidth         = 1024  ;
	mScreenHeight        = 768   ;
	mNowState            = NULL  ;
	mNextState           = NULL  ;
	mIsGameQuit          = false ;
	mAppInfo             = NULL  ;

}

void Game::ResourceInit()
{

}

Game::~Game()
{

}

void Game::draw()
{
	if( mNowState ) mNowState->draw(); 
}

void Game::setScreen( int width, int height, bool FullScreen )
{
	mScreenWidth  = width      ;
	mScreenHeight = height     ;
	mFullScreen   = FullScreen ;
	init();
}


int Game::move()
{

	INPUT_INSTANCE.update();
	if( mNowState ) mNextState = mNowState->move();

	return 0;

}

int Game::update()
{
	//���̃X�e�[�^�X
	if( mNextState != mNowState )
	{
		delete mNowState;
		mNowState = mNextState;
	}

	//�I������
	if( !mNowState ) return -1;

	return 0;
}

void Game::init()
{
	if( !mFullScreen )
	{
		ChangeWindowMode( TRUE );
	}
	SetGraphMode( mScreenWidth, mScreenHeight, 32, 60 );
    DxLib_Init();   // DX���C�u��������������

	SetMouseDispFlag( true );
	SetDrawScreen( DX_SCREEN_BACK ); //�`���𗠉�ʂɐݒ�

	systemText.setFontImage(16, 6, "image/font.bmp");
	systemText.setFontColor(255, 255, 255);
	systemText.setFontShadowOffset(1, 2);
	systemText.setFontColorShadow(64, 64, 64);
	systemText.reMapText(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\tabcdefghijklmnopqrstuvwxyz{|}~\\");
}

void Game::input()
{
	GetMousePoint( &mMouseX, &mMouseY );
	mMouseButton = GetMouseInput();	
}

void Game::Run()
{

	bool ProgramLooping = true;

	LONGLONG nowCount, prevCount;                      // �}�C�N���b(100������1�b�P�ʂŎ����擾)
	nowCount = prevCount = GetNowHiPerformanceCount();
	float waitFrameTime = 15500;                       // 16000�}�C�N���b = 16�~���b = 0.016�b

	//�Q�[�����[�v
	while( ProgramLooping )
	{
		// deltaTime�v��
		float deltaTime;
		nowCount = GetNowHiPerformanceCount();
		deltaTime = (nowCount - prevCount) / 1000000.0f;

        if( ProcessMessage() != 0 ){
                break;
		}
        if( CheckHitKey(KEY_INPUT_ESCAPE) == 1 ){
                break;
        }
		//�Q�[���֘A����
		input();
		move();
		if( update() ) break;

		if( mIsGameQuit ) break;

		draw();
		ScreenFlip();

		//60FPS�҂�
		while (GetNowHiPerformanceCount() - nowCount < waitFrameTime)
		{
			;
		}
		prevCount = nowCount;

	}

	DxLib_End();
}

void Game::callQuit( char *nextappPath, char* nextexename )
{
	mAppInfo = new SHELLEXECUTEINFO;
	memset( mAppInfo, 0, sizeof(SHELLEXECUTEINFO) );
	mAppInfo->cbSize       = sizeof(SHELLEXECUTEINFO);
	mAppInfo->fMask        = SEE_MASK_NO_CONSOLE     ;
	mAppInfo->hwnd         = GetMainWindowHandle()   ; 
	mAppInfo->lpParameters = NULL                    ;
	mAppInfo->lpDirectory  = _T(nextappPath)           ; //�p�X
	mAppInfo->nShow        = SW_SHOWNORMAL           ;
	mAppInfo->lpFile       = _T(nextexename);
	
	mIsGameQuit = true;

}


float clamp(float clampMax, float clampMin, float val)
{
	if (clampMax < val || clampMin > val)
	{
		if (clampMax < val)
			return clampMax;
		if (clampMax > val)
			return clampMin;
	}

	return val;
}

float getRandom(float min, float max)
{
	float length  = max - min;
	float tmprand = (rand() % 10000) / 10000.0f;

	float ret;
	ret = tmprand * length + min;

	return ret;
}
