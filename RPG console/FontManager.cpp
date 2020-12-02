#include "FontManager.h"

Fonts::Fonts(string Name, State _state, string Path)
{
	name = Name;
	state = _state;

	if (!(font.loadFromFile(Path)))
		cout << "ERROR: Font : " << name << "didn't load" << endl;
	else
		font.loadFromFile(Path);
}

list<Fonts*> FontList;

void LoadFont(State _state)
{
	for (RessourcesManager& ActualRessource : RessourcesList)
		if (ActualRessource.Get_state() == _state)
			if (ActualRessource.Get_Type() == RessourceType::FONT)
				FontList.push_back(new Fonts(ActualRessource.Get_Name(), ActualRessource.Get_state(), ActualRessource.Get_Path()));
}

Font& getFont(string Name)
{
	for (Fonts* ActualFont : FontList)
		if (ActualFont->getName() == Name)
			return ActualFont->getFont();

	std::cout << "Error Loading Font : " << Name << std::endl;
}

void RemoveAllFonts()
{
	bool Removed = true;
	while (Removed)
	{
		Removed = false;
		for (Fonts* ActualFont : FontList)
		{
			if (ActualFont->getState() != State::ALL)
			{
				delete ActualFont;
				FontList.remove(ActualFont);
				Removed = true;
				break;
			}
		}
	}
}

void RemoveStateFonts(State _state)
{
	bool Removed = true;
	while (Removed)
	{
		Removed = false;
		for (Fonts* ActualFont : FontList)
		{
			if (ActualFont->getState() == _state && _state != State::ALL)
			{
				delete ActualFont;
				FontList.remove(ActualFont);
				Removed = true;
				break;
			}
		}
	}
}