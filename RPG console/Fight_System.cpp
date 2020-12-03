#include "Fight_System.h"
#include "FontManager.h"
#include "SpriteManager.h"

Fight_System::Fight_System(Hero _player, Npc _enemy)
{
	Player = _player;
	Player.Set_Orientation(Direction::Droite);
	getSprite("Hero").setScale(Vector2f(10,10));
	getSprite("Hero").setPosition(500, 800);
	Enemy = _enemy;
	Enemy.Set_Orientation(Direction::Bas);
	getSprite(Enemy.Get_Name()).setPosition(1500, 250);

	//if (Player.Get_Vitesse() > Enemy.Get_Vitesse())
	//	Turn_Player = true;
	//else
	Turn_Player = false;
		Turn_Enemy = true;

	PvPerdu = Text("", getFont("Times"));

	Button.push_back(Bouton("Epee", "Times", 50, Vector2f(100, 50), 3, Vector2f(20, 950), Color(50, 120, 255, 255)));

	FixView = Views();
}

void Fight_System::Update()
{
	timer += MainTime.GetTimeDeltaF();

	if (Turn_Enemy == true)
	{

		if (timer > 1.f)
		{
			int Rand_Damage = irandom(Enemy.Get_MinDamage(), Enemy.Get_MaxDamage());
			PvPerdu.setString(to_string(-Rand_Damage));
			PvPerdu.setPosition(Vector2f(100, 400));
			Player.Get_Vie() -= Rand_Damage;

			if (timer > 1.5f)
			{
				Turn_Enemy = false;
				Turn_Player = true;
				PvPerdu.setString("");
				timer = 0;
			}
		}
	}
	else if (Turn_Player == true)
	{

	}

	Player.Get_BeatRight().Animation(getSprite("Hero"));
	Enemy.Get_BeatDown().Animation(getSprite(Enemy.Get_Name()));
}

void Fight_System::Display()
{
	FixView.Display();

	for (Bouton& Current_Button : Button)
		Current_Button.Display();

	if (PvPerdu.getString() != "")
		App.Get_Window().draw(PvPerdu);

	Player.Display();
	Enemy.Display_Fight(Vector2f(-10,10));
}