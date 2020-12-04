#include "Bouton.h"
#include "FontManager.h"
#include "SpriteManager.h"

Button_Text::Button_Text(string _name, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
{
	Name = _name;

	Texte = Text(_name, getFont(_nameFont), _sizeTexte);
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(Vector2f(_Position));
	Texte.setFillColor(_color);

	Shape = RectangleShape(_sizeShape);
	Shape.setOrigin(getMidle(Shape));
	Shape.setPosition(_Position);
	Shape.setFillColor(Color::Transparent);
	Shape.setOutlineThickness(_outlinesize);
	Shape.setOutlineColor(_color);
}

Button_Sprite::Button_Sprite(string _name, float _rotate, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
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

Box::Box(string _max, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
{
	Texte = Text(_max, getFont(_nameFont), _sizeTexte);
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(Vector2f(_Position));
	Texte.setFillColor(_color);

	Shape = RectangleShape(_sizeShape);
	Shape.setOrigin(getMidle(Shape));
	Shape.setPosition(_Position);
	Shape.setFillColor(_color);
	Shape.setOutlineThickness(_outlinesize);
	Shape.setOutlineColor(Color::Transparent);
}

void Box::Display(string _currentstat)
{
	Texte.setString(_currentstat + "/" + Texte.getString());
	App.Get_Window().draw(Shape);
	App.Get_Window().draw(Texte);
}

void Button_Text::Set_Color(Color _color)
{
	Texte.setFillColor(_color);
	Shape.setOutlineColor(_color);
}

void Button_Text::Display()
{
	App.Get_Window().draw(Shape);
	App.Get_Window().draw(Texte);
}

void Button_Sprite::Display()
{

	Shape.setOutlineColor(color);
	getSprite(Name).setColor(color);
	App.Get_Window().draw(Shape);
	getSprite(Name).setOrigin(getMidle(getSprite(Name)));
	getSprite(Name).setPosition(Vector2f(Shape.getPosition().x, Shape.getPosition().y));
	getSprite(Name).setRotation(Rotate);
	App.Get_Window().draw(getSprite(Name));

}