#pragma once
#include "Tools.h"
#include "StateManager.h"
#include "RessourcesManager.h"

class Fonts
{
public:
	Fonts() { state = State::RTNULL; };
	Fonts(string Name, State _state, string Path);
	~Fonts() = default;

	string getName() const { return name; };
	State getState() const { return state; };
	Font& getFont() { return font; };

	bool operator == (const Fonts& s) const { return name == s.name && state == s.state; };
	bool operator != (const Fonts& s) const { return !operator==(s); };

private:
	string name;
	State state;
	Font font;
};

extern list<Fonts*> FontList;

void LoadFont(State _state);
Font& getFont(string Name);
void RemoveAllFonts();
void RemoveStateFonts(State _state);