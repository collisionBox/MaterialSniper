#include "DxLib.h"
////////////////////////////////////////////////////////////////
// Bitmap Text class
// 
// �����`�A���t�@�x�b�g�����񂾃r�b�g�}�b�v�摜���t�H���g�Ƃ��ēo�^
// ���������ʕ\������N���X
////////////////////////////////////////////////////////////////

#ifndef __BITMAPTEXT_H__
#define __BITMAPTEXT_H__

class BitmapText
{
public:
	BitmapText();
	~BitmapText();

	void          setBackGroundAlpha(bool bg_alpha_on) { mBgalpha = bg_alpha_on; }                 // �t�H���g�w�i�𓧉߂��邩�H
	void          setFontImage(int Xnum, int Ynum, char* fontImgfilename);                          // �t�H���g�摜���t�H���g���Z�b�g����
	void          setFontColor(int r, int g, int b);                                                // �t�H���g�J���[�Z�b�g
	void          setFontColorShadow(int r, int g, int b);                                          // �e�J���[���Z�b�g
	void          textDrawRandom(int x, int y, char* string, int maxRand, int countDown);           // �����_�������\��
	
	void          setFontShadowOffset(int ofsX, int ofsY);                                          // �e�t�H���g�ʒu�I�t�Z�b�g
	void          textDraw(int x, int y, char* string);                                             // �e�L�X�g��`��
	void          textDrawWithShadow(int x, int y, char* string);                                   // �e�t���Ńe�L�X�g�`��

	void          textDrawMessage(int x, int y, char* string, unsigned int display_lengh);          // ���b�Z�[�W���\���i��������������j
	void          textDrawMessageWithShadow(int x, int y, char*string, unsigned int display_lengh); // ���b�Z�[�W���\���i��������������j
	void          reMapText(char* remapText); // �r�b�g�}�b�v�ɕ���ł��镶��������āA�e�L�X�g���當���������悤�ɂ���B�i�������ŕK�v�j

private:
	int           mFontImg[256] ; // �t�H���g�C���[�W�z��
	int           mFontMap[256] ; // �����}�b�v char�^�������t�H���g�C���[�W�z��Y�����ԍ��̃}�b�s���O

	unsigned int  mSizeX        ; // �t�H���g1���������T�C�Y
	unsigned int  mSizeY        ; // �t�H���g1�������c�T�C�Y	
	int           mShadowOffsetX; // �e�t�H���g�ʒu�I�t�Z�b�gX
	int           mShadowOffsetY; // �e�t�H���g�ʒu�I�t�Z�b�gY
	bool          mUseflag      ; // �t�H���g�g�p�\�t���O
	bool          mBgalpha      ; // �����w�i�𓧉߂����邩

	int           isString(char c)          ; // �������C���[�W�z��̓Y�����ɕϊ�
	unsigned char R, G, B;         // �����F 
	unsigned char mShadowR;
	unsigned char mShadowG;
	unsigned char mShadowB;
};

#endif