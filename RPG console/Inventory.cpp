#include "Inventory.h"
#include "FontManager.h"
#include "SpriteManager.h"
#include "Sort_Container.h"
#include "Hero.h"

void Inventory::init()
{
	timer = 0;
	Current_Item = 1;

	Invent = RectangleShape(Vector2f(800, 600));
	Invent.setFillColor(Color(200, 200, 200, 255));
	Invent.setOutlineThickness(5);
	Invent.setOutlineColor(Color::Black);
	Invent.setOrigin(getMidle(Invent));
	Invent.setPosition(960, 540);

	Encadré = RectangleShape(Vector2f(50, 60));
	Encadré.setOrigin(getMidle(Encadré));
	Encadré.setFillColor(Color::Transparent);
	Encadré.setOutlineThickness(2);
	Encadré.setOutlineColor(Color::Black);

	for (Sort Current : Sorts.Get_Container())
		Spell.push_back(new Sort(Current));

	Title = Text("Inventory", getFont("Times"), 50);
	Title.setOrigin(getMidle(Title));
	Title.setPosition(Invent.getPosition().x, Invent.getPosition().y - 280);
	Title.setFillColor(Color(255, 120, 50, 255));

	Current_MenuSub = 0;
	Sub_Menu.push_back(Button_Text("Equipement", "Times", 30, Vector2f(200, 30), 2, Vector2f(Invent.getPosition().x - 250, Invent.getPosition().y - 120), Color(255, 120, 50, 255)));
	Sub_Menu.push_back(Button_Text("Spell", "Times", 30, Vector2f(200, 30), 2, Vector2f(Invent.getPosition().x + 250, Invent.getPosition().y - 120), Color(50, 120, 255, 255)));

	Item_Load();
}

void Inventory::Add_Consumable(Consumable _consomable)
{
	bool find = false;
	for (Consumable* Current : consumable)
		if (Current->Get_Name() == _consomable.Get_Name())
		{
			Current->Add_Number(_consomable.Get_Number());
			find = true;
		}

	if(find == false)
		consumable.push_back(new Consumable(_consomable));
}

void Inventory::Item_Load()
{
	int x = 0;
	int y = 0;
	if (Current_MenuSub == 0)
	{
		for (Weapon* Current : weapon)
		{
			Current->Set_Position(Vector2f(Invent.getPosition().x - 370 + (x * 55), Invent.getPosition().y - 67.5 + (y * 65)));
			x++;
			if (x == 8)
			{
				x = 0;
				y++;
			}
		}
		for (Armor* Current : armor)
		{
			Current->Set_Position(Vector2f(Invent.getPosition().x - 370 + (x * 55), Invent.getPosition().y - 67.5 + (y * 65)));
			x++;
			if (x == 8)
			{
				x = 0;
				y++;
			}
		}
		for (Consumable* Current : consumable)
		{
			Current->Set_Position(Vector2f(Invent.getPosition().x - 370 + (x * 55), Invent.getPosition().y - 67.5 + (y * 65)));
			x++;
			if (x == 8)
			{
				x = 0;
				y++;
			}
		}
	}

	int i = 0;
	for (Button_Text& Current : Sub_Menu)
	{
		if (Current_MenuSub == i)
			Current.Set_Color(Color(255, 120, 50, 255));
		else
			Current.Set_Color(Color(50, 120, 255, 255));
		i++;
	}
}

