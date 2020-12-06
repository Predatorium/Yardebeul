#include "Button.h"
#include "FontManager.h"
#include "SpriteManager.h"

Button_Text::Button_Text(string _name, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
{
	Name = _name;

	Texte = Text(_name, getFont(_nameFont), _sizeTexte);
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(Vector2f(_Position));
	Texte.setFillColor(_color);

	shape = RectangleShape(Vector2f(_sizeShape));
	shape.setOrigin(getMidle(shape));
	shape.setPosition(Vector2f(_Position));
	shape.setFillColor(Color::Transparent);
	shape.setOutlineThickness(_outlinesize);
	shape.setOutlineColor(_color);
}

Button_Sprite::Button_Sprite(string _name, float _rotate, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
{
	Name = _name;
	Rotate = _rotate;
	color = _color;

	shape = RectangleShape(_sizeShape);
	shape.setOrigin(getMidle(shape));
	shape.setPosition(_Position);
	shape.setFillColor(Color::Transparent);
	shape.setOutlineThickness(_outlinesize);
	shape.setOutlineColor(color);
	SetSmooth(Name);
}

Box::Box(string _max, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
{
	Texte = Text("", getFont(_nameFont), _sizeTexte);
	Position = _Position;
	Texte.setFillColor(Color::White);
	Max = stoi(_max);

	Size = _sizeShape;

	Outline = RectangleShape(Size);
	Outline.setOrigin(getMidle(Outline));
	Outline.setPosition(Position);
	Outline.setFillColor(Color::Transparent);
	Outline.setOutlineThickness(_outlinesize);
	Outline.setOutlineColor(Color::White);

	Rod = RectangleShape(Size);
	Rod.setOrigin(getMidle(Rod));
	Rod.setPosition(Position);
	Rod.setFillColor(_color);
	Rod.setOutlineThickness(_outlinesize);
	Rod.setOutlineColor(Color::Transparent);
}

void Box::Display(string _currentstat)
{
	Texte.setString(_currentstat + to_string(Max));
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(Position);
	App.Get_Window().draw(Outline);

	Rod.setSize(Vector2f((Outline.getSize().x / Max) * stoi(_currentstat), Size.y));

	App.Get_Window().draw(Rod);
	App.Get_Window().draw(Texte);
}

void Button_Text::Set_Color(Color _color)
{
	Texte.setFillColor(_color);
	shape.setOutlineColor(_color);
}

void Button_Text::Display()
{
	App.Get_Window().draw(shape);
	App.Get_Window().draw(Texte);
}

void Button_Sprite::Display()
{

	shape.setOutlineColor(color);
	getSprite(Name).setColor(color);
	App.Get_Window().draw(shape);
	getSprite(Name).setOrigin(getMidle(getSprite(Name)));
	getSprite(Name).setPosition(Vector2f(shape.getPosition().x, shape.getPosition().y));
	getSprite(Name).setRotation(Rotate);
	App.Get_Window().draw(getSprite(Name));

}