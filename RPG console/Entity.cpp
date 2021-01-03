#include "Entity.h"
#include "SpriteManager.h"

Entity::Entity(string _name) : Name(_name), sprite(getTexture(_name)){}