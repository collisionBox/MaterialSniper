#include "Sequence.h"

#ifndef __Q26_H__
#define __Q26_H__

class Sequence; // 前置宣言 

class Quest26Seq : public Sequence
{
public:
	Quest26Seq();
	~Quest26Seq();

	Sequence*      move();
	void           draw();

private:

	// マップ関連									  //
	unsigned int   m_mapWidth;            // マップの幅(横ブロック数）
	unsigned int   m_mapHeight;           // マップ高さ（縦ブロック数）
	unsigned int   m_mapChipSizeX;        // マップチップの横サイズ
	unsigned int   m_mapChipSizeY;        // マップチップの縦サイズ
	unsigned char *mMapData;             // マップデータ配列
	int           *mMapChipHandleArray;
	unsigned int   mMapChipHandleArrayIndexMax;

	int            m_mapIndexX;
	int            m_mapIndexY;

	bool           mbHit;

	// スクロール関連
	int            m_camX;               // カメラのワールド座標系位置　x, y 
	int            m_camY;

	// スクロール方向管理
	int            m_camVx;
	int            m_camVy;

	// 1行分をコメント(行頭//がある行)を飛ばしながら読む
	void           readDataLine(char* buf, size_t bufSize, FILE *p);

	// マップファイルヘッダ情報を読む マップの幅高さ、マップチップ大きさ等
	bool           readHeader(const char* mapFilename);

	// マップ実データ読み込み
	bool           readMapdata(const char* mapFileName);

	// マップ描画
	void           mapDraw();

	// グリッド描画
	void           gridDraw();

	// スクロール関連

	// スクリーン座標系からワールド座標系への座標変換
	void           screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y);

	// ワールド座標系からスクリーン座標系への座標変換
	void           worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y);

	bool           isMapHit(unsigned int worldX, unsigned int worldY);
};


#endif
