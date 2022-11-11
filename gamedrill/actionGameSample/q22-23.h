#include "Sequence.h"

#ifndef __Q22_23_H__
#define __Q22_23_H__

class Sequence; // 前置宣言 

class Quest22_23Seq : public Sequence
{
public:
	Quest22_23Seq();
	~Quest22_23Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

	Point2D m_Pos[4];          // ブロック座標
	Point2D m_startPos[4];     // 開始点
	Point2D m_endPos[4];       // 終了点

	float   m_anim;            // アニメーション用
	float   m_animInc;         // アニメーション増分

	enum EASETYPE_ENUM
	{
		EASETYPE_NORMAL,
		EASETYPE_CUBIC,
		EASETYPE_CIRCULAR,
		EASETYPE_EXPONENTIAL,
	};

	int m_easingType;

	char m_easeInOutNames[3][16];
	char m_easingTypeNames[4][16];
};


#endif
