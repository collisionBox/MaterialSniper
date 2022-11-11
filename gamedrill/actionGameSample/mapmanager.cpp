#include "Game.h"
#include "mapManager.h"
#include "camera.h"

#pragma warning (disable:4996)

MapManager::~MapManager()
{
	//マップデーター本体
	if( !mMapData )
	{
		for( unsigned int i = 0; i < m_layerMaxnum ; i++ )
		{
			delete[] mMapData[i];
		}
		delete[] *mMapData;
	}
	mMapData = NULL;

	// チップ座標
	if( !m_chipType )
	{	
		delete m_chipType;
	}
	m_chipType = NULL;

	// 画像
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

	// マップデータサイズ確保＆0クリア
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

	// 画像ID登録
	m_ImgHandle = LoadGraph( filename );
	if( m_ImgHandle == -1 )
		return false;

	// 画像のサイズからチップの縦横のチップが並んでいる個数を算出
	int x,y;
	GetGraphSize( m_ImgHandle, &x, &y );

	m_mapChipXnum = x / chipSizeX ;
	m_mapChipYnum = y / chipSizeY ;

	// チップタイプ種別配列確保
	m_chipType = new s_chipCoord[ m_mapChipXnum * m_mapChipYnum ];

	// チップ種別配列計算　タイプ番号→x,y座標生成
	for( unsigned int i = 0; i < m_mapChipXnum * m_mapChipYnum ; i++ )
	{
		m_chipType[i].x = (i % m_mapChipXnum) * m_mapChipSizeX ;
		m_chipType[i].y = (i / m_mapChipXnum) * m_mapChipSizeY ;
	}

	return true;

}


//X座標からマップの横方向添え字を返す
int MapManager::getCollisionMapIndex_X( int posx )
{
	// posXがマップの中に入っていない場合は-1を返す
	if( posx < 0 || (int)(m_mapChipSizeX * m_mapWidth) < posx )
	{
		return -1;
	}

	return posx / m_mapChipSizeX;
}

//Y座標からマップの縦方向添え字を返す
int MapManager::getCollisionMapIndex_Y( int posy )
{
	// posYがマップの中に入っていない場合は-1を返す
	if( posy < 0 || (int)(m_mapChipSizeY * m_mapHeight) < posy )
	{
		return -1;
	}

	return posy / m_mapChipSizeY;
}

// マップのインデックスからブロックの種類を返す
unsigned char MapManager::getCollisionMapIdFromIndex( int xIndex, int yIndex )
{
	//マップチップサイズ超えていないか？
	if( xIndex < 0 || xIndex > (int)m_mapWidth || yIndex < 0 || yIndex > (int)m_mapHeight)
	{
		return 0;
	}
	// マップデータよりブロックタイプ返す
	return mMapData[m_layerMaxnum - 1][xIndex + yIndex * m_mapWidth ];
}

void MapManager::getCollisionRectFromIndex( int xIndex, int yIndex, rectangle* outRect )
{

	rectangle ret;
	ret.sx = 0;
	ret.sy = 0;
	ret.height = 0;
	ret.width  = 0;

	//マップチップサイズ超えていた場合は大きさ０の矩形を返す
	if( xIndex < 0 || xIndex > (int)m_mapWidth || yIndex < 0 || yIndex > (int)m_mapHeight)
	{
		*outRect = ret;
		return ;
	}

	// ブロック矩形返す
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
	
	// マップをトラバースしながら描画   ............ToDo マップのスクロール座標に合わせて切り出して描画考える
	for( unsigned char layer = 0; layer < (m_layerMaxnum) - 1 ; layer++ )  
	{
		for( unsigned int i = 0; i < m_mapHeight; i++ )
		{
			for( unsigned int j = 0; j < m_mapWidth; j++)
			{
				int id = mMapData[layer][ i * m_mapWidth + j ];
				DrawRectGraph( j * m_mapChipSizeX - camx, i * m_mapChipSizeY - camy, //描画位置
					           m_chipType[id].x         , m_chipType[id].y  ,  //元画像切り出し位置 
							   m_mapChipSizeX           , m_mapChipSizeY    , //チップサイズ
							   m_ImgHandle              , TRUE, 0 );
			}
		}
	}
}


// 当たり判定データを返す
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


// データを１行読み取る
// 空行、先頭が'/'行は読み飛ばす
void MapManager::readDataLine(char* buf,size_t bufSize, FILE *p)
{
	//１行読み込み
	fgets( buf, bufSize, p );

	//コメント行である限り読み飛ばす
	while( buf[0] == '/' || buf[0]=='\n' )
	{
		fgets( buf, bufSize, p );
	}
	// コメント行では無い行が取り込めた
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

	// テンポラリ
	char buf[1024];

	// ブロックサイズ読み込み
	readDataLine( buf, 1024, fp );
	char *token = NULL;

	// マップデータのヘッダ部分読み込み
	token = strtok( buf,  "," );
	m_mapWidth = atoi( token ); // マップX方向のチップ個数

	token = strtok( NULL, "," );
	m_mapHeight = atoi( token ); // マップY方向のチップ個数

	token = strtok( NULL, "," );
	m_mapChipSizeX= atoi( token ); // チップ１個の大きさX

	token = strtok( NULL, "," );
	m_mapChipSizeY = atoi( token ); //チップ１個の大きさY

	token = strtok( NULL, "," );
	m_layerMaxnum = atoi( token ); // レイヤー枚数

	//ファイルクローズ
	fclose( fp );

	return true;
}

