#include "SoftBodyTest.h"

SoftBodyTestSeq::SoftBodyTestSeq()
{
	mMaxParticleNum = 100;
	mMode = 0;

	// プレーヤー、カメラ、マップ作製
	pCam = new Camera;
	pMap = new Map;
	pParticle = new LinkedParticle[mMaxParticleNum];


	//カメラスクロール範囲座標作成
	const int scrHalfWidth  = 64;
	const int scrHalfHeight = 64;

	int scrhalfX = GAMEINSTANCE.getScreenWidth() / 2;
	int scrhalfY = GAMEINSTANCE.getScreenHeight() / 2;

	//カメラ初期化
	pCam->Init(0, 0,                             // カメラの開始位置
		scrhalfX - scrHalfWidth, scrhalfY - scrHalfHeight, // カメラの左上許容座標
		scrHalfWidth * 2, scrHalfHeight * 2);              // 左上許容座標を中心に、許容幅、高さセット
														   //マップ初期化
	pMap->readMapdata("image/dungeon.csv", "image/dungeonSheet.png");

	//質点定義
	resetMassPoint();

	LinkedParticle::setGravity(1.0f);
	LinkedParticle::setMaxSpeed(16.0f);
}

SoftBodyTestSeq::~SoftBodyTestSeq()
{
	delete pCam;
	delete pMap;

}

Sequence * SoftBodyTestSeq::move()
{
	static bool allowParticleHit = false;
	// [H] keyが押されたらコンストレイント（拘束）切る
	if (INPUT_INSTANCE.getInput(KEY_INPUT_H) == KEY_STATE_PUSHDOWN)
	{
		for (int i = 0;i < mMaxParticleNum; i++)
		{
			if (pParticle[i].isConstraint())
			{
				pParticle[i].CutConstraint();
			}
		}
	}

	// Sキーで初期位置戻る
	if (INPUT_INSTANCE.getInput(KEY_INPUT_S) == KEY_STATE_PUSHDOWN)
	{
		resetMassPoint();
		mMode++;

		if (mMode == 3)
		{
			mMode = 0;
		}
	}

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest01Seq;
	}


	//プレーヤーを注視点としてカメラ作成
	pCam->move(pMap, (int)(pParticle[6].getPosX()), (int)(pParticle[6].getPosY()));

	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < mMaxParticleNum; i++)
		{
			pParticle[i].linkCalc(pMap);
		}
	}

	for (int i = 0; i < mMaxParticleNum; i++)
	{
		pParticle[i].move(pMap);
	}

	return this;
}

void SoftBodyTestSeq::draw()
{
	char buf[128];
	ClearDrawScreen();

	//マップ描画
	pMap->mapDraw(pCam);
	pMap->gridDraw(pCam);

	//パーティクル描画
	for (int i = 0; i < mMaxParticleNum; i++)
	{
		pParticle[i].debugDraw(pCam);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);

	GAMEINSTANCE.systemText.textDraw(10, 42, buf);
	GAMEINSTANCE.systemText.textDraw(10, 10, "SoftBodyTest.");
}

void SoftBodyTestSeq::resetMassPoint()
{

	for (int i = 0; i < mMaxParticleNum; i++)
	{
		pParticle[i].reset();
	}

	// モード０
	if (mMode == 0)
	{
		//ロープ
		for (int i = 0; i < 6; i++)
		{
			int startpos = 640;
			int distance = 60;
			pParticle[i].setMassPoint((float)(startpos - i * distance), 100, 2.0f + i * 0.5f);
		}

		//ボックス
		pParticle[6].setMassPoint(760, 100, 1.0f);
		pParticle[7].setMassPoint(860, 100, 1.0f);
		pParticle[8].setMassPoint(860, 120, 1.0f);
		pParticle[9].setMassPoint(760, 120, 3.0f);

		pParticle[0].setConstraint();
		pParticle[6].setConstraint();

		//ロープ
		pParticle[0].link(&pParticle[1], 1.0f);
		pParticle[1].link(&pParticle[2], 1.0f);
		pParticle[2].link(&pParticle[3], 1.0f);
		pParticle[3].link(&pParticle[4], 1.0f);
		pParticle[4].link(&pParticle[5], 1.0f);

		// ボックス
		pParticle[6].link(&pParticle[7]);
		pParticle[7].link(&pParticle[8]);
		pParticle[8].link(&pParticle[9]);
		pParticle[9].link(&pParticle[6]);

		pParticle[6].link(&pParticle[8]);
		pParticle[9].link(&pParticle[7]);
	}

	//モード１
	if (mMode == 1)
	{
		for (int i = 0; i < mMaxParticleNum / 3; i++)
		{
			float tx, ty, len;
			tx = getRandom(100.0f, 1000.0f);
			ty = getRandom(120.0f, 300.0f);
			len = getRandom(10.0f, 80.0f);

			pParticle[i * 3 + 0].setMassPoint(tx - len / 2, ty);
			pParticle[i * 3 + 1].setMassPoint(tx + len / 2, ty);
			pParticle[i * 3 + 2].setMassPoint(tx, ty + len / 2);

			pParticle[i * 3 + 0].link(&pParticle[i * 3 + 1]);
			pParticle[i * 3 + 1].link(&pParticle[i * 3 + 2]);
			pParticle[i * 3 + 2].link(&pParticle[i * 3 + 0]);

			pParticle[i * 3 + 0].setConstraint();
		}
	}
	
	// モード２
	if (mMode == 2)
	{
		float radius = 100.0f;
		float posx, posy;
		posx = 700;
		posy = 1000;
		float theta = 0.0f;
		int sepNum = 16;

		float thetaplus = 3.14159f * 2.0f / sepNum;

		pParticle[0].setMassPoint(posx, posy);
		for (int i = 1; i <= sepNum; i++)
		{
			pParticle[i].setMassPoint(posx + cosf(theta) * radius, posy + sinf(theta) * radius);
			pParticle[i].link(&pParticle[i - 1], 1.0f);
			theta += thetaplus;
		}
		pParticle[1].link(&pParticle[sepNum]);

		for (int i = 2; i <= sepNum; i++)
		{
			pParticle[i].link(&pParticle[0], 0.2f);
		}
	}
}
