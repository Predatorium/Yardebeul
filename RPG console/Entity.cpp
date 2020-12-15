#include "Entity.h"
#include "SpriteManager.h"

Entity::Entity(string _name)
{
	Name = _name;
	if (Name != "Rien")
		sprite = getSprite(Name);
}
