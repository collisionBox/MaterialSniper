#include "Particle.h"

//静的メンバ定義
int  Particle::mGraphID     ;  
int  Particle::mGraphSize   ;
int  Particle::mNumSubstance;
bool Particle::mMortionBlurOn = true;

void Particle::setGraph(int graphID)
{
	mGraphID = graphID;
	GetGraphSize(graphID, &mGraphSize, &mGraphSize);
}

void Particle::setStartPos(float x, float y, float vx, float vy)
{
	//初期座標セット
	mx = x;
	my = y;

	// 速度より前座標算出
	mPrevX = mx - vx;
	mPrevY = my - vy;

	mIsHit = false;
}

void Particle::setLifeTime(int frameNum)
{
	mMaxLifeFrameTime = frameNum;
	mNowFrameTime     = mMaxLifeFrameTime;
	mAlive = true;
	mAlpha = 255;
	mNumSubstance++;
}

void Particle::move(Map *pMap)
{
	//過去座標と現在座標から速度算出
	float vx, vy;
	vx = mx - mPrevX;
	vy = my - mPrevY;

	//加速度 
	float ax, ay;
	ax = 0;
	ay = 2.0f; //重力加速度

	vx += ax;
	vy += ay;

	mPrevX = mx;
	mPrevY = my;

	//最高速度でクランプ
	mx += clamp( 32.0f , -32.0f, vx );
	my += clamp( 32.0f , -32.0f, vy );

	// マップのポインタが入っていたらあたり判定考慮
	if (pMap)
	{
		//マップとあたり判定を考慮した座標算出
		mapHit(pMap);
	}

	// 寿命減らす
	mNowFrameTime--;

	if (mNowFrameTime < mMaxLifeFrameTime / 4)
	{
		mAlpha = (int)(255.0f * mNowFrameTime / (mMaxLifeFrameTime / 4) );
	}

	// 寿命が尽きたか？
	if (mNowFrameTime < 0)
	{
		mAlive = false;
		mNumSubstance--;
	}
}

// パーティクル描画
void Particle::draw(Camera *pCam)
{
	int camX, camY;
	camX = pCam->GetCameraX();
	camY = pCam->GetCameraY();

	SetDrawBright(255, mAlpha / 4, 0);
	SetDrawBlendMode(DX_BLENDMODE_ADD, mAlpha);
	DrawGraph((int)mx - camX,
		      (int)my - camY, mGraphID, TRUE);


	// 残像描画
	if (mMortionBlurOn)
	{
		// ヒットした直後なら残像描画しない
		if (mIsHit)
		{
			mIsHit = false;
			return;
		}

		float sx, sy;
		sx = mPrevX;
		sy = mPrevY;

		//パーティクル速度算出
		float ax, ay;
		ax = (mx - mPrevX) ;
		ay = (my - mPrevY) ;

		float length2 = ax * ax + ay * ay;

		// 残像距離算出
		float length = sqrtf(length2);

		// 残像つけない速度ならリターン
		if (length < 5.0f)
			return;

		int  maxLen = (int)length / (mGraphSize / 4);

		//残像用座標増加分
		ax /= maxLen;
		ay /= maxLen;

		//残像スタートα値とαの増分値を算出
		int alphaStart = mAlpha / 3;
		int alphaStep = (mAlpha - alphaStart) / maxLen;

		// 前座標から、現時点の座標まで線分を描くように描画
		int i = 0;

		//残像の描画
		for (int i = 0; i < maxLen; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, alphaStart + alphaStep * i);
			DrawGraph((int)sx - camX,
				(int)sy - camY,
				mGraphID, TRUE);
			    sx += ax;
			    sy += ay;
		}
	}

}

// 残像効果ありなしの切り替え
void Particle::toggleMortionBlur()
{
	if (mMortionBlurOn)
	{
		mMortionBlurOn = false;
	}
	else
	{
		mMortionBlurOn = true;
	}
}

// パーティクルがマップとぶつかったか？
void Particle::mapHit(Map * pMap)
{
	// どちらの向きからブロックに当たったのか？
	// 速度算出
	float vx = mx - mPrevX;
	float vy = my - mPrevY;

	bool ishit = false;

	// 上に向かっているとき
	if (vy < 0)
	{
		int ix1 = pMap->getCollisionMapIndex_X((int)mx + mGraphSize / 2 );
		int iy  = pMap->getCollisionMapIndex_Y((int)my - 1);

		//天井に衝突していた場合めり込み防止位置補正
		if (pMap->getCollisionMapIdFromIndex(ix1, iy) != 0)
		{
			my = (float)(iy + 1) * pMap->getMapChipSizeY();
			ishit = true;
		}
	}
	// 下に向かっているとき
	if (vy > 0)
	{
		int ix1 = pMap->getCollisionMapIndex_X((int)mx + mGraphSize / 2);
		int iy = pMap->getCollisionMapIndex_Y((int)my + mGraphSize);

		// 地面に衝突しているか
		if (pMap->getCollisionMapIdFromIndex(ix1, iy) != 0)
		{

			//かつ自分の真横にブロック存在していないなら地面衝突
			if (pMap->getCollisionMapIdFromIndex(ix1, iy - 1) == 0)
			{
				mPrevY = my;
				my = (float(iy) * pMap->getMapChipSizeY()) - 8;
				ishit = true;
			}
		}
	}
	//右に向かっているとき
	if (vx > 0)
	{
		int ix = pMap->getCollisionMapIndex_X((int)mx + mGraphSize);
		int iy = pMap->getCollisionMapIndex_Y((int)my + mGraphSize / 2);
		if (pMap->getCollisionMapIdFromIndex(ix, iy) != 0)
		{
			mPrevX = mx;
			mx = (float)(ix * pMap->getMapChipSizeX() - 8);
			ishit = true;
		}
	}

	// 左に向かっているとき
	if (vx < 0)
	{
		int ix = pMap->getCollisionMapIndex_X((int)mx);
		int iy = pMap->getCollisionMapIndex_Y((int)my + mGraphSize / 2 );
		if (pMap->getCollisionMapIdFromIndex(ix, iy) != 0)
		{
			mPrevX = mx;
			mx = (float)((ix + 1) * pMap->getMapChipSizeX() + 2 );
			ishit = true;
		}
	}
	// ぶつかったら寿命が縮む
	if (ishit)
	{
		//１つ前のフレームでも衝突し、今回も衝突した場合は即死
		if (mIsHit)
		{
			mAlive = false;
		} 
		else 
		{
			//今回の衝突が初の場合は寿命半分に
			mIsHit = true;
			mNowFrameTime -= mNowFrameTime / 4;
		}
	}
}
