#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include "game.h"
#include "mapManager.h"
#include "player.h"
#include "math2D.h"

class Camera;

// シーケンスベースクラス
class Sequence
{
public:
	              Sequence(){};
	virtual      ~Sequence(){};

	virtual       Sequence*  move() = 0;
	virtual void  draw() = 0;
};


#endif