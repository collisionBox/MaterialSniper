#include "Game.h"
#include "input.h"
Input::Input()
{
	nowKey  = 0;
	prevKey = 1;

	for( int i = 0; i < 256; i++ )
	{
		key[i] = 0;
		keyState[nowKey][i]  = KEY_STATE_OFF;
		keyState[prevKey][i] = KEY_STATE_OFF;
	}
}

void Input::update()
{
	// 現在のキーと一つ前のフレームのキー状態を入れ替える
	nowKey  ^= 1;
	prevKey  = nowKey ^ 1;

	// キー状態取得
	GetHitKeyStateAll( keyState[nowKey] );

	//
	for( int i = 0; i < 256; i++ )
	{
		char nowInput  = keyState[nowKey][i];
		char prevInput = keyState[prevKey][i];

		if( nowInput )
		{
			//現在押されている

			//前のフレームも押されていた？
			if( prevInput )
			{
				key[i] = KEY_STATE_PRESSED; // 押されっぱなし
			} else {
				key[i] = KEY_STATE_PUSHDOWN;// 今押された
			}

		}
		else
		{
			// 現在キーは押されていない
			
			// 前のフレームで押されていた？
			if( prevInput )
			{
				key[i] = KEY_STATE_PULLUP;
			} else {
				key[i] = KEY_STATE_OFF;
			}
		}
	}

#ifdef DEBUG_CONSOLE
	//printf("[%d]\n",key[KEY_INPUT_Z] );
#endif

}