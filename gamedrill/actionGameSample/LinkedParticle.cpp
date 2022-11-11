#include "LinkedParticle.h"

float LinkedParticle::mGravity       = 0.0f   ;
float LinkedParticle::mMaxSpeed      = 5.0f   ;
float LinkedParticle::mFrictionRatio = 0.95f  ;
float LinkedParticle::mEpsiron       = 0.0001f;

unsigned int ColPallete[] = 
{ 
                   0xff0000ff, // CONSTRAINT
                   0xff00aa00, // SLEEP
                   0xffffff00, // ACTIVE
                   0xffffaa00, // ONGROUND
				   0xffff0000, // HIT
				   0xff000000, // RESERVED
};

LinkedParticle::LinkedParticle()
{
	mx           = 0.0f ; // パーティクル位置
	my           = 0.0f ; // 
	mPrevX      = 0.0f ; // パーティクル前回位置 
	mPrevY      = 0.0f ; // 
	mFx          = 0.0f ; // パーティクルにかかる力
	mFy          = 0.0f ; // 
	mWeight      = 1.0f ; // パーティクル重さ
	mbConstraint = false; // 拘束パーティクルか？
	mbHitWall    = false; // 壁に現在当たっているか？
	mbActive     = false; // 計算対象か？
}

LinkedParticle::~LinkedParticle()
{
	//パーティクル連結配列削除
	if (!mParticleArray.empty())
	{
		mParticleArray.clear();
	}
}

// 質点の定義
void LinkedParticle::setMassPoint(float posx, float posy, float weight)
{
	mx = mPrevX = posx                 ;
	my = mPrevY = posy                 ;
	mFx = mFy    = 0.0f                 ;
	mbConstraint  = false                ;
	mbHitWall     = false                ;
	mbActive      = true                 ;
	mWeight       = weight               ;
	mState        = LP_STATE_ENUM_ACTIVE ;
}

void LinkedParticle::setConstraint()
{
	mbConstraint = true                     ;
	mState       = LP_STATE_ENUM_CONSTRAINT ;
}

void LinkedParticle::CutConstraint()
{
	 mbConstraint = false                   ; 
	 mState       = LP_STATE_ENUM_ACTIVE    ;
}

void LinkedParticle::linkCalc(Map* pMap)
{
	// アクティブか？
	if (!mbActive)
	{
		return;
	}

	//かかっている力をクリア
	mFx = 0.0f;
	mFy = 0.0f;

	//コンストレイント（拘束）されているときは計算スキップ
	if (mbConstraint)
	{
		return;
	}

	// 自分にかかるすべての力の計算

	float px, py;    // 相手パーティクルの座標

	float nowLen;    //現在の長さ

	//このパーティクルが受ける力の総和を計算
	for (unsigned int i = 0; i < mParticleArray.size(); i++)
	{
		//パーティクル間の長さ算出
		px = mParticleArray[i].m_particle->mx;
		py = mParticleArray[i].m_particle->my;

		nowLen = (px - mx) * (px - mx) +
			(py - my) * (py - my);
		nowLen = sqrt(nowLen);

		//パーティクル間の張力を計算
		// ばね定数 * (現在の長さ) / (通常長さ)
		float tention = mParticleArray[i].m_springConstant * (nowLen - mParticleArray[i].m_springLen) / mParticleArray[i].m_springLen;
		tention *= mParticleArray[i].m_particle->mWeight * 0.5f;

		// 許容値以下は力の計算切り捨て
		if (tention > -mEpsiron && tention < mEpsiron)
		{
			mFx += 0.0f;
			mFy += 0.0f;
		}
		else
		{
			//許容量以上なので力を足す
			mFx += (px - mx) * tention / 2.0f;
			mFy += (py - my) * tention / 2.0f;
		}
	}
	mx += mFx;
	my += mFy;

	// 現時点で壁にぶつかっているか？ぶつかっていたら修正
	if (pMap)
	{
		mapHit(pMap);

		//ぶつかっていたら速度ゼロに
		if (mbHitWall)
		{
			mPrevX = mx;
			mPrevY = my;
		}
	}


}

// 移動処理
void LinkedParticle::move(Map* pMap)
{
	// アクティブか？
	if (!mbActive)
	{
		return;
	}

	//コンストレイント（拘束）されているときは計算スキップ
	if (mbConstraint)
		return;

	//このパーティクルの速度を算出
	float vx, vy;
	vx = mx - mPrevX;
	vy = my - mPrevY;

	vx += 0.0f ;
	vy += mGravity; 

	mPrevX = mx;
	mPrevY = my;

	//最高速度でクランプした速度で位置更新
	mx += clamp(mMaxSpeed, -mMaxSpeed, vx * mFrictionRatio);
	my += clamp(mMaxSpeed, -mMaxSpeed, vy * mFrictionRatio);

	//マップとのあたり判定
	if ( mbHitWall && pMap )
	{
		mapHit(pMap);
	}
}

