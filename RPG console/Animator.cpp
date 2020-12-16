#include "Animator.h"

Animator::Animator(IntRect _rect, int _nbframe, float _frametimer, const int _space)
{
	Rect = _rect;
	NbFrame = _nbframe;
	Frame_Timer = _frametimer;
	Space = _space;
	Frame = 0;
	Timer = 0;
}

void Animator::Animation(Sprite& _sprite)
{
	Timer += MainTime.GetTimeDeltaF();

	if (Timer > Frame_Timer)
	{
		Frame++;

		if (Frame >= NbFrame)
			Frame = 0;

		Timer = 0;
	}

	_sprite.setTextureRect(IntRect(Rect.left + (Frame * Rect.width) + (Frame * Space), Rect.top, Rect.width, Rect.height));
}