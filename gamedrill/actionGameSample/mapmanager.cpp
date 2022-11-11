#include "Game.h"
#include "mapManager.h"
#include "camera.h"

#pragma warning (disable:4996)

MapManager::~MapManager()
{
	//�}�b�v�f�[�^�[�{��
	if( !mMapData )
	{
		for( unsigned int i = 0; i < m_layerMaxnum ; i++ )
		{
			delete[] mMapData[i];
		}
		delete[] *mMapData;
	}
	mMapData = NULL;

	// �`�b�v���W
	if( !m_chipType )
	{	
		delete m_chipType;
	}
	m_chipType = NULL;

	// �摜
	if( !m_ImgHandle )
	{ 
		DeleteGraph( m_ImgHandle );
	}
	m_ImgHandle = 0;
}

void MapManager::Init(unsigned int mapWidth, unsigned int mapHeight, unsigned int layernum )
{

	if( layernum == 0 )
		return;

	m_X = 0; m_Y = 0;
	m_mapWidth     = mapWidth  ;
	m_mapHeight    = mapHeight ;

	m_layerMaxnum  = layernum  ;

	// �}�b�v�f�[�^�T�C�Y�m�ہ�0�N���A
	mMapData = new unsigned char*[ layernum ];

	for( unsigned int i = 0; i < m_layerMaxnum; i++ )
	{
		mMapData[i] = new unsigned char[m_mapWidth * m_mapHeight];
	}
}

bool MapManager::setImage( const char* filename, unsigned int chipSizeX, unsigned int chipSizeY )
{
	m_mapChipSizeX = chipSizeX;
	m_mapChipSizeY = chipSizeY;

	// �摜ID�o�^
	m_ImgHandle = LoadGraph( filename );
	if( m_ImgHandle == -1 )
		return false;

	// �摜�̃T�C�Y����`�b�v�̏c���̃`�b�v������ł�������Z�o
	int x,y;
	GetGraphSize( m_ImgHandle, &x, &y );

	m_mapChipXnum = x / chipSizeX ;
	m_mapChipYnum = y / chipSizeY ;

	// �`�b�v�^�C�v��ʔz��m��
	m_chipType = new s_chipCoord[ m_mapChipXnum * m_mapChipYnum ];

	// �`�b�v��ʔz��v�Z�@�^�C�v�ԍ���x,y���W����
	for( unsigned int i = 0; i < m_mapChipXnum * m_mapChipYnum ; i++ )
	{
		m_chipType[i].x = (i % m_mapChipXnum) * m_mapChipSizeX ;
		m_chipType[i].y = (i / m_mapChipXnum) * m_mapChipSizeY ;
	}

	return true;

}


//X���W����}�b�v�̉������Y������Ԃ�
int MapManager::getCollisionMapIndex_X( int posx )
{
	// posX���}�b�v�̒��ɓ����Ă��Ȃ��ꍇ��-1��Ԃ�
	if( posx < 0 || (int)(m_mapChipSizeX * m_mapWidth) < posx )
	{
		return -1;
	}

	return posx / m_mapChipSizeX;
}

//Y���W����}�b�v�̏c�����Y������Ԃ�
int MapManager::getCollisionMapIndex_Y( int posy )
{
	// posY���}�b�v�̒��ɓ����Ă��Ȃ��ꍇ��-1��Ԃ�
	if( posy < 0 || (int)(m_mapChipSizeY * m_mapHeight) < posy )
	{
		return -1;
	}

	return posy / m_mapChipSizeY;
}

// �}�b�v�̃C���f�b�N�X����u���b�N�̎�ނ�Ԃ�
unsigned char MapManager::getCollisionMapIdFromIndex( int xIndex, int yIndex )
{
	//�}�b�v�`�b�v�T�C�Y�����Ă��Ȃ����H
	if( xIndex < 0 || xIndex > (int)m_mapWidth || yIndex < 0 || yIndex > (int)m_mapHeight)
	{
		return 0;
	}
	// �}�b�v�f�[�^���u���b�N�^�C�v�Ԃ�
	return mMapData[m_layerMaxnum - 1][xIndex + yIndex * m_mapWidth ];
}

void MapManager::getCollisionRectFromIndex( int xIndex, int yIndex, rectangle* outRect )
{

	rectangle ret;
	ret.sx = 0;
	ret.sy = 0;
	ret.height = 0;
	ret.width  = 0;

	//�}�b�v�`�b�v�T�C�Y�����Ă����ꍇ�͑傫���O�̋�`��Ԃ�
	if( xIndex < 0 || xIndex > (int)m_mapWidth || yIndex < 0 || yIndex > (int)m_mapHeight)
	{
		*outRect = ret;
		return ;
	}

	// �u���b�N��`�Ԃ�
	ret.sx    = xIndex * m_mapChipSizeX;
	ret.sy    = yIndex * m_mapChipSizeY;
	ret.width = m_mapChipSizeX ;
	ret.height= m_mapChipSizeY ;

	*outRect = ret;
}


void MapManager::move()
{

}

