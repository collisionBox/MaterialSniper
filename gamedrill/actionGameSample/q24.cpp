#include "questions.h"

Quest24Seq::Quest24Seq()
{
	const char *mapfilename = "image/dungeon.csv";
	const char *mapImgfilename = "image/dungeonSheet.png";

	// �}�b�v�̃t�@�C���w�b�_������ǂ�
	if (!readHeader(mapfilename))
	{
		printf("mapChipData read failed : %s", mapfilename);
	}
	//�t�@�C���w�b�_�����}�b�v�f�[�^�m��
	mMapData = new unsigned char[m_mapWidth * m_mapHeight];

	//�t�@�C������}�b�v�f�[�^����荞��
	if (!readMapdata(mapfilename))
	{
		printf("mapData is broken : %s ", mapfilename);
	}

	//�摜�T�C�Y���Q�b�g���邽�߂Ƀ}�b�v�摜����x��ǂ�
	int tmpID;
	tmpID = LoadGraph(mapImgfilename);
	int width, height;

	GetGraphSize(tmpID, &width, &height);

	DeleteGraph(tmpID);

	//�摜���c������������ł��邩���Q�b�g
	width /= m_mapChipSizeX;
	height /= m_mapChipSizeY;

	mMapChipHandleArrayIndexMax = width * height;

	//�}�b�v�`�b�v�n���h���z����m��
	mMapChipHandleArray = new int[mMapChipHandleArrayIndexMax];

	//�摜�ǂݍ���
	LoadDivGraph("image/dungeonSheet.png", mMapChipHandleArrayIndexMax, width, height, 64, 64, (int *)mMapChipHandleArray);

}


Quest24Seq::~Quest24Seq()
{
	//�}�b�v�`�b�v�摜�������
	for(unsigned int i = 0; i < mMapChipHandleArrayIndexMax; i++)
	{
		DeleteGraph(mMapChipHandleArray[i]);
	}
	delete[] mMapChipHandleArray;

	//�}�b�v�f�[�^���
	delete[] mMapData;
	mMapData = NULL;
}
Sequence* Quest24Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest26Seq;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest24Seq::draw()
{
	ClearDrawScreen();

	mapDraw();

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #24.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}

// �}�b�v�̕`�惋�[�`��
void Quest24Seq::mapDraw()
{
	unsigned int i, j;

	//�}�b�v�`�b�v���ׂ�
	for (i = 0; i < m_mapHeight; i++)
	{
		for (j = 0; j < m_mapWidth; j++)
		{
			int chipimgIndex = mMapData[i * m_mapHeight + j];
			int imgID = mMapChipHandleArray[ chipimgIndex ];

			DrawGraph(j * m_mapChipSizeX, i * m_mapChipSizeY, imgID, TRUE);
		}
	}
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
void Quest24Seq::readDataLine(char* buf, size_t bufSize, FILE *p)
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
bool Quest24Seq::readHeader(const char* mapFilename)
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
	m_mapWidth = atoi(token);     // �}�b�vX�����̃`�b�v��

	token = strtok(NULL, ",");
	m_mapHeight = atoi(token);    // �}�b�vY�����̃`�b�v��

	token = strtok(NULL, ",");
	m_mapChipSizeX = atoi(token); // �`�b�v�P�̑傫��X

	token = strtok(NULL, ",");
	m_mapChipSizeY = atoi(token); //�`�b�v�P�̑傫��Y

								  //�t�@�C���N���[�Y
	fclose(fp);

	return true;
}

///////////////////////////////////////////////////////////////////////////
// CSV�t�@�C�����A�}�b�v�f�[�^�{�̂�ǂݍ��ށB
// 
///////////////////////////////////////////////////////////////////////////
bool Quest24Seq::readMapdata(const char* mapFileName)
{
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

    // �}�b�v�{�̓ǂݍ���
	x = y = 0;
	while (y < m_mapHeight)
	{
		// �s�ǂݍ���
		readDataLine(tmp, 256, fp);
		if (tmp == NULL)
			return false;

		//���g�[�N�����擾
		token = strtok(tmp, ",");

		//�P�s���J���}��؂�Ń}�b�v�z��ɃR�s�[����
		while (token != NULL && x < m_mapWidth)
		{
			mMapData[y * m_mapWidth + x] = atoi(token);

			token = strtok(NULL, ",");
			x++;
		}
		x = 0;
		y++;
	}

#ifdef DEBUG_CONSOLE
	for (unsigned int i = 0; i < m_mapHeight; i++)
	{
		printf("%d:", i);
		for (unsigned int j = 0; j < m_mapWidth; j++)
		{
			printf("%2d,", mMapData[i * m_mapWidth + j]);
		}
		printf("\n");
	}
#endif

	fclose(fp);
	return true;
}

// �X�N���[�����W�n���烏�[���h���W�n�ւ̍��W�ϊ�
void Quest24Seq::screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y)
{
	*worldPos_X = scrPos_x + m_camX;
	*worldPos_Y = scrPos_y + m_camY;
}

// ���[���h���W�n����X�N���[�����W�n�ւ̍��W�ϊ�
void Quest24Seq::worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y)
{
	*scrPos_X = worldPos_x - m_camX;
	*scrPos_Y = worldPos_y - m_camY;
}
