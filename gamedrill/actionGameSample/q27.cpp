#include "q27.h"

Quest27Seq::Quest27Seq()
{
	// プレーヤー、カメラ、マップ作製
	pPlayer = new Player;
	pCam    = new Camera;
	pMap    = new Map;

	//プレーヤー初期化
	pPlayer->init("image/chara3.png", "image/player.png", 64, 64);
	pPlayer->setGameStartPos(500, 100);
	pPlayer->setCollision( 10, 0, 40, 56);

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

	//マップのデバッグ表示
	showDebugMap = false;

}

Quest27Seq::~Quest27Seq()
{
	delete pCam;
	delete pMap;
	delete pPlayer;

}

Sequence * Quest27Seq::move()
{
	static bool allowParticleHit = false;
	// [H] keyが押されたらパーティクルとマップとのあたり判定をするか切り替える
	if (INPUT_INSTANCE.getInput(KEY_INPUT_H) == KEY_STATE_PUSHDOWN)
	{
		allowParticleHit = !allowParticleHit;
	}
	// [M] keyが押されたらデバッグマップ描画するかの切り替え
	if (INPUT_INSTANCE.getInput(KEY_INPUT_M) == KEY_STATE_PUSHDOWN)
	{
		showDebugMap = !showDebugMap;
	}

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest28Seq;
	}

	//プレーヤー処理
	pPlayer->move(pMap, pCam);

	//プレーヤーを注視点としてカメラ作成
	pCam->move(pMap, pPlayer->getPlayerPosX(), pPlayer->getPlayerPosY());

	if (INPUT_INSTANCE.getInput(KEY_INPUT_B) == KEY_STATE_PUSHDOWN)
	{
		Particle::toggleMortionBlur();
	}

	return this;
}

void Quest27Seq::draw()
{
	ClearDrawScreen();
	
	// マップ描画
	pMap->mapDraw(pCam);

	// マップデバッグ描画
	if (showDebugMap)
	{
		pMap->gridDraw(pCam);
	}

	// プレーヤー描画
	pPlayer->draw(pCam);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #28.");
	GAMEINSTANCE.systemText.textDraw(10, GAMEINSTANCE.getScreenHeight() - 90, "HOW TO PLAY\nALLOW KEY - MOVE / [Z] KEY - JUMP\n[M] - Map Debug Show");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");
}
