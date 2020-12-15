#include "World.h"
#include "Dungeon_Container.h"
#include "Map_Manager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "Data.h"

World::World()
{
	if (SpriteList.size() > 0)
	{
		Player = Hero(Vector2f(100, 100));
		Load_Map(Get_PathMap("Map"));

		Menu_Pause = new Menu(1);

		WeaponList.push_back(Weapon(Weapons.Get_Weapon("Epee de feu"), Vector2f(200, 200)));

		Save = false;
		Load = true;
		Pause = false;
		IsDialogue = false;

		Vue = Views(Vector2f(960, 540), Vector2f(1920, 1080), FloatRect(0.f, 0.f, 1.f, 1.f));
		Screen = Views();
	}
}

World::World(int _load)
{
	if (SpriteList.size() > 0)
	{
		Data::Load_Player(_load, Player);
		Load_Map(Get_PathMap("Map"));

		Menu_Pause = new Menu(1);

		App.Get_Window().setMouseCursorVisible(false);

		Save = false;
		Load = false;
		Pause = false;
		IsDialogue = false;

		Vue = Views(Vector2f(960, 540), Vector2f(1920, 1080), FloatRect(0.f, 0.f, 1.f, 1.f));
		Screen = Views();
	}
}