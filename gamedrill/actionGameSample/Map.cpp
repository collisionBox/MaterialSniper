#include "Map.h"

Map::Map()
{
	// 初期化
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
		//マップチップ画像解放処理
		for (unsigned int i = 0; i < mMapChipHandleArrayIndexMax; i++)
		{
			DeleteGraph(mMapChipHandleArray[i]);
		}
		delete[] mMapChipHandleArray;
	}
}

//マップデータの読み込み
bool Map::readMapdata(const char * mapFileName, const char* mapchipGraphFileName)
{
	// マップのファイルヘッダ部分を読む
	if (!readHeader(mapFileName))
	{
		printf("mapChipData read failed : %s", mapFileName);
	}
	//ファイルヘッダ情報よりマップデータ確保
	mMapData = new unsigned char[mMapChipWidthNum * mMapChipHeightNum];

	// マップファイルCSV読み込み
	FILE *fp;
	fp = fopen(mapFileName, "rt");
	if (fp == NULL)
	{
		return false;
	}

	// テンポラリ
	char buf[1024], tmp[256];

	unsigned int x, y, layer = 0;
	char *token;

	readDataLine(buf, 1024, fp); //ヘッダ部分空読

	x = y = 0;
	while (y < mMapChipHeightNum)
	{
		// 行読み込み
		readDataLine(tmp, 256, fp);
		if (tmp == NULL)
			return false;

		//第一トークンを取得
		token = strtok(tmp, ",");

		//１行をカンマ区切りでマップ配列にコピーする
		while (token != NULL && x < mMapChipWidthNum)
		{
			mMapData[y * mMapChipWidthNum + x] = atoi(token);

			token = strtok(NULL, ",");
			x++;
		}
		x = 0;
		y++;
	}

	//画像サイズをゲットするためにマップ画像を一度空読み
	int tmpID;
	tmpID = LoadGraph((TCHAR *)mapchipGraphFileName);
	int width, height;

	GetGraphSize(tmpID, &width, &height);

	DeleteGraph(tmpID);

	//画像が縦横いくつずつ並んでいるかを計算 = 画像（幅）dot /  1ブロック長さdot
	width  /= mMapChipGraphSizeX;
	height /= mMapChipGraphSizeY;

	mMapChipHandleArrayIndexMax = width * height;

	//マップチップハンドル配列を確保
	mMapChipHandleArray = new int[mMapChipHandleArrayIndexMax];

	//画像読み込み
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

	//マップチップ並べる(カメラ座標分引く）
	//※スクロール範囲外までこのプログラムでは描画しています。
	// 画面内だけ描画するにはどうしたらいいか考えましょう～

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
	// スクリーン座標
	int x, y;
	int screenMaxX, screenMaxY;
	screenMaxX = GAMEINSTANCE.getScreenWidth();
	screenMaxY = GAMEINSTANCE.getScreenHeight();

	// スクリーン左上座標がグリッドから何ピクセルずれてるか算出
	int offsetX, offsetY;
	p_Camera->screenPos2WorldPos(0, 0, &offsetX, &offsetY);

	offsetX %= mMapChipGraphSizeX;
	offsetY %= mMapChipGraphSizeY;

	//グリッドラインカラー
	int color = 0xffff0000;

	// 縦横インデックス値
	int indexX, indexY;

	// インデクス値表示用文字列バッファ
	char buf[10];

	// 半透明ON
	SetDrawBlendMode(DX_BLENDMODE_ADD, 100);

	// 縦グリッド描画
	x = -offsetX;
	while (x < screenMaxX)
	{
		//グリッド描画
		DrawLine(x, 0, x, screenMaxY, color);

		// インデックス値算出
		p_Camera->screenPos2WorldPos(x, 0, &indexX, &indexY);
		sprintf(buf, "%3d", indexX / mMapChipGraphSizeX);
		GAMEINSTANCE.systemText.textDraw(x, 0, buf);

		x += mMapChipGraphSizeX;
	}

	//横グリッド
	y = -offsetY;
	while (y < screenMaxY)
	{
		DrawLine(0, y, screenMaxX, y, color);

		// インデックス値算出
		p_Camera->screenPos2WorldPos(0, y, &indexX, &indexY);
		sprintf(buf, "%3d", indexY / mMapChipGraphSizeY);
		GAMEINSTANCE.systemText.textDraw(0, y, buf);

		y += mMapChipGraphSizeY;
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

bool Map::isMapHit(unsigned int worldX, unsigned int worldY)
{
	// ワールド座標よりマップ添え字を算出する
	unsigned int m_mapIndexX = worldX / mMapChipGraphSizeX;
	unsigned int m_mapIndexY = worldY / mMapChipGraphSizeY;

	//そもそもマップの範囲内か？
	if (m_mapIndexX >= mMapChipWidthNum ||
	    m_mapIndexY >= mMapChipHeightNum)

	{
		return false;
	}

	// 調査点はマップの中なので、indexが当たりのチップか調べる
	int mapId;
	mapId = mMapData[m_mapIndexX + m_mapIndexY * mMapChipWidthNum];

	if (!mapId)
		return false;

	return true;
}

//X座標(ワールド)からマップの横方向添え字を返す
int Map::getCollisionMapIndex_X(int worldposx)
{
	// posXがマップの中に入っていない場合は-1を返す
	if (worldposx < 0 || (int)(mMapChipGraphSizeX * mMapChipWidthNum) < worldposx)
	{
		return -1;
	}

	return worldposx / mMapChipGraphSizeX;
}

//Y座標（ワールド）からマップの縦方向添え字を返す
int Map::getCollisionMapIndex_Y(int worldposy)
{
	// posYがマップの中に入っていない場合は-1を返す
	if (worldposy < 0 || (int)(mMapChipGraphSizeY * mMapChipHeightNum) < worldposy)
	{
		return -1;
	}
	return worldposy / mMapChipGraphSizeY;
}

// 縦横の添え字よりマップIDを返す
unsigned char Map::getCollisionMapIdFromIndex(int xIndex, int yIndex)
{

	//マップチップサイズ超えていないか？
	if (xIndex < 0 || xIndex >(int)mMapChipWidthNum || yIndex < 0 || yIndex >(int)mMapChipHeightNum)
	{
		return 0;
	}
	// マップデータよりブロックタイプ返す
	return mMapData[xIndex + yIndex * mMapChipWidthNum];

}



////////////////////////////////////////////////////////////////////////////
// 1行分をコメント(行頭//がある行)を飛ばしながら読む
// 引数：
// buf (in/out)  現在読んでいる1行分取り込んだデータへの先頭アドレス
// bufSize (int) bufのデータサイズ（バイト数）
// p             ファイルポインタ
// 戻り値：なし
// Desc   :  現在読みこんでいるファイルから1行分をbufの文字列に格納する
//           読みこんだ行がコメント// または \nなら次の行を読み、bufに格納する
////////////////////////////////////////////////////////////////////////////
void Map::readDataLine(char * buf, size_t bufSize, FILE * p)
{
	//１行読み込み
	fgets(buf, bufSize, p);

	//コメント行である限り読み飛ばす
	while (buf[0] == '/' || buf[0] == '\n')
	{
		fgets(buf, bufSize, p);
	}
	// コメント行では無い行が取り込めた
	return;
}
////////////////////////////////////////////////////////////////////////////
// マップファイルヘッダ情報を読む マップの幅高さ、マップチップ大きさ等
// 引　数：mapFilename csvファイル名
// 戻り値：読みこみ成功 true / 読み込み失敗 false
// desc  ：csvファイルを読み込み、ヘッダ情報を読み込む。
//         成功時にはマップのブロック縦横個数、1ブロックの幅高さ(pixel)
//         にデータが格納される。読み込み失敗時の値は不定。
////////////////////////////////////////////////////////////////////////////

bool Map::readHeader(const char * mapFilename)
{
	FILE *fp = NULL;
	fp = fopen(mapFilename, "rt");
	if (fp == NULL)
	{
		return false;
	}

	// テンポラリ
	char buf[1024];

	// ブロックサイズ読み込み
	readDataLine(buf, 1024, fp);
	char *token = NULL;

	// マップデータのヘッダ部分読み込み
	token = strtok(buf, ",");
	mMapChipWidthNum = atoi(token);     // マップX方向のチップ個数

	token = strtok(NULL, ",");
	mMapChipHeightNum = atoi(token);    // マップY方向のチップ個数

	token = strtok(NULL, ",");
	mMapChipGraphSizeX = atoi(token); // チップ１個の大きさX

	token = strtok(NULL, ",");
	mMapChipGraphSizeY = atoi(token); //チップ１個の大きさ

	//ファイルクローズ
	fclose(fp);

	return true;
}