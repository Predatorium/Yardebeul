#include "Niveau.h"
#include "SpriteManager.h"

bool Niveau::Get_MapsPos(Vector2i _position)
{
	for (Maps& Current_Map : Player_Layer)
	{
		if ((int)Current_Map.Get_Position().x / Taille_tile == _position.x &&
			(int)Current_Map.Get_Position().y / Taille_tile == _position.y)
			return true;
	}

	return false;
}

void Niveau::Collision(Character& _Character)
{
	Vector2i NextPosOnMap;

	NextPosOnMap.x = (int)_Character.Get_Position().x / Taille_tile;
	NextPosOnMap.y = (int)_Character.Get_Position().y / Taille_tile;

	if (_Character.Get_Droite() == true)
	{
		NextPosOnMap.x = (int)((_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 2) + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y) / Taille_tile;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Droite(false);

		NextPosOnMap.x = (int)((_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 2) + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y + _Character.Get_ColisionRect().height) / Taille_tile;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Droite(false);
	}
	if (_Character.Get_Gauche() == true)
	{
		NextPosOnMap.x = (int)((_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 2) - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y) / Taille_tile;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Gauche(false);

		NextPosOnMap.x = (int)((_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 2) - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y + _Character.Get_ColisionRect().height) / Taille_tile;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Gauche(false);
	}
	if (_Character.Get_Bas() == true)
	{
		NextPosOnMap.x = (int)(_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y + _Character.Get_ColisionRect().height + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Bas(false);

		NextPosOnMap.x = (int)(_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y + _Character.Get_ColisionRect().height + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Bas(false);
	}
	if (_Character.Get_Haut() == true)
	{
		NextPosOnMap.x = (int)(_Character.Get_Position().x - (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Haut(false);

		NextPosOnMap.x = (int)(_Character.Get_Position().x + (_Character.Get_ColisionRect().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Haut(false);
	}
}

void Niveau::Load_Map(string _file)
{
	Back_Layer.clear();
	Player_Layer.clear();
 	Front_Layer.clear();

	ifstream Read_Map(_file);
	if (Read_Map.is_open())
	{
		string line;
		string layer;
		int tmpposX = 0;
		int tmpposY = 0;
		int tmpX = 0;
		int tmpY = 0;
		Biomes tmpbiome;
		string name;

		Read_Map >> Range_Niveau.x;
		Read_Map >> Range_Niveau.y;

		while (getline(Read_Map, line))
		{
			if (line == "Back_Layer")
				layer = "Back_Layer";
			else if (line == "Player_Layer")
				layer = "Player_Layer";
			else if (line == "Front_Layer")
				layer = "Front_Layer";
			else if (line != "")
			{
				tmpposX = stoi(line.substr(0, line.find("|")));
				line.erase(0, line.find("|") + 1);

				tmpposY = stoi(line.substr(0, line.find("|")));
				line.erase(0, line.find("|") + 1);

				tmpX = stoi(line.substr(0, line.find("|")));
				line.erase(0, line.find("|") + 1);

				tmpY = stoi(line.substr(0, line.find("|")));
				line.erase(0, line.find("|") + 1);

				name = line.substr(0, line.find("|"));
				line.erase(0, line.find("|") + 1);

				tmpbiome = static_cast<Biomes>(stoi(line));
				line.erase(0, line.size());

				if (layer == "Back_Layer")
					Back_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Player_Layer")
					Player_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Front_Layer")
					Front_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
			}
		}
		Read_Map.close();
	}
}

void Niveau::Save_Map(string _file)
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
				Write_Map << to_string((int)Actual_Map.Get_Position().x) << "|";

				Write_Map << to_string((int)Actual_Map.Get_Position().y) << "|";

				Write_Map << to_string(Actual_Map.Get_Tile().x) << "|";

				Write_Map << to_string(Actual_Map.Get_Tile().y) << "|";

				Write_Map << Actual_Map.Get_Name() << "|";

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
			if (i == Back_Layer.size() + Player_Layer.size())
			{
				Write_Map << endl;
				Write_Map << "Front_Layer";
				tmpMaps = Front_Layer;
			}
			if (i == Back_Layer.size() + Player_Layer.size() + Front_Layer.size())
				done = false;

		}
		Write_Map.close();
	}
}

void Niveau::display()
{
	for (Maps& Current_Map : Back_Layer)
		Current_Map.display();

	for (Maps& Current_Map : Player_Layer)
		Current_Map.display();
	
	Player.Display();

	for (Npc& Current_Npc : NpcList)
		Current_Npc.Display();

	for (Maps& Current_Map : Front_Layer)
		Current_Map.display();
}