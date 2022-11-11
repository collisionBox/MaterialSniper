#include "Sequence.h"

#ifndef __Q9_H__
#define __Q9_H__

class Sequence; // 前置宣言 

				//キーの4状態定義
typedef enum KEY_STATE{
	KEY_OFF,        // ずっとOFF状態
	KEY_PUSH_DOWN,  // 今押された
	KEY_PRESSED,    // ずっと押されている
	KEY_PULLUP,     // 今離れた
}KEY_STATE;

class Quest09Seq : public Sequence
{
public:
	Quest09Seq();
	~Quest09Seq();

	Sequence* move();
	void      draw();

private:
	static const int m_maxBuf = 16;
	char mNowEnterKeyState;             // 現在のキーの状態
	char mPrevEneterKeyState;           // ひとつ前のフレームのキーの状態
	KEY_STATE mKeyLogRingBuffer[m_maxBuf];   // 表示用のログ（リングバッファ）

	int  mNowIndex;	                 // リングバッファの現在のインデックス
	int  mPrevIndex;                    // リングバッファのひとつ前のインデックス

	KEY_STATE indexToKeyState(int index);

};




#endif
