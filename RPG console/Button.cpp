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
	: sprite(getTexture(_name))
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
}

Box::Box(int _max, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color)
{
	Texte = Text("", getFont(_nameFont), _sizeTexte);
	Position = _Position;
	Texte.setFillColor(Color::White);
	Max = _max;

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
	if (Max > 0)
		Texte.setString(_currentstat + to_string(Max));
	else
		Texte.setString(_currentstat);
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(Position);
	App.Get_Window().draw(Outline);

	if (Max > 0)
		Rod.setSize(Vector2f((Outline.getSize().x / Max) * stoi(_currentstat), Size.y));
	else
		Rod.setSize(Vector2f((Outline.getSize().x / 100) * stoi(_currentstat.substr(0, _currentstat.find(" "))), Size.y));

	App.Get_Window().draw(Rod);
	App.Get_Window().draw(Texte);
}

void Button_Text::Set_String(string _string)
{
	Texte.setString(_string);
	Texte.setOrigin(getMidle(Texte));
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
	sprite.setColor(color);
	App.Get_Window().draw(shape);
	sprite.setOrigin(getMidle(sprite));
	sprite.setPosition(Vector2f(shape.getPosition().x, shape.getPosition().y));
	sprite.setRotation(Rotate);
	App.Get_Window().draw(sprite);
}