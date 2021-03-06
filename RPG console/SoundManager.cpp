#include "SoundManager.h"

std::list<Sounds> SoundList;
std::list<Musics*> MusicList;
int MusicMultip = 100;
int SoundMultip = 100;

void LoadSounds()
{
	for (RessourcesManager& ActualRessource : RessourcesList)
	{
		if (ActualRessource.Get_Type() == RessourceType::SOUNDFX)
		{
			SoundList.push_back(Sounds(ActualRessource.Get_Name(), ActualRessource.Get_Path(), ActualRessource.Get_Sound()));
		}
		else if (ActualRessource.Get_Type() == RessourceType::MUSIC)
		{
			Musics* ConstructMusic = new Musics;
			ConstructMusic->Construct(ActualRessource.Get_Name(), ActualRessource.Get_Path(), ActualRessource.Get_Sound());

			MusicList.push_back(ConstructMusic);
		}
	}
}

Sound& getSound(std::string Name)
{
	for (Sounds& ActualSound : SoundList)
	{
		if (ActualSound.getName() == Name)
		{
			return ActualSound.getSound();
		}
	}
}

sf::Music& getMusic(std::string Name)
{
	for (Musics* ActualMusic : MusicList)
	{
		if (ActualMusic->getName() == Name)
		{
			return ActualMusic->getMusic();
		}
	}
}

void MusicPlayManager()
{

}