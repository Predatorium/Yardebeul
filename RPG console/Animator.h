#pragma once
#include "Tools.h"

using namespace sf;

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

	inline bool operator == (const Animator& a) const { return Rect == a.Rect; };
	inline bool operator != (const Animator& a) const { return !operator==(a); };

	void Animation(Sprite& _sprite);
};