#include "questions.h"

const int scrSpeed = 3;
const int XPos = 300;
const int YPos = 300;


Quest26Seq::Quest26Seq()
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

	// カメラ位置セット
	m_camX = 0;
	m_camY = 0;

	m_camVx = 0;
	m_camVy = scrSpeed;

	mbHit = false;
}


Quest26Seq::~Quest26Seq()
{
	//マップチップ画像解放処理
	for (unsigned int i = 0; i < mMapChipHandleArrayIndexMax; i++)
	{
		DeleteGraph(mMapChipHandleArray[i]);
	}
	delete[] mMapChipHandleArray;

	//マップデータ解放
	delete[] mMapData;
	mMapData = NULL;
}
Sequence* Quest26Seq::move()
{
	int wLeft, wRight;
	int wTop, wBottom;

	// スクリーンの四隅がワールド座標でどの位置にあるかを算出
	screenPos2WorldPos(0, 0, &wLeft, &wTop);
	screenPos2WorldPos(GAMEINSTANCE.getScreenWidth(),
		GAMEINSTANCE.getScreenHeight(),
		&wRight, &wBottom);

	// ワールド座標の限界点（これ以上マップデータない座標）算出
	int minWorldX, maxWorldX;
	int minWorldY, maxWorldY;

	minWorldX = 0;
	minWorldY = 0;
	maxWorldX = m_mapChipSizeX * m_mapWidth;
	maxWorldY = m_mapChipSizeY * m_mapHeight;

	//速度更新

	//マップの右に突き抜けそう
	if (m_camX > maxWorldX - GAMEINSTANCE.getScreenWidth())
	{
		m_camX = maxWorldX - GAMEINSTANCE.getScreenWidth();
		m_camVx = 0;
		m_camVy = -scrSpeed;
	}

	//マップの左に突き抜けそう
	if (m_camX < minWorldX)
	{
		m_camX = minWorldX;
		m_camVx = 0;
		m_camVy = scrSpeed;
	}

	//マップの上に突き抜けそう
	if (m_camY < minWorldY)
	{
		m_camY = minWorldY;
		m_camVy = 0;
		m_camVx = -scrSpeed;
	}

	//マップの下に突き抜けそう
	if (m_camY > maxWorldX - GAMEINSTANCE.getScreenHeight())
	{
		m_camY = maxWorldX - GAMEINSTANCE.getScreenHeight();
		m_camVy = 0;
		m_camVx = scrSpeed;
	}
	//カメラのワールド位置を変更
	m_camX += m_camVx;
	m_camY += m_camVy;

    // 座標よりマップの添え字番号を算出する方法
	// スクリーン座標（固定）よりワールド座標算出
	int worldposX, worldposY;
	screenPos2WorldPos(XPos, YPos, &worldposX, &worldposY);

	// ワールド座標よりマップ添え字を算出する
	m_mapIndexX = worldposX / m_mapChipSizeX;
	m_mapIndexY = worldposY / m_mapChipSizeY;

	// ワールド座標より当たっているかのチェック
	mbHit = isMapHit(worldposX, worldposY);

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest27Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest26Seq::draw()
{
	char buf[256];
	ClearDrawScreen();

	mapDraw();
	gridDraw();

	//マップ添え字番号調べたい座標位置表示
	DrawCircle(XPos, YPos, 2, 0xff0000);

	sprintf(buf, "MAPINDEX (%3d,%3d)", m_mapIndexX, m_mapIndexY);
	GAMEINSTANCE.systemText.textDraw(XPos, YPos - 32, buf);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #25-26-27.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

	//あたり表示
	if (mbHit)
	{
		sprintf(buf, "HIT!");
		GAMEINSTANCE.systemText.textDraw(XPos + 100, YPos + 32, buf);
	}

}

// マップの描画ルーチン
void Quest26Seq::mapDraw()
{
	unsigned int i, j;

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//マップチップ並べる(カメラ座標分引く）
	//※スクロール範囲外までこのプログラムでは描画しています。
	// 画面内だけ描画するにはどうしたらいいか考えましょう〜
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

void Quest26Seq::gridDraw()
{
	// スクリーン座標
	int x , y;
	int screenMaxX, screenMaxY;
	screenMaxX = GAMEINSTANCE.getScreenWidth();
	screenMaxY = GAMEINSTANCE.getScreenHeight();

	// スクリーン左上座標がグリッドから何ピクセルずれてるか算出
	int offsetX, offsetY;
	screenPos2WorldPos(0, 0, &offsetX, &offsetY);

	offsetX %= m_mapChipSizeX;
	offsetY %= m_mapChipSizeY;

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
		screenPos2WorldPos(x, 0, &indexX, &indexY);
		sprintf(buf, "%3d", indexX / m_mapChipSizeX );
		GAMEINSTANCE.systemText.textDraw(x, 0, buf);

		x += m_mapChipSizeX;
	}

	//横グリッド
	y =  -offsetY;
	while (y < screenMaxY)
	{
		DrawLine(0, y, screenMaxX, y, color);

		// インデックス値算出
		screenPos2WorldPos(0, y, &indexX, &indexY);
		sprintf(buf, "%3d", indexY / m_mapChipSizeY);
		GAMEINSTANCE.systemText.textDraw(0, y, buf);

		y += m_mapChipSizeY;
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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
void Quest26Seq::readDataLine(char* buf, size_t bufSize, FILE *p)
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
bool Quest26Seq::readHeader(const char* mapFilename)
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
bool Quest26Seq::readMapdata(const char* mapFileName)
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
void Quest26Seq::screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y)
{
	*worldPos_X = scrPos_x + m_camX;
	*worldPos_Y = scrPos_y + m_camY;
}

// ワールド座標系からスクリーン座標系への座標変換
void Quest26Seq::worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y)
{
	*scrPos_X = worldPos_x - m_camX;
	*scrPos_Y = worldPos_y - m_camY;
}

bool Quest26Seq::isMapHit(unsigned int worldX, unsigned int worldY)
{
	// ワールド座標よりマップ添え字を算出する
	unsigned int m_mapIndexX = worldX / m_mapChipSizeX;
	unsigned int m_mapIndexY = worldY / m_mapChipSizeY;

	//そもそもマップの範囲内か？
	if ( m_mapIndexX >= m_mapWidth ||
		 m_mapIndexY >= m_mapHeight )

	{
		return false;
	}

	// 調査点はマップの中なので、indexが当たりのチップか調べる
	int mapId;
	mapId = mMapData[m_mapIndexX + m_mapIndexY * m_mapWidth];

	if (!mapId)
		return false;

	return true;
}