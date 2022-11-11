#include "Sequence.h"

#ifndef __Q17_H__
#define __Q17_H__

class Sequence; // �O�u�錾 

class Quest17Seq : public Sequence
{
public:
	Quest17Seq();
	~Quest17Seq();

	Sequence* move();
	void      draw();

private:
	int mImgBlock[2];

	int mBgXOffset; // �`��J�nx�I�t�Z�b�g�ʒu
	int mBgYOffset; // �`��J�ny�I�t�Z�b�g�ʒu

	int mBgVx; // �������̑��x
	int mBgVy; // �c�����̑��x

	int mBlockSize;  // �u���b�N�T�C�Y
	int mNowScrDirPattern; // �X�N���[���p�^�[��

};


#endif
