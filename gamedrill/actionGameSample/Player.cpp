#include "player.h"

const float player_accel              = 0.2f  ;
const float player_accel_inAir        = 0.08f ;
const float player_maxSpeedX          = 9.0f  ;
const float player_maxSpeedY          = 32.0f ;

const float player_jumpVel            = -13.0f;
const float pleyer_brakeRatio         = 2.0f  ;  //1フレームあたりのブレーキ係数　 
const float player_gravity            = 0.3f  ;
const int   player_offsetX            = -12   ;
const int   player_offsetY            = -4    ;
const int   player_AnimWaitnum        = 4     ;
const int   player_AnimWalknum        = 4     ;
const int   player_AnimAttackPowernum = 2     ;
const int   player_AnimAttackShootnum = 4     ;
const int   player_AnimSpeed          = 10    ; // 10フレームに１回アニメーション進める

								   // ウェイト　　            RUN                  ATTACK_POWER       ATTACK_SHOOT          JUMP/UP JUMP/DOWN 
int animationImageX[][4] = { { 0, 64, 128, 192, },{ 0,  64, 128,192, },{ 0,  64,  0, 0, },{ 128, 192,   0, 64 },{ 128, 192, 0, 0, } };
int animationImageY[][4] = { { 0,  0,   0,   0, },{ 64,  64,  64, 64, },{ 128, 128,  0, 0, },{ 128, 128, 192,192 },{ 192, 192, 0, 0, } };

Player::Player()
{
	mState     = PLAYER_WAIT     ;
	mx         = 0               ;
	my         = 0               ;
	mPrevX    = 0               ;
	mPrevY    = 0               ;

	mChipSizeX = 0               ;
	mChipSizeY = 0               ;
	mChipXnum  = 0               ;
	mChipYnum  = 0               ;
	mImg = 0;

	mAnimState = PLAYER_ANIM_WAIT;
	mAnimCount = 0               ;
	mAnimNum   = 0               ;
	mDir       = PLAYER_DIR_LEFT ;

}

Player::~Player()
{
	DeleteGraph( mImg );
}

bool Player::init(char* imgFilename, char* debugFilename, unsigned int chipsizeX, unsigned int chipsizeY)
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

void Player::setCollision(unsigned int offset_left_x, unsigned int offset_top_y, unsigned int w, unsigned int h)
{
	mOffsetDrawX = offset_left_x;
	mOffsetDrawY = offset_top_y;

	mh = h;
	mw = w;
}

void Player::animation()
{
	//////////////////////////////////////////
	// アニメーション関連
	//////////////////////////////////////////
	mAnimCount++;

	// ウェイト
	if (mAnimState == PLAYER_ANIM_WAIT)
	{
		if (mAnimCount > player_AnimSpeed)
		{
			mAnimNum++;
			mAnimCount = 0;

			if (mAnimNum == player_AnimWaitnum)
			{
				mAnimNum = 0;
			}
		}
	}
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
	// ジャンプ
	if (mState == PLAYER_JUMP)
	{
		mAnimState = PLAYER_ANIM_JUMP;
		if (mx - mPrevY < 0)
		{
			mAnimNum = 0;  // 上昇中
		}
		else {
			mAnimNum = 1;  // 下降中
		}
	}

	// 矢のパワー溜める
	if (mState == PLAYER_ATTACK_POWER)
	{
		if (mAnimCount > player_AnimSpeed)
		{
			if (mAnimNum < player_AnimAttackPowernum)
			{
				mAnimNum++;
				mAnimCount = 0;

				if (mAnimNum == player_AnimAttackPowernum)
				{
					mAnimNum = 0;
				}
			}
		}
	}

	// 矢をはなつ
	if (mState == PLAYER_ATTACK_SHOOT)
	{
		if (mAnimCount > player_AnimSpeed)
		{
			if (mAnimNum < player_AnimAttackShootnum)
			{
				mAnimNum++;
				mAnimCount = 0;

				if (mAnimNum == player_AnimAttackShootnum)
				{
					mAnimNum = 0;
					mState = PLAYER_WAIT;
					mAnimState = PLAYER_ANIM_WAIT;
				}
			}
		}
	}

}


