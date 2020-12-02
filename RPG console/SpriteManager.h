#pragma once
#include "Tools.h"
#include "RessourcesManager.h"

class Sprites
{
public:
	Sprites() = default;
	Sprites(string Name, string Path);
	~Sprites() = default;

	string getName() const { return m_name; };
	Sprite& getSprite() { return m_sprite; };
	Texture& getTexture() { return m_texture; };

	bool operator == (const Sprites& s) const { return m_name == s.m_name; }
	bool operator != (const Sprites& s) const { return !operator==(s); }

private:
	string m_name;
	Texture m_texture;
	Sprite m_sprite;
};

extern list<Sprites*> SpriteList;

void LoadSprite();
Sprite& getSprite(string Name);
Texture& getTexture(string Name);
Sprite& SetSmooth(string Name);