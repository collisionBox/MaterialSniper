#ifndef __Q27_H__
#define __Q27_H__

#include "questions.h"
#include "map.h"
#include "camera.h"
#include "player.h"
#include "Particle.h"

class Quest27Seq : public Sequence
{
public:
	Quest27Seq();
	~Quest27Seq();

	Sequence* move();
	void      draw();

private:
	Camera   *pCam;
	Map      *pMap;
	Player   *pPlayer;
	bool      showDebugMap;
};


#endif