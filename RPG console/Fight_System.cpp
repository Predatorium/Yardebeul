#include "Fight_System.h"
#include "FontManager.h"
#include "SpriteManager.h"
#include "StateManager.h"

Fight_System::Fight_System(Hero _player, Npc* _enemy)
{
	Player = _player;
	Player.Set_Orientation(Direction::Droite);
	getSprite("Hero").setScale(Vector2f(10,10));
	getSprite("Hero").setPosition(200, 700);
	Enemy = _enemy;
	Enemy->Set_Orientation(Direction::Bas);
	getSprite(Enemy->Get_Name()).setPosition(1650, 250);

	timer = 0;
	Selection = 0;

	Menu = RectangleShape(Vector2f(1914, 174));
	Menu.setPosition(Vector2f(3,903));
	Menu.setFillColor(Color(150, 150, 150, 100));
	Menu.setOutlineThickness(3);
	Menu.setOutlineColor(Color(50, 120, 255, 255));

	Pv_Joueur = Box(to_string(Player.Get_HP()), "Times", 50, Vector2f(500, 50), 5, Vector2f(255, 30), Color::Red);
	Pv_Enemy = Box(to_string(Enemy->Get_HP()), "Times", 50, Vector2f(500, 50), 5, Vector2f(1665, 873), Color::Red);

	if (Player.Get_Vitesse() > Enemy->Get_Vitesse())
		Turn_Player = true;
	else
		Turn_Enemy = true;

	PvPerdu = Text("", getFont("Times"), 100);

	Button.push_back(Button_Text("Epee", "Times", 50, Vector2f(100, 50), 3, Vector2f(200, 950), Color(50, 120, 255, 255)));
	Button.push_back(Button_Text("Soin", "Times", 50, Vector2f(100, 50), 3, Vector2f(200, 1020), Color(50, 120, 255, 255)));

	FixView = Views();
}


void Fight_System::Capacity_Select()
{
	int i = 0;
	for (Button_Text& Current_Button : Button)
	{
		if (Selection == i)
			Current_Button.Set_Color(Color::Blue);
		else
			Current_Button.Set_Color(Color(50, 120, 255, 255));

		i++;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && timer > 0.2f)
	{
		Selection--;
		if (Selection < 0)
			Selection = Button.size() - 1;
		timer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && timer > 0.2f)
	{
		Selection++;
		if (Selection >= Button.size())
			Selection = 0;
		timer = 0;
	}
}

void Fight_System::Hud_Update()
{
	Capacity_Select();

	if (Keyboard::isKeyPressed(Keyboard::Enter) && timer > 0.2f)
	{
		if (Selection == 0)
		{
		}
		if (Selection == 1)
		{
		}
		if (Selection == 2)
		{
		}
		if (Selection == 3)
		{
		}
	}
}

void Fight_System::Hud_Display()
{
	App.Get_Window().draw(Menu);

	for (Button_Text& Current_Button : Button)
		Current_Button.Display();


}

void Fight_System::Update()
{
	timer += MainTime.GetTimeDeltaF();

	if (Turn_Enemy == true)
	{
		if (timer > 1.f && PvPerdu.getString() == "")
		{
			int Rand_Damage = irandom(Enemy->Get_MinDamage(), Enemy->Get_MaxDamage());
			PvPerdu.setString(to_string(-Rand_Damage));
			PvPerdu.setPosition(Vector2f(getSprite("Hero").getPosition().x, getSprite("Hero").getPosition().y - 300));
			Player.Get_HP() -= Rand_Damage;
		}
		if (timer > 5.f)
		{
			Turn_Enemy = false;
			Turn_Player = true;
			PvPerdu.setString("");
			timer = 0;
		}
	}
	else if (Turn_Player == true)
	{
		Hud_Update();
		//Enemy->Set_Vie(0);
		//MState.ChangeState(State::GAME);
	}

	Player.Get_BeatRight().Animation(getSprite("Hero"));
	Enemy->Get_BeatDown().Animation(getSprite(Enemy->Get_Name()));
}

void Fight_System::Display()
{
	FixView.Display();

	Player.Display();
	Enemy->Display_Fight(Vector2f(-10,10));

	if (PvPerdu.getString() != "")
		App.Get_Window().draw(PvPerdu);

	Hud_Display();
}