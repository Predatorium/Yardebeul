#include "Map.h"
#include "SpriteManager.h"

Maps::Maps(Vector2f _position, Vector2i _tile, string _name, Biomes _biome)
{
	Name = _name;
	Position = _position;
	Tile = _tile;
	Biome = _biome;
	Name = _name;
	
	if(Name != "Rien")
		sprite = Sprite(getTexture(Name));

	sprite.setTextureRect(IntRect(Tile.x * Taille_tile, Tile.y * Taille_tile, Taille_tile, Taille_tile));
	sprite.setPosition(Position);
}

Interface_Maps::Interface_Maps(int _rank, Vector2f _position, Vector2i _tile, string _name, Biomes _biome) 
	: Maps(_position, _tile, _name, _biome)
{
	Rank = _rank;
}

void Maps::Display()
{
	App.Get_Window().draw(sprite);
}