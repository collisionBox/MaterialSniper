#ifndef __Q30_H__
#define __Q30_H__

#include "questions.h"
#include "map.h"
#include "camera.h"
#include "player.h"
#include "Particle.h"

class Quest30Seq : public Sequence
{
public:
	Quest30Seq();
	~Quest30Seq();

	Sequence* move();
	void      draw();

private:
	Camera   *pCam;
	Map      *pMap;
	Player   *pPlayer;

	Particle *mPerticleArray;
	int       mPerticleMax;
};


#endif