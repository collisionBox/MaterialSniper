#include "questions.h"

const int scrSpeed = 5;
int  testID;


Quest25Seq::Quest25Seq()
{
	const char *mapfilename = "image/dungeon.csv";
	const char *mapImgfilename = "image/dungeonSheet.png";

	testID=LoadGraph("image/block1.bmp");

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
	width  /= m_mapChipSizeX;
	height /= m_mapChipSizeY;

	mMapChipHandleArrayIndexMax = width * height;

	//�}�b�v�`�b�v�n���h���z����m��
	mMapChipHandleArray = new int[mMapChipHandleArrayIndexMax];

	//�摜�ǂݍ���
	LoadDivGraph("image/dungeonSheet.png", mMapChipHandleArrayIndexMax, width, height, 64, 64, (int *)mMapChipHandleArray);

	// �J�����ʒu�Z�b�g
	m_camX = 0;
	m_camY = 0;

	m_camVx = 0;
	m_camVy = scrSpeed;
}


Quest25Seq::~Quest25Seq()
{
	//�}�b�v�`�b�v�摜�������
	for (unsigned int i = 0; i < mMapChipHandleArrayIndexMax; i++)
	{
		DeleteGraph(mMapChipHandleArray[i]);
	}
	delete[] mMapChipHandleArray;

	//�}�b�v�f�[�^���
	delete[] mMapData;
	mMapData = NULL;
}
Sequence* Quest25Seq::move()
{
	int wLeft, wRight;
	int wTop, wBottom;

	// �X�N���[���̎l�������[���h���W�łǂ̈ʒu�ɂ��邩���Z�o
	screenPos2WorldPos(0, 0, &wLeft, &wTop);
	screenPos2WorldPos(GAMEINSTANCE.getScreenWidth(),
		               GAMEINSTANCE.getScreenHeight(),
		               &wRight, &wBottom);

	// ���[���h���W�̌��E�_�i����ȏ�}�b�v�f�[�^�Ȃ����W�j�Z�o
	int minWorldX, maxWorldX;
	int minWorldY, maxWorldY;

	minWorldX = 0; 
	minWorldY = 0;
	maxWorldX = m_mapChipSizeX * m_mapWidth;
	maxWorldY = m_mapChipSizeY * m_mapHeight;

	//���x�X�V

	//�}�b�v�̉E�ɓ˂���������
	if (m_camX > maxWorldX - GAMEINSTANCE.getScreenWidth())
	{
		m_camX = maxWorldX - GAMEINSTANCE.getScreenWidth();
		m_camVx = 0;
		m_camVy = -scrSpeed;
	}

	//�}�b�v�̍��ɓ˂���������
	if (m_camX < minWorldX)
	{
		m_camX = minWorldX;
		m_camVx = 0;
		m_camVy = scrSpeed;
	}

	//�}�b�v�̏�ɓ˂���������
	if (m_camY < minWorldY)
	{
		m_camY = minWorldY;
		m_camVy = 0;
		m_camVx = -scrSpeed;
	}
	
	//�}�b�v�̉��ɓ˂���������
	if (m_camY > maxWorldX - GAMEINSTANCE.getScreenHeight())
	{
		m_camY = maxWorldX - GAMEINSTANCE.getScreenHeight();
		m_camVy = 0;
		m_camVx = scrSpeed;
	}
	//�J�����̃��[���h�ʒu��ύX
	m_camX += m_camVx;
	m_camY += m_camVy;

	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest26Seq;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest25Seq::draw()
{
	ClearDrawScreen();

	static int i = 0;
	i++;
	if (i >= 255)
		i = 0;

	mapDraw();

	DrawGraph(100, 100, testID, TRUE);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #25.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}

// �}�b�v�̕`�惋�[�`��
void Quest25Seq::mapDraw()
{
	unsigned int i, j;

	


	//�}�b�v�`�b�v���ׂ�(�J�������W�������j
	//���X�N���[���͈͊O�܂ł��̃v���O�����ł͕`�悵�Ă��܂��B
	// ��ʓ������`�悷��ɂ͂ǂ������炢�����l���܂��傤�`
	for (i = 0; i < m_mapHeight; i++)
	{
		for (j = 0; j < m_mapWidth; j++)
		{
			int chipimgIndex = mMapData[i * m_mapHeight + j];
			int imgID = mMapChipHandleArray[chipimgIndex];

			DrawGraph(j * m_mapChipSizeX - m_camX,
				      i * m_mapChipSizeY - m_camY,
				      imgID, TRUE);
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
void Quest25Seq::readDataLine(char* buf, size_t bufSize, FILE *p)
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
bool Quest25Seq::readHeader(const char* mapFilename)
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
bool Quest25Seq::readMapdata(const char* mapFileName)
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
void Quest25Seq::screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y)
{
	*worldPos_X = scrPos_x + m_camX;
	*worldPos_Y = scrPos_y + m_camY;
}

// ���[���h���W�n����X�N���[�����W�n�ւ̍��W�ϊ�
void Quest25Seq::worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y)
{
	*scrPos_X = worldPos_x - m_camX;
	*scrPos_Y = worldPos_y - m_camY;
}
