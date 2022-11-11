#include "Sequence.h"

#ifndef __Q18_H__
#define __Q18_H__

class Sequence; // �O�u�錾 

class Quest18Seq : public Sequence
{
public:
	Quest18Seq();
	~Quest18Seq();

	Sequence* move();
	void      draw();

private:
	int mImgPlayer[16];
	int mImgBG;

	//�v���[���[�L�����֘A
	//�L�����̏��
	typedef enum CHARA_STATE_ENUM
	{
		CHARA_STATE_ON_GROUND,   // �n�ʂɋ���
		CHARA_STATE_JUMP,        // �W�����v��
		CHARA_STATE_RUN,         // �����Ă���
		CHARA_STATE_WAIT,        // �ҋ@���[�V����
	}CHARA_STATE_ENUM;
	
	//�L�������W
	int mPx, mPy;               // �L�������W
	int mPVx, mPVy;             // �L�������x
	int mPHeight;                // �L��������
	int mPJumpPow;               // �L�����W�����v��
	int mPStartAnimNum[4];       // �L�����A�j���J�n�ԍ�
	int mPEndAnimNum[4];         // �L�����A�j���I���ԍ�
	int mPAnimNum;               // �Đ����̃A�j���ԍ�

	CHARA_STATE_ENUM mPState;    // �L�����̏��

	int mGroundY;
	bool mRightFlg ;

};


#endif