#pragma once
#include "Tools.h"

class Maps
{
protected :
	Vector2f Position;
	string Name;
	Vector2i Tile;
	Biomes Biome;
	bool actif;

public :
	Maps() = default;
	Maps(Vector2f _position, Vector2i _tile, string _name, Biomes _biome);
	~Maps() = default;

	inline Vector2f Get_Position() { return Position; };
	inline bool Get_Actif() { return actif; };
	inline Vector2i Get_Tile() { return Tile; };
	inline Biomes Get_Biome() { return Biome; };
	inline string Get_Name() { return Name; };

	inline void Set_Position(Vector2f _position) { Position = _position; };
	inline void Set_Actif(bool _actif) { actif = _actif; };
	inline void Set_Tile(Vector2i _tile) { Tile = _tile; };
	inline void Set_Biome(Biomes _biome) { Biome = _biome; };
	inline void Set_Name(string _name) { Name = _name; };

	void display();
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