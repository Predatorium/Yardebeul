#pragma once
#include "Tools.h"
#include "RessourcesManager.h"

class Sprites
{
public :
	Sprites() = default;
	Sprites(string Name, string Path);
	~Sprites() = default;

	string getName() const { return m_name; };
	Texture& getTexture() { return m_texture; };

	bool operator ==(const Sprites& s) const { return m_name == s.m_name; }
	bool operator !=(const Sprites& s) const { return m_name != s.m_name; }

private :
	string m_name;
	Texture m_texture;
};

extern list<Sprites*> SpriteList;

void LoadSprite();
Texture& getTexture(string Name);