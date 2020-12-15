#include "Armor.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "Hero.h"

Armor::Armor(int _defense, int _durability, string _name, int _price, Effect _effect)
	: Item(_name, _price, _effect)
{
	Defense = _defense;
	Durability = _durability;
	PickUp = false;

}

Armor::Armor(const Armor& _armor, Vector2f _position)
{
	*this = _armor;
	Position = _position;
}

void Armor::Take_Item(Hero& _player)
{
	if (Circle_Collision(_player.Get_Position(), Position, 20, 20) && _player.Get_Interact())
	{
		_player.Get_Inventory().Add_Armor(*this);
		PickUp = true;
	}
}

void Armor::Display(Vector2f _position)
{
	sprite.setPosition(Position);
	sprite.setScale(Vector2f(1, 1));
	App.Get_Window().draw(sprite);

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

void Armor::Display_Inventory(Vector2f _scale)
{
	Anim.Animation(sprite);
	sprite.setOrigin(Vector2f(10.5, 15));
	sprite.setPosition(Position);
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
}