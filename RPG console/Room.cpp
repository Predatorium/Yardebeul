#include "Event.h"
#include "Room.h"
#include "StateManager.h"
#include "Npc_Container.h"
#include "FontManager.h"
#include "Dungeon.h"

Room::Room(Biomes _biome, int _difficulte, bool _isBoss, int _number, Hero& _player)
{
	Menu_Pause = new Menu(1);

	Range_Niveau = Vector2i(3000, 3000);

	Player = _player;

	Save = false;
	Load = true;
	Pause = false;
	IsDialogue = false;
	Timer = 0;

	Vue = Views(Vector2f(480, 270), Vector2f(960, 540), FloatRect(0, 0, 1, 1));
	Screen = Views(Vector2f(1440, 810), Vector2f(2880, 1620), FloatRect(0, 0, 1, 1));

	C_MiniMap = CircleShape(150);
	C_MiniMap.setPosition(Vector2f(1918 - C_MiniMap.getGlobalBounds().width, 2));
	C_MiniMap.setOutlineThickness(2);
	C_MiniMap.setOutlineColor(Color::Blue);

	Numero = _number;
	Biome = _biome;
	Difficulte = _difficulte;
	isBoss = _isBoss;

	Size = Vector2i(irandom(10, 10), irandom(8, 8));
}

