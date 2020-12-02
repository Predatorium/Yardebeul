#include "FontManager.h"

Fonts::Fonts(string Name, string Path)
{
	name = Name;

	if (!(font.loadFromFile(Path)))
		cout << "ERROR: Font : " << name << "didn't load" << endl;
	else
		font.loadFromFile(Path);
}

list<Fonts*> FontList;

void LoadFont()
{
	for (RessourcesManager& ActualRessource : RessourcesList)
		if (ActualRessource.Get_Type() == RessourceType::FONT)
			FontList.push_back(new Fonts(ActualRessource.Get_Name(), ActualRessource.Get_Path()));
}

Font& getFont(string Name)
{
	for (Fonts* ActualFont : FontList)
		if (ActualFont->getName() == Name)
			return ActualFont->getFont();

	std::cout << "Error Loading Font : " << Name << std::endl;
}