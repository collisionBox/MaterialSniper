#include "questions.h"

Quest24Seq::Quest24Seq()
{
	const char *mapfilename = "image/dungeon.csv";
	const char *mapImgfilename = "image/dungeonSheet.png";

	// マップのファイルヘッダ部分を読む
	if (!readHeader(mapfilename))
	{
		printf("mapChipData read failed : %s", mapfilename);
	}
	//ファイルヘッダ情報よりマップデータ確保
	mMapData = new unsigned char[m_mapWidth * m_mapHeight];

	//ファイルからマップデータを取り込む
	if (!readMapdata(mapfilename))
	{
		printf("mapData is broken : %s ", mapfilename);
	}

	//画像サイズをゲットするためにマップ画像を一度空読み
	int tmpID;
	tmpID = LoadGraph(mapImgfilename);
	int width, height;

	GetGraphSize(tmpID, &width, &height);

	DeleteGraph(tmpID);

	//画像が縦横いくつずつ並んでいるかをゲット
	width /= m_mapChipSizeX;
	height /= m_mapChipSizeY;

	mMapChipHandleArrayIndexMax = width * height;

	//マップチップハンドル配列を確保
	mMapChipHandleArray = new int[mMapChipHandleArrayIndexMax];

	//画像読み込み
	LoadDivGraph("image/dungeonSheet.png", mMapChipHandleArrayIndexMax, width, height, 64, 64, (int *)mMapChipHandleArray);

}


Quest24Seq::~Quest24Seq()
{
	//マップチップ画像解放処理
	for(unsigned int i = 0; i < mMapChipHandleArrayIndexMax; i++)
	{
		DeleteGraph(mMapChipHandleArray[i]);
	}
	delete[] mMapChipHandleArray;

	//マップデータ解放
	delete[] mMapData;
	mMapData = NULL;
}
Sequence* Quest24Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest26Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest24Seq::draw()
{
	ClearDrawScreen();

	mapDraw();

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #24.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}

// マップの描画ルーチン
void Quest24Seq::mapDraw()
{
	unsigned int i, j;

	//マップチップ並べる
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
// 1行分をコメント(行頭//がある行)を飛ばしながら読む
// 引数：
// buf (in/out)  現在読んでいる1行分取り込んだデータへの先頭アドレス
// bufSize (int) bufのデータサイズ（バイト数）
// p             ファイルポインタ
// 戻り値：なし
// Desc   :  現在読みこんでいるファイルから1行分をbufの文字列に格納する
//           読みこんだ行がコメント// または \nなら次の行を読み、bufに格納する
////////////////////////////////////////////////////////////////////////////
void Quest24Seq::readDataLine(char* buf, size_t bufSize, FILE *p)
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
bool Quest24Seq::readHeader(const char* mapFilename)
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
	m_mapWidth = atoi(token);     // マップX方向のチップ個数

	token = strtok(NULL, ",");
	m_mapHeight = atoi(token);    // マップY方向のチップ個数

	token = strtok(NULL, ",");
	m_mapChipSizeX = atoi(token); // チップ１個の大きさX

	token = strtok(NULL, ",");
	m_mapChipSizeY = atoi(token); //チップ１個の大きさY

								  //ファイルクローズ
	fclose(fp);

	return true;
}

///////////////////////////////////////////////////////////////////////////
// CSVファイルより、マップデータ本体を読み込む。
// 
///////////////////////////////////////////////////////////////////////////
bool Quest24Seq::readMapdata(const char* mapFileName)
{
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

    // マップ本体読み込み
	x = y = 0;
	while (y < m_mapHeight)
	{
		// 行読み込み
		readDataLine(tmp, 256, fp);
		if (tmp == NULL)
			return false;

		//第一トークンを取得
		token = strtok(tmp, ",");

		//１行をカンマ区切りでマップ配列にコピーする
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

// スクリーン座標系からワールド座標系への座標変換
void Quest24Seq::screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y)
{
	*worldPos_X = scrPos_x + m_camX;
	*worldPos_Y = scrPos_y + m_camY;
}

// ワールド座標系からスクリーン座標系への座標変換
void Quest24Seq::worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y)
{
	*scrPos_X = worldPos_x - m_camX;
	*scrPos_Y = worldPos_y - m_camY;
}
