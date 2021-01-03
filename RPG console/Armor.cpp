#include "Armor.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "Hero.h"

Armor::Armor(int _defense, string _name, Effect _effect)
	: Item(_name, _effect)
{
	Defense = _defense;
	PickUp = false;
	sprite.setOrigin(getMidle(sprite));
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

void Armor::Display(Vector2f _circlecol)
{
	sprite.setPosition(Position);
	sprite.setScale(Vector2f(1, 1));
	App.Get_Window().draw(sprite);

	if (Circle_Collision(Position, _circlecol, 20, 20))
	{
		Text My(Name, getFont("Times"), 20);
		My.setOrigin(getMidle(My));
		My.setFillColor(Color::Black);
		My.setPosition(Vector2f(Position.x, Position.y - 20));
		App.Get_Window().draw(My);
	}
}

void Armor::Display_Inventory(Vector2f _scale)
{
	if (Anim[Name] != Animator())
		Anim[Name].Animation(sprite);
	sprite.setPosition(Position);
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
}