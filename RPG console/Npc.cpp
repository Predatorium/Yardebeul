#include "Npc.h"
#include "SpriteManager.h"
#include "Dialogue_Container.h"
#include "StateManager.h"

Npc::Npc(string _name, Vector2f _position, int _niveau, int _pv, int vitesse, Comportement _attitude)
	: Character(_name)
{
	Position = _position;
	Level = _niveau;
	Life_Point = _pv;
	Life_Max = Life_Point;
	Mana = 50;
	Endurance = 25;
	Mental_Health = 100;
	Speed = vitesse;
	Attitude = _attitude;
	Orientation = Direction::Left;
	IsDialogue = false;
	dialogue = Dialogues.Get_Dialogue("1_1");

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

		Damage_Min = 1;
		Damage_Max = 3;

		Defense = 10;

		getSprite(Name).setOrigin(Vector2f(21, 22.5));
		getSprite(Name).setTextureRect(IntRect(5, 72, 54, 44));

		Colision_Rect = IntRect(0, 0, 45, 22.5);
	}

	if (Name == "Fairy")
	{
		Beat_Down = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Beat_Right = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Beat_Top = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Walk_Down = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Walk_Right = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);
		Walk_Top = Animator(IntRect(5, 99, 44, 46), 16, 0.15f);

		Damage_Min = 0;
		Damage_Max = 0;

		Defense = 0;

		getSprite(Name).setOrigin(Vector2f(22, 23));
		getSprite(Name).setTextureRect(IntRect(5, 99, 44, 46));

		Colision_Rect = IntRect(0, 0, 44, 23);
	}

}

void Npc::Update_Attack(Hero& _player)
{
	if (Left == true || Right == true)
		Position.x += 5 * Delta.x * MainTime.GetTimeDeltaF();
	if (Up == true || Down == true)
		Position.y += 5 * Delta.y * MainTime.GetTimeDeltaF();

	if (Circle_Collision(Position, _player.Get_Position(), getSprite(Name).getGlobalBounds().width * 4, getSprite("Hero").getGlobalBounds().width * 4))
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
		if (Circle_Collision(Position, _player.Get_Position(), getSprite(Name).getGlobalBounds().width / 2, getSprite("Hero").getGlobalBounds().width / 2))
			MState.State_Fight(&_player, this);
	}
	else
	{
		Left = false;
		Right = false;
		Up = false;
		Down = false;
	}
	
	Colision_Rect = IntRect(Vector2i(Position.x, Position.y - Colision_Rect.height), Vector2i(Colision_Rect.width, Colision_Rect.height));
}

void Npc::Update_Dialogue(bool& _dial, Hero _player)
{
	if (Circle_Collision(Position, _player.Get_Position(), getSprite(Name).getGlobalBounds().width, getSprite("Hero").getGlobalBounds().width)
		&& _player.Get_Interact() == true && &dialogue != nullptr)
		_dial = true;

	if (IsDialogue)
		dialogue.Update(_dial);

	IsDialogue = _dial;
}

void Npc::Display_Fight(Vector2f _scale)
{
	getSprite(Name).setScale(_scale);
	App.Get_Window().draw(getSprite(Name));
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
			Beat_Right.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left)
		{
			Beat_Right.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down)
		{
			Beat_Down.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up)
		{
			Beat_Top.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
	}
	else
	{
		if (Orientation == Direction::Right)
		{
			Walk_Right.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Left)
		{
			Walk_Right.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Down)
		{
			Walk_Down.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Up)
		{
			Walk_Top.Animation(getSprite(Name));
			if (Delta.x > 0)
				getSprite(Name).setScale(Vector2f(-1, 1));
			else
				getSprite(Name).setScale(Vector2f(1, 1));
		}
	}

	getSprite(Name).setPosition(Position);
	App.Get_Window().draw(getSprite(Name));
}