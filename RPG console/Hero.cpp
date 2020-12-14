#include "Hero.h"
#include "SpriteManager.h"
#include "Controle.h"
#include "Effects_Container.h"
#include "Weapons_Container.h"

Hero::Hero(Vector2f _position)
{
	if (SpriteList.size() > 0)
	{
		Name = "Francis";
		Level = 1;
		Life_Point = 20;
		Mana = 50;
		Endurance = 20;
		Mental_Health = 100;
		Speed = 30;
		Capacity_Point = 1;
		Life_Max = Life_Point;

		Xp_Total = 0;
		Xp_Level = 0;
		Next_Niveau = 0;
		weapon = new Weapon(Weapons.Get_Weapon("Epee de feu"));
		inventory = Inventory();
		IsInventory = false;
		Time = 0;
		timer = 0;

		Position = _position;

		for (int i = 0; i < 11; i++)
		{
			if (i == 0)
				Tableau_Niveau[i] = 0;
			else
				Tableau_Niveau[i] = (log(i) * ((double)5 * i) + 5);
		}

		Next_Niveau = Tableau_Niveau[Level] - Xp_Level;

		Right = false;
		Left = false;
		Down = false;
		Up = false;
		Interaction = false;

		Orientation = Direction::Right;

		Walk_Down = Animator(IntRect(331, 21, 23, 35), 6, 0.15f);
		Walk_Right = Animator(IntRect(331, 57, 24, 33), 6, 0.15f);
		Walk_Top = Animator(IntRect(331, 91, 26, 36), 6, 0.15f);

		Beat_Down = Animator(IntRect(116, 21, 25, 32), 8, 0.15f);
		Beat_Right = Animator(IntRect(115, 54, 23, 31), 8, 0.15f);
		Beat_Top = Animator(IntRect(115, 86, 24, 32), 8, 0.15f);

		Walk_Right.Animation(getSprite("Hero"));
		getSprite("Hero").setOrigin(Vector2f(12, 16.5));
		getSprite("Hero").setTextureRect(IntRect(115, 54, 23, 31));

		Colision_Rect = IntRect(0, 0, 26, 18);
	}
}

int Hero::Pourcentage_Niveau()
{
	float Resultat_pourcentage = 0;

	if (Level == 10)
		Resultat_pourcentage = 100;
	
	else
		Resultat_pourcentage = (Xp_Level / Next_Niveau) * 100;

	return Resultat_pourcentage;
}

void Hero::Gain_Xp(float _gainxp)
{
	if (Level < 10)
	{
		Xp_Level += _gainxp;
		Xp_Total += _gainxp;
	}
}

void Hero::Passage_Niveau()
{
	if (Xp_Level >= Tableau_Niveau[Level] && Level < 10)
	{
		while (Xp_Level >= Tableau_Niveau[Level] && Level < 10)
		{
			Xp_Level -= Tableau_Niveau[Level];
			Level++;
			Capacity_Point++;
		}

		if (Level >= 10)
		{
			Level = 10;
			Xp_Level = 0;
			Next_Niveau = 0;
		}
		else
			Next_Niveau = Tableau_Niveau[Level] - Xp_Level;
	}

	if (Level < 10)
	{
		cout << "Experience du niveau actuel "<< Xp_Level << "/" << Tableau_Niveau[Level] << " xp." << endl;
		cout << "Il reste : " << Next_Niveau << " Xp pour passer au niveau suivant." << endl;
	}
	cout << "Level Actuel : " << Get_Level() << " ." << endl;
	cout << Pourcentage_Niveau() << " %." << endl << endl;

	system("pause");
}

void Hero::Affectation_Stat(Effect _effet)
{
	if (_effet.Get_Affectation() == Affect_Stat::LIFE_POINT)
		Life_Point += _effet.Get_Power();

	if (_effet.Get_Affectation() == Affect_Stat::MANA)
		Mana += _effet.Get_Power();

	if (_effet.Get_Affectation() == Affect_Stat::MENTAL_HEALTH)
		Mental_Health += _effet.Get_Power();

	if (_effet.Get_Affectation() == Affect_Stat::SPEED)
		Speed += _effet.Get_Power();

	if (_effet.Get_Affectation() == Affect_Stat::ENDURANCE)
		Endurance += _effet.Get_Power();

}

