#include "Tools.h"

Times MainTime;

Global::Global()
{
	window.create(VideoMode(1920, 1080), "Projet RPG", Style::Fullscreen);
	isVSync = true;
	event;

	/*window.setVerticalSyncEnabled(isVSync);*/
}

float Get_Affinité(Element _attaque, Element _defense)
{
	return Affinité[(int)_attaque][(int)_defense];
}

void CinNumberCheck(string _message)
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << _message << endl;
	system("pause");
}

int irandom(int Min, int Max)
{
	return rand() % (Max) + Min;
}

double frandom(float Min, float Max)
{
	return ((rand() / (double)RAND_MAX) * ((double)Max - (double)Min) + (double)Min);
}

bool Circle_Collision(Vector2f Pos1, Vector2f Pos2, float Rayon1, float Rayon2)
{
	if (sqrt(pow(Pos1.x - Pos2.x, 2) + pow(Pos1.y - Pos2.y, 2)) < Rayon1 + Rayon2)
	{
		return true;
	}
	else return false;
}

float Angle_calc(Vector2f pointA, Vector2f pointB)
{
	float angle;


	if (pointA.y < pointB.y)
		angle = (float)acos(((double)pointB.x - pointA.x) / (sqrt(pow((double)pointB.x - pointA.x, 2) + pow((double)pointB.y - pointA.y, 2))));
	else
		angle = (float)-acos(((double)pointB.x - pointA.x) / (sqrt(pow((double)pointB.x - pointA.x, 2) + pow((double)pointB.y - pointA.y, 2))));

	return angle;
}

Vector2f lerp(Vector2f a, Vector2f b, float t)
{
	return (b - a) * t + a ;
}

Vector2f getMidle(Sprite& _o)
{
	return Vector2f(_o.getLocalBounds().width / 2, _o.getLocalBounds().height / 2);
}

Vector2f getMidle(RectangleShape& _o)
{
	return Vector2f(_o.getGlobalBounds().width / 2, _o.getGlobalBounds().height / 2);
}

Vector2f getMidle(Text& _o)
{
	return Vector2f(_o.getLocalBounds().left + _o.getLocalBounds().width / 2, _o.getLocalBounds().top + _o.getLocalBounds().height / 2);
}

float Norme(Vector2f _vecteur)
{
	return sqrt((pow(_vecteur.x, 2) + pow(_vecteur.y, 2)));
}

Vector2f normalisation(Vector2f pos1, Vector2f pos2)
{
	Vector2f pos;
	Vector2f dir;
	float norme;

	pos.x = pos2.x + pos1.x;
	pos.y = pos2.y + pos1.y;

	dir.x = pos.x / Norme(pos);
	dir.y = pos.y / Norme(pos);

	return dir;
}