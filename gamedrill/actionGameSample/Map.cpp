#include "Map.h"

Map::Map()
{
	// ������
	mMapChipWidthNum             = 0     ;
	mMapChipHeightNum            = 0     ;
	mMapChipGraphSizeX           = 0     ;
	mMapChipGraphSizeY           = 0     ;
	mMapData                     = NULL  ; 
	mMapChipHandleArray          = NULL  ;
	mMapChipHandleArrayIndexMax  = 0     ;
	mbHit                        = false ;

}

Map::~Map()
{
	if ( mMapData )
	{
		delete[] mMapData;
		mMapData = NULL;
	}

	if (mMapChipHandleArray)
	{
		//�}�b�v�`�b�v�摜�������
		for (unsigned int i = 0; i < mMapChipHandleArrayIndexMax; i++)
		{
			DeleteGraph(mMapChipHandleArray[i]);
		}
		delete[] mMapChipHandleArray;
	}
}

//�}�b�v�f�[�^�̓ǂݍ���
bool Map::readMapdata(const char * mapFileName, const char* mapchipGraphFileName)
{
	// �}�b�v�̃t�@�C���w�b�_������ǂ�
	if (!readHeader(mapFileName))
	{
		printf("mapChipData read failed : %s", mapFileName);
	}
	//�t�@�C���w�b�_�����}�b�v�f�[�^�m��
	mMapData = new unsigned char[mMapChipWidthNum * mMapChipHeightNum];

	// �}�b�v�t�@�C��CSV�ǂݍ���
	FILE *fp;
	fp = fopen(mapFileName, "rt");
	if (fp == NULL)
	{
		return false;
	}

	// �e���|����
	char buf[1024], tmp[256];

	unsigned int x, y, layer = 0;
	char *token;

	readDataLine(buf, 1024, fp); //�w�b�_�������

	x = y = 0;
	while (y < mMapChipHeightNum)
	{
		// �s�ǂݍ���
		readDataLine(tmp, 256, fp);
		if (tmp == NULL)
			return false;

		//���g�[�N�����擾
		token = strtok(tmp, ",");

		//�P�s���J���}��؂�Ń}�b�v�z��ɃR�s�[����
		while (token != NULL && x < mMapChipWidthNum)
		{
			mMapData[y * mMapChipWidthNum + x] = atoi(token);

			token = strtok(NULL, ",");
			x++;
		}
		x = 0;
		y++;
	}

	//�摜�T�C�Y���Q�b�g���邽�߂Ƀ}�b�v�摜����x��ǂ�
	int tmpID;
	tmpID = LoadGraph((TCHAR *)mapchipGraphFileName);
	int width, height;

	GetGraphSize(tmpID, &width, &height);

	DeleteGraph(tmpID);

	//�摜���c������������ł��邩���v�Z = �摜�i���jdot /  1�u���b�N����dot
	width  /= mMapChipGraphSizeX;
	height /= mMapChipGraphSizeY;

	mMapChipHandleArrayIndexMax = width * height;

	//�}�b�v�`�b�v�n���h���z����m��
	mMapChipHandleArray = new int[mMapChipHandleArrayIndexMax];

	//�摜�ǂݍ���
	LoadDivGraph(mapchipGraphFileName,
		         mMapChipHandleArrayIndexMax,
		         width, height,
		         mMapChipGraphSizeX,
		         mMapChipGraphSizeY,
		         (int *)mMapChipHandleArray);

	return true;
}

