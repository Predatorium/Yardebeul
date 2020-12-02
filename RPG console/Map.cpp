#include "Map.h"
#include "SpriteManager.h"

Maps::Maps(Vector2f _position, Vector2i _tile, string _name, Biomes _biome)
{
	Position = _position;
	actif = true;
	Tile = _tile;
	Biome = _biome;
	Name = _name;
}

Interface_Maps::Interface_Maps(int _rank, Vector2f _position, Vector2i _tile, string _name, Biomes _biome) 
	: Maps(_position, _tile, _name, _biome)
{
	Rank = _rank;
}

void Maps::display()
{
	getSprite(Name).setTextureRect(IntRect(Tile.x * Taille_tile, Tile.y * Taille_tile, Taille_tile, Taille_tile));
	getSprite(Name).setPosition(Position);
	App.Get_Window().draw(getSprite(Name));
}