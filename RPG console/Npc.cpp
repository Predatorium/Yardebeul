#include "Npc.h"
#include "SpriteManager.h"
#include "Dialogue_Container.h"
#include "StateManager.h"

Npc::Npc(string _name, Vector2f _position, int _niveau, int _pv, int vitesse, Comportement _attitude)
	: Character(_name)
{
	Position = _position;
	Niveau = _niveau;
	Point_de_vie = _pv;
	Mana = 50;
	Endurance = 25;
	Santé_mentale = 100;
	Vitesse = vitesse;
	Attitude = _attitude;
	Orientation = Direction::Gauche;
	IsDialogue = false;
	dial = Dialogues.Get_Dialogue("1_1");

	Droite = false;
	Gauche = false;
	Bas = false;
	Haut = false;

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

}

void Npc::Update_Attack(Hero& _player)
{
	if (Gauche == true || Droite == true)
		Position.x += 5 * Delta.x * MainTime.GetTimeDeltaF();
	if (Haut == true || Bas == true)
		Position.y += 5 * Delta.y * MainTime.GetTimeDeltaF();

	if (Circle_Collision(Position, _player.Get_Position(), getSprite(Name).getGlobalBounds().width * 4, getSprite("Hero").getGlobalBounds().width * 4))
	{
		Delta.x = 20 * cos(Angle_calc(Position, _player.Get_Position()));
		Delta.y = 20 * sin(Angle_calc(Position, _player.Get_Position()));

		if (Delta.x >= 0 && Delta.y >= 0)
		{
			if (Delta.x > Delta.y)
				Orientation = Direction::Droite;
			else
				Orientation = Direction::Bas;
		}
		else if (Delta.x < 0 && Delta.y < 0)
		{
			if (Delta.x < Delta.y)
				Orientation = Direction::Gauche;
			else
				Orientation = Direction::Haut;
		}
		else if (Delta.x >= 0 && Delta.y < 0)
		{
			if (Delta.x > -(Delta.y))
				Orientation = Direction::Droite;
			else
				Orientation = Direction::Haut;
		}
		else if (Delta.x < 0 && Delta.y >= 0)
		{
			if (-(Delta.x) > Delta.y)
				Orientation = Direction::Gauche;
			else
				Orientation = Direction::Bas;
		}

		if (Delta.x < 0)
		{
			Gauche = true;
			Droite = false;
		}
		else if (Delta.x > 0)
		{
			Gauche = false;
			Droite = true;
		}

		if (Delta.y < 0)
		{
			Haut = true;
			Bas = false;
		}
		else if (Delta.y > 0)
		{
			Haut = false;
			Bas = true;
		}
		if (Circle_Collision(Position, _player.Get_Position(), getSprite(Name).getGlobalBounds().width / 2, getSprite("Hero").getGlobalBounds().width / 2))
			MState.State_Fight(&_player, this);
	}
	else
	{
		Gauche = false;
		Droite = false;
		Haut = false;
		Bas = false;
	}
	
	Colision_Rect = IntRect(Vector2i(Position.x, Position.y - Colision_Rect.height), Vector2i(Colision_Rect.width, Colision_Rect.height));
}

void Npc::Update_Dialogue(bool& _dial, Hero _player)
{
	if (Circle_Collision(Position, _player.Get_Position(), getSprite(Name).getGlobalBounds().width, getSprite("Hero").getGlobalBounds().width)
		&& _player.Get_Interact() == true && &dial != nullptr)
		_dial = true;

	if (IsDialogue)
		dial.Update(_dial);

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
		dial.Display();
}

void Npc::Display()
{
	if (Droite == false && Gauche == false && Haut == false && Bas == false)
	{
		if (Orientation == Direction::Droite)
		{
			Beat_Right.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Gauche)
		{
			Beat_Right.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Bas)
		{
			Beat_Down.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Haut)
		{
			Beat_Top.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
	}
	else
	{
		if (Orientation == Direction::Droite)
		{
			Walk_Right.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Gauche)
		{
			Walk_Right.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(-1, 1));
		}
		else if (Orientation == Direction::Bas)
		{
			Walk_Down.Animation(getSprite(Name));
			getSprite(Name).setScale(Vector2f(1, 1));
		}
		else if (Orientation == Direction::Haut)
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