void Map::mapDraw(Camera *p_Camera)
{
	unsigned int i, j;

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//�}�b�v�`�b�v���ׂ�(�J�������W�������j
	//���X�N���[���͈͊O�܂ł��̃v���O�����ł͕`�悵�Ă��܂��B
	// ��ʓ������`�悷��ɂ͂ǂ������炢�����l���܂��傤�`

	int cameraoffsetX = p_Camera->GetCameraX();
	int cameraoffsetY = p_Camera->GetCameraY();

	for (i = 0; i < mMapChipHeightNum; i++)
	{
		for (j = 0; j < mMapChipWidthNum; j++)
		{
			int chipimgIndex = mMapData[i * mMapChipHeightNum + j];
			int imgID = mMapChipHandleArray[chipimgIndex];

			DrawGraph(j * mMapChipGraphSizeX - cameraoffsetX,
				i * mMapChipGraphSizeY - cameraoffsetY,
				imgID, TRUE);
		}
	}
}

void Map::gridDraw(Camera *p_Camera)
{
	// �X�N���[�����W
	int x, y;
	int screenMaxX, screenMaxY;
	screenMaxX = GAMEINSTANCE.getScreenWidth();
	screenMaxY = GAMEINSTANCE.getScreenHeight();

	// �X�N���[��������W���O���b�h���牽�s�N�Z������Ă邩�Z�o
	int offsetX, offsetY;
	p_Camera->screenPos2WorldPos(0, 0, &offsetX, &offsetY);

	offsetX %= mMapChipGraphSizeX;
	offsetY %= mMapChipGraphSizeY;

	//�O���b�h���C���J���[
	int color = 0xffff0000;

	// �c���C���f�b�N�X�l
	int indexX, indexY;

	// �C���f�N�X�l�\���p������o�b�t�@
	char buf[10];

	// ������ON
	SetDrawBlendMode(DX_BLENDMODE_ADD, 100);

	// �c�O���b�h�`��
	x = -offsetX;
	while (x < screenMaxX)
	{
		//�O���b�h�`��
		DrawLine(x, 0, x, screenMaxY, color);

		// �C���f�b�N�X�l�Z�o
		p_Camera->screenPos2WorldPos(x, 0, &indexX, &indexY);
		sprintf(buf, "%3d", indexX / mMapChipGraphSizeX);
		GAMEINSTANCE.systemText.textDraw(x, 0, buf);

		x += mMapChipGraphSizeX;
	}

	//���O���b�h
	y = -offsetY;
	while (y < screenMaxY)
	{
		DrawLine(0, y, screenMaxX, y, color);

		// �C���f�b�N�X�l�Z�o
		p_Camera->screenPos2WorldPos(0, y, &indexX, &indexY);
		sprintf(buf, "%3d", indexY / mMapChipGraphSizeY);
		GAMEINSTANCE.systemText.textDraw(0, y, buf);

		y += mMapChipGraphSizeY;
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

bool Map::isMapHit(unsigned int worldX, unsigned int worldY)
{
	// ���[���h���W���}�b�v�Y�������Z�o����
	unsigned int m_mapIndexX = worldX / mMapChipGraphSizeX;
	unsigned int m_mapIndexY = worldY / mMapChipGraphSizeY;

	//���������}�b�v�͈͓̔����H
	if (m_mapIndexX >= mMapChipWidthNum ||
	    m_mapIndexY >= mMapChipHeightNum)

	{
		return false;
	}

	// �����_�̓}�b�v�̒��Ȃ̂ŁAindex��������̃`�b�v�����ׂ�
	int mapId;
	mapId = mMapData[m_mapIndexX + m_mapIndexY * mMapChipWidthNum];

	if (!mapId)
		return false;

	return true;
}

//X���W(���[���h)����}�b�v�̉������Y������Ԃ�
int Map::getCollisionMapIndex_X(int worldposx)
{
	// posX���}�b�v�̒��ɓ����Ă��Ȃ��ꍇ��-1��Ԃ�
	if (worldposx < 0 || (int)(mMapChipGraphSizeX * mMapChipWidthNum) < worldposx)
	{
		return -1;
	}

	return worldposx / mMapChipGraphSizeX;
}

//Y���W�i���[���h�j����}�b�v�̏c�����Y������Ԃ�
int Map::getCollisionMapIndex_Y(int worldposy)
{
	// posY���}�b�v�̒��ɓ����Ă��Ȃ��ꍇ��-1��Ԃ�
	if (worldposy < 0 || (int)(mMapChipGraphSizeY * mMapChipHeightNum) < worldposy)
	{
		return -1;
	}
	return worldposy / mMapChipGraphSizeY;
}

// �c���̓Y�������}�b�vID��Ԃ�
unsigned char Map::getCollisionMapIdFromIndex(int xIndex, int yIndex)
{

	//�}�b�v�`�b�v�T�C�Y�����Ă��Ȃ����H
	if (xIndex < 0 || xIndex >(int)mMapChipWidthNum || yIndex < 0 || yIndex >(int)mMapChipHeightNum)
	{
		return 0;
	}
	// �}�b�v�f�[�^���u���b�N�^�C�v�Ԃ�
	return mMapData[xIndex + yIndex * mMapChipWidthNum];

}



////////////////////////////////////////////////////////////////////////////
// 1�s�����R�����g(�s��//������s)���΂��Ȃ���ǂ�
// �����F
// buf (in/out)  ���ݓǂ�ł���1�s����荞�񂾃f�[�^�ւ̐擪�A�h���X
// bufSize (int) buf�̃f�[�^�T�C�Y�i�o�C�g���j
// p             �t�@�C���|�C���^
// �߂�l�F�Ȃ�
// Desc   :  ���ݓǂ݂���ł���t�@�C������1�s����buf�̕�����Ɋi�[����
//           �ǂ݂��񂾍s���R�����g// �܂��� \n�Ȃ玟�̍s��ǂ݁Abuf�Ɋi�[����
////////////////////////////////////////////////////////////////////////////
void Map::readDataLine(char * buf, size_t bufSize, FILE * p)
{
	//�P�s�ǂݍ���
	fgets(buf, bufSize, p);

	//�R�����g�s�ł������ǂݔ�΂�
	while (buf[0] == '/' || buf[0] == '\n')
	{
		fgets(buf, bufSize, p);
	}
	// �R�����g�s�ł͖����s����荞�߂�
	return;
}
////////////////////////////////////////////////////////////////////////////
// �}�b�v�t�@�C���w�b�_����ǂ� �}�b�v�̕������A�}�b�v�`�b�v�傫����
// ���@���FmapFilename csv�t�@�C����
// �߂�l�F�ǂ݂��ݐ��� true / �ǂݍ��ݎ��s false
// desc  �Fcsv�t�@�C����ǂݍ��݁A�w�b�_����ǂݍ��ށB
//         �������ɂ̓}�b�v�̃u���b�N�c�����A1�u���b�N�̕�����(pixel)
//         �Ƀf�[�^���i�[�����B�ǂݍ��ݎ��s���̒l�͕s��B
////////////////////////////////////////////////////////////////////////////

bool Map::readHeader(const char * mapFilename)
{
	FILE *fp = NULL;
	fp = fopen(mapFilename, "rt");
	if (fp == NULL)
	{
		return false;
	}

	// �e���|����
	char buf[1024];

	// �u���b�N�T�C�Y�ǂݍ���
	readDataLine(buf, 1024, fp);
	char *token = NULL;

	// �}�b�v�f�[�^�̃w�b�_�����ǂݍ���
	token = strtok(buf, ",");
	mMapChipWidthNum = atoi(token);     // �}�b�vX�����̃`�b�v��

	token = strtok(NULL, ",");
	mMapChipHeightNum = atoi(token);    // �}�b�vY�����̃`�b�v��

	token = strtok(NULL, ",");
	mMapChipGraphSizeX = atoi(token); // �`�b�v�P�̑傫��X

	token = strtok(NULL, ",");
	mMapChipGraphSizeY = atoi(token); //�`�b�v�P�̑傫��

	//�t�@�C���N���[�Y
	fclose(fp);

	return true;
}