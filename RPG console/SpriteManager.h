#pragma once
#include "Tools.h"
#include "StateManager.h"
#include "RessourcesManager.h"

class Sprites
{
public:
	Sprites() { m_state = State::RTNULL; };
	Sprites(string Name, State _state, string Path);
	~Sprites();

	string getName() const { return m_name; };
	State getState() const { return m_state; };
	Sprite& getSprite() { return m_sprite; };
	Texture& getTexture() { return m_texture; };

	bool operator == (const Sprites& s) const { return m_name == s.m_name && m_state == s.m_state; }
	bool operator != (const Sprites& s) const { return !operator==(s); }

private:
	string m_name;
	State m_state;
	Texture m_texture;
	Sprite m_sprite;

};

extern list<Sprites*> SpriteList;

void LoadSprite(State _state);
Sprite& getSprite(string Name);
Texture& getTexture(string Name);
Sprite& SetSmooth(string Name);
void RemoveAllSprites();
void RemoveStateSprites(State _state);