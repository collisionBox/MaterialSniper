#ifndef __MAP_H__
#define __MAP_H__

#include "dxlib.h"
#include "Game.h"
#include "camera.h"

#pragma warning(disable:4996)

class Camera;

class Map
{
public:
	Map();
	~Map();
	bool           readMapdata(const char* mapFileName, const char* mapchipGraphFileName);  	// �}�b�v���f�[�^�ǂݍ���
	void           mapDraw(Camera* p_Camera);	                            // �}�b�v�`��
	void           gridDraw(Camera* p_Camera);	                            // �O���b�h�`��
	bool           isMapHit(unsigned int worldX, unsigned int worldY);        // �����_�̓}�b�v�ƏՓ˂������H
	int            getMapWidth() { return mMapChipWidthNum * mMapChipGraphSizeX; }
	int            getMapHeight() { return mMapChipHeightNum * mMapChipGraphSizeY; }
	int            getCollisionMapIndex_X(int posx);
	int            getCollisionMapIndex_Y(int posy);
	unsigned char  getCollisionMapIdFromIndex(int xIndex, int yIndex);
	int            getMapChipSizeX() { return mMapChipGraphSizeX; }
	int            getMapChipSizeY() { return mMapChipGraphSizeY; }

private:
	unsigned int   mMapChipWidthNum;                       // �}�b�v�̕�(���u���b�N���j
	unsigned int   mMapChipHeightNum;                      // �}�b�v�����i�c�u���b�N���j
	unsigned int   mMapChipGraphSizeX;                     // �}�b�v�`�b�v�̉��T�C�Y
	unsigned int   mMapChipGraphSizeY;                     // �}�b�v�`�b�v�̏c�T�C�Y
	unsigned char *mMapData;                               // �}�b�v�f�[�^�z��
	int           *mMapChipHandleArray;                    // �}�b�v�`�b�v�摜�n���h���i�[�z��
	unsigned int   mMapChipHandleArrayIndexMax;            // �摜�n���h���z��̓Y�����ő�l

	bool           mbHit;                                  // �q�b�g�������H

	void           readDataLine(char* buf, size_t bufSize, FILE *p);	// 1�s�����R�����g(�s��//������s)���΂��Ȃ���ǂ�
	bool           readHeader(const char* mapFilename);	    // �}�b�v�t�@�C���w�b�_����ǂ� �}�b�v�̕������A�}�b�v�`�b�v�傫����
};

#endif