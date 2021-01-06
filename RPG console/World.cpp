#include "World.h"
#include "Map_Manager.h"
#include "StateManager.h"
#include "Data.h"
#include "SpriteManager.h"

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
		IsDialogue = false;
		Timer = 0;

		Vue = Views(Vector2f(480, 270), Vector2f(960, 540), FloatRect(0, 0, 1, 1));
		Screen = Views(Vector2f(1440, 810), Vector2f(2880, 1620), FloatRect(0, 0, 1, 1));

		C_MiniMap = CircleShape(150);
		C_MiniMap.setPosition(Vector2f(1918 - C_MiniMap.getGlobalBounds().width, 2));
		C_MiniMap.setOutlineThickness(2);
		C_MiniMap.setOutlineColor(Color::Blue);
	}
}

World::World(int _load)
{
	Load_Map(Get_PathMap("Map"));
	Data::Load_Player(_load, Player, *this);

	Menu_Pause = new Menu(1);

	Save = false;
	Load = true;
	Pause = false;
	IsDialogue = false;
	Timer = 0;

	Vue = Views(Vector2f(480, 270), Vector2f(960, 540), FloatRect(0, 0, 1, 1));
	Screen = Views(Vector2f(1440, 810), Vector2f(2880, 1620), FloatRect(0, 0, 1, 1));

	C_MiniMap = CircleShape(150);
	C_MiniMap.setPosition(Vector2f(1918 - C_MiniMap.getGlobalBounds().width, 2));
	C_MiniMap.setOutlineThickness(2);
	C_MiniMap.setOutlineColor(Color::Blue);
}

void World::Load_Map(string _file)
{
	Back_Layer.clear();
	Deco_Layer.clear();
	Player_Layer.clear();
	Front_Layer.clear();
	dungeon.clear();
	NpcList.clear();

	ifstream Read_Map(_file);
	if (Read_Map.is_open())
	{
		string line;
		string layer;

		Read_Map >> Range_Niveau.x;
		Read_Map >> Range_Niveau.y;

		while (getline(Read_Map, line))
		{
			string name = "----";
			int tmpposX = 0;
			int tmpposY = 0;

			if (line == "Back_Layer")
				layer = "Back_Layer";
			else if (line == "Player_Layer")
				layer = "Player_Layer";
			else if (line == "Deco_Layer")
				layer = "Deco_Layer";
			else if (line == "Front_Layer")
				layer = "Front_Layer";
			else if (line == "Npc_List")
				layer = "Npc_List";
			else if (line == "Dungeon_List")
				layer = "Dungeon_List";
			else if (layer == "Back_Layer" || layer == "Player_Layer" || layer == "Front_Layer" || layer == "Deco_Layer")
			{
				int tmpX = 0;
				int tmpY = 0;
				Biomes tmpbiome;

				name = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmpposX = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpposY = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpX = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpY = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpbiome = static_cast<Biomes>(stoi(line));
				line.erase(0, line.size());

				if (layer == "Back_Layer")
					Back_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Player_Layer")
					Player_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Deco_Layer")
					Deco_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Front_Layer")
					Front_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
			}
			else if (layer == "Npc_List")
			{
				name = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmpposX = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpposY = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.size());

				NpcList.push_back(Npc(Npcs.Get_Npc(name), Vector2f(tmpposX, tmpposY)));
			}
			else if (layer == "Dungeon_List")
			{
				int tmpdiff = 0;
				State_Event tmpstat = State_Event(0);

				name = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmpdiff = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpstat = State_Event(stoi(line.substr(0, line.find(" "))));
				line.erase(0, line.find(" ") + 1);

				tmpposX = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpposY = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.size());

				dungeon.push_back(Dungeon(tmpstat,name, tmpdiff, Vector2f(tmpposX, tmpposY)));
			}

			if (!Read_Map)
				Read_Map.close();
		}
		Read_Map.close();
	}
}

