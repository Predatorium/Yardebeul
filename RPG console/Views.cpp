#include "Views.h"
#include "Editeur.h"

Views::Views()
{
	Zoom = false;
	Dezoom = false;
	Move = true;

	Size = Vector2f(1920, 1080);
	Position = Vector2f(960,540);
	view = View(Position, Size);
	view.setViewport(FloatRect(0.f,0.f,1.f,1.f));
}

Views::Views(Vector2f _position, Vector2f _size, FloatRect _viewport)
{
	Zoom = false;
	Dezoom = false;
	Move = true;

	Size = _size;
	Position = _position;
	view = View(Position, Size);
	view.setViewport(_viewport);
}

void Views::Update(Vector2i _limit, list<Button_Sprite> &_move, Vector2f _position)
{
	for (Button_Sprite& Current_Shape : _move)
	{
		if (Current_Shape.Get_Shape().getGlobalBounds().contains(_position))
		{
			if ((int)Current_Shape.Get_Rotate() == 90 &&
				view.getCenter().x < (_limit.x * Taille_tile) - ((view.getSize().x / 2) - 180))
				Position.x += 200 * MainTime.GetTimeDeltaF();

			if ((int)Current_Shape.Get_Rotate() == 270 &&
				view.getCenter().x > view.getSize().x / 2 - 180)
				Position.x -= 200 * MainTime.GetTimeDeltaF();

			if ((int)Current_Shape.Get_Rotate() == 180 &&
				view.getCenter().y < (_limit.y * Taille_tile) - ((view.getSize().y / 2) - 180))
				Position.y += 200 * MainTime.GetTimeDeltaF();

			if ((int)Current_Shape.Get_Rotate() == 0 &&
				view.getCenter().y > view.getSize().y / 2 - 180)
				Position.y -= 200 * MainTime.GetTimeDeltaF();

			Current_Shape.Set_ColorShape(Color::Red);
		}
		else
			Current_Shape.Set_ColorShape(Color::White);
	}

	if (Keyboard::isKeyPressed(Keyboard::F2))
	{
		Size = Vector2f(1920, 1080);
		view.setSize(Size);
	}

	if (Keyboard::isKeyPressed(Keyboard::P))
		Zoom = true;
	else
		Zoom = false;
	if (Keyboard::isKeyPressed(Keyboard::M))
		Dezoom = true;
	else
		Dezoom = false;

	if (Keyboard::isKeyPressed(Keyboard::LControl) && Mouse::isButtonPressed(Mouse::Left))
	{
		if (Move)
		{
			Move = false;
			last_Past = _position;
		}
		else
		{
			Position += last_Past - _position;
			last_Past = _position;
		}
	}
	else
		Move = true;

	if (Keyboard::isKeyPressed(Keyboard::BackSpace))
		Position = Vector2f(840, 420);

	if (Zoom)
	{
		Size.x -= 1920 * MainTime.GetTimeDeltaF();
		Size.y -= 1080 * MainTime.GetTimeDeltaF();
		view.setSize(Size);
	}
	if (Dezoom)
	{
		Size.x += 1920 * MainTime.GetTimeDeltaF();
		Size.y += 1080 * MainTime.GetTimeDeltaF();
		view.setSize(Size);
	}

	view.setCenter(Position);
}

void Views::Update(Vector2i _limit, Hero _player)
{
	if (_player.Get_Position().x > 960 && _player.Get_Position().x < (_limit.x * 32) - 960)
		Position.x = _player.Get_Position().x;

	if (_player.Get_Position().y > 540 && _player.Get_Position().y < (_limit.y * 32) - 540)
		Position.y = _player.Get_Position().y;

	view.setCenter(Position);
}

void Views::Display()
{
	App.Get_Window().setView(view);
}