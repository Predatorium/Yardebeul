#include "World.h"
#include "Dungeon_Container.h"
#include "Map_Manager.h"
#include "SpriteManager.h"
#include "Menu.h"
#include "Data.h"

World::World()
{
	if (SpriteList.size() > 0)
	{
		Player = Hero(Vector2f(100, 100));
		Load_Map(Get_PathMap("Map"));

		Menu_Pause = new Menu(1);

		Save = false;
		Load = true;
		Pause = false;

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

		Save = false;
		Load = false;
		Pause = false;

		Vue = Views(Vector2f(960, 540), Vector2f(1920, 1080), FloatRect(0.f, 0.f, 1.f, 1.f));
		Screen = Views();
	}
}

void World::ScreenShot(int _party)
{
	RenderTexture texture;
	string path = "../Ressources/Infos/Screen" + to_string(_party) + ".png";
	texture.create(1920, 1080);

	texture.clear(Color::Black);
	for (Maps Current_Maps : Back_Layer)
	{
		getSprite(Current_Maps.Get_Name()).setTextureRect(IntRect(Current_Maps.Get_Tile().x * Taille_tile, Current_Maps.Get_Tile().y * Taille_tile, Taille_tile, Taille_tile));
		getSprite(Current_Maps.Get_Name()).setPosition(Current_Maps.Get_Position());
		App.Get_Window().draw(getSprite(Current_Maps.Get_Name()));
		texture.draw(getSprite(Current_Maps.Get_Name()));
	}
	for (Maps Current_Maps : Player_Layer)
	{
		getSprite(Current_Maps.Get_Name()).setTextureRect(IntRect(Current_Maps.Get_Tile().x * Taille_tile, Current_Maps.Get_Tile().y * Taille_tile, Taille_tile, Taille_tile));
		getSprite(Current_Maps.Get_Name()).setPosition(Current_Maps.Get_Position());
		App.Get_Window().draw(getSprite(Current_Maps.Get_Name()));
		texture.draw(getSprite(Current_Maps.Get_Name()));
	}
	for (Maps Current_Maps : Front_Layer)
	{
		getSprite(Current_Maps.Get_Name()).setTextureRect(IntRect(Current_Maps.Get_Tile().x * Taille_tile, Current_Maps.Get_Tile().y * Taille_tile, Taille_tile, Taille_tile));
		getSprite(Current_Maps.Get_Name()).setPosition(Current_Maps.Get_Position());
		App.Get_Window().draw(getSprite(Current_Maps.Get_Name()));
		texture.draw(getSprite(Current_Maps.Get_Name()));
	}

	texture.display();

	texture.getTexture().copyToImage().saveToFile(path);
}

void World::Update()
{
	Collision();
	if (Pause == false)
	{
		Player.Update(Range_Niveau);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			Pause = true;
	}

	if (Pause == true)
		Menu_Pause->Update_Pause(*this, Pause);

	Vue.Update_Game(Range_Niveau, Player);
}

void World::Display()
{
	Vue.Display();
	display();

	if (Pause == true)
		Menu_Pause->Display_Pause();
}