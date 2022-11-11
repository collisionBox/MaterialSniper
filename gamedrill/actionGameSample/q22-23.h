#include "Sequence.h"

#ifndef __Q22_23_H__
#define __Q22_23_H__

class Sequence; // �O�u�錾 

class Quest22_23Seq : public Sequence
{
public:
	Quest22_23Seq();
	~Quest22_23Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

	Point2D m_Pos[4];          // �u���b�N���W
	Point2D m_startPos[4];     // �J�n�_
	Point2D m_endPos[4];       // �I���_

	float   m_anim;            // �A�j���[�V�����p
	float   m_animInc;         // �A�j���[�V��������

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
