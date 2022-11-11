#ifndef __Q28_H__
#define __Q28_H__

#include "questions.h"
#include "map.h"
#include "camera.h"
#include "PlayerTopView.h"

class Quest28Seq : public Sequence
{
public:
	Quest28Seq();
	~Quest28Seq();

	Sequence* move();
	void      draw();

private:
	Camera        *pCam;
	Map           *pMap;
	PlayerTopview *pPlayer;
	bool          showDebugMap;
};


#endif