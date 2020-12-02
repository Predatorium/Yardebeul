#include "Hero.h"
#include "SpriteManager.h"
#include "Controle.h"
#include "Effects_Container.h"

Hero::Hero(Vector2f _position)
{
	if (SpriteList.size() > 0)
	{
		Name = "Francis";
		Niveau = 1;
		Point_de_vie = 20;
		Mana = 50;
		Endurance = 20;
		Santé_mentale = 100;
		Vitesse = 20;
		Point_Capacité = 1;

		Xp_Total = 0;
		Xp_Niveau = 0;
		Next_Niveau = 0;
		Arme = NULL;
		Armure = NULL;
		Argent = 0;
		Time = 0;

		Position = _position;

		for (int i = 0; i < 10; i++)
		{
			if (i == 0)
				Tableau_Niveau[i] = 0;
			else
				Tableau_Niveau[i] = (log(i) * ((double)5 * i) + 5);
		}

		Next_Niveau = Tableau_Niveau[Niveau] - Xp_Niveau;

		Droite = false;
		Gauche = false;
		Bas = false;
		Haut = false;

		Orientation = Direction::Droite;

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

	if (Niveau == 10)
		Resultat_pourcentage = 100;
	
	else
		Resultat_pourcentage = (Xp_Niveau / Next_Niveau) * 100;

	return Resultat_pourcentage;
}

void Hero::Gain_Xp(float _gainxp)
{
	if (Niveau < 10)
	{
		Xp_Niveau += _gainxp;
		Xp_Total += _gainxp;
	}
}

void Hero::Passage_Niveau()
{
	if (Xp_Niveau >= Tableau_Niveau[Niveau] && Niveau < 10)
	{
		while (Xp_Niveau >= Tableau_Niveau[Niveau] && Niveau < 10)
		{
			Xp_Niveau -= Tableau_Niveau[Niveau];
			Niveau++;
			Point_Capacité++;
		}

		if (Niveau >= 10)
		{
			Niveau = 10;
			Xp_Niveau = 0;
			Next_Niveau = 0;
		}
		else
			Next_Niveau = Tableau_Niveau[Niveau] - Xp_Niveau;
	}

	if (Niveau < 10)
	{
		cout << "Experience du niveau actuel "<< Xp_Niveau << "/" << Tableau_Niveau[Niveau] << " xp." << endl;
		cout << "Il reste : " << Next_Niveau << " Xp pour passer au niveau suivant." << endl;
	}
	cout << "Niveau Actuel : " << Get_Niveau() << " ." << endl;
	cout << Pourcentage_Niveau() << " %." << endl << endl;

	system("pause");
}

void Hero::Affectation_Stat(Effect _effet)
{
	if (_effet.Get_Affectation() == Affect_Stat::PV)
		Point_de_vie += _effet.Get_Puissance();

	if (_effet.Get_Affectation() == Affect_Stat::MANA)
		Mana += _effet.Get_Puissance();

	if (_effet.Get_Affectation() == Affect_Stat::SANTE_MENTAL)
		Santé_mentale += _effet.Get_Puissance();

	if (_effet.Get_Affectation() == Affect_Stat::VITESSE)
		Vitesse += _effet.Get_Puissance();

	if (_effet.Get_Affectation() == Affect_Stat::ENDURANCE)
		Endurance += _effet.Get_Puissance();

}

void Hero::Amelioration_stat()
{
	int Choix = 0;
	system("CLS");
	cout << "Tu as " << Point_Capacité << " point de capacite." << endl;
	cout << "Souhaite-tu en depense dans" << endl << "1 : Point de vie" << endl << "2 : Mana" << endl << "3 : Endurance" << endl << "4 : Vitesse" << endl;
	cin >> Choix;

	if (Choix == 1)
	{
		Point_de_vie += 1 * 5;
		Point_Capacité--;
	}
	else if (Choix == 2)
	{
		Mana += 1 * 5;
		Point_Capacité--;
	}
	else if (Choix == 3)
	{
		Endurance += 1 * 3;
		Point_Capacité--;
	}
	else if (Choix == 4)
	{
		Vitesse += 1 * 2;
		Point_Capacité--;
	}
	else
		CinNumberCheck("Fait un effort");
}

void Hero::Update(Vector2i _limitMap)
{
	//Passage_Niveau();
	//Amelioration_stat();
	//static float timer = 0;
	//timer += MainTime.GetTimeDeltaF();
	//float trueTimer = sinf(timer) / 2.f + 0.5f;

	//Position = lerp(Vector2f(50.f, 50.f), Vector2f(100.f, 100.f), trueTimer);
	Time += MainTime.GetTimeDeltaF();

	if (Gauche == true)
	{
		Position.x -= 200 * MainTime.GetTimeDeltaF();
		Orientation = Direction::Gauche;
	}
	if (Droite == true)
	{
		Position.x += 200 * MainTime.GetTimeDeltaF();
		Orientation = Direction::Droite;
	}
	if (Haut == true)
	{
		Position.y -= 200 * MainTime.GetTimeDeltaF();
		Orientation = Direction::Haut;
	}
	if (Bas == true)
	{
		Position.y += 200 * MainTime.GetTimeDeltaF();
		Orientation = Direction::Bas;
	}

	if (Droite == false && Gauche == false && Haut == false && Bas == false)
	{
		if (Orientation == Direction::Droite)
		{
			Beat_Right.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Gauche)
		{
			Beat_Right.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Bas)
		{
			Beat_Down.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Haut)
		{
			Beat_Top.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
		}
	}
	else
	{
		if (Orientation == Direction::Droite)
		{
			Walk_Right.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
			getSprite("Hero").setOrigin(Vector2f(12, 16.5));
		}
		else if (Orientation == Direction::Gauche)
		{
			Walk_Right.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(-1, 1));
			getSprite("Hero").setOrigin(Vector2f(12, 16.5));
		}
		else if (Orientation == Direction::Bas)
		{
			Walk_Down.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
			getSprite("Hero").setOrigin(Vector2f(10.5, 17.5));
		}
		else if (Orientation == Direction::Haut)
		{
			Walk_Top.Animation(getSprite("Hero"));
			getSprite("Hero").setScale(Vector2f(1, 1));
			getSprite("Hero").setOrigin(Vector2f(13, 18));
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Q) && Position.x > Colision_Rect.width)
		Gauche = true;
	else
		Gauche = false;

	if (Keyboard::isKeyPressed(Keyboard::D) && Position.x < (_limitMap.x * Taille_tile) - Colision_Rect.width)
		Droite = true;
	else
		Droite = false;

	if (Keyboard::isKeyPressed(Keyboard::S) && Position.y < ((_limitMap.y - 1) * Taille_tile) - Colision_Rect.height)
		Bas = true;
	else
		Bas = false;

	if (Keyboard::isKeyPressed(Keyboard::Z) && Position.y > Colision_Rect.height / 2)
		Haut = true;
	else
		Haut = false;

	Colision_Rect = IntRect(Vector2i(Position.x, Position.y - Colision_Rect.height), Vector2i(Colision_Rect.width, Colision_Rect.height));
	getSprite("Hero").setPosition(Position);
}

void Hero::Affichage_Type()
{
	cout << "Je suis le Hero" << endl;
}

void Hero::Affichage_Stat()
{
	cout << "Mon nom est : " << Name << endl;
	cout << "Mon niveau est : " << Niveau << endl;
	cout << "Mes pv sont a : " << Point_de_vie << endl;
	cout << "Mon mana est a : " << Mana << endl;
	cout << "Mon endurance est a : " << Endurance << endl;
	cout << "Ma sante mental est a : " << Santé_mentale << endl;
	cout << "Ma vitesse est de : " << Vitesse << endl << endl;

	cout << endl;
	Display_StatFull(*Arme);
}

void Hero::Display()
{
	App.Get_Window().draw(getSprite("Hero"));
}