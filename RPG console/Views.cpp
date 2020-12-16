#include "Views.h"
#include "Editeur.h"

#define MapSizeX 1920/1080
#define MapSizeY 1080/1920

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

bool Views::Occlusion_CullingRectangle(Vector2f _position)
{
	if (FloatRect(Position.x - Size.x / 2 - 32, Position.y - Size.y / 2 - 32, Size.x + 32, Size.y + 32).contains(_position))
		return true;
	else
		return false;
}

bool Views::Occlusion_CullingCircle(Vector2f _position)
{
	if (Circle_Collision(Position, _position, Size.x / 4 , Size.x / 4))
		return true;
	else
		return false;
}		

void Views::Update_Editeur(Vector2i _limit, Vector2f _position)
{
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

void Views::Update(Vector2i _limit, Vector2f _player)
{
	if (_player.x > 960 && _player.x < (_limit.x * 32) - 960)
		Position.x = _player.x;
	else if (_player.x < 960)
		Position.x = 960;
	else if (_player.x > (_limit.x * 32) - 960)
		Position.x = (_limit.x * 32) - 960;

	if (_player.y > 540 && _player.y < (_limit.y * 32) - 540)
		Position.y = _player.y;
	else if (_player.y < 540)
		Position.y = 540;
	else if (_player.y > (_limit.y * 32) - 540)
		Position.y = (_limit.y * 32) - 540;

	view.setCenter(Position);
}

void Views::Display()
{
	App.Get_Window().setView(view);
}