void Room::Procedural_Room(string _biome)
{
	Back_Layer.clear();
	Player_Layer.clear();
	Player.Set_Position(Vector2f((Range_Niveau.x * 32) / 2 + 50, (Range_Niveau.y * 32) / 2 + 50));

	Escalier[0].first = -1;
	Escalier[0].second = Maps(Vector2f(0, 0), Vector2i(2, 9), _biome, Biomes::Castle);

	Escalier[1].first = 1;
	Escalier[1].second = Maps(Vector2f(0, 0), Vector2i(2, 9), _biome, Biomes::Castle);

	int Number_Event = irandom(8, 5);
	Vector2f position((Range_Niveau.x * 32) / 2, (Range_Niveau.y * 32) / 2);
	Vector2f Prev_pos((Range_Niveau.x * 32) / 2, (Range_Niveau.y * 32) / 2);

	Dir Direction = Dir::None;
	Dir Prev_Dir = Dir::None;

	for (int i = 0; i < Number_Event; i++)
	{
		if (i == 0)
			Evenement.push_back(Events(State_Event::Rien));
		else if (i == Number_Event - 1 && isBoss == true)
			Evenement.push_back(Events(State_Event::Combat));
		else
		{
			int rand = irandom(0, 4);
			Evenement.push_back(Events(State_Event(rand)));
		}

		if (i > 0)
		{
			Direction = Dir::None;

			while (Direction == Dir::None)
			{
				Direction = Dir(irandom(1, 4));
				while (Direction == Prev_Dir)
					Direction = Dir(irandom(1, 4));

				if (Direction == Dir::Droite)
					position = Vector2f(position.x + ((Size.x + 2) * 32), position.y);

				if (Direction == Dir::Gauche)
					position = Vector2f(position.x - ((Size.x + 2) * 32), position.y);

				if (Direction == Dir::Haut)
					position = Vector2f(position.x, position.y - ((Size.y + 2) * 32));

				if (Direction == Dir::Bas)
					position = Vector2f(position.x, position.y + ((Size.y + 2) * 32));

				bool look = false;
				for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
					if (Vector2i(Current->Get_Position()) == Vector2i(position.x + (position.x - Prev_pos.x), position.y + (position.y - Prev_pos.y)))
					{
						look = true;
						break;
					}

				if (look == true)
				{
					int possibility = 3;
					Vector2f Check;
					Dir SaveDir = Direction;
					Direction = Dir::Bas;
					while (Direction != Dir::None)
					{
						if (Direction != Prev_Dir)
						{
							Check = position;

							if (Direction == Dir::Droite)
								Check = Vector2f(Check.x + ((Size.x + 2) * 32), Check.y);

							if (Direction == Dir::Gauche)
								Check = Vector2f(Check.x - ((Size.x + 2) * 32), Check.y);

							if (Direction == Dir::Haut)
								Check = Vector2f(Check.x, Check.y - ((Size.y + 2) * 32));

							if (Direction == Dir::Bas)
								Check = Vector2f(Check.x, Check.y + ((Size.y + 2) * 32));

							for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
								if (Vector2i(Current->Get_Position()) == Vector2i(Check))
								{
									possibility--;
									break;
								}
						}

						Direction = Dir((int)Direction - 1);

						if (Direction == Prev_Dir)
							Direction = Dir((int)Direction - 1);
					}

					if (possibility == 0)
					{
						Direction = Dir::None;
						position = Prev_pos;
					}
					else
						Direction = SaveDir;
				}

				for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
					if (Vector2i(Current->Get_Position()) == Vector2i(position))
					{
						Direction = Dir::None;
						position = Prev_pos;
						break;
					}

				if (position.x < 0 || position.x + (Size.x * 32) > Range_Niveau.x * 32 || position.y < 0 || position.y + (Size.y * 32) > Range_Niveau.y * 32)
				{
					Direction = Dir::None;
					position = Prev_pos;
				}
			}

			Prev_pos = position;
		}

		for (int y = 0; y < Size.y; y++)
			for (int x = 0; x < Size.x; x++)
			{
				if (i == 0)
					if (y == Size.y - 2 && x == 1)
						Escalier[0].second.Set_Position(Vector2f(position.x + (x * 32), position.y + (y * 32)));

				if (i == Number_Event - 1)
					if (y == 1 && x == Size.x - 2)
						Escalier[1].second.Set_Position(Vector2f(position.x + (x * 32), position.y + (y * 32)));

				bool find = false;
				for (Maps& Current : Back_Layer)
					if (Vector2i(Current.Get_Position()) == Vector2i(position.x + (x * 32), position.y + (y * 32)))
					{
						find = true;
						break;
					}

				for (Maps& Current : Player_Layer)
					if (Vector2i(Current.Get_Position()) == Vector2i(position.x + (x * 32), position.y + (y * 32)))
					{
						find = true;
						break;
					}

				if (find == false)
				{
					if (x == 0 && y > 0 && y < Size.y - 1)
						Back_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(3, 1), _biome, Biomes::Castle));

					else if (x == Size.x - 1 && y > 0 && y < Size.y - 1)
						Back_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(0, 1), _biome, Biomes::Castle));

					else if (x > 0 && x < Size.x - 1 && y == 0)
						Back_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(2, 2), _biome, Biomes::Castle));

					else if (y == 0 && x == 0)
						Back_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(1, 3), _biome, Biomes::Castle));

					else if (y == 0 && x == Size.x - 1)
						Back_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(3, 2), _biome, Biomes::Castle));

					else if (y == Size.y - 1 && x == 0)
						Player_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(3, 4), _biome, Biomes::Castle));

					else if (y == Size.y - 1 && x == Size.x - 1)
						Player_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(2, 4), _biome, Biomes::Castle));

					else if (y == Size.y - 1 && x > 0 && x < Size.x - 1)
						Player_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(1, 4), _biome, Biomes::Castle));

					else
						Back_Layer.push_back(Maps(Vector2f(position.x + (x * 32), position.y + (y * 32)), Vector2i(irandom(0, 5), 0), _biome, Biomes::Castle));
				}
			}

		if (Evenement.back().Get_Type() == State_Event::Combat)
		{
			if (isBoss == true && i == Number_Event - 1)
				NpcList.push_back(Npc(Npcs.Random_Boss(), Vector2f(position.x + (Size.x * 32) / 2, position.y + (Size.y * 32) / 2)));
			else
				NpcList.push_back(Npc(Npcs.Random_Npc(Comportement::Agressif), Vector2f(position.x + (Size.x * 32) / 2, position.y + (Size.y * 32) / 2)));
		}
		else if (Evenement.back().Get_Type() == State_Event::Rencontre)
		{
			NpcList.push_back(Npc(Npcs.Random_Npc(Comportement::Amical), Vector2f(position.x + (Size.x * 32) / 2, position.y + (Size.y * 32) / 2)));
		}
		else if (Evenement.back().Get_Type() == State_Event::Coffre)
		{
			Coffre.push_back(Chest(Vector2f(position.x + (Size.x * 32) / 2, position.y + (Size.y * 32) / 2)));
			Player_Layer.push_back(Maps(Vector2f(position.x + (Size.x * 32) / 2, position.y + (Size.y * 32) / 2), Vector2i(0, 0), "Chest", Biomes::Castle));
		}

		if (Direction == Dir::Bas)
		{
			for (int y = 3; y > -1; y--)
				for (int x = 0; x < 2; x++)
				{
					for (auto Current = Player_Layer.begin(); Current != Player_Layer.end(); Current++)
						if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x + (x * 32), Prev_pos.y - (y * 32)))
						{
							Player_Layer.erase(Current);
							break;
						}

					for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
						if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x + (x * 32), Prev_pos.y - (y * 32)))
						{
							Back_Layer.erase(Current);
							break;
						}

					if (x == 0)
						Back_Layer.push_back(Maps(Vector2f(Prev_pos.x + (x * 32), Prev_pos.y - (y * 32)), Vector2i(3, 1), _biome, Biomes::Castle));

					else if (x == 1 && y > 0)
						Back_Layer.push_back(Maps(Vector2f(Prev_pos.x + (x * 32), Prev_pos.y - (y * 32)), Vector2i(0, 1), _biome, Biomes::Castle));

					else
						Back_Layer.push_back(Maps(Vector2f(Prev_pos.x + (x * 32), Prev_pos.y - (y * 32)), Vector2i(irandom(0, 5), 0), _biome, Biomes::Castle));
				}

			Prev_Dir = Dir::Haut;
		}

		if (Direction == Dir::Haut)
		{
			for (int y = 0; y < 4; y++)
				for (int x = 0; x < 2; x++)
				{
					for (auto Current = Player_Layer.begin(); Current != Player_Layer.end(); Current++)
						if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x + (x * 32), (Prev_pos.y + (Size.y - 1) * 32) + (y * 32)))
						{
							Player_Layer.erase(Current);
							break;
						}

					for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
						if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x + (x * 32), (Prev_pos.y + (Size.y - 1) * 32) + (y * 32)))
						{
							if (y == 3 && x == 0)
							{
								if (Current->Get_Tile() == Vector2i(2, 2))
									Back_Layer.push_back(Maps(Vector2f(Current->Get_Position()), Vector2i(irandom(0, 5), 0), _biome, Biomes::Castle));
							}
							Back_Layer.erase(Current);
							break;
						}

					if (x == 0)
					{
						bool find = false;
						if (y == 3 && x == 0)
						{
							for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
								if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x + (x * 32), (Prev_pos.y + (Size.y - 1) * 32) + (y * 32)))
								{
									if (Current->Get_Tile() == Vector2i(0, 0) || Current->Get_Tile() == Vector2i(1, 0) || Current->Get_Tile() == Vector2i(2, 0)
										|| Current->Get_Tile() == Vector2i(3, 0) || Current->Get_Tile() == Vector2i(4, 0))
										find = true;
									break;
								}

						}
						if (find == false)
							Back_Layer.push_back(Maps(Vector2f(Prev_pos.x + (x * 32), (Prev_pos.y + (Size.y - 1) * 32) + (y * 32)), Vector2i(3, 1), _biome, Biomes::Castle));
					}

					else if (x == 1 && y < 3)
						Back_Layer.push_back(Maps(Vector2f(Prev_pos.x + (x * 32), (Prev_pos.y + (Size.y - 1) * 32) + (y * 32)), Vector2i(0, 1), _biome, Biomes::Castle));

					else
						Back_Layer.push_back(Maps(Vector2f(Prev_pos.x + (x * 32), (Prev_pos.y + (Size.y - 1) * 32) + (y * 32)), Vector2i(irandom(0, 5), 0), _biome, Biomes::Castle));
				}

			Prev_Dir = Dir::Bas;
		}

		if (Direction == Dir::Droite)
		{
			for (int y = 0; y < 2; y++)
				for (int x = 3; x > -1; x--)
				{
					if ((y == 1 && x == 0) || y == 1 && x == 3)
						;
					else
					{
						for (auto Current = Player_Layer.begin(); Current != Player_Layer.end(); Current++)
							if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x - (x * 32), Prev_pos.y + (y * 32)))
							{
								Player_Layer.erase(Current);
								break;
							}

						for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
							if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x - (x * 32), Prev_pos.y + (y * 32)))
							{
								Back_Layer.erase(Current);
								break;
							}
					}

					if (y == 0)
						Back_Layer.push_back(Maps(Vector2f(Prev_pos.x - (x * 32), Prev_pos.y + (y * 32)), Vector2i(2, 2), _biome, Biomes::Castle));

					else if (y == 1 && x < 3 && x > 0)
						Player_Layer.push_back(Maps(Vector2f(Prev_pos.x - (x * 32), Prev_pos.y + (y * 32)), Vector2i(1, 4), _biome, Biomes::Castle));
				}

			Prev_Dir = Dir::Gauche;
		}

		if (Direction == Dir::Gauche)
		{
			for (int y = 0; y < 2; y++)
				for (int x = 0; x < 4; x++)
				{
					if ((y == 1 && x == 0) || y == 1 && x == 3)
						;
					else
					{
						for (auto Current = Player_Layer.begin(); Current != Player_Layer.end(); Current++)
							if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x + ((Size.x - 1) * 32) + (x * 32), Prev_pos.y + (y * 32)))
							{
								Player_Layer.erase(Current);
								break;
							}

						for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
							if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x + ((Size.x - 1) * 32) + (x * 32), Prev_pos.y + (y * 32)))
							{
								if (y == 0 && x == 3)
								{
									if (Current->Get_Tile() == Vector2i(3, 1))
										Back_Layer.push_back(Maps(Vector2f(Current->Get_Position()), Vector2i(irandom(0, 5), 0), _biome, Biomes::Castle));
								}
								Back_Layer.erase(Current);
								break;
							}
					}

					if (y == 0)
					{
						bool find = false;
						if (y == 0 && x == 3)
						{
							for (auto Current = Back_Layer.begin(); Current != Back_Layer.end(); Current++)
								if (Vector2i(Current->Get_Position()) == Vector2i(Prev_pos.x + ((Size.x - 1) * 32) + (x * 32), Prev_pos.y + (y * 32)))
								{
									if (Current->Get_Tile() == Vector2i(0, 0) || Current->Get_Tile() == Vector2i(1, 0) || Current->Get_Tile() == Vector2i(2, 0)
										|| Current->Get_Tile() == Vector2i(3, 0) || Current->Get_Tile() == Vector2i(4, 0))
										find = true;
									break;
								}

						}
						if (find == false)
							Back_Layer.push_back(Maps(Vector2f(Prev_pos.x + ((Size.x - 1) * 32) + (x * 32), Prev_pos.y + (y * 32)), Vector2i(2, 2), _biome, Biomes::Castle));
					}

					else if (y == 1 && x > 0 && x < 3)
						Player_Layer.push_back(Maps(Vector2f(Prev_pos.x + ((Size.x - 1) * 32) + (x * 32), Prev_pos.y + (y * 32)), Vector2i(1, 4), _biome, Biomes::Castle));
				}

			Prev_Dir = Dir::Droite;
		}
	}
}

