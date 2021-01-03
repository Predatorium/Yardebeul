#include "Views.h"
#include "Editeur.h"

#define MapSizeX 1920/1080
#define MapSizeY 1080/1920

Views::Views()
	: View(Vector2f(960, 540), Vector2f(1920, 1080))
{
	Zoom = false;
	Dezoom = false;
	Move = true;

	setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));
}

Views::Views(Vector2f _position, Vector2f _size, FloatRect _viewport)
	: View(_position, _size)
{
	Zoom = false;
	Dezoom = false;
	Move = true;

	setViewport(_viewport);
}

bool Views::Occlusion_CullingRectangle(Vector2f _position)
{
	if (FloatRect(getCenter().x - getSize().x / 2 - 32, getCenter().y - getSize().y / 2 - 32, getSize().x + 32, getSize().y + 32).contains(_position))
		return true;
	else
		return false;
}

bool Views::Occlusion_CullingCircle(Vector2f _position)
{
	if (Circle_Collision(getCenter(), _position, this->getSize().x / 7, this->getSize().x / 6))
		return true;
	else
		return false;
}

void Views::Update_Editeur(Vector2i _limit, Vector2f _position)
{
	if (Keyboard::isKeyPressed(Keyboard::F2))
		setSize(Vector2f(1920, 1080));

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
			setCenter(getCenter() + last_Past - _position);
			last_Past = _position;
		}
	}
	else
		Move = true;

	if (Keyboard::isKeyPressed(Keyboard::BackSpace))
		setCenter(Vector2f(840, 420));

	if (Zoom)
		setSize(getSize().x - 1920 * MainTime.GetTimeDeltaF(), getSize().y - 1080 * MainTime.GetTimeDeltaF());
	if (Dezoom)
		setSize(getSize().x + 1920 * MainTime.GetTimeDeltaF(), getSize().y + 1080 * MainTime.GetTimeDeltaF());
}

void Views::Update(Vector2i _limit, Vector2f _player)
{
	if (_player.x > getSize().x / 2 && _player.x < (_limit.x * 32) - getSize().x / 2)
		this->setCenter(_player.x, getSize().y);
	else if (_player.x < getSize().x / 2)
		setCenter(getSize().x / 2, getSize().y);
	else if (_player.x > (_limit.x * 32) - getSize().x / 2)
		setCenter((_limit.x * 32) - getSize().x / 2, getSize().y);

	if (_player.y > getSize().y / 2 && _player.y < (_limit.y * 32) - getSize().y / 2)
		this->setCenter(getCenter().x, _player.y);
	else if (_player.y < getSize().y / 2)
		setCenter(getCenter().x, getSize().y / 2);
	else if (_player.y > (_limit.y * 32) - getSize().y / 2)
		setCenter(getCenter().x, (_limit.y * 32) - getSize().y / 2);
}

void Views::Update_MiniMap(Vector2i _limit, Vector2f _player)
{
	if (Keyboard::isKeyPressed(Keyboard::Add) && getSize().x > 576 && getSize().y > 324)
		Zoom = true;
	else
		Zoom = false;
	if (Keyboard::isKeyPressed(Keyboard::Subtract) && getSize().x < 3840 && getSize().y < 2160)
		Dezoom = true;
	else
		Dezoom = false;

	if (Zoom)
		setSize(getSize().x - 1920 * MainTime.GetTimeDeltaF(), getSize().y - 1080 * MainTime.GetTimeDeltaF());
	if (Dezoom)
		setSize(getSize().x + 1920 * MainTime.GetTimeDeltaF(), getSize().y + 1080 * MainTime.GetTimeDeltaF());

	setCenter(_player);
}

void Views::Display()
{
	App.Get_Window().setView(*this);
}