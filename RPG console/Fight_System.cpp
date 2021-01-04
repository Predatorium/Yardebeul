#include "Fight_System.h"
#include "FontManager.h"
#include "SpriteManager.h"
#include "StateManager.h"

Fight_System::Fight_System(Hero* _player, Npc* _enemy, Game_State _state)
	: sprite(getTexture("Fight"))
{
	Player = _player;
	Player->Set_Orientation(Direction::Right);
	Player->Get_Sprite().setPosition(200, 700);
	Enemy = _enemy;
	Enemy->Set_Orientation(Direction::Down);
	Enemy->Get_Sprite().setPosition(1650, 250);
	Previous_state = _state;
	etape = Etape::Attack;
	timer = 0;
	Selection = 0;

	Menu = RectangleShape(Vector2f(1914, 174));
	Menu.setPosition(Vector2f(3,903));
	Menu.setFillColor(Color(150, 150, 150, 100));
	Menu.setOutlineThickness(3);
	Menu.setOutlineColor(Color(50, 120, 255, 255));

	Pv_Joueur = Box(Player->Get_LifeMax(), "Times", 50, Vector2f(500, 50), 5, Vector2f(255, 30), Color::Red);
	Pv_Enemy = Box(Enemy->Get_LifeMax(), "Times", 50, Vector2f(500, 50), 5, Vector2f(1665, 873), Color::Red);

	if (Player->Get_Speed() > Enemy->Get_Speed())
	{
		Turn_Player = Etat::IsMyTurn;
		Turn_Enemy = Etat::WaitMyTurn;
	}
	else
	{
		Turn_Player = Etat::WaitMyTurn;
		Turn_Enemy = Etat::IsMyTurn;
	}

	Texte = Text("", getFont("Times"), 100);
	Button.push_back(Button_Text(Player->Get_Weapon()->Get_Name().substr(0, Player->Get_Weapon()->Get_Name().find(" ")), "Times", 50, Vector2f(300, 50), 3, Vector2f(200, 950), Color(50, 120, 255, 255)));
	if (Player->Get_Consumable() != nullptr)
	{
		Button.push_back(Button_Text(Player->Get_Consumable()->Get_Name(), "Times", 50, Vector2f(300, 50), 3, Vector2f(200, 1010), Color(50, 120, 255, 255)));
		Button.back().Set_String(Player->Get_Consumable()->Get_Name() + " " + to_string(Player->Get_Consumable()->Get_Number()));
	}
	else
		Button.push_back(Button_Text("None", "Times", 50, Vector2f(300, 50), 3, Vector2f(200, 1010), Color(50, 120, 255, 255)));

	Button.push_back(Button_Text(Player->Get_OneSpell(1)->Get_Name(), "Times", 50, Vector2f(300, 50), 3, Vector2f(600, 950), Color(50, 120, 255, 255)));
	Button.push_back(Button_Text(Player->Get_OneSpell(2)->Get_Name(), "Times", 50, Vector2f(300, 50), 3, Vector2f(600, 1010), Color(50, 120, 255, 255)));
	Button.push_back(Button_Text(Player->Get_OneSpell(3)->Get_Name(), "Times", 50, Vector2f(300, 50), 3, Vector2f(1000, 950), Color(50, 120, 255, 255)));
	Button.push_back(Button_Text(Player->Get_OneSpell(4)->Get_Name(), "Times", 50, Vector2f(300, 50), 3, Vector2f(1000, 1010), Color(50, 120, 255, 255)));
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
			int Damage = Player->Attack(Enemy);
			Texte.setString(to_string(-Damage));
			Texte.setPosition(Vector2f(Pv_Enemy.Get_Shape().getPosition().x, Pv_Enemy.Get_Shape().getPosition().y - 140));
		}
		if (Selection == 1 && Player->Get_Consumable() != nullptr)
		{
			int Heal = 0;
			for (Button_Text& Current : Button)
				if (Current.Get_Name() == Player->Get_Consumable()->Get_Name())
				{
					Heal = Player->Use_Consumable(Current);
					break;
				}

			Texte.setString("+" + to_string(Heal));
			Texte.setPosition(Vector2f(Pv_Joueur.Get_Shape().getPosition().x, Pv_Joueur.Get_Shape().getPosition().y + 20));
		}
		if (Selection == 2)
		{
			pair<string, int> Damage = Player->Use_Spell(Enemy, *Player->Get_OneSpell(1));
			if (Damage.first == "Damage")
			{
				Texte.setString(to_string(-Damage.second));
				Texte.setPosition(Vector2f(Pv_Enemy.Get_Shape().getPosition().x, Pv_Enemy.Get_Shape().getPosition().y - 140));
			}
			if (Damage.first == "Buff")
			{
				Texte.setString("+" + to_string(Damage.second));
				Texte.setPosition(Vector2f(Pv_Joueur.Get_Shape().getPosition().x, Pv_Joueur.Get_Shape().getPosition().y + 20));
			}
		}
		if (Selection == 3)
		{
			pair<string, int> Damage = Player->Use_Spell(Enemy, *Player->Get_OneSpell(2));
			if (Damage.first == "Damage")
			{
				Texte.setString(to_string(-Damage.second));
				Texte.setPosition(Vector2f(Pv_Enemy.Get_Shape().getPosition().x, Pv_Enemy.Get_Shape().getPosition().y - 140));
			}
			if (Damage.first == "Buff")
			{
				Texte.setString("+" + to_string(Damage.second));
				Texte.setPosition(Vector2f(Pv_Joueur.Get_Shape().getPosition().x, Pv_Joueur.Get_Shape().getPosition().y + 20));
			}
		}
		if (Selection == 4)
		{
			pair<string, int> Damage = Player->Use_Spell(Enemy, *Player->Get_OneSpell(3));
			if (Damage.first == "Damage")
			{
				Texte.setString(to_string(-Damage.second));
				Texte.setPosition(Vector2f(Pv_Enemy.Get_Shape().getPosition().x, Pv_Enemy.Get_Shape().getPosition().y - 140));
			}
			if (Damage.first == "Buff")
			{
				Texte.setString("+" + to_string(Damage.second));
				Texte.setPosition(Vector2f(Pv_Joueur.Get_Shape().getPosition().x, Pv_Joueur.Get_Shape().getPosition().y + 20));
			}
		}
		if (Selection == 5)
		{
			pair<string, int> Damage = Player->Use_Spell(Enemy, *Player->Get_OneSpell(4));
			if (Damage.first == "Damage")
			{
				Texte.setString(to_string(-Damage.second));
				Texte.setPosition(Vector2f(Pv_Enemy.Get_Shape().getPosition().x, Pv_Enemy.Get_Shape().getPosition().y - 140));
			}
			if (Damage.first == "Buff")
			{
				Texte.setString("+" + to_string(Damage.second));
				Texte.setPosition(Vector2f(Pv_Joueur.Get_Shape().getPosition().x, Pv_Joueur.Get_Shape().getPosition().y + 20));
			}
		}

		etape = Etape::AfDamage;
		Turn_Player = Etat::Finish;
		timer = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Numpad1))
		Player->Add_Life(50);
}