//デバッグ描画
void LinkedParticle::debugDraw(Camera * pCam)
{
	// アクティブか？
	if (!mbActive)
	{
		return;
	}

	//スクリーン座標を得る
	int x, y;
	pCam->worldPos2ScreenPos((int)mx, (int)my, &x, &y);

	//質点描画
	DrawCircle(x, y, 5, ColPallete[mState]);


	//自分から接続されているパーティクルへの接続を描画
	for (unsigned int i = 0; i < mParticleArray.size(); i++)
	{
		int px, py;

		pCam->worldPos2ScreenPos((int)mParticleArray[i].m_particle->mx,
			                     (int)mParticleArray[i].m_particle->my,
			                     &px, &py);

		DrawLine(x, y, px, py, 0xffffffff);
	}

}

//パーティクルの連結
void LinkedParticle::link(LinkedParticle *p, float springStrengthRatio)
{
	if (springStrengthRatio > 1.0f)
	{
		springStrengthRatio = 1.0f;
	}
	if (springStrengthRatio < 0.0f)
	{
		springStrengthRatio = 0.001f;
	}

	//パーティクル間の距離を計算
	float len;

	len = (p->mx - mx) * (p->mx - mx) +
		  (p->my - my) * (p->my - my);
	len = sqrtf(len);

	//リンク情報作る
	LinkedParticleConnectionInfo linkinfo;
	linkinfo.m_springLen      = len                 ; // もともとの長さ
	linkinfo.m_particle       = p                   ; // リンク先
	linkinfo.m_springConstant = springStrengthRatio ; // リンク先とのばね係数

	//リンク情報登録
	mParticleArray.push_back(linkinfo);

	//相手にも自分のリンク情報登録
	linkinfo.m_particle = this;
	p->mParticleArray.push_back(linkinfo);
}

void LinkedParticle::mapHit(Map * pMap)
{
	//マップインデックス算出
	int ix, iy;
	ix = pMap->getCollisionMapIndex_X((int)mx);
	iy = pMap->getCollisionMapIndex_Y((int)my);

	// そのマップ位置は壁でないなら抜ける
	if (pMap->getCollisionMapIdFromIndex(ix, iy) == 0)
	{
		mbHitWall = false;
		mState    = LP_STATE_ENUM_ACTIVE;
		return;
	}

	// 壁にめり込んでいることが確定
	// 最短距離で壁からの脱出を計算
	mbHitWall = true;
	mState = LP_STATE_ENUM_HIT;

	//あたりブロックの矩形範囲座標算出
	int b_min_x, b_min_y;
	int b_max_x, b_max_y;

	b_min_x =       ix * pMap->getMapChipSizeX();
	b_min_y =       iy * pMap->getMapChipSizeY();
	b_max_x = (ix + 1) * pMap->getMapChipSizeX();
	b_max_y = (iy + 1) * pMap->getMapChipSizeY();

	// めり込み許容範囲内か？
	int fixedX, fixedY;
	const int intrudeAcceseptable = 20;

	fixedX = (int)mx;
	fixedY = (int)my;

	// 縦方向めり込み許容範囲内なら戻す
	if (my - b_min_y < intrudeAcceseptable && my - b_min_y > 0)
	{
		fixedY = b_min_y - 1;
		mState = LP_STATE_ENUM_ON_GROUND;
	}

	if (b_max_y - my < intrudeAcceseptable && b_max_y - my > 0)
	{
		fixedY = b_max_y + 1;
	}

	// 上下方向でOKなら先に抜ける
	iy = pMap->getCollisionMapIndex_Y(fixedY);
	if (pMap->getCollisionMapIdFromIndex(ix, iy) == 0)
	{
		my = (float)fixedY;

		return ;
	}

	// 横方向めり込み許容範囲内なら戻す
	if (mx - b_min_x < intrudeAcceseptable && mx - b_min_x > 0)
	{
		fixedX = b_min_x ;
	}

	if (b_max_x - mx < intrudeAcceseptable && b_max_x - mx > 0)
	{
		fixedX = b_max_x + 1;
	}

	mx = (float)fixedX;
	my = (float)fixedY;


}

void LinkedParticle::addForce(float addFx, float addFy)
{
	mFx += addFx;
	mFy += addFy;
}

void LinkedParticle::reset()
{
	mbConstraint = false;
	mbHitWall    = false;
	mFx = 0.0f;
	mFy = 0.0f;
	mPrevX = 0.0f;
	mPrevY = 0.0f;
	mx = 0.0f;
	my = 0.0f;

	if (mParticleArray.size() > 0)
	{
		mParticleArray.clear();
	}
}

// 最高速度セット
void LinkedParticle::setMaxSpeed(float speed)
{
	mMaxSpeed = speed;
}

// 重力のセット
void LinkedParticle::setGravity(float gravity)
{
	mGravity = gravity;
}

// 微小値切り捨てしきい値
void LinkedParticle::setEpsiron(float epsiron)
{
	mEpsiron = epsiron;
}