void Player::move(Map *pMap, Camera *pCam)
{
	// プレーヤー最高速度
	const float maxSpeed = 16.0;

	//速度
	float vx = mx - mPrevX;
	float vy = my - mPrevY;

	//加速度
	const float friction = 0.5f;
	float ax = 0; 
	float ay = player_gravity;

	// キャラアニメ処理
	animation();

	bool inputflg = false;


	////////////////////////////////////////////////
	// キー入力
	////////////////////////////////////////////////
	// 左キーをおした時
	if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT) == KEY_STATE_PRESSED && mState != PLAYER_ATTACK_POWER)
	{
		//地面の上か？
		if (mState == PLAYER_ONGROUND)
		{
			ax += -player_accel;
			mAnimState = PLAYER_ANIM_RUN;
		}
		else {
			ax += -player_accel_inAir;
		}

		mDir       = PLAYER_DIR_LEFT ;
		inputflg    = true            ;
	}

	// 右キーおした時
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED && mState != PLAYER_ATTACK_POWER)
	{
		if (mState == PLAYER_ONGROUND)
		{
			ax += player_accel;
			mAnimState = PLAYER_ANIM_RUN;
		}
		else {
			ax += player_accel_inAir;
		}
		mDir       = PLAYER_DIR_RIGHT ;
		inputflg    = true             ;
		
	}

	// ジャンプ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_Z) == KEY_STATE_PUSHDOWN)
	{
		if (mState & PLAYER_ONGROUND)
		{
			mState = PLAYER_JUMP;
			mAnimState = PLAYER_ANIM_JUMP;
			vy = player_jumpVel;
		}
	}

	if (!inputflg)
	{
		//地面にいるときの摩擦
		if (mState == PLAYER_ONGROUND)
		{
			//走っていないとき、静止摩擦かける
			if (mState != PLAYER_RUN)
			{
				ax = -friction * vx;
			}
		}
		else
		{
			ax = -friction / 2.0f * vx;
		}
	}

	// 空中でなくかつキー入力が無いときはウェイトアニメに移行
	if (mState & PLAYER_ONGROUND && !inputflg )
	{
		mAnimState = PLAYER_ANIM_WAIT;
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

	// 上に向かっているとき（頭上右上、左上2か所がマップに当たってないか確認)
	if (vy < 0)
	{
		//頭上のチップ番号算出
		int ix1 = pMap->getCollisionMapIndex_X((int)(mx + 4));
		int ix2 = pMap->getCollisionMapIndex_X((int)(mx + mw - 4));
		int iy = pMap->getCollisionMapIndex_Y((int)(my - 1));

		//天井に衝突していた場合
		if (( pMap->getCollisionMapIdFromIndex(ix1, iy) != 0) ||
			  pMap->getCollisionMapIdFromIndex(ix2, iy) != 0 )
		{
			// 頭上ブロック座標をもとにめり込まないよう位置修正
			my = (float)(iy + 1) * pMap->getMapChipSizeY();
		}
	}

	// 下に向かっているとき（足元　右下左下2か所がマップに当たっていないか確認）
	if (vy > 0)
	{
		//足下のチップ番号の左端と右端2か所算出
		int ix1 = pMap->getCollisionMapIndex_X((int)(mx + 4));
		int ix2 = pMap->getCollisionMapIndex_X((int)(mx + mw - 4));
		int iy = pMap->getCollisionMapIndex_Y((int)(my + mh + 1));
		//地面に衝突しているか
		if (pMap->getCollisionMapIdFromIndex(ix1, iy) != 0 ||
			pMap->getCollisionMapIdFromIndex(ix2, iy) != 0 )
		{
			//かつ、自分の真横にブロックが存在していないか
			if (pMap->getCollisionMapIdFromIndex(ix1, iy - 1) == 0 &&
				pMap->getCollisionMapIdFromIndex(ix2, iy - 1) == 0)
			{
				//衝突していた時は下地面を基準にプレーヤーを立たせる位置に修正
				my = (float)iy * pMap->getMapChipSizeY() - mh;

				// 速度をゼロにするために過去y座標も同じ位置に
				mPrevY = my;

				//プレーヤを接地状態に移行
				mState = PLAYER_ONGROUND;
			}
		}
	}

	// 右に向かっているとき (プレーヤー右端上下中央の代表点とマップあたり確認)
	if (vx > 0)
	{
		int ix = pMap->getCollisionMapIndex_X((int)(mx + mw - 1));
		int iy = pMap->getCollisionMapIndex_Y((int)(my + mh / 2));
		if ( pMap->getCollisionMapIdFromIndex(ix, iy) != 0)
		{
			mx = (float)(ix * pMap->getMapChipSizeX() - mw);
		}
	}

	// 左に向かっているとき（プレーヤ左端、上下中央の代表点とマップあたり確認）
	if (vx < 0 )
	{
		int ix = pMap->getCollisionMapIndex_X((int)(mx + 1));
		int iy = pMap->getCollisionMapIndex_Y((int)(my + mh / 2));
		if ( pMap->getCollisionMapIdFromIndex(ix, iy) != 0)
		{
			mx = (float)((ix + 1) * pMap->getMapChipSizeX());
		}
	}

	// 実は空中にいないか？
	if (mState == PLAYER_ONGROUND)
	{
		//足下のチップ番号の左端と右端2か所算出
		int ix1 = pMap->getCollisionMapIndex_X((int)(mx + 1));
		int ix2 = pMap->getCollisionMapIndex_X((int)(mx + mw - 1));
		int iy = pMap->getCollisionMapIndex_Y((int)(my + mh + 1));

		// 2点とも空中か？
		if (pMap->getCollisionMapIdFromIndex(ix1, iy) == 0 &&
			pMap->getCollisionMapIdFromIndex(ix2, iy) == 0)
		{
			//プレーヤを空中状態に移行
			mState = PLAYER_JUMP;
		}
	}
	printf("[%d, %d] prev[%d, %d] anim %d [%d] vx %.2f ax %.2f\n", (int)mx, (int)my, (int)mPrevX, (int)mPrevY, mAnimState, mAnimNum, vx, ax);
}

void Player::draw( Camera *pCam )
{
	//カメラのオフセット取得
	int camx, camy;

	camx = pCam->GetCameraX();
	camy = pCam->GetCameraY();

	//状態に応じて描画～　TODO
	DrawRectGraph((int)mx - camx - mOffsetDrawX,
		          (int)my - camy - mOffsetDrawY,
		          animationImageX[mAnimState][mAnimNum],
		          animationImageY[mAnimState][mAnimNum],
		          64, 64, mImg, TRUE, mDir);

	// デバッグ（当たり判定画像）描画　リリース時に消す。
	DrawRectGraph((int)mx - camx, (int)my - camy, 0, 0, mChipSizeX, mChipSizeY, mDebugImg, TRUE, FALSE);
}



