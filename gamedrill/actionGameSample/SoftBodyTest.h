#ifndef __SOFTBODY_TEST_H__
#define __SOCTBODY_TEST_H__

#include "questions.h"
#include "map.h"
#include "camera.h"
#include "LinkedParticle.h"

class SoftBodyTestSeq : public Sequence
{
public:
	SoftBodyTestSeq();
	~SoftBodyTestSeq();

	Sequence* move();
	void      draw();

private:
	int       mMode               ;
	int       mMaxParticleNum     ;

	Camera   *pCam                 ;
	Map      *pMap                 ;
	LinkedParticle *pParticle      ;

	void resetMassPoint()          ;
};


#endif