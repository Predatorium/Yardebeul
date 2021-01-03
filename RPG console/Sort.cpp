#include "Sort.h"
#include "SpriteManager.h"
#include "FontManager.h"

Sort::Sort(string _name, int _damage, Target _target, Effect _effect)
{
	Name = _name;
	target = _target;
	effect = _effect;
	Damage = _damage;

	sprite.setTexture(getTexture(Name.substr(0, Name.size() - 2)));
	sprite.setOrigin(getMidle(sprite));
}

void Sort::Display(Vector2f _position)
{
	Position = _position;
	Text level(to_string(effect.Get_Level()), getFont("Times"));
	level.setPosition(Position);
	sprite.setPosition(Position);
	App.Get_Window().draw(sprite);
	App.Get_Window().draw(level);
}