void Inventory::Update(Hero& _player)
{
	timer += MainTime.GetTimeDeltaF();

	if (Keyboard::isKeyPressed(Keyboard::Tab) && timer > 0.2f)
	{
		Current_MenuSub++;
		if (Current_MenuSub >= 2)
			Current_MenuSub = 0;

		Current_Item = 1;

		Item_Load();
		timer = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) && timer > 0.2f)
	{
		Current_Item++;
		if (Current_MenuSub == 0)
			if (Current_Item > weapon.size() + armor.size() + consumable.size())
				Current_Item = 1;

		if (Current_MenuSub == 1)
			if (Current_Item > Spell.size())
				Current_Item = 1;

		timer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && timer > 0.2f)
	{
		Current_Item--;
		if (Current_MenuSub == 0)
			if (Current_Item < 1)
			{
				if (weapon.size() + armor.size() + consumable.size() > 0)
					Current_Item = weapon.size() + armor.size() + consumable.size();
				else
					Current_Item = 1;
			}

		if (Current_MenuSub == 1)
			if (Current_Item < 1)
			{
				if (Spell.size() > 0)
					Current_Item = Spell.size();
				else
					Current_Item = 1;
			}

		timer = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && timer > 0.2f)
	{
		Current_Item -= 8;
		if (Current_MenuSub == 0)
			if (Current_Item < 1)
				Current_Item = 1;

		if (Current_MenuSub == 1)
			if (Current_Item < 1)
				Current_Item = 1;

		timer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && timer > 0.2f)
	{
		Current_Item += 8;
		if (Current_MenuSub == 0)
			if (Current_Item > weapon.size() + armor.size() + consumable.size())
				Current_Item = weapon.size() + armor.size() + consumable.size();

		if (Current_MenuSub == 1)
			if (Current_Item > Spell.size())
				Current_Item = Spell.size();

		timer = 0;
	}

	if (Current_MenuSub == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::Enter) && timer > 0.2f)
		{
			if (Current_Item > 0 && Current_Item <= weapon.size())
			{
				int i = 1;
				for (Weapon* Current : weapon)
				{
					if (i == Current_Item)
					{
						Weapon *tmp = _player.Get_Weapon();
						_player.Set_Weapon(*Current);
						*Current = *tmp;
						break;
					}
					i++;
				}
			}
			if (Current_Item > weapon.size() && Current_Item <= armor.size())
			{
				int i = weapon.size() + 1;
				for (Armor* Current : armor)
				{
					if (i == Current_Item)
					{
						Armor* tmp = _player.Get_Armor();

						if (_player.Get_Armor()->Get_Effect().Get_Affectation() == Affect_Stat::ENDURANCE)
							_player.Set_Endurance(_player.Get_Endurance() - _player.Get_Armor()->Get_Effect().Get_Power());
						if (_player.Get_Armor()->Get_Effect().Get_Affectation() == Affect_Stat::LIFE_POINT)
						{
							_player.Set_LifeMax(_player.Get_LifeMax() - _player.Get_Armor()->Get_Effect().Get_Power());
							_player.Set_Life(_player.Get_LifeMax());
						}
						if (_player.Get_Armor()->Get_Effect().Get_Affectation() == Affect_Stat::MANA)
							_player.Set_Endurance(_player.Get_Mana() - _player.Get_Armor()->Get_Effect().Get_Power());
						if (_player.Get_Armor()->Get_Effect().Get_Affectation() == Affect_Stat::SPEED)
							_player.Set_Endurance(_player.Get_Speed() - _player.Get_Armor()->Get_Effect().Get_Power());

						if (Current->Get_Effect().Get_Affectation() == Affect_Stat::ENDURANCE)
							_player.Set_Endurance(_player.Get_Endurance() + Current->Get_Effect().Get_Power());
						if (Current->Get_Effect().Get_Affectation() == Affect_Stat::LIFE_POINT)
						{
							_player.Set_LifeMax(_player.Get_LifeMax() + Current->Get_Effect().Get_Power());
							_player.Set_Life(_player.Get_LifeMax());
						}
						if (Current->Get_Effect().Get_Affectation() == Affect_Stat::MANA)
							_player.Set_Endurance(_player.Get_Mana() + Current->Get_Effect().Get_Power());
						if (Current->Get_Effect().Get_Affectation() == Affect_Stat::SPEED)
							_player.Set_Endurance(_player.Get_Speed() + Current->Get_Effect().Get_Power());

						_player.Set_Armor(*Current);
						*Current = *tmp;
						break;
					}
					i++;
				}
			}
			if (Current_Item > armor.size() && Current_Item <= consumable.size())
			{
				int i = armor.size() + 1;
				for (Consumable* Current : consumable)
				{
					if (i == Current_Item)
					{
						Consumable* tmp = _player.Get_Consumable();
						_player.Set_Consumable(*Current);
						*Current = *tmp;
						break;
					}
					i++;
				}
			}

			Item_Load();
			timer = 0;
		}
	}

	if (Current_MenuSub == 1)
	{
		int limit = 0;
		int Choise = 0;
		if (Keyboard::isKeyPressed(Keyboard::Numpad1))
		{
			Choise = 1;
			int i = 1;
			for (Sort* Current : _player.Get_Spell())
			{
				if (i != Choise)
					limit += Current->Get_Effect().Get_Level();

				i++;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad2))
		{
			Choise = 2;
			int i = 1;
			for (Sort* Current : _player.Get_Spell())
			{
				if (i != Choise)
					limit += Current->Get_Effect().Get_Level();

				i++;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad3))
		{
			Choise = 3;
			int i = 1;
			for (Sort* Current : _player.Get_Spell())
			{
				if (i != Choise)
					limit += Current->Get_Effect().Get_Level();

				i++;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad4))
		{
			Choise = 4;
			int i = 1;
			for (Sort* Current : _player.Get_Spell())
			{
				if (i != Choise)
					limit += Current->Get_Effect().Get_Level();

				i++;
			}
		}

		if (Choise != 0)
		{
			int i = 1;
			for (Sort* Current : Spell)
			{
				if (i == Current_Item)
				{
					int x = 1;
					for (Sort* Current_p : _player.Get_Spell())
					{
						if (x == Choise && limit + Current->Get_Effect().Get_Level() <= _player.Get_Level() + 3)
						{
							*Current_p = *Current;
							break;
						}

						x++;
					}
					break;
				}
				i++;
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::I) && timer > 0.2f)
	{
		_player.Set_IsInventory(false);
		timer = 0;
	}
}

