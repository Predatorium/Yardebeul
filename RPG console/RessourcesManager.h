#pragma once
#include "Tools.h"

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
	RessourceType type;
	string name;
	string path;
	float soundmultiplier;

public:
	RessourcesManager() = default;
	RessourcesManager(RessourceType _type, string _name, string _path, float _soundmultiplier);
	~RessourcesManager() = default;

	inline RessourceType Get_Type() { return type; };
	inline string Get_Name() { return name; };
	inline string Get_Path() { return path; };
	inline float Get_Sound() { return soundmultiplier; };

	inline void Set_Sound(float _soundmultiplier) { soundmultiplier = _soundmultiplier; };
};

extern list<RessourcesManager> RessourcesList;

void RessourcesLoad(string path);