void MapManager::draw()
{
	int camx, camy;
	camx = m_pCamera->GetCameraX();
	camy = m_pCamera->GetCameraY();

	if( !m_ImgHandle )
		return ;
	
	// �}�b�v���g���o�[�X���Ȃ���`��   ............ToDo �}�b�v�̃X�N���[�����W�ɍ��킹�Đ؂�o���ĕ`��l����
	for( unsigned char layer = 0; layer < (m_layerMaxnum) - 1 ; layer++ )  
	{
		for( unsigned int i = 0; i < m_mapHeight; i++ )
		{
			for( unsigned int j = 0; j < m_mapWidth; j++)
			{
				int id = mMapData[layer][ i * m_mapWidth + j ];
				DrawRectGraph( j * m_mapChipSizeX - camx, i * m_mapChipSizeY - camy, //�`��ʒu
					           m_chipType[id].x         , m_chipType[id].y  ,  //���摜�؂�o���ʒu 
							   m_mapChipSizeX           , m_mapChipSizeY    , //�`�b�v�T�C�Y
							   m_ImgHandle              , TRUE, 0 );
			}
		}
	}
}


// �����蔻��f�[�^��Ԃ�
unsigned char MapManager::getCollisionMapId( int in_posx, int in_posy,int *out_block_x, int *out_block_y )
{
	int x, y;
	x = in_posx / m_mapChipSizeX ;
	y = in_posy / m_mapChipSizeY ;

	if( x > (int)m_mapWidth || y > (int)m_mapHeight )
	{
		out_block_x = 0; 
		out_block_y = 0;
		return 0;
	}

	*out_block_x = x * (int)m_mapChipSizeX ;
	*out_block_y = y * (int)m_mapChipSizeY ;
	return mMapData[m_layerMaxnum - 1][ x + y * m_mapWidth ];
}


// �f�[�^���P�s�ǂݎ��
// ��s�A�擪��'/'�s�͓ǂݔ�΂�
void MapManager::readDataLine(char* buf,size_t bufSize, FILE *p)
{
	//�P�s�ǂݍ���
	fgets( buf, bufSize, p );

	//�R�����g�s�ł������ǂݔ�΂�
	while( buf[0] == '/' || buf[0]=='\n' )
	{
		fgets( buf, bufSize, p );
	}
	// �R�����g�s�ł͖����s����荞�߂�
	return;
}

bool MapManager::readHeader( const char* mapFilename )
{
	FILE *fp = NULL;
	fp = fopen(mapFilename , "rt" );
	if( fp == NULL )
	{
		return false;
	}

	// �e���|����
	char buf[1024];

	// �u���b�N�T�C�Y�ǂݍ���
	readDataLine( buf, 1024, fp );
	char *token = NULL;

	// �}�b�v�f�[�^�̃w�b�_�����ǂݍ���
	token = strtok( buf,  "," );
	m_mapWidth = atoi( token ); // �}�b�vX�����̃`�b�v��

	token = strtok( NULL, "," );
	m_mapHeight = atoi( token ); // �}�b�vY�����̃`�b�v��

	token = strtok( NULL, "," );
	m_mapChipSizeX= atoi( token ); // �`�b�v�P�̑傫��X

	token = strtok( NULL, "," );
	m_mapChipSizeY = atoi( token ); //�`�b�v�P�̑傫��Y

	token = strtok( NULL, "," );
	m_layerMaxnum = atoi( token ); // ���C���[����

	//�t�@�C���N���[�Y
	fclose( fp );

	return true;
}

bool MapManager::readMapdata( const char* mapFileName )
{
	// �}�b�v�t�@�C��CSV�ǂݍ���
	FILE *fp;
	fp = fopen(mapFileName , "rt" );
	if( fp == NULL )
	{
		return false;
	}

	// �e���|����
	char buf[1024],tmp[256];

	unsigned int x, y, layer = 0;
	char *token;

	readDataLine( buf, 1024, fp ); //�w�b�_������ǂ�

	// �}�b�v�{�̓ǂݍ���
	for( int layer = 0; layer < m_layerMaxnum; layer++ )
	{
		x = y = 0;
		while( y < m_mapHeight )
		{
			readDataLine( tmp, 256, fp );
			if ( tmp == NULL)
				return false;

			// �s�ǂݍ���
			token = strtok( tmp, "," );

			//�P�s���J���}��؂�Ń}�b�v�z��ɃR�s�[����
			while( token != NULL && x < m_mapWidth )
			{
				mMapData[layer][y * m_mapWidth + x] = atoi( token );

				token = strtok( NULL, ",");
				x++;
			}
			x = 0;
			y++;
		}
	}

#ifdef DEBUG_CONSOLE
	for( unsigned int i = 0; i < m_mapHeight; i++ )
	{
		printf("%d:",i);
		for( unsigned int j = 0; j < m_mapWidth; j++ )
		{
			printf( "%2d,",mMapData[1][i * m_mapWidth + j] );
		}
		printf("\n");
	}
#endif

	return true;
}