void Inventory::Display_stat()
{
	if (Current_MenuSub == 0)
	{
		if (Current_Item > 0 && Current_Item <= weapon.size())
		{
			int i = 1;
			for (Weapon* Current : weapon)
			{
				if (i == Current_Item)
				{
					Text Name("Name : " + Current->Get_Name(), getFont("Times"), 30);
					Name.setFillColor(Color(255, 120, 50, 255));
					Name.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 100);
					App.Get_Window().draw(Name);
					Text Damage("Damage : " + to_string(Current->Get_Mindamage()) + "/" + to_string(Current->Get_MaxDamage()), getFont("Times"), 30);
					Damage.setFillColor(Color(255, 120, 50, 255));
					Damage.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 70);
					App.Get_Window().draw(Damage);
					Text Effect("Effect : " + Current->Get_Effect().Get_Name(), getFont("Times"), 30);
					Effect.setFillColor(Color(255, 120, 50, 255));
					Effect.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 40);
					App.Get_Window().draw(Effect);
				}
				i++;
			}
		}
		if (Current_Item > weapon.size() && Current_Item <= armor.size())
		{
			int i = weapon.size() + 1;
			for (Armor* Current : armor)
			{
				if (i == Current_Item)
				{
					Text Name("Name : " + Current->Get_Name(), getFont("Times"), 30);
					Name.setFillColor(Color(255, 120, 50, 255));
					Name.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 100);
					App.Get_Window().draw(Name);
					Text Damage("Defense : " + to_string(Current->Get_Defense()), getFont("Times"), 30);
					Damage.setFillColor(Color(255, 120, 50, 255));
					Damage.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 70);
					App.Get_Window().draw(Damage);
					Text Effect("Effect : " + Current->Get_Effect().Get_Name(), getFont("Times"), 30);
					Effect.setFillColor(Color(255, 120, 50, 255));
					Effect.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 40);
					App.Get_Window().draw(Effect);
				}
				i++;
			}
		}
		if (Current_Item > armor.size() && Current_Item <= consumable.size())
		{
			int i = armor.size() + 1;
			for (Consumable* Current : consumable)
			{
				if (i == Current_Item)
				{
					Text Name("Name : " + Current->Get_Name(), getFont("Times"), 30);
					Name.setFillColor(Color(255, 120, 50, 255));
					Name.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 100);
					App.Get_Window().draw(Name);
					Text Effect("Effect : " + Current->Get_Effect().Get_Name(), getFont("Times"), 30);
					Effect.setFillColor(Color(255, 120, 50, 255));
					Effect.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 70);
					App.Get_Window().draw(Effect);
				}
				i++;
			}
		}
	}
	if (Current_MenuSub == 1)
	{
		int i = 1;
		for (Sort* Current : Spell)
		{
			if (i == Current_Item)
			{
				Text Name("Name : " + Current->Get_Name(), getFont("Times"), 30);
				Name.setFillColor(Color(255, 120, 50, 255));
				Name.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 100);
				App.Get_Window().draw(Name);
				Text Damage("Damage : " + to_string(Current->Get_Damage()), getFont("Times"), 30);
				Damage.setFillColor(Color(255, 120, 50, 255));
				Damage.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 70);
				App.Get_Window().draw(Damage);
				Text Effect("Effect : " + Current->Get_Effect().Get_Name(), getFont("Times"), 30);
				Effect.setFillColor(Color(255, 120, 50, 255));
				Effect.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 40);
				App.Get_Window().draw(Effect);
				Text Duration("Durée : " + to_string(Current->Get_Effect().Get_Duration()), getFont("Times"), 30);
				Duration.setFillColor(Color(255, 120, 50, 255));
				Duration.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y - 10);
				App.Get_Window().draw(Duration);
				Text Puissance("Puissance : " + to_string(Current->Get_Effect().Get_Power()), getFont("Times"), 30);
				Puissance.setFillColor(Color(255, 120, 50, 255));
				Puissance.setPosition(Invent.getPosition().x + 90, Invent.getPosition().y + 20);
				App.Get_Window().draw(Puissance);
			}
			i++;
		}
	}
}

