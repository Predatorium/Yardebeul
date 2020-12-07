#include "Niveau.h"
#include "SpriteManager.h"

bool Level::Get_MapsPos(Vector2i _position)
{
	for (Maps& Current_Map : Player_Layer)
	{
		if ((int)Current_Map.Get_Position().x / Taille_tile == _position.x &&
			(int)Current_Map.Get_Position().y / Taille_tile == _position.y)
			return true;
	}

	return false;
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
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Left(false);

		NextPosOnMap.x = (int)((_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 2) - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y + _Character.Get_ColisionRect().height) / Taille_tile;
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
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Up(false);

		NextPosOnMap.x = (int)(_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Up(false);
	}
}

void Level::Load_Map(string _file)
{
	Back_Layer.clear();
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
				int tmpniveau = 0;
				int tmppv = 0;
				int tmpvitesse = 0;
				Comportement tmpcomp;

				name = line.substr(0, line.find("|"));
				line.erase(0, line.find("|") + 1);

				tmpposX = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find("|") + 1);

				tmpposY = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find("|") + 1);

				tmpniveau = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find("|") + 1);

				tmppv = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find("|") + 1);

				tmpvitesse = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpcomp = static_cast<Comportement>(stoi(line));
				line.erase(0, line.size());

				NpcList.push_back(Npc(name, Vector2f(tmpposX, tmpposY), tmpniveau, tmppv, tmpvitesse, tmpcomp));
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
					Write_Map << "1";
				if (Actual_Map.Get_Biome() == Biomes::Desert)
					Write_Map << "2";
				if (Actual_Map.Get_Biome() == Biomes::Caverne)
					Write_Map << "3";
				if (Actual_Map.Get_Biome() == Biomes::Montagne)
					Write_Map << "4";
			}
			if (i == Back_Layer.size())
			{
				Write_Map << endl;
				Write_Map << "Player_Layer";
				tmpMaps = Player_Layer;
			}
			if (i == Back_Layer.size() + Deco_Layer.size())
			{
				Write_Map << endl;
				Write_Map << "Deco_Layer";
				tmpMaps = Deco_Layer;
			}
			if (i == Back_Layer.size() + Deco_Layer.size() + Player_Layer.size())
			{
				Write_Map << endl;
				Write_Map << "Front_Layer";
				tmpMaps = Front_Layer;
			}
			if (i == Back_Layer.size() + Deco_Layer.size() + Player_Layer.size() + Front_Layer.size())
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
			Write_Map << to_string(static_cast<int>(Current.Get_Position().y)) << " ";
			Write_Map << to_string(Current.Get_Level()) << " ";
			Write_Map << to_string(Current.Get_LifePoint()) << " ";
			Write_Map << to_string(Current.Get_Speed()) << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Attitude()));

		}
		Write_Map.close();
	}
}

void Level::Destroy_Npc()
{
	for (Npc& Current_Npc : NpcList)
		if (Current_Npc.Get_LifePoint() == 0)
		{
			NpcList.remove(Current_Npc);
			break;
		}
}

void Level::display()
{
	for (Maps& Current_Map : Back_Layer)
		Current_Map.display();

	for (Maps& Current_Map : Deco_Layer)
		Current_Map.display();

	for (Maps& Current_Map : Player_Layer)
		Current_Map.display();
	
	for (Npc& Current_Npc : NpcList)
		Current_Npc.Display();

	Player.Display();

	for (Maps& Current_Map : Front_Layer)
	{
		if (FloatRect(Current_Map.Get_Position().x, Current_Map.Get_Position().y,32,32).intersects(getSprite("Hero").getGlobalBounds()))
			getSprite(Current_Map.Get_Name()).setColor(Color(255,255,255,100));
		else
			getSprite(Current_Map.Get_Name()).setColor(Color::White);

		Current_Map.display();

		getSprite(Current_Map.Get_Name()).setColor(Color::White);
	}
}