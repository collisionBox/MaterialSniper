#include "DxLib.h"

#ifndef __INPUT_H__
#define __INPUT_H__

typedef enum KEY_STATE_ENUM
{
	KEY_STATE_OFF      = 0,
	KEY_STATE_PUSHDOWN    ,
	KEY_STATE_PRESSED     ,
	KEY_STATE_PULLUP
}KEY_STATE_ENUM;

class Input
{
private:
	Input(); // ƒVƒ“ƒOƒ‹ƒgƒ“

	char key[256];
	char keyState[2][256];

	BYTE nowKey,prevKey;

public:
	static Input& InputInstance()
	{
		static Input InputInst;
		return InputInst;
	}

	~Input(){};
	void update();
	char getInput(int keyCode ){ return key[keyCode]; }
};

#define INPUT_INSTANCE Input::InputInstance() 

#endif