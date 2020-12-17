#include "SpriteManager.h"

Sprites::Sprites(string Name, string Path)
{
	m_name = Name;

	if (!m_texture.loadFromFile(Path))
		cout << "ERROR: Sprite : " << m_name << " didn't load" << endl;
	else
	{
		m_texture.loadFromFile(Path);
		/*m_texture.setSmooth(true);*/
	}
}

std::list<Sprites*> SpriteList;

void LoadSprite()
{
	for (RessourcesManager& ActualRessource : RessourcesList)
		if (ActualRessource.Get_Type() == RessourceType::TEXTURE)
			SpriteList.push_back(new Sprites(ActualRessource.Get_Name(), ActualRessource.Get_Path()));
}

Texture& getTexture(std::string Name)
{
	for (Sprites* ActualSprite : SpriteList)
		if (ActualSprite->getName() == Name)
			return ActualSprite->getTexture();

	std::cout << "Error Loading Texture : " << Name << std::endl;
}