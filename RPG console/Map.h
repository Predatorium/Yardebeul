#pragma once
#include "Tools.h"
#include "Entity.h"

class Maps
{
protected :
	Sprite sprite;
	Vector2f Position;
	string Name;
	Vector2i Tile;
	Biomes Biome;

public :
	Maps() = default;
	Maps(Vector2f _position, Vector2i _tile, string _name, Biomes _biome);
	~Maps() = default;

	bool operator == (const Maps& m) const { return Name == m.Name && Tile == m.Tile && Biome == m.Biome && Position == m.Position; };

	inline Vector2i Get_Tile() { return Tile; };
	inline Biomes Get_Biome() { return Biome; };
	inline Vector2f Get_Position() { return Position; };
	inline string Get_Name() { return Name; };
	inline Sprite& Get_Sprite() { return sprite; };

	inline void Set_Position(Vector2f _position) { Position = _position; sprite.setPosition(Position); };
	inline void Set_Name(string _name) { Name = _name; };
	inline void Set_Tile(Vector2i _tile) { Tile = _tile; };
	inline void Set_Biome(Biomes _biome) { Biome = _biome; };

	virtual void Update() {};
	virtual void Display();
};

class Interface_Maps : public Maps
{
private :
	int Rank;

public :
	Interface_Maps() = default;
	Interface_Maps(int _rank, Vector2f _position, Vector2i _tile, string _name, Biomes _biome);
	~Interface_Maps() = default;

	inline int Get_Rank() { return Rank; };
};