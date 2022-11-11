#include "Sequence.h"

#ifndef __Q17_H__
#define __Q17_H__

class Sequence; // 前置宣言 

class Quest17Seq : public Sequence
{
public:
	Quest17Seq();
	~Quest17Seq();

	Sequence* move();
	void      draw();

private:
	int mImgBlock[2];

	int mBgXOffset; // 描画開始xオフセット位置
	int mBgYOffset; // 描画開始yオフセット位置

	int mBgVx; // 横方向の速度
	int mBgVy; // 縦方向の速度

	int mBlockSize;  // ブロックサイズ
	int mNowScrDirPattern; // スクロールパターン

};


#endif
