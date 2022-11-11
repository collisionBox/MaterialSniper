#include "q30.h"

Quest30Seq::Quest30Seq()
{
	// プレーヤー、カメラ、マップ作製
	pPlayer = new Player;
	pCam = new Camera;
	pMap = new Map;

	//プレーヤー初期化
	pPlayer->init("image/chara3.png", "image/player.png", 64, 64);
	pPlayer->setGameStartPos(500, 100);
	pPlayer->setCollision(10, 0, 40, 56);

	//カメラスクロール範囲座標作成
	const int scrHalfWidth = 64;
	const int scrHalfHeight = 64;

	int scrhalfX = GAMEINSTANCE.getScreenWidth() / 2;
	int scrhalfY = GAMEINSTANCE.getScreenHeight() / 2;

	//カメラ初期化
	pCam->Init(0, 0,                             // カメラの開始位置
		scrhalfX - scrHalfWidth, scrhalfY - scrHalfHeight, // カメラの左上許容座標
		scrHalfWidth * 2, scrHalfHeight * 2);              // 左上許容座標を中心に、許容幅、高さセット
														   //マップ初期化
	pMap->readMapdata("image/dungeon.csv", "image/dungeonSheet.png");

	int perticleImg = LoadGraph("image/perticle.png");
	mPerticleMax = 512;
	mPerticleArray = new Particle[mPerticleMax];
	mPerticleArray->setGraph(perticleImg);

}

Quest30Seq::~Quest30Seq()
{
	delete pCam;
	delete pMap;
	delete pPlayer;

	delete[] mPerticleArray;
}

Sequence * Quest30Seq::move()
{
	static bool allowParticleHit = false;
	// [H] keyが押されたらパーティクルとマップとのあたり判定をするか切り替える
	if (INPUT_INSTANCE.getInput(KEY_INPUT_H) == KEY_STATE_PUSHDOWN)
	{
		allowParticleHit = !allowParticleHit;
	}

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest01Seq;
	}

	//プレーヤー処理
	pPlayer->move(pMap, pCam);

	//プレーヤーを注視点としてカメラ作成
	pCam->move(pMap, pPlayer->getPlayerPosX(), pPlayer->getPlayerPosY());

	if (INPUT_INSTANCE.getInput(KEY_INPUT_B) == KEY_STATE_PUSHDOWN)
	{
		Particle::toggleMortionBlur();
	}

	// パーティクルの追加
	// パーティクル配列内の空きを見つけて毎フレーム5個追加
	int cnt = 0;
	int createParticleNumInFrame = 10;
	for (int i = 0; i < mPerticleMax; i++)
	{
		if (!mPerticleArray[i].isAlive())
		{
			mPerticleArray[i].setStartPos(360.0f, 200.0f, getRandom(-15.0f, +15.0f), getRandom(-30.0f, -5.0f));
			mPerticleArray[i].setLifeTime((int)getRandom(20, 40));
			cnt++;
			if (cnt > createParticleNumInFrame)
				break;
		}
	}

	// 現在生きている全てのパーティクルの移動処理
	for (int i = 0; i < mPerticleMax; i++)
	{
		if (mPerticleArray[i].isAlive())
		{
			if (allowParticleHit)
			{
				mPerticleArray[i].move(pMap);
			}
			else
			{
				mPerticleArray[i].move(NULL);
			}
		}
	}
	return this;
}

void Quest30Seq::draw()
{
	char buf[128];
	ClearDrawScreen();

	//マップ描画
	pMap->mapDraw(pCam);
	pMap->gridDraw(pCam);

	//プレーヤー描画
	pPlayer->draw(pCam);

	//パーティクル描画
	for (int i = 0; i < mPerticleMax; i++)
	{
		if (mPerticleArray[i].isAlive())
		{
			mPerticleArray[i].draw(pCam);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);

	sprintf(buf, "PARTICLES NUM [%3d]", Particle::getNumSubstance());
	GAMEINSTANCE.systemText.textDraw(10, 42, buf);
	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #30.");
	GAMEINSTANCE.systemText.textDraw(10, GAMEINSTANCE.getScreenHeight() - 90, "ALLOW KEY - MOVE / [Z] KEY - JUMP \n[H]KEY - PARTICLE HIT ON / OFF\n[B]KEY - BLUR ON / OFF");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");
}
