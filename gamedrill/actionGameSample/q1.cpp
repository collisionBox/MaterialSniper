#include "questions.h"

void blinkingString(int x, int y, char *str)
{
	// 明滅ルーチン
	static int alpha = 0;
	static int inc = 4;

	if (alpha > 255 && inc > 0)
		inc *= -1;

	if (alpha < 0 && inc < 0)
		inc *= -1;

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	GAMEINSTANCE.systemText.setFontColor(255, 0, 0);
	GAMEINSTANCE.systemText.textDraw(x, y, str);
	GAMEINSTANCE.systemText.setFontColor(255, 255, 255);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

Quest01Seq::Quest01Seq()
{
	mImgHandle = LoadGraph("image/fcaLogo.png");
}


Quest01Seq::~Quest01Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest01Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest02Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest01Seq::draw()
{
	ClearDrawScreen();

	DrawGraph(200, 100, mImgHandle, true);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #01.");
	blinkingString( 10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}