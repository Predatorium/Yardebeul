#pragma once
#include "Tools.h"
#include "Character.h"

class My_Shape : public RectangleShape, public Character
{
private :

public :
	My_Shape() = default;
	My_Shape(Vector2f _size, string _string, Font _font, Color _text, Color _outline);
	~My_Shape() = default;

	void Display();
};