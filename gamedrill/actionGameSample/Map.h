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
	bool           readMapdata(const char* mapFileName, const char* mapchipGraphFileName);  	// マップ実データ読み込み
	void           mapDraw(Camera* p_Camera);	                            // マップ描画
	void           gridDraw(Camera* p_Camera);	                            // グリッド描画
	bool           isMapHit(unsigned int worldX, unsigned int worldY);        // 調査点はマップと衝突したか？
	int            getMapWidth() { return mMapChipWidthNum * mMapChipGraphSizeX; }
	int            getMapHeight() { return mMapChipHeightNum * mMapChipGraphSizeY; }
	int            getCollisionMapIndex_X(int posx);
	int            getCollisionMapIndex_Y(int posy);
	unsigned char  getCollisionMapIdFromIndex(int xIndex, int yIndex);
	int            getMapChipSizeX() { return mMapChipGraphSizeX; }
	int            getMapChipSizeY() { return mMapChipGraphSizeY; }

private:
	unsigned int   mMapChipWidthNum;                       // マップの幅(横ブロック数）
	unsigned int   mMapChipHeightNum;                      // マップ高さ（縦ブロック数）
	unsigned int   mMapChipGraphSizeX;                     // マップチップの横サイズ
	unsigned int   mMapChipGraphSizeY;                     // マップチップの縦サイズ
	unsigned char *mMapData;                               // マップデータ配列
	int           *mMapChipHandleArray;                    // マップチップ画像ハンドル格納配列
	unsigned int   mMapChipHandleArrayIndexMax;            // 画像ハンドル配列の添え字最大値

	bool           mbHit;                                  // ヒットしたか？

	void           readDataLine(char* buf, size_t bufSize, FILE *p);	// 1行分をコメント(行頭//がある行)を飛ばしながら読む
	bool           readHeader(const char* mapFilename);	    // マップファイルヘッダ情報を読む マップの幅高さ、マップチップ大きさ等
};

#endif