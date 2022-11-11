#include "Sequence.h"

#ifndef __QSELECTOR_H__
#define __QSELECTOR_H__

class Sequence; // 前置宣言 

class QuestSelector : public Sequence
{
public:
	QuestSelector();
	~QuestSelector();

	Sequence* move();
	void      draw();

private:

	//画像系
	int mImgHandle;
	int mCharaImgHandle[16];
	int mBlockSize;                      // 画像ブロックサイズ

	int mScreenBuffer;                   // 画面バッファ
	int mReduceScreen;                   // 縮小スクリーンバッファ
	int mBlurScreenBuffer;               // ぼかし画面

	// スタート時背景アニメカウント
	float mStartUpAnimCount;             // スタートアニメカウンタ

	// ステージ選択制御関連
	int mStageNo;                        // 選択中のステージNo
	int mStageNumMax;                    // 最大登録ステージ数
	int mStageNumInParagrah;             // 1つの段落に入るステージ数

	// シーケンス以降関連
	bool mbChangeSeqNow;                 // シーケンス移行中か？
	int  mChangeTimeCount;               // シーケンス移行アニメーションカウンタ
	static const int  mMaxTime = 80;     // シーケンス移行フレーム数

	//スクロールアニメーション制御関連
	int mBgXOffset;                     // スクロールオフセット量
	int	mBgYOffset;
	int mBgVx;						  // スクロール x, y方向速度
	int mBgVy;
	int mScrollSpeed;                    // スクロール速度

	// 文字出現アニメーション関連
	Point2D *mpMenuStartPos;  // メニュー文字出現位置
	Point2D *mpMenuEndPos;    // メニュー文字最終位置
	Point2D *mpMenuNowPos;    //
	float   *mpMenuAnimTime;  // メニュー文字アニメーションカウンタ

	// ステージ移動・遷移関連メソッド
	Sequence* stageCreator(int stageNum); // 選択ステージnoよりそのシーケンスを生成する
	int stageDecrement(int stageNum);     // 選択ステージを1個前に
	int stageIncrement(int stageNum);     // 選択ステージを1個先に

};


#endif
