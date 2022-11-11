#include "Sequence.h"

#ifndef __Q9_H__
#define __Q9_H__

class Sequence; // �O�u�錾 

				//�L�[��4��Ԓ�`
typedef enum KEY_STATE{
	KEY_OFF,        // ������OFF���
	KEY_PUSH_DOWN,  // �������ꂽ
	KEY_PRESSED,    // �����Ɖ�����Ă���
	KEY_PULLUP,     // �����ꂽ
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
	char mNowEnterKeyState;             // ���݂̃L�[�̏��
	char mPrevEneterKeyState;           // �ЂƂO�̃t���[���̃L�[�̏��
	KEY_STATE mKeyLogRingBuffer[m_maxBuf];   // �\���p�̃��O�i�����O�o�b�t�@�j

	int  mNowIndex;	                 // �����O�o�b�t�@�̌��݂̃C���f�b�N�X
	int  mPrevIndex;                    // �����O�o�b�t�@�̂ЂƂO�̃C���f�b�N�X

	KEY_STATE indexToKeyState(int index);

};




#endif
