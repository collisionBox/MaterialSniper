#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

#include "dxlib.h"
#include "Game.h"

class Player;     // 前置宣言
class Camera;


class MapManager
{
public:
					MapManager(){ mMapData = NULL; m_ImgHandle = 0; }
				   ~MapManager();
			

			 bool   LoadMapData(const char* imageFileName, const char* mapFileName);  //ToDo
			 void   move(); // マップの移動
			 void	draw(); // マップの描画
					// 座標から当たり判定用マップIDを返す。そのブロックの左上座標を返す
	unsigned char	getCollisionMapId( int posx, int posy, int* out_block_x, int *out_block_y );
	unsigned char   getCollisionMapIdFromIndex( int xIndex, int yIndex );
	         void 	getCollisionRectFromIndex( int xIndex, int yIndex, rectangle* outRect );
	          int   getCollisionMapIndex_X( int posx );
			  int   getCollisionMapIndex_Y( int posy );
	
	          int   getMapWidth() { return m_mapWidth  * m_mapChipSizeX ; }
			  int   getMapHeight(){ return m_mapHeight * m_mapChipSizeY ; }
	unsigned char   getMapChipSize(){ return m_mapChipSizeX; }
			void    setCamera( Camera* p ) { m_pCamera = p ; }

private:
	unsigned char **mMapData;                          // マップ配列[Layer][xy]
	unsigned char   m_layerMaxnum;                        // 最大レイヤー枚数
	unsigned int    m_mapWidth, m_mapHeight;              // マップ全体の幅・高さ（チップ個数）
	unsigned int    m_mapChipSizeX, m_mapChipSizeY;       // マップチップ1つ分の幅・高さ
	unsigned int    m_mapChipXnum , m_mapChipYnum;        // マップチップ画像の横方向個数・縦方向個数
	
	unsigned int    m_X,m_Y;                              // マップの現在スクロール位置
	int             m_ImgHandle;						  // マップチップのイメージハンドル

	Camera*         m_pCamera;

	typedef struct  s_chipCoord                           // マップチップの座標構造体
	{
		unsigned int x, y;
	}s_chipCoord;

	 s_chipCoord   *m_chipType;                           // マップチップのタイプ番号→マップチップ画像のx,y切り出し位置変換用テーブル

			void	readDataLine(char* buf,size_t bufSize, FILE *p);
			bool	setImage( const char* filename, unsigned int chipSizeX, unsigned int chipSizeY ); //マップチップ画像定義
			bool    readHeader( const char* mapFilename );
			bool    readMapdata( const char* mapFileName );
			void	Init( unsigned int mapWidth, unsigned int mapHeight, unsigned int layernum);  // マップ全体の幅・高さチップ個数定義
};


#endif