bool MapManager::readMapdata( const char* mapFileName )
{
	// マップファイルCSV読み込み
	FILE *fp;
	fp = fopen(mapFileName , "rt" );
	if( fp == NULL )
	{
		return false;
	}

	// テンポラリ
	char buf[1024],tmp[256];

	unsigned int x, y, layer = 0;
	char *token;

	readDataLine( buf, 1024, fp ); //ヘッダ部分空読み

	// マップ本体読み込み
	for( int layer = 0; layer < m_layerMaxnum; layer++ )
	{
		x = y = 0;
		while( y < m_mapHeight )
		{
			readDataLine( tmp, 256, fp );
			if ( tmp == NULL)
				return false;

			// 行読み込み
			token = strtok( tmp, "," );

			//１行をカンマ区切りでマップ配列にコピーする
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

	// ヘッダー読み込み
	if( !readHeader( mapFileName ) )
	{
		return false;
	}

	// マップデータ確保
	Init( m_mapWidth, m_mapHeight, m_layerMaxnum );

	//イメージファイル読み込み
	if( !setImage( imageFileName, m_mapChipSizeX, m_mapChipSizeY ) )
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// マップデータ本体
	// マップデータ１行ずつ取り込み
	if(!readMapdata( mapFileName ))
	{
		return false;
	}

	return true;
}


/*

// マップデータ読み込み
bool MapManager::loadMap(char* filename)
{
	FILE *fp;
	fp = fopen( filename, "rt" );

	if( fp == NULL )
	{
		return false;
	}

	// テンポラリ
	char tmp[256];

	// ブロックサイズ読み込み
	readDataLine( tmp, 256, fp );
	mBlockSize = atoi( tmp );

	// マップサイズ読み込み
	readDataLine( tmp, 256, fp );
	m_mapXBlockNum = atoi( tmp );

	readDataLine( tmp, 256, fp );
	m_mapYBlockNum = atoi( tmp );

	//マップデータ確保
	m_pmap = new unsigned char[m_mapXBlockNum * m_mapYBlockNum];

	char *token = NULL;
	unsigned int x,y;
	x = y = 0;

	//マップデータ１行ずつ取り込み
	while( y < m_mapYBlockNum )
	{
		readDataLine( tmp, 256, fp );
		// 行読み込み
		token = strtok( tmp, "," );

		//１行をカンマ区切りでマップ配列にコピーする
		while( token != NULL && x < m_mapXBlockNum )
		{
			m_pmap[y * m_mapXBlockNum + x] = atoi( token );

			token = strtok( NULL, ",");
			x++;
		}
		x = 0;
		y++;
	} 

	// マップ内容表示
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

//マップチップデータ読み込み
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

	// マップチップ種類数読み込み。チップ種類は0番（空白）が予約済みなので+1する
	readDataLine( tmp, 512, fp );
	m_ChipNum = atoi(tmp) + 1;

	//チップの種類を格納する配列を確保
	m_pChipArray = new mapChip[ m_ChipNum ];

	//チップ０番は空白として使われるため、0番はダミーデータ格納
	m_pChipArray[0].chipID         = 0;
	m_pChipArray[0].gbvFilePath[0] = '\0';
	m_pChipArray[0].mesh.vaoHandle = 0;
	m_pChipArray[0].mesh.format    = 0;
	m_pChipArray[0].mesh.vertexNum = 0;

	char* token = NULL;
	int id = 1;

	// マップチップIDとGBVファイル名を読み込む
	for( unsigned int i = 1; i < m_ChipNum; i++ )
	{
		readDataLine( tmp, 512, fp );
		if( tmp == NULL )
		{
			printf( "mapChipfile %s is broken\n", filename );
			return false;
		}
		
		// 行読み込み
		token = strtok( tmp, ",\n" );

		//１行をカンマ区切りでマップ配列にコピーする
		while( token != NULL )
		{
			m_pChipArray[id].chipID = atoi( token );
			token = strtok( NULL, ",\n");
			strcpy( m_pChipArray[id].gbvFilePath, token );
			id++;
			token = strtok( NULL, ",\n" );
		}
	} 

	//デバッグ中身確認
	for( unsigned int i = 0; i < m_ChipNum; i++ )
	{
		printf( "chipID:[%3d] filePath = %s\n", m_pChipArray[i].chipID, m_pChipArray[i].gbvFilePath );
	}

	// メッシュデータ読み込み
	for( unsigned int i = 1; i < m_ChipNum; i++ )
	{
		if( !load_GBV_file( m_pChipArray[i].gbvFilePath, &(m_pChipArray[i].mesh)) )
		{
			printf("Mapchip Mesh読み込みエラー %s がありません\n",m_pChipArray[i].gbvFilePath );
		} else {
			printf( "load %s\n", m_pChipArray[i].gbvFilePath );
		}
		
	}
	fclose(fp);
	return true;
}
*/