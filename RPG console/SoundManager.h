#pragma once
#include "RessourcesManager.h"

extern int MusicMultip;
extern int SoundMultip;

class Sounds
{
public:
	Sounds(string Name, string Path, float VolumeMultiplier)
	{
		m_name = Name;
		m_volume_multi = VolumeMultiplier;

		if (m_Buffer.loadFromFile(Path))
		{
			m_sound.setBuffer(m_Buffer);	// need to redo it beacause the address is moved when pushback
		}
		else
		{
			cout << "ERROR: sounds : " << m_name << " didn't load" << endl;
		}
	};
	~Sounds() {};

	string getName() const { return m_name; };
	Sound& getSound() { return m_sound; };
	SoundBuffer& getSoundBuffer() { return m_Buffer; };
	void update()
	{
		m_sound.setVolume(SoundMultip * m_volume_multi);
		if (m_sound.getStatus() != Sound::Playing)
			m_sound.setBuffer(m_Buffer);
	};

	bool operator == (const Sounds& s) const { return m_name == s.m_name; }
	bool operator != (const Sounds& s) const { return !operator==(s); }

private:
	string m_name;
	RessourceType m_type;
	SoundBuffer m_Buffer;
	Sound m_sound;
	float m_volume_multi;

};
extern list<Sounds> SoundList;

void LoadSounds();
sf::Sound& getSound(string Name);

class Musics
{
public:
	Musics() { m_volume_multi = 0; };
	~Musics() {};

	string getName() const { return m_name; };
	Music& getMusic() { return m_Music; };
	void update() { m_Music.setVolume(MusicMultip * m_volume_multi); };

	void Construct(string Name, string Path, float VolumeMultiplier)
	{
		m_name = Name;
		m_volume_multi = VolumeMultiplier;

		if (m_Music.openFromFile(Path))
		{
		}
		else
		{
			cout << "ERROR: Music : " << m_name << " didn't load" << endl;
		}
	};

	bool operator == (const Musics& s) const { return m_name == s.m_name; };
	bool operator != (const Musics& s) const { return !operator==(s); };

private:
	string m_name;
	//RessourceType m_type;Sounds
	Music m_Music;
	float m_volume_multi;
};

extern list<Musics*> MusicList;
Music& getMusic(string Name);
void MusicPlayManager();