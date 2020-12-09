#include "Armor.h"
#include "SpriteManager.h"
#include "FontManager.h"

Armor::Armor(int _defense, int _durability, string _name, int _price, Effect _effect)
	: Item(_name, _price, _effect)
{
	Defense = _defense;
	Durability = _durability;
}

Armor::Armor(const Armor& _armor, Vector2f _position)
{
	*this = _armor;
	Position = _position;
}

void Armor::Display(Vector2f _position)
{
	getSprite(Name.substr(0, Name.find(" "))).setPosition(Position);
	App.Get_Window().draw(getSprite(Name.substr(0, Name.find(""))));

	if (Circle_Collision(Position, _position, 20, 20))
	{
		Text My(Name, getFont("Times"), 20);
		My.setPosition(Position);

		RectangleShape Shape(getMidle(My));
		Shape.setFillColor(Color::Black);
		Shape.setOutlineThickness(3);
		Shape.setOutlineColor(Color::White);
		Shape.setPosition(Position);

		App.Get_Window().draw(Shape);
		App.Get_Window().draw(My);
	}
}