void Fight_System::Hud_Display()
{
	App.Get_Window().draw(Menu);

	for (Button_Text& Current_Button : Button)
		Current_Button.Display();

	Pv_Joueur.Display(to_string(Player->Get_LifePoint()) + "/");
	Pv_Enemy.Display(to_string(Enemy->Get_LifePoint()) + "/");
}

void Fight_System::Update()
{
	static map<string, int> tmp;
	timer += MainTime.GetTimeDeltaF();

	if (etape == Etape::Attack)
	{
		if (Turn_Enemy == Etat::IsMyTurn)
		{
			if (Enemy->Get_LifePoint() <= 0)
			{
				Game_Manager::Get_Singleton().state = Previous_state;
				Player->Gain_Xp(3 * Enemy->Get_Level());
			}

			int Damage = Enemy->Attack(Player);
			Texte.setString(to_string(-Damage));
			Texte.setPosition(Vector2f(Pv_Joueur.Get_Shape().getPosition().x, Pv_Joueur.Get_Shape().getPosition().y + 20));

			etape = Etape::AfDamage;
			Turn_Enemy = Etat::Finish;
		}
		else if (Turn_Player == Etat::IsMyTurn)
		{
			if (Player->Get_LifePoint() <= 0)
			{
				Game_Manager::Get_Singleton().ChangeState(Game_State::WORLD);
				StateManager::Get_Singleton().ChangeState(State::MENU);
			}

			if (Texte.getString() == "")
				Hud_Update();
		}
	}

	if (etape == Etape::AfDamage && timer > 2.f)
	{
		if (Turn_Player == Etat::Finish && Turn_Enemy == Etat::Finish)
		{
			if (Player->Get_Speed() > Enemy->Get_Speed())
			{
				Turn_Player = Etat::IsMyTurn;
				Turn_Enemy = Etat::WaitMyTurn;
				tmp = Player->Effect_Update();
				Texte.setPosition(Vector2f(Pv_Joueur.Get_Shape().getPosition().x, Pv_Joueur.Get_Shape().getPosition().y + 20));
			}
			else
			{
				Turn_Player = Etat::WaitMyTurn;
				Turn_Enemy = Etat::IsMyTurn;
				tmp = Enemy->Effect_Update();
				Texte.setPosition(Vector2f(Pv_Enemy.Get_Shape().getPosition().x, Pv_Enemy.Get_Shape().getPosition().y - 140));
			}

			Texte.setString("");
			Player->Reset_Speed();
			Enemy->Reset_Speed();
		}
		else if (Turn_Enemy == Etat::Finish && Turn_Player == Etat::WaitMyTurn)
		{
			Turn_Player = Etat::IsMyTurn;
			tmp = Player->Effect_Update();
			Texte.setPosition(Vector2f(Pv_Joueur.Get_Shape().getPosition().x, Pv_Joueur.Get_Shape().getPosition().y + 20));
			Texte.setString("");
		}
		else if (Turn_Player == Etat::Finish && Turn_Enemy == Etat::WaitMyTurn)
		{
			Turn_Enemy = Etat::IsMyTurn;
			tmp = Enemy->Effect_Update();
			Texte.setPosition(Vector2f(Pv_Enemy.Get_Shape().getPosition().x, Pv_Enemy.Get_Shape().getPosition().y - 140));
			Texte.setString("");
		}

		etape = Etape::AfEffect;
		timer = 0;
	}

	if (etape == Etape::AfEffect)
	{
		static int Current_stats = 0;
		int i = 0;
		for (pair<string, int> Current : tmp)
		{
			if (i == Current_stats)
			{
				if (Current.second != 0)
				{
					Texte.setString("-" + to_string(Current.second));
					if (Current.first == "Pv")
						Texte.setFillColor(Color::Red);
					if (Current.first == "Mana")
						Texte.setFillColor(Color::Blue);
					if (Current.first == "Speed")
						Texte.setFillColor(Color::White);
					if (Current.first == "Endurance")
						Texte.setFillColor(Color::Yellow);
					break;
				}
				else
					Current_stats++;
			}

			i++;
		}

		if (timer > 1.f)
		{
			if (Current_stats < tmp.size())
				Current_stats++;
			else
			{
				Texte.setString("");
				etape = Etape::Attack;
				Texte.setFillColor(Color::White);
				Current_stats = 0;
			}
			timer = 0;
		}
	}
}

void Fight_System::Display()
{
	Player->Get_Anim("Beat_Right").Animation(Player->Get_Sprite());
	Enemy->Get_Anim("Beat_Down").Animation(Enemy->Get_Sprite());

	App.Get_Window().setView(App.Get_Window().getDefaultView());

	App.Get_Window().draw(sprite);

	Player->Display_Fight(Vector2f(10, 10));
	Enemy->Display_Fight(Vector2f(-10,10));

	if (Texte.getString() != "")
		App.Get_Window().draw(Texte);

	Hud_Display();
}