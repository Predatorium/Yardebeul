#include "Npc.h"
#include "SpriteManager.h"
#include "Dialogue_Container.h"
#include "StateManager.h"

Npc::Npc(string _name, Armor _armor, Weapon _weapon, int _level, int _hp, int _speed)
	: Character(_name, _armor, _weapon)
{
	Level = _level;
	Life_Point = _hp;
	Life_Max = Life_Point;
	Mana = 50;
	Endurance = 25;
	Mental_Health = 100;
	Speed = _speed;
	Attitude = Comportement::Agressif;
	Orientation = Direction::Left;
	IsDialogue = false;
	Right = false;
	Left = false;
	Down = false;
	Up = false;

	if (Name == "Knucles")
	{
		Anim["Walk_Down"] = Animator(IntRect(160, 189, 61, 43), 3, 0.15f, 0);
		Anim["Walk_Right"] = Animator(IntRect(348, 189, 40, 44), 3, 0.15f, 0);
		Anim["Walk_Top"] = Animator(IntRect(5, 189, 50, 42), 3, 0.15f, 0);

		Anim["Beat_Down"] = Animator(IntRect(5, 72, 54, 44), 8, 0.15f, 0);
		Anim["Beat_Right"] = Animator(IntRect(5, 121, 42, 45), 8, 0.15f, 0);
		Anim["Beat_Top"] = Animator(IntRect(5, 23, 50, 44), 8, 0.15f, 0);
	}
	if (Name == "Yves")
	{
		Anim["Walk_Down"] = Animator(IntRect(1057, 19, 24, 38), 6, 0.15f, 1);
		Anim["Walk_Right"] = Animator(IntRect(1057, 58, 28, 37), 6, 0.15f, 1);
		Anim["Walk_Top"] = Animator(IntRect(1057, 96, 24, 38), 6, 0.15f, 1);

		Anim["Beat_Down"] = Animator(IntRect(941, 19, 24, 36), 4, 0.15f, 1);
		Anim["Beat_Right"] = Animator(IntRect(941, 56, 26, 35), 4, 0.15f, 1);
		Anim["Beat_Top"] = Animator(IntRect(941, 92, 24, 36), 4, 0.15f, 1);
	}
}

Npc::Npc(string _name, int _level, int _hp, int _speed, Dialogue &_dial)
	: Character(_name, Armor(), Weapon())
{
	Level = _level;
	Life_Point = _hp;
	Life_Max = Life_Point;
	Mana = 50;
	Endurance = 25;
	Mental_Health = 100;
	Speed = _speed;
	Attitude = Comportement::Amical;
	Orientation = Direction::Down;
	IsDialogue = false;
	Right = false;
	Left = false;
	Down = false;
	Up = false;
	dialogue = _dial;

	if (Name == "Fairy")
	{
		Anim["Beat_Down"] = Animator(IntRect(5, 99, 44, 46), 16, 0.15f, 0);

		sprite.setTextureRect(IntRect(5, 99, 44, 46));
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	}
}

Npc::Npc(const Npc& _npc, Vector2f _position)
{
	*this = _npc;
	Position = _position;
	sprite.setPosition(Position);
}

void Npc::Update_Attack(Hero& _player)
{
	if (Left == true || Right == true)
		Position.x += 100 * Delta.x * MainTime.GetTimeDeltaF();
	if (Up == true || Down == true)
		Position.y += 100 * Delta.y * MainTime.GetTimeDeltaF();

	if (Circle_Collision(Position, _player.Get_Position(), 130, 130))
	{
		Delta.x = normalisation(Position, _player.Get_Position()).x;
		Delta.y = normalisation(Position, _player.Get_Position()).y;

		if (Delta.x >= 0 && Delta.y >= 0)
		{
			if (Delta.x > Delta.y)
				Orientation = Direction::Right;
			else
				Orientation = Direction::Down;
		}
		else if (Delta.x < 0 && Delta.y < 0)
		{
			if (Delta.x < Delta.y)
				Orientation = Direction::Left;
			else
				Orientation = Direction::Up;
		}
		else if (Delta.x >= 0 && Delta.y < 0)
		{
			if (Delta.x > -(Delta.y))
				Orientation = Direction::Right;
			else
				Orientation = Direction::Up;
		}
		else if (Delta.x < 0 && Delta.y >= 0)
		{
			if (-(Delta.x) > Delta.y)
				Orientation = Direction::Left;
			else
				Orientation = Direction::Down;
		}

		if (Delta.x < 0)
		{
			Left = true;
			Right = false;
		}
		else if (Delta.x > 0)
		{
			Left = false;
			Right = true;
		}

		if (Delta.y < 0)
		{
			Up = true;
			Down = false;
		}
		else if (Delta.y > 0)
		{
			Up = false;
			Down = true;
		}
		if (Circle_Collision(Position, _player.Get_Position(), 25, 25))
			StateManager::Get_Singleton().State_Fight(&_player, this);
	}
	else
	{
		Left = false;
		Right = false;
		Up = false;
		Down = false;
	}
}

void Npc::Update_Dialogue(bool& _dial, Hero _player)
{
	if (Circle_Collision(Position, _player.Get_Position(), 50, 50)
		&& _player.Get_Interact() == true && &dialogue != nullptr)
		_dial = true;

	if (IsDialogue)
		dialogue.Update(_dial);

	IsDialogue = _dial;
}

void Npc::Display_Fight(Vector2f _scale)
{
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
}

void Npc::Display_Dialogue()
{
	if (IsDialogue)
		dialogue.Display();
}

void Npc::Display()
{
	if (Right == false && Left == false && Up == false && Down == false)
	{
		if (Orientation == Direction::Right && Anim["Beat_Right"] != Animator())
		{
			Anim["Beat_Right"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left && Anim["Beat_Right"] != Animator())
		{
			Anim["Beat_Right"].Animation(sprite);
			sprite.setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down && Anim["Beat_Down"] != Animator())
		{
			Anim["Beat_Down"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up && Anim["Beat_Top"] != Animator())
		{
			Anim["Beat_Top"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else
			Anim["Beat"].Animation(sprite);
	}
	else
	{
		if (Orientation == Direction::Right && Anim["Walk_Right"] != Animator())
		{
			Anim["Walk_Right"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left && Anim["Walk_Right"] != Animator())
		{
			Anim["Walk_Right"].Animation(sprite);
			sprite.setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down && Anim["Walk_Down"] != Animator())
		{
			Anim["Walk_Down"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up && Anim["Walk_Top"] != Animator())
		{
			Anim["Walk_Top"].Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else
		{
			if (Anim["Walk"] != Animator())
				Anim["Walk"].Animation(sprite);
			else
				Anim["Beat"].Animation(sprite);
		}
	}

	sprite.setPosition(Position);
	App.Get_Window().draw(sprite);
}