void Room::Update(Dungeon& _d)
{
	Level::Update();

	if (Player.Get_Interact() == true)
	{
		if (Escalier[0].second.Get_Sprite().getGlobalBounds().intersects(Player.Get_Sprite().getGlobalBounds()))
		{
			_d.Add_CurrentRoom(Escalier[0].first);
			Player.Set_Position(Vector2f((Range_Niveau.x * 32) / 2 + 50, (Range_Niveau.y * 32) / 2 + 50));
		}

		if (Escalier[1].second.Get_Sprite().getGlobalBounds().intersects(Player.Get_Sprite().getGlobalBounds()))
		{
			int y = 0;
			for (Npc& Current : NpcList)
				if (Current.Get_Attitude() == Comportement::Amical)
					y++;

			if (NpcList.size() == y)
			{
				_d.Add_CurrentRoom(Escalier[1].first);
				Player.Set_Position(Vector2f((Range_Niveau.x * 32) / 2 + 50, (Range_Niveau.y * 32) / 2 + 50));
			}
		}
	}

	int y = 0;
	for (Npc& Current : NpcList)
		if (Current.Get_Attitude() == Comportement::Amical)
			y++;

	if (NpcList.size() == y)
	{
		_d.Add_CurrentRoom(Escalier[1].first);
		Player.Set_Position(Vector2f((Range_Niveau.x * 32) / 2 + 50, (Range_Niveau.y * 32) / 2 + 50));
	}

	if (isBoss == true)
	{
		if (_d.Get_Finished() == false)
		{
			if (NpcList.size() == y)
			{
				if (_d.Get_Name() == "First")
				{
					WeaponList.push_back(Weapon(Weapons.Get_Weapon("Epee de feu"), Player.Get_Position()));
					ArmorList.push_back(Armor(Armors.Get_Armor("Armor fire"), Player.Get_Position()));
				}
				if (_d.Get_Name() == "Second")
				{
					WeaponList.push_back(Weapon(Weapons.Get_Weapon("Epee d'eau"), Player.Get_Position()));
					ArmorList.push_back(Armor(Armors.Get_Armor("Armor water"), Player.Get_Position()));
				}
				if (_d.Get_Name() == "Third")
				{
					WeaponList.push_back(Weapon(Weapons.Get_Weapon("Epee d'air"), Player.Get_Position()));
					ArmorList.push_back(Armor(Armors.Get_Armor("Armor air"), Player.Get_Position()));
				}
				if (_d.Get_Name() == "Fourth")
				{
					WeaponList.push_back(Weapon(Weapons.Get_Weapon("Epee de terre"), Player.Get_Position()));
					ArmorList.push_back(Armor(Armors.Get_Armor("Armor earth"), Player.Get_Position()));
				}
			}

			_d.Set_Finish(true);
		}
	}


	for (Chest& Current : Coffre)
		Current.Take_Objet(*this, Player.Get_Position());

	if (Keyboard::isKeyPressed(Keyboard::F5))
		_d.Procedural_Dungeon(Player);
}

