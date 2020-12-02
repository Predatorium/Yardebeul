#include "Bouton.h"
#include "FontManager.h"
#include "SpriteManager.h"

Bouton::Bouton(string _name, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
{
	Name = _name;

	Texte = Text(_name, getFont(_nameFont), _sizeTexte);
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(Vector2f(_Position));
	Texte.setFillColor(_color);

	RShape = RectangleShape(_sizeShape);
	RShape.setOrigin(getMidle(RShape));
	RShape.setPosition(_Position);
	RShape.setFillColor(Color::Transparent);
	RShape.setOutlineThickness(_outlinesize);
	RShape.setOutlineColor(_color);
}

RShape::RShape(string _name, float _rotate, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
{
	Name = _name;
	Rotate = _rotate;
	color = _color;

	Shape = RectangleShape(_sizeShape);
	Shape.setOrigin(getMidle(Shape));
	Shape.setPosition(_Position);
	Shape.setFillColor(Color::Transparent);
	Shape.setOutlineThickness(_outlinesize);
	Shape.setOutlineColor(color);
	SetSmooth(Name);
}

void Bouton::Set_Color(Color _color)
{
	Texte.setFillColor(_color);
	RShape.setOutlineColor(_color);
}

void Bouton::Display()
{
	App.Get_Window().draw(RShape);
	App.Get_Window().draw(Texte);
}

void RShape::Display()
{

	Shape.setOutlineColor(color);
	getSprite(Name).setColor(color);
	App.Get_Window().draw(Shape);
	getSprite(Name).setOrigin(getMidle(getSprite(Name)));
	getSprite(Name).setPosition(Vector2f(Shape.getPosition().x, Shape.getPosition().y));
	getSprite(Name).setRotation(Rotate);
	App.Get_Window().draw(getSprite(Name));

}