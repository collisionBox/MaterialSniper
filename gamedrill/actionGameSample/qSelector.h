#include "Sequence.h"

#ifndef __QSELECTOR_H__
#define __QSELECTOR_H__

class Sequence; // �O�u�錾 

class QuestSelector : public Sequence
{
public:
	QuestSelector();
	~QuestSelector();

	Sequence* move();
	void      draw();

private:

	//�摜�n
	int mImgHandle;
	int mCharaImgHandle[16];
	int mBlockSize;                      // �摜�u���b�N�T�C�Y

	int mScreenBuffer;                   // ��ʃo�b�t�@
	int mReduceScreen;                   // �k���X�N���[���o�b�t�@
	int mBlurScreenBuffer;               // �ڂ������

	// �X�^�[�g���w�i�A�j���J�E���g
	float mStartUpAnimCount;             // �X�^�[�g�A�j���J�E���^

	// �X�e�[�W�I�𐧌�֘A
	int mStageNo;                        // �I�𒆂̃X�e�[�WNo
	int mStageNumMax;                    // �ő�o�^�X�e�[�W��
	int mStageNumInParagrah;             // 1�̒i���ɓ���X�e�[�W��

	// �V�[�P���X�ȍ~�֘A
	bool mbChangeSeqNow;                 // �V�[�P���X�ڍs�����H
	int  mChangeTimeCount;               // �V�[�P���X�ڍs�A�j���[�V�����J�E���^
	static const int  mMaxTime = 80;     // �V�[�P���X�ڍs�t���[����

	//�X�N���[���A�j���[�V��������֘A
	int mBgXOffset;                     // �X�N���[���I�t�Z�b�g��
	int	mBgYOffset;
	int mBgVx;						  // �X�N���[�� x, y�������x
	int mBgVy;
	int mScrollSpeed;                    // �X�N���[�����x

	// �����o���A�j���[�V�����֘A
	Point2D *mpMenuStartPos;  // ���j���[�����o���ʒu
	Point2D *mpMenuEndPos;    // ���j���[�����ŏI�ʒu
	Point2D *mpMenuNowPos;    //
	float   *mpMenuAnimTime;  // ���j���[�����A�j���[�V�����J�E���^

	// �X�e�[�W�ړ��E�J�ڊ֘A���\�b�h
	Sequence* stageCreator(int stageNum); // �I���X�e�[�Wno��肻�̃V�[�P���X�𐶐�����
	int stageDecrement(int stageNum);     // �I���X�e�[�W��1�O��
	int stageIncrement(int stageNum);     // �I���X�e�[�W��1���

};


#endif
