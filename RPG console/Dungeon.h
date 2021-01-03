#pragma once
#include "Tools.h"
#include "Room.h"
#include "Entity.h"
#include "Hero.h"

class Dungeon : public Entity
{
private :
	State_Event Statut_Event;
	int Difficulté;
	bool DungeonIsFinished;
	int Current_Room;

	list<Room> Rooms;

public :
	Dungeon() = default;
	Dungeon(State_Event _event, string _name, int _difficulte, Vector2f _position);
	~Dungeon() = default;

	inline State_Event Get_Statut() { return Statut_Event; };
	inline string Get_Name() { return Name; };
	inline int Get_Difficulte() { return Difficulté; };
	inline list<Room> Get_Rooms() { return Rooms; };
	inline bool Get_Finished() { return DungeonIsFinished; };

	inline void Set_Finish(bool _bool) { DungeonIsFinished = _bool; };

	inline void Add_CurrentRoom(int _add) { Current_Room += _add; };

	bool operator == (const Dungeon& _a) const { return Name == _a.Name; }
	bool operator != (const Dungeon& _a) const { return !operator==(_a); }

	void Procedural_Dungeon(Hero& _player);
	void Update(Hero& _player);

	void Update() {};
	void Display();
	void Display_World();
};