void Inventory::Display_CurrentItem(Hero _player)
{
	if (Current_MenuSub == 0)
	{
		_player.Get_Weapon()->Set_Position(Vector2f(Invent.getPosition().x - 250, Invent.getPosition().y - 200));
		_player.Get_Weapon()->Display_Inventory(Vector2f(2, 2));
		_player.Get_Armor()->Set_Position(Vector2f(Invent.getPosition().x, Invent.getPosition().y - 200));
		_player.Get_Armor()->Display_Inventory(Vector2f(2, 2));
		_player.Get_Consumable()->Set_Position(Vector2f(Invent.getPosition().x + 250, Invent.getPosition().y - 200));
		_player.Get_Consumable()->Display_Inventory(Vector2f(2, 2));
	}
	if (Current_MenuSub == 1)
	{
		int i = 0;
		for (Sort* Current : _player.Get_Spell())
		{
			Current->Display(Vector2f(Invent.getPosition().x - 150 + (i * 100), Invent.getPosition().y - 200));
			i++;
		}
	}
}

void Inventory::Display()
{
	App.Get_Window().draw(Invent);

	App.Get_Window().draw(Title);

	for (Button_Text& Current : Sub_Menu)
		Current.Display();

	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 6; y++)
		{
			if (x + (y * 8) + 1 == Current_Item)
				Encadré.setOutlineColor(Color(255, 120, 50, 255));
			else
				Encadré.setOutlineColor(Color(50, 120, 255, 255));

			Encadré.setPosition(Invent.getPosition().x - 370 + (x * 55), Invent.getPosition().y - 67.5 + (y * 65));
			App.Get_Window().draw(Encadré);
		}

	if (Current_MenuSub == 0)
	{
		for (Weapon* Current : weapon)
			Current->Display_Inventory(Vector2f(2, 2));

		for (Armor* Current : armor)
			Current->Display_Inventory(Vector2f(2, 2));
	
		for (Consumable* Current : consumable)
			Current->Display_Inventory(Vector2f(2, 2));
	}
	if (Current_MenuSub == 1)
	{
		int x = 0;
		int y = 0;
		for (Sort* Current : Spell)
		{
			Current->Display(Vector2f(Invent.getPosition().x - 370 + (x * 55), Invent.getPosition().y - 67.5 + (y * 65)));
			x++;
			if (x == 8)
			{
				x = 0;
				y++;
			}
		}
	}

	Display_stat();
}