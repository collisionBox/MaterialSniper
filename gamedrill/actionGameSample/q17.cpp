#include "questions.h"


//スクロールパターン
int scrX[] = {  0, -1,  0, +1, +1, +1, -1, -1 };
int scrY[] = { +1,  0, -1,  0, +1, -1, -1, +1 };

//スクロールパターンの最大数
const int scrMaxPattern = sizeof(scrX) / sizeof(int);

Quest17Seq::Quest17Seq()
{
	mImgBlock[0] = LoadGraph("image/block0.bmp");
	mImgBlock[1] = LoadGraph("image/block1.bmp");


	// 描画開始オフセット位置
	mBgXOffset = 0;
	mBgYOffset = 0;

	mNowScrDirPattern = 0;

	//移動量
	mBgVx = scrX[mNowScrDirPattern];
	mBgVy = scrY[mNowScrDirPattern];

	//ブロックサイズ取得（正方形であることを前提。縦横サイズ違うときは変数用意する）
	int tmp;
	GetGraphSize(mImgBlock[0], &mBlockSize, &tmp);

}


Quest17Seq::~Quest17Seq()
{
	for (int i = 0; i < 2; i++)
	{
		if (mImgBlock[i] != -1)
		{
			DeleteGraph(mImgBlock[i]);
		}
	}
}
Sequence* Quest17Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest18Seq;
	}

	if (INPUT_INSTANCE.getInput(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN)
	{
		mNowScrDirPattern = (mNowScrDirPattern + 1) % scrMaxPattern;
	}

	static int scrollSpeed = 8;

	// スクロール速度
	mBgVx = scrX[mNowScrDirPattern] * scrollSpeed;
	mBgVy = scrY[mNowScrDirPattern] * scrollSpeed;

	// 速度に応じて移動
	mBgXOffset += mBgVx;
	mBgYOffset += mBgVy;

	// 左上オフセット座標を算出 左上書き始めが常に画面外からになるように
	// mBlockSize分マイナスしている

	mBgXOffset = (mBgXOffset % mBlockSize) - mBlockSize;
	mBgYOffset = (mBgYOffset % mBlockSize) - mBlockSize;

	// 現行シーケンス続行
	return this;
}


void Quest17Seq::draw()
{
	ClearDrawScreen();

	//スクロール画面描画　左上画面外から右下画面外まで描画

	// 画面高さ幅を取得（ループ終端条件）
	int screenHeight = GAMEINSTANCE.getScreenHeight();
	int screenWidth  = GAMEINSTANCE.getScreenWidth();


	// y座標 : 上画面外から、下画面外になるまでループ
	for (int i = 0; mBgYOffset + i * mBlockSize < screenHeight ; i++)
	{
		// x座標 : 左画面外から右画面外になるまでループ
		for (int j = 0; mBgXOffset + j * mBlockSize < screenWidth ; j++)
		{

			DrawGraph( mBgXOffset + j * mBlockSize, 
				       mBgYOffset + i * mBlockSize,
				       mImgBlock[ 0 ], true);
		}
	}
	GAMEINSTANCE.systemText.textDraw(60, 300, "HIT RETURN KEY TO CHANGE SCROLL DIR.");
	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #17.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}