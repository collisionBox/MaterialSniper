#pragma once

class Sean
{
public:
	Sean() {};
	virtual ~Sean() {};

	virtual Sean* Update() = 0;
	virtual void Draw() = 0;
};