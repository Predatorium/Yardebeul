#include "My_Shape.h"

My_Shape::My_Shape(Vector2f _size, string _string, Font _font, Color _text, Color _outline)
	: RectangleShape(_size)
{
	this->RectangleShape::setOutlineThickness(2);
	this->RectangleShape::setOutlineColor(_outline);
}

void My_Shape::Display()
{
	App.Get_Window().draw(*this);
}