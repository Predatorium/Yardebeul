#pragma once
#include "Tools.h"
#include "RessourcesManager.h"

class Fonts
{
public:
	Fonts() = default;
	Fonts(string Name, string Path);
	~Fonts() = default;

	string getName() const { return name; };
	Font& getFont() { return font; };

	bool operator == (const Fonts& s) const { return name == s.name; };
	bool operator != (const Fonts& s) const { return !operator==(s); };

private:
	string name;
	Font font;
};

extern list<Fonts*> FontList;

void LoadFont();
Font& getFont(string Name);