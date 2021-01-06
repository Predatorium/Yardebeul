#include "Dungeon.h"
#include "StateManager.h"

Dungeon::Dungeon(State_Event _event, string _name, int _difficulte, Vector2f _position)
	:Entity(_name)
{
	Statut_Event = _event;
	Difficulté = _difficulte;
	Current_Room = 1;
	Position = _position;
	DungeonIsFinished = false;

	sprite.setOrigin(getMidle(sprite));
	sprite.setPosition(Position);
}

void Dungeon::Procedural_Dungeon(Hero& _player)
{
	Rooms.clear();

	string biome;
	int rand = irandom(1, 2);
	biome = "Castle" + to_string(rand);

	int Number_Rooms = irandom(5, 3);

	for (int i = 0; i < Number_Rooms; i++)
	{
		if (i < Number_Rooms - 1)
			Rooms.push_back(Room(Biomes::Castle, 1, false, i + 1, _player));
		else
			Rooms.push_back(Room(Biomes::Castle, 1, true, i + 1, _player));

		Rooms.back().Procedural_Room(biome);
	}
}

void Dungeon::Update(Hero& _player)
{
	for (Room& Current : Rooms)
		if (Current_Room == Current.Get_Numero())
		{
			Current.Update(*this);
			break;
		}

	if (Current_Room == 0)
	{
		_player.Set_Position(Position);
		Game_Manager::Get_Singleton().ChangeState(Game_State::WORLD);
		Current_Room = 1;
	}

	if (Current_Room == Rooms.size() + 1)
	{
		_player.Set_Position(Position);
		Game_Manager::Get_Singleton().ChangeState(Game_State::WORLD);
		Current_Room = 1;
	}

}

void Dungeon::Display()
{
	for (Room& Current : Rooms)
		if (Current_Room == Current.Get_Numero())
		{
			Current.Display();
			break;
		}
}

void Dungeon::Display_World()
{
	App.Get_Window().draw(sprite);
}