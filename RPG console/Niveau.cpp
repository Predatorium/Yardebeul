#include "Niveau.h"
#include "SpriteManager.h"
#include "Menu.h"

bool Level::Get_Void(vector<Maps> _Layer, Vector2i _position)
{
	for (Maps& Current_Map : _Layer)
	{
		if ((int)Current_Map.Get_Position().x / Taille_tile == _position.x &&
			(int)Current_Map.Get_Position().y / Taille_tile == _position.y)
			return false;
	}

	return true;
}

bool Level::Get_MapsPos(Vector2i _position)
{
	for (Maps& Current_Map : Player_Layer)
	{
		if ((int)Current_Map.Get_Position().x / Taille_tile == _position.x &&
			(int)Current_Map.Get_Position().y / Taille_tile == _position.y)
			return true;
	}

	if (Get_Void(Back_Layer, _position) == false)
		return false;
	else
		return true;
}

void Level::Collision(Character& _Character)
{
	Vector2i NextPosOnMap;

	NextPosOnMap.x = (int)_Character.Get_Position().x / Taille_tile;
	NextPosOnMap.y = (int)_Character.Get_Position().y / Taille_tile;

	if (_Character.Get_Right() == true)
	{
		NextPosOnMap.x = (int)((_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 2) + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y) / Taille_tile;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Right(false);

		NextPosOnMap.x = (int)((_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 2) + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y + _Character.Get_ColisionRect().height) / Taille_tile;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Right(false);
	}
	if (_Character.Get_Left() == true)
	{
		NextPosOnMap.x = (int)((_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 2) - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y) / Taille_tile;
		if ((_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 2) - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.x--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Left(false);

		NextPosOnMap.x = (int)((_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 2) - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y + _Character.Get_ColisionRect().height) / Taille_tile;
		if ((_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 2) - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.x--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Left(false);
	}
	if (_Character.Get_Down() == true)
	{
		NextPosOnMap.x = (int)(_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y + _Character.Get_ColisionRect().height + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Down(false);

		NextPosOnMap.x = (int)(_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y + _Character.Get_ColisionRect().height + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Down(false);
	}
	if (_Character.Get_Up() == true)
	{
		NextPosOnMap.x = (int)(_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if ((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.y--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Up(false);

		NextPosOnMap.x = (int)(_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if ((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.y--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Up(false);
	}
}

void Level::Load_Map(string _file)
{
	Back_Layer.clear();
	Deco_Layer.clear();
	Player_Layer.clear();
 	Front_Layer.clear();
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
			else if (line == "Deco_Layer")
				layer = "Deco_Layer";
			else if (line == "Player_Layer")
				layer = "Player_Layer";
			else if (line == "Front_Layer")
				layer = "Front_Layer";
			else if (line == "Npc_List")
				layer = "Npc_List";
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
				if (layer == "Deco_Layer")
					Deco_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Player_Layer")
					Player_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
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
		}
		Read_Map.close();
	}
}

void Level::Save_Map(string _file)
{
	ofstream Write_Map(_file);
	if (Write_Map.is_open())
	{
		vector<Maps> tmpMaps = Back_Layer;
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

				if (Actual_Map.Get_Biome() == Biomes::Prairie)
					Write_Map << "0";
				if (Actual_Map.Get_Biome() == Biomes::Desert)
					Write_Map << "1";
				if (Actual_Map.Get_Biome() == Biomes::Caverne)
					Write_Map << "2";
				if (Actual_Map.Get_Biome() == Biomes::Montagne)
					Write_Map << "3";
			}
			if (i == Back_Layer.size() && tmp == "Back_Layer")
			{
				Write_Map << endl;
				Write_Map << "Deco_Layer";
				tmp = "Deco_Layer";
				tmpMaps = Deco_Layer;
			}
			if (i == Back_Layer.size() + Deco_Layer.size() && tmp == "Deco_Layer")
			{
				Write_Map << endl;
				Write_Map << "Player_Layer";
				tmp = "Player_Layer";
				tmpMaps = Player_Layer;
			}
			if (i == Back_Layer.size() + Deco_Layer.size() + Player_Layer.size() && tmp == "Player_Layer")
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
		Write_Map.close();
	}
}

void Level::Destroy_List()
{
	for (Npc& Current_Npc : NpcList)
		if (Current_Npc.Get_LifePoint() <= 0)
		{
			NpcList.remove(Current_Npc);
			break;
		}

	for (Weapon& Current : WeaponList)
		if (Current.Get_PickUp() == true)
		{
			WeaponList.remove(Current);
			break;
		}

	for (Armor& Current : ArmorList)
		if (Current.Get_PickUp() == true)
		{
			ArmorList.remove(Current);
			break;
		}

	for (Consumable& Current : ConsumableList)
		if (Current.Get_PickUp() == true)
		{
			ConsumableList.remove(Current);
			break;
		}
}

void Level::Display()
{
	Vue.Display();

	for (Maps& Current_Map : Back_Layer)
		Current_Map.Display();

	for (Maps& Current_Map : Deco_Layer)
		Current_Map.Display();

	for (Maps& Current_Map : Player_Layer)
		Current_Map.Display();
	
	for (Npc& Current_Npc : NpcList)
		Current_Npc.Display();

	for (Weapon& Current_Weapon : WeaponList)
		Current_Weapon.Display(Player.Get_Position());

	for (Armor& Current_Armor : ArmorList)
		Current_Armor.Display(Player.Get_Position());

	for (Consumable& Current_Consumable : ConsumableList)
		Current_Consumable.Display(Player.Get_Position());

	Player.Display();

	for (Maps& Current_Map : Front_Layer)
	{

		if (Circle_Collision(Vector2f(Player.Get_Position().x, Player.Get_Position().y + Player.Get_ColisionRect().height / 2.1f),
			Vector2f(Current_Map.Get_Position().x + 16, Current_Map.Get_Position().y + 16), 30, Player.Get_ColisionRect().width))
			getSprite(Current_Map.Get_Name()).setColor(Color(255,255,255,100));
		else
			getSprite(Current_Map.Get_Name()).setColor(Color::White);

		Current_Map.Display();

		getSprite(Current_Map.Get_Name()).setColor(Color::White);
	}

	Screen.Display();

	for (Npc& Current : NpcList)
		Current.Display_Dialogue();

	if (Pause == true)
		Menu_Pause->Display_Pause();
}