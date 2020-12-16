#pragma once
#include "Tools.h"

class Animator
{
private :
	IntRect Rect;
	int NbFrame;
	int Frame;
	int Space;
	float Frame_Timer;
	float Timer;

public :
	Animator() = default;
	Animator(IntRect _rect, int _nbframe, float _frametimer, const int _space = 1);
	~Animator() = default;

	void Animation(Sprite& _sprite);
};

