#include "SpriteManager.h"

Sprites::Sprites(string Name, State _state, string Path)
{
	m_name = Name;
	m_state = _state;

	if (m_texture.loadFromFile(Path))
		m_sprite.setTexture(m_texture);
	else
		cout << "ERROR: Sprite : " << m_name << " didn't load" << endl;
}

Sprites::~Sprites()
{
}

std::list<Sprites*> SpriteList;

void LoadSprite(State _state)
{
	for (RessourcesManager& ActualRessource : RessourcesList)
		if (ActualRessource.Get_state() == _state)
			if (ActualRessource.Get_Type() == RessourceType::TEXTURE)
				SpriteList.push_back(new Sprites(ActualRessource.Get_Name(), ActualRessource.Get_state(), ActualRessource.Get_Path()));
}

Sprite& getSprite(std::string Name)
{
	for (Sprites* ActualSprite : SpriteList)
	{
		if (ActualSprite->getName() == Name)
		{
			return ActualSprite->getSprite();
		}
	}
	std::cout << "Error Loading Sprite : " << Name << std::endl;
}

Texture& getTexture(std::string Name)
{
	for (Sprites* ActualSprite : SpriteList)
		if (ActualSprite->getName() == Name)
			return ActualSprite->getTexture();

	std::cout << "Error Loading Texture : " << Name << std::endl;
}

Sprite& SetSmooth(string Name)
{
	for (Sprites* ActualSprite : SpriteList)
	{
		if (ActualSprite->getName() == Name)
		{
			ActualSprite->getTexture().setSmooth(true);
			ActualSprite->getSprite().setTexture(ActualSprite->getTexture());
			return ActualSprite->getSprite();
		}
	}
}

void RemoveStateSprites(State _state)
{
	bool Removed = true;
	while (Removed)
	{
		Removed = false;
		for (Sprites* ActualSprite : SpriteList)
		{
			if (ActualSprite->getState() == _state && _state != State::ALL)
			{
				delete ActualSprite;
				SpriteList.remove(ActualSprite);
				Removed = true;
				break;
			}
		}
	}
}

void RemoveAllSprites()
{
	bool Removed = true;
	while (Removed)
	{
		Removed = false;
		for (Sprites* ActualSprite : SpriteList)
		{
			if (ActualSprite->getState() != State::ALL)
			{
				delete ActualSprite;
				SpriteList.remove(ActualSprite);
				Removed = true;
				break;
			}
		}
	}
}