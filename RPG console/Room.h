#pragma once
#include "Tools.h"
#include "Event.h"
#include "Niveau.h"
#include "Chest.h"

class Dungeon;

enum class Dir : int
{
	None,
	Droite,
	Gauche,
	Haut,
	Bas
};

class Room : public Level
{
private:
	int Numero;
	Biomes Biome;
	Vector2i Size;
	int Difficulte;
	bool isBoss;

	pair<int, Maps> Escalier[2];

	list<Chest> Coffre;
	list<Events> Evenement;

public :
	Room() = default;
	Room(Biomes _biome, int _difficulte, bool _isBoss, int _number, Hero& _player);
	~Room() = default;

	inline void Add_Consumable(Consumable _consu, Vector2f _position) { ConsumableList.push_back(Consumable(_consu, _position)); };

	inline Vector2i Get_Size() { return Size; };
	inline Biomes Get_biome() { return Biome; };
	inline bool Get_Boss() { return isBoss; };
	inline int Get_Difficulte() { return Difficulte; };
	inline int Get_Numero() { return Numero; };

	void Procedural_Room(string _biome);

	void Update(Dungeon& _d);
	void Display();
};