#include "questions.h"

Quest06Seq::Quest06Seq()
{
	mImgHandle1 = LoadGraph("image/block0.bmp");
	mImgHandle2 = LoadGraph("image/block1.bmp");
}


Quest06Seq::~Quest06Seq()
{
	if (mImgHandle1 != -1)
	{
		DeleteGraph(mImgHandle1);
	}

	if (mImgHandle2 != -1)
	{
		DeleteGraph(mImgHandle2);
	}
}
Sequence* Quest06Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest07Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest06Seq::draw()
{
	static int alpha = 0;
	const int maxcolor = 255;

	const int blockSize = 64;
	const int maxWidthIndex = GAMEINSTANCE.getScreenWidth() / blockSize + 1;
	const int maxHeightIndex = GAMEINSTANCE.getScreenHeight() / blockSize + 1;

	static int alphainc = 1;

	//透明度アニメーション
	alpha += alphainc;
	if (alphainc > 0 && alpha > 255)
	{
		alphainc = -1;
		alpha = 255;
	}

	if (alphainc < 0 && alpha < 0)
	{
		alpha = 0;
		alphainc = 1;
	}


	ClearDrawScreen();


	int i, j;

	// 背景を書く
	for (i = 0; i < maxHeightIndex; i++)
	{
		for (j = 0; j < maxWidthIndex; j++)
		{
			DrawGraph(j * blockSize, i* blockSize, mImgHandle1, false);
		}
	}

	//半透明物体を描く(加算半透明）
	SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
	DrawGraph(150, 100, mImgHandle2, true);

	//半透明物体を描く(乗算半透明）
	SetDrawBlendMode(DX_BLENDMODE_MUL, alpha);
	DrawGraph(150, 200, mImgHandle2, true);

	//半透明物体を描く(乗算半透明α）
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawGraph(150, 300, mImgHandle2, true);

	//半透明物体を描く(減算半透明α）
	SetDrawBlendMode(DX_BLENDMODE_SUB, alpha);
	DrawGraph(150, 400, mImgHandle2, true);


	//半透明描画モードを通常モードへ戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	char buf[256];
	sprintf(buf, "ALPHA = %3d", alpha);

	GAMEINSTANCE.systemText.textDraw(100, 50, buf);

	GAMEINSTANCE.systemText.textDraw(100, 70, "DX_BLENDMODE_ADD");
	GAMEINSTANCE.systemText.textDraw(100, 180, "DX_BLENDMODE_MUL");
	GAMEINSTANCE.systemText.textDraw(100, 280, "DX_BLENDMODE_MULA");
	GAMEINSTANCE.systemText.textDraw(100, 370, "DX_BLENDMODE_SUB");


	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #06.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");
}