void Room::Display()
{
	Vue.Display();

	for (Maps& Current : Back_Layer)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display();

	for (Maps& Current : Player_Layer)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display();

	for (int i = 0; i < 2; i++)
		if (Vue.Occlusion_CullingRectangle(Escalier[i].second.Get_Position()))
			Escalier[i].second.Display();

	for (Npc& Current : NpcList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display();

	for (Chest& Current : Coffre)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display();

	for (Weapon& Current : WeaponList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Armor& Current : ArmorList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Consumable& Current : ConsumableList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	Player.Display();

	for (Npc& Current : NpcList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display();

	for (Chest& Current : Coffre)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display();

	for (Weapon& Current : WeaponList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Armor& Current : ArmorList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Consumable& Current : ConsumableList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	App.Get_Window().setView(App.Get_Window().getDefaultView());

	int i = 0;
	for (Npc& Current : NpcList)
		if (Current.Get_Attitude() == Comportement::Agressif)
			i++;

	Text N_Enemy("Current enemy :" + to_string(i), getFont("Times"), 50);
	N_Enemy.setPosition(0, 0);
	App.Get_Window().draw(N_Enemy);

	for (Npc& Current : NpcList)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display_Dialogue();

	if (Player.Get_IsInventory() == true)
	{
		Player.Get_Inventory().Display();
		Player.Get_Inventory().Display_CurrentItem(Player);
	}

	if (Pause == true)
		Menu_Pause->Display_Pause();

	C_MiniMap.setTexture(&Get_TextureMap(&Views::Occlusion_CullingCircle, Screen));
	C_MiniMap.setTextureRect(IntRect(420, 0, 1080, 1080));
	App.Get_Window().draw(C_MiniMap);
}