#pragma once
#include "Tools.h"
#include "StateManager.h"

enum class RessourceType
{
	UNKNOWN,
	TEXTURE,
	SOUNDFX,
	MUSIC,
	FONT,
	LANG,
	MAP,
};

class RessourcesManager
{
private:
	State state;
	RessourceType type;
	string name;
	string path;
	float soundmultiplier;

public:
	RessourcesManager() = default;
	RessourcesManager(State _state, RessourceType _type, string _name, string _path, float _soundmultiplier);
	~RessourcesManager() = default;

	inline State Get_state() { return state; };
	inline RessourceType Get_Type() { return type; };
	inline string Get_Name() { return name; };
	inline string Get_Path() { return path; };
	inline float Get_Sound() { return soundmultiplier; };

	inline void Set_Sound(float _soundmultiplier) { soundmultiplier = _soundmultiplier; };
};

extern list<RessourcesManager> RessourcesList;

void RessourcesLoad(string path);