void World::Save_Map(string _file)
{
	ofstream Write_Map(_file);
	if (Write_Map.is_open())
	{
		list<Maps> tmpMaps = Back_Layer;
		Write_Map << Range_Niveau.x << endl;
		Write_Map << Range_Niveau.y << endl;
		int i = 0;
		Write_Map << "Back_Layer";
		string tmp = "Back_Layer";
		bool done = true;
		while (done)
		{
			for (Maps& Actual_Map : tmpMaps)
			{
				i++;
				Write_Map << endl;
				Write_Map << Actual_Map.Get_Name() << " ";

				Write_Map << to_string(static_cast<int>(Actual_Map.Get_Position().x)) << " ";

				Write_Map << to_string(static_cast<int>(Actual_Map.Get_Position().y)) << " ";

				Write_Map << to_string(Actual_Map.Get_Tile().x) << " ";

				Write_Map << to_string(Actual_Map.Get_Tile().y) << " ";

				Write_Map << to_string(static_cast<int>(Actual_Map.Get_Biome()));
			}
			if (i == Back_Layer.size() && tmp == "Back_Layer")
			{
				Write_Map << endl;
				Write_Map << "Player_Layer";
				tmp = "Player_Layer";
				tmpMaps = Player_Layer;
			}
			if (i == Back_Layer.size() + Player_Layer.size() && tmp == "Player_Layer")
			{
				Write_Map << endl;
				Write_Map << "Deco_Layer";
				tmp = "Deco_Layer";
				tmpMaps = Deco_Layer;
			}
			if (i == Back_Layer.size() + Player_Layer.size() + Deco_Layer.size() && tmp == "Deco_Layer")
			{
				Write_Map << endl;
				Write_Map << "Front_Layer";
				tmp = "Front_Layer";
				tmpMaps = Front_Layer;
			}
			if (i == Back_Layer.size() + Deco_Layer.size() + Player_Layer.size() + Front_Layer.size() && tmp == "Front_Layer")
			{
				Write_Map << endl;
				Write_Map << "Npc_List";
				done = false;
			}
		}

		for (Npc& Current : NpcList)
		{
			Write_Map << endl;
			Write_Map << Current.Get_Name() << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Position().x)) << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Position().y));
		}

		Write_Map << "Dungeon_List";

		for (Dungeon& Current : dungeon)
		{
			Write_Map << endl;
			Write_Map << Current.Get_Name() << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Difficulte())) << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Statut())) << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Position().x)) << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Position().y));
		}
		Write_Map.close();
	}
}

void World::Update()
{
	Level::Update();

	for (Dungeon& Current : dungeon)
	{
		if (Current.Get_Sprite().getGlobalBounds().intersects(Player.Get_Sprite().getGlobalBounds()) && Player.Get_Interact() == true)
		{
			if (Current.Get_Finished() == false)
			{
				if (Current.Get_Name() != "Final")
				{
					Game_Manager::Get_Singleton().ChangeState(Game_State::DUNGEON);
					Current.Procedural_Dungeon(Player);
					Current_Dungeon = Current.Get_Name();
				}
			}
		}
	}
}

void World::Display()
{
	Vue.Display();

	for (Maps& Current : Back_Layer)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display();

	for (Maps& Current : Player_Layer)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display();

	for (Maps& Current : Deco_Layer)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display();

	for (Npc& Current : NpcList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display();

	for (Dungeon& Current : dungeon)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display_World();

	Player.Display();

	for (Npc& Current : NpcList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display();

	for (Maps& Current : Front_Layer)
	{
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
		{
			if (Circle_Collision(Vector2f(Player.Get_Position().x, Player.Get_Position().y + Player.Get_Sprite().getGlobalBounds().height / 2.6f),
				Vector2f(Current.Get_Position().x + 16, Current.Get_Position().y + 16), 30, Player.Get_Sprite().getGlobalBounds().width))
				Current.Get_Sprite().setColor(Color(255, 255, 255, 100));
			else
				Current.Get_Sprite().setColor(Color::White);

			Current.Display();

			Current.Get_Sprite().setColor(Color::White);
		}
	}

	App.Get_Window().setView(App.Get_Window().getDefaultView());

	for (Npc& Current : NpcList)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display_Dialogue();

	Player.Display_HUD();

	if (Pause == true)
		Menu_Pause->Display_Pause();

	C_MiniMap.setTexture(&Get_TextureMap(&Views::Occlusion_CullingCircle, Screen));
	C_MiniMap.setTextureRect(IntRect(420, 0, 1080, 1080));
	App.Get_Window().draw(C_MiniMap);
}