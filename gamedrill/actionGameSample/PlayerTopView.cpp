#include "playertopview.h"

const float player_accel = 0.2f;
const float player_maxSpeedX = 5.0f;
const float player_maxSpeedY = 5.0f;

const int   player_offsetX = -12;
const int   player_offsetY = -4;
const int   player_AnimWaitnum = 4;
const int   player_AnimWalknum = 4;
const int   player_AnimSpeed = 10; // 10フレームに１回アニメーション進める


PlayerTopview::PlayerTopview()
{
	mState = PLAYER_WAIT;
	mx = 0;
	my = 0;
	mPrevX = 0;
	mPrevY = 0;

	mChipSizeX = 0;
	mChipSizeY = 0;
	mChipXnum = 0;
	mChipYnum = 0;
	mImg = 0;

	mAnimState = PLAYER_ANIM_WAIT;
	mAnimCount = 0;
	mAnimNum = 0;
	mDir = PLAYER_DIR_DOWN;

}

PlayerTopview::~PlayerTopview()
{
	DeleteGraph(mImg);
}

bool PlayerTopview::init(char* imgFilename, char* debugFilename, unsigned int chipsizeX, unsigned int chipsizeY)
{
	mImg = LoadGraph(imgFilename);

	if (!imgFilename)
		return false;

	// デバッグ画像読み込み
	mDebugImg = LoadGraph(debugFilename);
	if (!mDebugImg)
		return false;

	mChipSizeX = chipsizeX;
	mChipSizeY = chipsizeY;

	//デフォルト時はデバック画像からコリジョン抜き出す
	int w, h;
	GetGraphSize(mDebugImg, &w, &h);
	setCollision(0, 0, w, h);

	return true;
}

void PlayerTopview::setCollision(unsigned int offset_left_x, unsigned int offset_top_y, unsigned int w, unsigned int h)
{
	mOffsetDrawX = offset_left_x;
	mOffsetDrawY = offset_top_y;

	mh = h;
	mw = w;
}

void PlayerTopview::animation()
{
	//////////////////////////////////////////
	// アニメーション関連
	//////////////////////////////////////////
	mAnimCount++;

	// 歩き
	if (mAnimState == PLAYER_ANIM_RUN)
	{
		mAnimCount++;
		if (mAnimCount > player_AnimSpeed)
		{
			if (mAnimNum < player_AnimWalknum)
			{
				mAnimNum++;
				mAnimCount = 0;

				if (mAnimNum == player_AnimWalknum)
				{
					mAnimNum = 0;
				}
			}
		}
	}

}


void PlayerTopview::setDrawOffset(int ofsX, int ofsY)
{
	mOffsetDrawX = ofsX;
	mOffsetDrawY = ofsY;
}

