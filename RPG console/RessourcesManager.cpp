#include "RessourcesManager.h"

list<RessourcesManager> RessourcesList;

RessourcesManager::RessourcesManager(State _state, RessourceType _type, string _name, string _path, float _soundmultiplier)
{
	state = _state;
	type = _type;
	name = _name;
	path = _path;
	soundmultiplier = _soundmultiplier;
}

void RessourcesLoad(string _path)
{
	ifstream Read_Ressources(_path);
	if (Read_Ressources.is_open())
	{
		string line;
		while (getline(Read_Ressources, line))
		{
			RessourceType tmptype;
			State tmpstate;
			string tmpname;
			string tmppath;
			float tmpsound = 0;

			bool done = false;
			while (!done)
			{
				if (line.find(" "))
				{
					if (line.substr(0, line.find(" ")) == "Sprite")
						tmptype = RessourceType::TEXTURE;
					else if (line.substr(0, line.find(" ")) == "Font")
						tmptype = RessourceType::FONT;
					else if (line.substr(0, line.find(" ")) == "Map")
						tmptype = RessourceType::MAP;
					line.erase(0, line.find(" ") + 1);

					if (line.substr(0, line.find(" ")) == "All")
						tmpstate = State::ALL;
					else if (line.substr(0, line.find(" ")) == "Menu")
						tmpstate = State::MENU;
					line.erase(0, line.find(" ") + 1);

					tmpname = line.substr(0, line.find(" "));
					line.erase(0, line.find(" ") + 1);

					tmppath = line.substr(0, line.find(" "));
					line.erase(0, line.find(" ") + 1);

					if (line.find(" ") == -1)
						done = true;
				}
			}
			RessourcesList.push_back(RessourcesManager(tmpstate, tmptype, tmpname, tmppath, tmpsound));
		}
	}
}