#include "sequence.h"

#include "camera.h"
#include "player.h"
#include "mapManager.h"

bool G_pause;


GameSeq::GameSeq()
{
	// ゲーム中オブジェクトの設定
	m_pMap    = new MapManager;
	m_pPlayer = new Player;
	m_pCamera = new Camera;

	// マップ関連
	m_pMap->LoadMapData( "image/mapchip.png", "data/Test2_type2.csv" );
	m_pMap->setCamera( m_pCamera );

	// プレーヤ関連
	m_pPlayer->init( "image/chara3.png","image/player.png", 40, 56 );
	m_pPlayer->setCollision( (40 - 64) / 2, -6, 40, 56 );
	m_pPlayer->setGameStartPos( 522, 1900 );
	m_pPlayer->setCamera( m_pCamera );
	m_pPlayer->setMap( m_pMap );

	// カメラ関連
	int quatscreen_x = GAMEINSTANCE.getScreenWidth()  / 4;
	int quatscreen_y = GAMEINSTANCE.getScreenHeight() / 4;

	m_pCamera->SetPlayerPointer( m_pPlayer );
	m_pCamera->setMapPointer( m_pMap );
	m_pCamera->Init( 0, 0, 
		             quatscreen_x, quatscreen_y, 
					 quatscreen_x * 2, quatscreen_y * 2 );
}

GameSeq::~GameSeq()
{
	delete m_pMap;
	delete m_pPlayer;
	delete m_pCamera;
}

Sequence* GameSeq::move()
{
	if( !G_pause )
	{
		m_pPlayer->move();
		m_pCamera->move();
	}

	//pause キー
	if( INPUT_INSTANCE.getInput( KEY_INPUT_SPACE ) == KEY_STATE_PUSHDOWN )
	{
		G_pause ^= 1;
	}

	return this;
}

void GameSeq::draw()
{
	ClearDrawScreen();

	m_pMap->draw();
	m_pPlayer->draw();

}
