#pragma once
#include "Tools.h"
#include "Button.h"
#include "Hero.h"

class Views
{
private :
	View view;
	Vector2f Position;
	Vector2f last_Past;
	Vector2f Size;
	bool Move;
	bool Zoom;
	bool Dezoom;

public :
	Views();
	Views(Vector2f _position, Vector2f _size, FloatRect _viewport);
	~Views() = default;

	inline Vector2f Get_Position() { return Position; };
	inline View& Get_View() { return view; };
	inline Vector2f Get_Size() { return Size; };
	inline bool Get_Zoom() { return Zoom; };
	inline bool Get_Dezoom() { return Dezoom; };

	inline void Set_Position(Vector2f _position) { Position = _position; };
	inline void Set_Zoom(bool _zoom) { Zoom = _zoom; };
	inline void Set_Dezoom(bool _dezoom) { Dezoom = _dezoom; };

	bool Occlusion_CullingRectangle(Vector2f _position);
	bool Occlusion_CullingCircle(Vector2f _position);

	void Update_Editeur(Vector2i _limit, Vector2f _position);
	void Update(Vector2i _limit, Vector2f _player);
	void Update_MiniMap(Vector2i _limit, Vector2f _player);
	void Display();
};