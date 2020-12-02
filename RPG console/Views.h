#pragma once
#include "Tools.h"
#include "Bouton.h"
#include "Hero.h"

class Views
{
private :
	View view;
	Vector2f Position;
	Vector2f last_Past;
	bool Move;
	Vector2f Size;
	bool Zoom;
	bool Dezoom;

public :
	Views();
	Views(Vector2f _position, Vector2f _size, FloatRect _viewport);
	~Views() = default;

	inline Vector2f Get_Position() { return Position; };
	inline View Get_View() { return view; };
	inline Vector2f Get_Size() { return Size; };
	inline bool Get_Zoom() { return Zoom; };
	inline bool Get_Dezoom() { return Dezoom; };

	inline void Set_Position(Vector2f _position) { Position = _position; };
	inline void Set_Zoom(bool _zoom) { Zoom = _zoom; };
	inline void Set_Dezoom(bool _dezoom) { Dezoom = _dezoom; };

	void Update_Editor(Vector2i _limit, list<RShape> &_move, Vector2f _position);
	void Update_Game(Vector2i _limit, Hero _player);
	void Display();
};