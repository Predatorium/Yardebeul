#include "SpriteManager.h"

Sprites::Sprites(string Name, string Path)
{
	m_name = Name;

	if (m_texture.loadFromFile(Path))
		m_sprite.setTexture(m_texture);
	else
		cout << "ERROR: Sprite : " << m_name << " didn't load" << endl;
}

std::list<Sprites*> SpriteList;

void LoadSprite()
{
	for (RessourcesManager& ActualRessource : RessourcesList)
		if (ActualRessource.Get_Type() == RessourceType::TEXTURE)
			SpriteList.push_back(new Sprites(ActualRessource.Get_Name(), ActualRessource.Get_Path()));
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