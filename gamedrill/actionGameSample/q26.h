#include "Sequence.h"

#ifndef __Q26_H__
#define __Q26_H__

class Sequence; // �O�u�錾 

class Quest26Seq : public Sequence
{
public:
	Quest26Seq();
	~Quest26Seq();

	Sequence*      move();
	void           draw();

private:

	// �}�b�v�֘A									  //
	unsigned int   m_mapWidth;            // �}�b�v�̕�(���u���b�N���j
	unsigned int   m_mapHeight;           // �}�b�v�����i�c�u���b�N���j
	unsigned int   m_mapChipSizeX;        // �}�b�v�`�b�v�̉��T�C�Y
	unsigned int   m_mapChipSizeY;        // �}�b�v�`�b�v�̏c�T�C�Y
	unsigned char *mMapData;             // �}�b�v�f�[�^�z��
	int           *mMapChipHandleArray;
	unsigned int   mMapChipHandleArrayIndexMax;

	int            m_mapIndexX;
	int            m_mapIndexY;

	bool           mbHit;

	// �X�N���[���֘A
	int            m_camX;               // �J�����̃��[���h���W�n�ʒu�@x, y 
	int            m_camY;

	// �X�N���[�������Ǘ�
	int            m_camVx;
	int            m_camVy;

	// 1�s�����R�����g(�s��//������s)���΂��Ȃ���ǂ�
	void           readDataLine(char* buf, size_t bufSize, FILE *p);

	// �}�b�v�t�@�C���w�b�_����ǂ� �}�b�v�̕������A�}�b�v�`�b�v�傫����
	bool           readHeader(const char* mapFilename);

	// �}�b�v���f�[�^�ǂݍ���
	bool           readMapdata(const char* mapFileName);

	// �}�b�v�`��
	void           mapDraw();

	// �O���b�h�`��
	void           gridDraw();

	// �X�N���[���֘A

	// �X�N���[�����W�n���烏�[���h���W�n�ւ̍��W�ϊ�
	void           screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y);

	// ���[���h���W�n����X�N���[�����W�n�ւ̍��W�ϊ�
	void           worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y);

	bool           isMapHit(unsigned int worldX, unsigned int worldY);
};


#endif
