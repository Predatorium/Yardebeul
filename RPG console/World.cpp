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
		Change_ShapeMap = false;
		Timer = 0;

		Vue = Views(Vector2f(480, 270), Vector2f(960, 540), FloatRect(0, 0, 1, 1));
		Screen = Views(Vector2f(1440, 810), Vector2f(2880, 1620), FloatRect(0, 0, 1, 1));

		C_MiniMap = CircleShape(150);
		C_MiniMap.setPosition(Vector2f(1918 - C_MiniMap.getGlobalBounds().width, 2));
		C_MiniMap.setOutlineThickness(2);
		C_MiniMap.setOutlineColor(Color::Blue);

		R_MiniMap = RectangleShape(Vector2f(384, 216));
		R_MiniMap.setPosition(Vector2f(1918 - R_MiniMap.getGlobalBounds().width, 2));
		R_MiniMap.setOutlineThickness(2);
		R_MiniMap.setOutlineColor(Color::Blue);
	}
}

World::World(int _load)
{
	if (SpriteList.size() > 0)
	{
		Data::Load_Player(_load, Player);
		Load_Map(Get_PathMap("Map"));

		Menu_Pause = new Menu(1);

		WeaponList.push_back(Weapon(Weapons.Get_Weapon("Epee de feu"), Vector2f(200, 200)));

		Save = false;
		Load = false;
		Pause = false;
		IsDialogue = false;
		Change_ShapeMap = false;
		Timer = 0;

		Vue = Views();
		Screen = Views();

		C_MiniMap = CircleShape(200);
		C_MiniMap.setScale(0.96f, 0.54f);
		C_MiniMap.setPosition(Vector2f(1526, 854));
		C_MiniMap.setOutlineThickness(2);
		C_MiniMap.setOutlineColor(Color::Blue);
	}
}