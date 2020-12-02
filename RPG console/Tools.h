#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <sstream>
#include <math.h>
#include <vector>
#include <list>
#include "Erreur.h"

#define pi 3.141592653589793238462643383279502884197169399375105820974944592307816406286

using namespace std;
using namespace sf;

class Global
{
private:
	RenderWindow window;
	bool isVSync;
	Event event;

public:
	Global();
	~Global() = default;

	inline RenderWindow& Get_Window() { return window; };
	inline bool Get_Sync() { return isVSync; };
	inline Event& Get_Event() { return event; };

	inline void Set_Sync(bool _bool) { isVSync = _bool; };
};
extern Global App;

enum class Biomes : int
{
	Montagne,
	Caverne,
	Prairie,
	Desert,
};

enum class State_Event : int
{
	Combat,
	Rencontre,
	Rien,
	Environnement,
	Puzzle
};

enum class Element : int
{
	Feu,
	Lave,
	Eau,
	Glace,
	Air,
	Foudre,
	Terre,
	Gravité,
	Neutre
};

static float Affinité[9][9] = {
0.5 ,0.25, 0.5,2   ,1   ,1   ,1   ,1   ,0,
0.75,0.5 , 2  ,1.5 ,0.75,1   ,1.25,1   ,0,
2   ,1.5 ,0.5 ,0.25,1   ,1   ,1   ,1   ,0,
2   ,0.25,0.75,0.5 ,1.25,1   ,1   ,1   ,0,
1.5 ,1.25,1   ,1   ,0.5 ,0.25,0.75,0.5 ,0,
1   ,1   ,1   ,1   ,0.75,0.5 ,0.5 ,1   ,0,
1   ,0.75,1   ,1   ,1.25,2   ,0.5 ,0.25,0,
1   ,1   ,1   ,1   ,2   ,1   ,0.75,0.5 ,0,
0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0
};

class Times
{
public:
	Times() { m_fDeltaTime = 0; };
	~Times() {};

	float GetTimeDeltaF() const { return m_fDeltaTime; };

	Time GetTimeDeltaT() const { return m_tDeltaTime; };

	void RestartClock() { m_tDeltaTime = m_Time.restart(); m_fDeltaTime = m_tDeltaTime.asSeconds(); };

private:
	float m_fDeltaTime;
	Time m_tDeltaTime;
	Clock m_Time;
};
extern Times MainTime;

float Get_Affinité(Element _attaque, Element _defense);
void CinNumberCheck(string _message);

int irandom(int Min, int Max);
double frandom(float Min, float Max);

bool Circle_Collision(Vector2f _pos1, Vector2f _pos2, float _rayon1, float _rayon2);
float Angle_calc(Vector2f pointA, Vector2f pointB);
float Norme(Vector2f _vecteur);
Vector2f lerp(Vector2f a, Vector2f b, float t);

Vector2f getMidle(Sprite& _o);
Vector2f getMidle(RectangleShape& _o);
Vector2f getMidle(Text& _o);