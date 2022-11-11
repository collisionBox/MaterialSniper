#include "Sequence.h"

#ifndef __Q11_14_H__
#define __Q11_14_H__

class Sequence; // �O�u�錾 

class Quest11_14Seq : public Sequence
{
public:
	Quest11_14Seq();
	~Quest11_14Seq();

	Sequence* move();
	void      draw();

private:
	int mScore;      // �X�R�A
	int mAimScore;   // �ڕW�X�R�A�i�������Ɏg�p�j
	int mCountdown;  // �J�E���g�_�E���^�C�}�[
	int mCountup;    // �J�E���g�A�b�v�^�C�}�[
	int mMiliSec;    // �P�b�ȉ��̕b�����v�Z�i�����_���ʂ܂Łj
	int mMin;        // ��

	DWORD mTime;
	DWORD mNowTime;

};


#endif
