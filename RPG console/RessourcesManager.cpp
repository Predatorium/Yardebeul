#include "RessourcesManager.h"

list<RessourcesManager> RessourcesList;

RessourcesManager::RessourcesManager(RessourceType _type, string _name, string _path, float _soundmultiplier)
{
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
			if (line != "")
			{
				RessourceType tmptype;
				string tmpname;
				string tmppath;
				float tmpsound = 0;

				if (line.substr(0, line.find(" ")) == "Sprite")
					tmptype = RessourceType::TEXTURE;
				else if (line.substr(0, line.find(" ")) == "Font")
					tmptype = RessourceType::FONT;
				else if (line.substr(0, line.find(" ")) == "Map")
					tmptype = RessourceType::MAP;
				line.erase(0, line.find(" ") + 1);

				tmpname = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmppath = line.substr(0, line.find(" "));
				line.erase(0, line.size());

				RessourcesList.push_back(RessourcesManager(tmptype, tmpname, tmppath, tmpsound));
			}
		}
	}
}