void Hero::Amelioration_stat()
{
	int Choix = 0;
	system("CLS");
	cout << "Tu as " << Capacity_Point << " point de capacite." << endl;
	cout << "Souhaite-tu en depense dans" << endl << "1 : Point de vie" << endl << "2 : Mana" << endl << "3 : Endurance" << endl << "4 : Speed" << endl;
	cin >> Choix;

	if (Choix == 1)
	{
		Life_Point += 1 * 5;
		Capacity_Point--;
	}
	else if (Choix == 2)
	{
		Mana += 1 * 5;
		Capacity_Point--;
	}
	else if (Choix == 3)
	{
		Endurance += 1 * 3;
		Capacity_Point--;
	}
	else if (Choix == 4)
	{
		Speed += 1 * 2;
		Capacity_Point--;
	}
	else
		CinNumberCheck("Fait un effort");
}

Consumable* Hero::Get_OneConsumable(int _select)
{
	int i = 0;
	for (Consumable* Current : consumable)
	{
		if (i == _select)
			return Current;
		i++;
	}
}

void Hero::Update()
{
	Time += MainTime.GetTimeDeltaF();
	timer += MainTime.GetTimeDeltaF();
	//Passage_Niveau();
	//Amelioration_stat();

	if (Left == true)
	{
		Position.x -= 200 * MainTime.GetTimeDeltaF();
		Orientation = Direction::Left;
	}
	if (Right == true)
	{
		Position.x += 200 * MainTime.GetTimeDeltaF();
		Orientation = Direction::Right;
	}
	if (Up == true)
	{
		Position.y -= 200 * MainTime.GetTimeDeltaF();
		Orientation = Direction::Up;
	}
	if (Down == true)
	{
		Position.y += 200 * MainTime.GetTimeDeltaF();
		Orientation = Direction::Down;
	}

	if (Keyboard::isKeyPressed(Keyboard::Q))
		Left = true;
	else
		Left = false;

	if (Keyboard::isKeyPressed(Keyboard::D))
		Right = true;
	else
		Right = false;

	if (Keyboard::isKeyPressed(Keyboard::S))
		Down = true;
	else
		Down = false;

	if (Keyboard::isKeyPressed(Keyboard::Z))
		Up = true;
	else
		Up = false;

	if (Keyboard::isKeyPressed(Keyboard::E))
		Interaction = true;
	else
		Interaction = false;

	if (Keyboard::isKeyPressed(Keyboard::I) && timer > 0.2f)
	{
		IsInventory = !IsInventory;
		timer = 0;
	}

	Colision_Rect = IntRect(Vector2i(Position.x, Position.y - Colision_Rect.height), Vector2i(Colision_Rect.width, Colision_Rect.height));
	getSprite("Hero").setPosition(Position);
}

void Hero::Display_Fight(Vector2f _scale)
{
	getSprite("Hero").setScale(_scale);
	App.Get_Window().draw(getSprite("Hero"));
}

void Hero::Display()
{
	if (Right == false && Left == false && Up == false && Down == false)
	{
		if (Orientation == Direction::Right)
		{
			Beat_Right.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left)
		{
			Beat_Right.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down)
		{
			Beat_Down.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up)
		{
			Beat_Top.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
		}
	}
	else
	{
		if (Orientation == Direction::Right)
		{
			Walk_Right.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
			getSprite("Hero").setOrigin(Vector2f(12, 16.5));
		}
		else if (Orientation == Direction::Left)
		{
			Walk_Right.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(-1, 1));
			getSprite("Hero").setOrigin(Vector2f(12, 16.5));
		}
		else if (Orientation == Direction::Down)
		{
			Walk_Down.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
			getSprite("Hero").setOrigin(Vector2f(10.5, 17.5));
		}
		else if (Orientation == Direction::Up)
		{
			Walk_Top.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
			getSprite("Hero").setOrigin(Vector2f(13, 18));
		}
	}

	App.Get_Window().draw(getSprite("Hero"));
}