void PlayerTopview::move(Map *pMap, Camera *pCam)
{
	// プレーヤー最高速度
	const float maxSpeed = 16.0;

	//速度
	float vx = mx - mPrevX;
	float vy = my - mPrevY;

	//加速度
	const float friction = 0.5f;
	float ax = 0.0f;
	float ay = 0.0f;

	// キャラアニメ処理
	animation();

	bool inputLRflg = false;
	bool inputUDflg = false;

	////////////////////////////////////////////////
	// キー入力
	////////////////////////////////////////////////
	// 左キーをおした時
	if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
	{
		ax += -player_accel;
		mAnimState = PLAYER_ANIM_RUN;
		mDir = PLAYER_DIR_LEFT;
		inputLRflg = true;
	}

	// 右キーおした時
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
	{
		ax += player_accel;
		mAnimState = PLAYER_ANIM_RUN;
		mDir = PLAYER_DIR_RIGHT;
		inputLRflg = true;
	}
	// 上キー押したとき
	if (INPUT_INSTANCE.getInput(KEY_INPUT_UP) == KEY_STATE_PRESSED)
	{
		ay -= player_accel;
		mAnimState = PLAYER_ANIM_RUN;
		mDir = PLAYER_DIR_UP;
		inputUDflg = true;
	}
	// 下キー押したとき
	if (INPUT_INSTANCE.getInput(KEY_INPUT_DOWN) == KEY_STATE_PRESSED)
	{
		ay += player_accel;
		mAnimState = PLAYER_ANIM_RUN;
		mDir = PLAYER_DIR_DOWN;
		inputUDflg = true;
	}

	// キー入力が無いときはウェイトアニメに移行
	if (!inputUDflg && !inputLRflg)
	{
		mAnimState = PLAYER_ANIM_WAIT;
	}
	//上下キーの入力がないとき
	if (!inputUDflg)
	{
		vy *= friction;
	}
	//左右キーの入力がないとき
	if (!inputLRflg)
	{
		vx *= friction;
	}

	// 速度に加速度を加算
	vx += ax;
	vy += ay;

	// 最高速度を超えないようにクランプ（-player_maxSpeed ～ +player_maxSpeedの範囲を取るようにする）
	vx = clamp(player_maxSpeedX, -player_maxSpeedX, vx);
	vy = clamp(player_maxSpeedY, -player_maxSpeedY, vy);

	//前の座標を記憶
	mPrevX = mx;
	mPrevY = my;

	//あたり判定座標計算 
	mx = mx + vx;
	my = my + vy;

	// 速度方向によってあたり判定をおこなう
	int ixL, ixR, iy, iy2; // 調査したい座標のマップのインデックス番号

	ixL = pMap->getCollisionMapIndex_X((int)mx);           //左
	ixR = pMap->getCollisionMapIndex_X((int)(mx + mw));  //右

	// 上に向かっているとき(左上＆右上の２点で判定)
	if (vy < 0.0f)
	{
		iy  = pMap->getCollisionMapIndex_Y((int)(my - 1));   // 上

		//上部2点は壁に当たっているか？かつその下は空白ブロックか？
		if ((pMap->getCollisionMapIdFromIndex(ixL, iy) != 0 && pMap->getCollisionMapIdFromIndex(ixL, iy + 1) == 0 )||
			(pMap->getCollisionMapIdFromIndex(ixR, iy) != 0 && pMap->getCollisionMapIdFromIndex(ixR, iy + 1) == 0 ))
		{
 
			//当たっていたときはめり込まない位置に戻す
			my = (float)((iy + 1) * pMap->getMapChipSizeY()) + 1;
			mPrevY = my; //速度ゼロに
		}
	}

	// 下に向かっているとき(左下、右下の2点で判定)
	if (vy > 0.0f)
	{
		iy  = pMap->getCollisionMapIndex_Y((int)(my + mh + 1)); //下

		// 左下右下は壁に当たっているか？かつその下は空白ブロックか？
		if ((pMap->getCollisionMapIdFromIndex(ixL, iy) != 0 && pMap->getCollisionMapIdFromIndex(ixL, iy - 1) == 0) ||
			(pMap->getCollisionMapIdFromIndex(ixR, iy) != 0 && pMap->getCollisionMapIdFromIndex(ixR, iy - 1) == 0))
		{
			my = (float)(iy * pMap->getMapChipSizeY() - mh) - 1;
			mPrevY = my; //速度ゼロに
		}
	}

	iy = pMap->getCollisionMapIndex_Y((int)(my));
	iy2 = pMap->getCollisionMapIndex_Y((int)(my + mh));

	// 右に向かっているとき 
	if (vx > 0.0f)
	{
		ixR = pMap->getCollisionMapIndex_X((int)(mx + mw + 1));  //右

		if ((pMap->getCollisionMapIdFromIndex(ixR,  iy) != 0 && pMap->getCollisionMapIdFromIndex(ixR - 1, iy) == 0 )||
			(pMap->getCollisionMapIdFromIndex(ixR, iy2) != 0 && pMap->getCollisionMapIdFromIndex(ixR - 1, iy2) == 0))
		{
			mx = (float)(ixR * pMap->getMapChipSizeX() - mw) - 1;
			mPrevX = mx;
		}
	}

	// 左に向かっているとき
	if (vx < 0.0f)
	{
		ixL  = pMap->getCollisionMapIndex_X((int)(mx - 1));       //左

		if ((pMap->getCollisionMapIdFromIndex(ixL,  iy) != 0 && pMap->getCollisionMapIdFromIndex(ixL + 1 , iy) == 0) ||
			(pMap->getCollisionMapIdFromIndex(ixL, iy2) != 0 && pMap->getCollisionMapIdFromIndex(ixL + 1, iy2) == 0))
		{
			mx = (float)((ixL + 1) * pMap->getMapChipSizeX()) + 1;
			mPrevX = mx;
		}
	}

	printf("[%d, %d] prev[%d, %d] anim %d [%d] vx %.2f ax %.2f\n", (int)mx, (int)my, (int)mPrevX, (int)mPrevY, mAnimState, mAnimNum, vx, ax);
}

void PlayerTopview::draw(Camera *pCam)
{
	//カメラのオフセット取得
	int camx, camy;

	camx = pCam->GetCameraX();
	camy = pCam->GetCameraY();

	//状態に応じて描画～　TODO
	DrawRectGraph((int)mx - camx + mOffsetDrawX,
		(int)my - camy + mOffsetDrawY,
		mAnimNum * mChipSizeX,
		mDir     * mChipSizeY,
		mChipSizeX, mChipSizeY, mImg, TRUE, FALSE);

	// デバッグ（当たり判定画像）描画　リリース時に消す。
	DrawRectGraph((int)mx - camx, (int)my - camy, 0, 0, mChipSizeX, mChipSizeY, mDebugImg, TRUE, FALSE);
}



