#include "q28.h"

Quest28Seq::Quest28Seq()
{
	// プレーヤー、カメラ、マップ作製
	pCam = new Camera;
	pMap = new Map;
	pPlayer = new PlayerTopview;

	//プレーヤー初期化
	pPlayer->init("image/greenboy.png", "image/debugtopview.png", 48, 48);
	pPlayer->setGameStartPos(100, 100);
	pPlayer->setDrawOffset(-3, -22);

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
	pMap->readMapdata("image/topviewmap.csv", "image/topview.png");

	//マップのデバッグ表示
	showDebugMap = false;

}

Quest28Seq::~Quest28Seq()
{
	delete pCam;
	delete pMap;
	delete pPlayer;

}

Sequence * Quest28Seq::move()
{

	// [M] keyが押されたらデバッグマップ描画するかの切り替え
	if (INPUT_INSTANCE.getInput(KEY_INPUT_M) == KEY_STATE_PUSHDOWN)
	{
		showDebugMap = !showDebugMap;
	}

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest30Seq;
	}

	//プレーヤー処理
	pPlayer->move(pMap, pCam);


	//プレーヤーを注視点としてカメラ作成
	pCam->move(pMap,
		   	   pPlayer->getPlayerPosX(),
		       pPlayer->getPlayerPosY());

	
	return this;
}

void Quest28Seq::draw()
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

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #29.");
	GAMEINSTANCE.systemText.textDraw(10, GAMEINSTANCE.getScreenHeight() - 90, "HOW TO PLAY\nALLOW KEY - MOVE / [M] - Map Debug Show");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");
}
