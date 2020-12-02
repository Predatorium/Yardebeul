#pragma once
#include "Tools.h"

class Animator
{
private :
	IntRect Rect;
	int NbFrame;
	int Frame;
	float Frame_Timer;
	float Timer;

public :
	Animator() = default;
	Animator(IntRect _rect, int _nbframe, float _frametimer);
	~Animator() = default;

	void Animation(Sprite& _sprite);
};

