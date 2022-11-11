#include "questions.h"

Quest03Seq::Quest03Seq()
{
	mImgHandle = LoadGraph("image/block1.bmp");

	pos[0].x = 300;
	pos[0].y = 100;
	pos[1].x = 500;
	pos[1].y = 300;
	pos[2].x = 500;
	pos[2].y = 100;
	pos[3].x = 300;
	pos[3].y = 300;

}


Quest03Seq::~Quest03Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest03Seq::move()
{

	//キャラの移動
	pos[0].x++;
	pos[1].x--;
	pos[2].y++;
	pos[3].y--;


	//画面外を超えたら戻す
	if (pos[0].x > GAMEINSTANCE.getScreenWidth())
	{
		pos[0].x = -64;
	}

	if (pos[1].x < -64)
	{
		pos[1].x = GAMEINSTANCE.getScreenWidth();
	}

	if (pos[2].y > GAMEINSTANCE.getScreenHeight())
	{
		pos[2].y = -64;
	}

	if (pos[3].y < -64)
	{
		pos[3].y = GAMEINSTANCE.getScreenHeight();
	}

	// シーケンス移行
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest04Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest03Seq::draw()
{
	ClearDrawScreen();

	for (int i = 0; i < 4; i++)
	{
		DrawGraph(pos[i].x, pos[i].y, mImgHandle, false);
	}

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #03.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");
}