#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

#include "dxlib.h"
#include "Game.h"

class Player;     // �O�u�錾
class Camera;


class MapManager
{
public:
					MapManager(){ mMapData = NULL; m_ImgHandle = 0; }
				   ~MapManager();
			

			 bool   LoadMapData(const char* imageFileName, const char* mapFileName);  //ToDo
			 void   move(); // �}�b�v�̈ړ�
			 void	draw(); // �}�b�v�̕`��
					// ���W���瓖���蔻��p�}�b�vID��Ԃ��B���̃u���b�N�̍�����W��Ԃ�
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
	unsigned char **mMapData;                          // �}�b�v�z��[Layer][xy]
	unsigned char   m_layerMaxnum;                        // �ő僌�C���[����
	unsigned int    m_mapWidth, m_mapHeight;              // �}�b�v�S�̂̕��E�����i�`�b�v���j
	unsigned int    m_mapChipSizeX, m_mapChipSizeY;       // �}�b�v�`�b�v1���̕��E����
	unsigned int    m_mapChipXnum , m_mapChipYnum;        // �}�b�v�`�b�v�摜�̉��������E�c������
	
	unsigned int    m_X,m_Y;                              // �}�b�v�̌��݃X�N���[���ʒu
	int             m_ImgHandle;						  // �}�b�v�`�b�v�̃C���[�W�n���h��

	Camera*         m_pCamera;

	typedef struct  s_chipCoord                           // �}�b�v�`�b�v�̍��W�\����
	{
		unsigned int x, y;
	}s_chipCoord;

	 s_chipCoord   *m_chipType;                           // �}�b�v�`�b�v�̃^�C�v�ԍ����}�b�v�`�b�v�摜��x,y�؂�o���ʒu�ϊ��p�e�[�u��

			void	readDataLine(char* buf,size_t bufSize, FILE *p);
			bool	setImage( const char* filename, unsigned int chipSizeX, unsigned int chipSizeY ); //�}�b�v�`�b�v�摜��`
			bool    readHeader( const char* mapFilename );
			bool    readMapdata( const char* mapFileName );
			void	Init( unsigned int mapWidth, unsigned int mapHeight, unsigned int layernum);  // �}�b�v�S�̂̕��E�����`�b�v����`
};


#endif