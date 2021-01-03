#include "Hero.h"
#include "SpriteManager.h"
#include "Controle.h"
#include "FontManager.h"
#include "Weapons_Container.h"
#include "Consumables_Container.h"
#include "Armors_Container.h"
#include "Sort_Container.h"

Hero::Hero(Vector2f _position)
	: Character("Hero", 20, 50, 20, 30, Armors.Get_Armor("Armor"), Weapons.Get_Weapon("Epee"))
{
	if (SpriteList.size() > 0)
	{
		Xp_Total = 0;
		Xp_Level = 0;
		Next_Niveau = 0;
		Interaction = false;
		IsInventory = false;
		Time = 0;
		timer = 0;

		Spell.push_back(new Sort(Sorts.Get_Sort("Soin 1")));
		Spell.push_back(new Sort(Sorts.Get_Sort("Immolation 1")));
		Spell.push_back(new Sort(Sorts.Get_Sort("Gel 1")));
		Spell.push_back(new Sort(Sorts.Get_Sort("Choc 1")));

		consumable = new Consumable(Consumables.Get_Consumable("Potion Soin"));
		consumable->Add_Number(4);

		inventory.init();

		Position = _position;

		for (int i = 0; i < 11; i++)
		{
			if (i == 0)
				Tableau_Niveau[i] = 0;
			else
				Tableau_Niveau[i] = (log(i) * ((double)5 * i) + 5);
		}

		Next_Niveau = Tableau_Niveau[Level] - Xp_Level;

		Anim["Walk_Down"] = Animator(IntRect(1805, 21, 23, 35), 6, 0.15f);
		Anim["Walk_Right"] = Animator(IntRect(1805, 57, 24, 33), 6, 0.15f);
		Anim["Walk_Top"] = Animator(IntRect(1805, 91, 26, 36), 6, 0.15f);
		Anim["Beat_Down"] = Animator(IntRect(1589, 21, 25, 32), 8, 0.15f);
		Anim["Beat_Right"] = Animator(IntRect(1589, 54, 23, 31), 8, 0.15f);
		Anim["Beat_Top"] = Animator(IntRect(1589, 86, 24, 32), 8, 0.15f);

		sprite.setPosition(Position);
	}
}

int Hero::Pourcentage_Niveau()
{
	float Resultat_pourcentage = 0;

	if (Level == 10)
		Resultat_pourcentage = 100;
	
	else
		Resultat_pourcentage = ((float)Xp_Level / (float)Next_Niveau) * 100;

	return Resultat_pourcentage;
}

void Hero::Gain_Xp(float _gainxp)
{
	if (Level < 10)
		Xp_Level += _gainxp;

	Passage_Niveau();
}

void Hero::Passage_Niveau()
{
	if (Xp_Level >= Tableau_Niveau[Level] && Level < 10)
	{
		while (Xp_Level >= Tableau_Niveau[Level] && Level < 10)
		{
			Xp_Level -= Tableau_Niveau[Level];
			Level++;
			Amelioration_stat();
		}

		if (Level >= 10)
		{
			Level = 10;
			Xp_Level = 0;
			Next_Niveau = 0;
		}
		else
			Next_Niveau = Tableau_Niveau[Level];
	}
}

void Hero::Amelioration_stat()
{
	Life_Point += 1 * 5;

	Mana += 1 * 5;

	Endurance += 1 * 3;

	Speed += 1 * 2;
}

void Hero::Set_Consumable(Consumable _consomable)
{
	if (consumable->Get_Name() == _consomable.Get_Name())
		consumable->Add_Number(_consomable.Get_Number());
	else
		consumable = new Consumable(_consomable);
}

void Hero::Update()
{
	Time += MainTime.GetTimeDeltaF();
	timer += MainTime.GetTimeDeltaF();

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

	if (Keyboard::isKeyPressed(Keyboard::E) && timer > 0.2f)
	{
		Interaction = true;
		timer = 0;
	}
	else
		Interaction = false;

	if (Keyboard::isKeyPressed(Keyboard::I) && timer > 0.2f)
	{
		IsInventory = !IsInventory;
		inventory.Item_Load();
		timer = 0;
	}

	sprite.setPosition(Position);
}

int Hero::Use_Consumable(Button_Text& _b)
{
	static int power = consumable->Get_Effect().Get_Power();
	Effect_Received(consumable->Get_Effect());
	consumable->Add_Number(-1);

	if (consumable->Get_Number() != 0)
		_b.Set_String(consumable->Get_Name() + " " + to_string(consumable->Get_Number()));

	if (consumable->Get_Number() == 0)
	{
		delete consumable;
		consumable = nullptr;
		_b.Set_String("None");
	}

	return power;
}

void Hero::Display_Fight(Vector2f _scale)
{
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
}

void Hero::Display_HUD()
{
	if (IsInventory == true)
	{
		inventory.Display();
		inventory.Display_CurrentItem(*this);
	}

	if (Level < 10)
	{
		Text Xp("Experience : " + to_string(Xp_Level) + "/" + to_string(Tableau_Niveau[Level]) + " xp.", getFont("Times"), 40);
		Xp.setPosition(0, 40);
		App.Get_Window().draw(Xp);
	}

	Text tLevel("Level Actuel : " + to_string(Level), getFont("Times"), 40);
	tLevel.setPosition(0, 0);
	App.Get_Window().draw(tLevel);

	Box Pourcentage(0, "Times", 20.f, Vector2f(200, 20), 2.f, Vector2f(102, 122), Color::Green);
	Pourcentage.Display(to_string(Pourcentage_Niveau()) + " %.");
	stoi("0");
}

void Hero::Display()
{
	if (Right == false && Left == false && Up == false && Down == false)
	{
		if (Orientation == Direction::Right)
		{
			Anim["Beat_Right"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left)
		{
			Anim["Beat_Right"].Animation(sprite);
			sprite.setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down)
		{
			Anim["Beat_Down"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up)
		{
			Anim["Beat_Top"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
	}
	else
	{
		if (Orientation == Direction::Right)
		{
			Anim["Walk_Right"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left)
		{
			Anim["Walk_Right"].Animation(sprite);
			sprite.setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down)
		{
			Anim["Walk_Down"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up)
		{
			Anim["Walk_Top"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
	}

	App.Get_Window().draw(sprite);
}