#include "World.h"
#include "Dungeon_Container.h"
#include "Map_Manager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "Menu.h"
#include "Data.h"

World::World()
{
	if (SpriteList.size() > 0)
	{
		Player = Hero(Vector2f(100, 100));
		Load_Map(Get_PathMap("Map"));

		Menu_Pause = new Menu(1);

		App.Get_Window().setMouseCursorVisible(false);

		Nbr_Enemy = 0;
		NpcList.push_back(Npc("Knucles", Vector2f(500, 500), Nbr_Enemy, 7, 20, 25, Comportement::Agressif));
		NpcList.push_back(Npc("Knucles", Vector2f(200, 600), Nbr_Enemy, 7, 20, 25, Comportement::Agressif));

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

		Nbr_Enemy = 0;
		App.Get_Window().setMouseCursorVisible(false);
		NpcList.push_back(Npc("Knucles", Vector2f(500, 500), Nbr_Enemy, 7, 20, 25, Comportement::Agressif));
		NpcList.push_back(Npc("Knucles", Vector2f(200, 600), Nbr_Enemy, 7, 20, 25, Comportement::Agressif));

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
	View view(Player.Get_Position(), Vector2f(1920, 1080));
	texture.create(1920, 1080);

	texture.clear(Color::Black);
	view.setCenter(Player.Get_Position());
	texture.setView(view);
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

void World::Destroy_Npc()
{
	for (Npc& Current_Npc : NpcList)
		if (Current_Npc.Get_HP() == 0)
		{
			NpcList.remove(Current_Npc);
			break;
		}
}

void World::Update()
{
	if (Pause == false)
	{
		Collision(Player);
		Player.Update(Range_Niveau);

		Destroy_Npc();

		for (Npc& Current_Npc : NpcList)
		{
			Collision(Current_Npc);

			if (Current_Npc.Get_Attitude() == Comportement::Agressif)
			{
				Current_Npc.Update_Attack(Player.Get_Position());
				if (Circle_Collision(Current_Npc.Get_Position(), Player.Get_Position(), getSprite(Current_Npc.Get_Name()).getGlobalBounds().width / 2, getSprite("Hero").getGlobalBounds().width / 2))
					MState.State_Fight(&Player, &Current_Npc);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			App.Get_Window().setMouseCursorVisible(true);
			Pause = true;
		}
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