bool MapManager::LoadMapData( const char *imageFileName, const char* mapFileName )
{

	// �w�b�_�[�ǂݍ���
	if( !readHeader( mapFileName ) )
	{
		return false;
	}

	// �}�b�v�f�[�^�m��
	Init( m_mapWidth, m_mapHeight, m_layerMaxnum );

	//�C���[�W�t�@�C���ǂݍ���
	if( !setImage( imageFileName, m_mapChipSizeX, m_mapChipSizeY ) )
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// �}�b�v�f�[�^�{��
	// �}�b�v�f�[�^�P�s����荞��
	if(!readMapdata( mapFileName ))
	{
		return false;
	}

	return true;
}


/*

// �}�b�v�f�[�^�ǂݍ���
bool MapManager::loadMap(char* filename)
{
	FILE *fp;
	fp = fopen( filename, "rt" );

	if( fp == NULL )
	{
		return false;
	}

	// �e���|����
	char tmp[256];

	// �u���b�N�T�C�Y�ǂݍ���
	readDataLine( tmp, 256, fp );
	mBlockSize = atoi( tmp );

	// �}�b�v�T�C�Y�ǂݍ���
	readDataLine( tmp, 256, fp );
	m_mapXBlockNum = atoi( tmp );

	readDataLine( tmp, 256, fp );
	m_mapYBlockNum = atoi( tmp );

	//�}�b�v�f�[�^�m��
	m_pmap = new unsigned char[m_mapXBlockNum * m_mapYBlockNum];

	char *token = NULL;
	unsigned int x,y;
	x = y = 0;

	//�}�b�v�f�[�^�P�s����荞��
	while( y < m_mapYBlockNum )
	{
		readDataLine( tmp, 256, fp );
		// �s�ǂݍ���
		token = strtok( tmp, "," );

		//�P�s���J���}��؂�Ń}�b�v�z��ɃR�s�[����
		while( token != NULL && x < m_mapXBlockNum )
		{
			m_pmap[y * m_mapXBlockNum + x] = atoi( token );

			token = strtok( NULL, ",");
			x++;
		}
		x = 0;
		y++;
	} 

	// �}�b�v���e�\��
	for( unsigned int i = 0; i < m_mapYBlockNum; i++ )
	{
		for( unsigned int j = 0; j < m_mapXBlockNum; j++ )
		{
			printf( "%2d, ", m_pmap[ i * m_mapXBlockNum + j ] );
		}
		printf( "\n" );
	}

	fclose(fp);
	return true;
}

//�}�b�v�`�b�v�f�[�^�ǂݍ���
bool MapManager::loadMapChipDef( char* filename )
{
	FILE *fp;
	char tmp[512];

	fp = fopen( filename, "rt" );
	if( fp == NULL )
	{
		printf( "mapChipFile %s is not found\n" );
		return false;
	}

	// �}�b�v�`�b�v��ސ��ǂݍ��݁B�`�b�v��ނ�0�ԁi�󔒁j���\��ς݂Ȃ̂�+1����
	readDataLine( tmp, 512, fp );
	m_ChipNum = atoi(tmp) + 1;

	//�`�b�v�̎�ނ��i�[����z����m��
	m_pChipArray = new mapChip[ m_ChipNum ];

	//�`�b�v�O�Ԃ͋󔒂Ƃ��Ďg���邽�߁A0�Ԃ̓_�~�[�f�[�^�i�[
	m_pChipArray[0].chipID         = 0;
	m_pChipArray[0].gbvFilePath[0] = '\0';
	m_pChipArray[0].mesh.vaoHandle = 0;
	m_pChipArray[0].mesh.format    = 0;
	m_pChipArray[0].mesh.vertexNum = 0;

	char* token = NULL;
	int id = 1;

	// �}�b�v�`�b�vID��GBV�t�@�C������ǂݍ���
	for( unsigned int i = 1; i < m_ChipNum; i++ )
	{
		readDataLine( tmp, 512, fp );
		if( tmp == NULL )
		{
			printf( "mapChipfile %s is broken\n", filename );
			return false;
		}
		
		// �s�ǂݍ���
		token = strtok( tmp, ",\n" );

		//�P�s���J���}��؂�Ń}�b�v�z��ɃR�s�[����
		while( token != NULL )
		{
			m_pChipArray[id].chipID = atoi( token );
			token = strtok( NULL, ",\n");
			strcpy( m_pChipArray[id].gbvFilePath, token );
			id++;
			token = strtok( NULL, ",\n" );
		}
	} 

	//�f�o�b�O���g�m�F
	for( unsigned int i = 0; i < m_ChipNum; i++ )
	{
		printf( "chipID:[%3d] filePath = %s\n", m_pChipArray[i].chipID, m_pChipArray[i].gbvFilePath );
	}

	// ���b�V���f�[�^�ǂݍ���
	for( unsigned int i = 1; i < m_ChipNum; i++ )
	{
		if( !load_GBV_file( m_pChipArray[i].gbvFilePath, &(m_pChipArray[i].mesh)) )
		{
			printf("Mapchip Mesh�ǂݍ��݃G���[ %s ������܂���\n",m_pChipArray[i].gbvFilePath );
		} else {
			printf( "load %s\n", m_pChipArray[i].gbvFilePath );
		}
		
	}
	fclose(fp);
	return true;
}
*/