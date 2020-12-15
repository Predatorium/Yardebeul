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
		Beat_Down = Animator(IntRect(5, 72, 54, 44), 8, 0.15f);
		Beat_Right = Animator(IntRect(5, 121, 42, 45), 8, 0.15f);
		Beat_Top = Animator(IntRect(5, 23, 50, 44), 8, 0.15f);

		Walk_Down = Animator(IntRect(160, 189, 61, 43), 3, 0.15f);
		Walk_Right = Animator(IntRect(348, 189, 40, 44), 3, 0.15f);
		Walk_Top = Animator(IntRect(5, 189, 50, 42), 3, 0.15f);

		sprite.setOrigin(Vector2f(21, 22.5));
		sprite.setTextureRect(IntRect(5, 72, 54, 44));
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
	Orientation = Direction::Left;
	IsDialogue = false;
	Right = false;
	Left = false;
	Down = false;
	Up = false;
	dialogue = _dial;

	if (Name == "Fairy")
	{
		Beat_Down = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Beat_Right = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Beat_Top = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Walk_Down = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Walk_Right = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Walk_Top = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);

		sprite.setOrigin(Vector2f(22, 23));
		sprite.setTextureRect(IntRect(5, 99, 44, 46));
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
		Position.x += 5 * Delta.x * MainTime.GetTimeDeltaF();
	if (Up == true || Down == true)
		Position.y += 5 * Delta.y * MainTime.GetTimeDeltaF();

	if (Circle_Collision(Position, _player.Get_Position(), 200, 200))
	{
		Delta.x = 20 * cos(Angle_calc(Position, _player.Get_Position()));
		Delta.y = 20 * sin(Angle_calc(Position, _player.Get_Position()));

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
		if (Orientation == Direction::Right)
		{
			Beat_Right.Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left)
		{
			Beat_Right.Animation(sprite);
			sprite.setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down)
		{
			Beat_Down.Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up)
		{
			Beat_Top.Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
	}
	else
	{
		if (Orientation == Direction::Right)
		{
			Walk_Right.Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left)
		{
			Walk_Right.Animation(sprite);
			sprite.setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down)
		{
			Walk_Down.Animation(sprite);
			sprite.setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up)
		{
			Walk_Top.Animation(sprite);
			if (Delta.x > 0)
				sprite.setScale(Vector2f(-1, 1));
			else
				sprite.setScale(Vector2f(1, 1));
		}
	}

	sprite.setPosition(Position);
	App.Get_Window().draw(sprite);
}