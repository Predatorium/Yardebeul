#pragma once
#include "Tools.h"

class Button_Text
{
private :
	RectangleShape Shape;
	Text Texte;
	string Name;

public :
	Button_Text() = default;
	Button_Text(string _name, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color);
	~Button_Text() = default;

	inline string Get_Name() { return Name; };
	inline Text& Get_Texte() { return Texte; };
	inline RectangleShape& Get_Shape() { return Shape; };

	void Set_Color(Color _color);
	void Set_ColorText(Color _color) { Texte.setFillColor(_color); };
	void Set_ColorShape(Color _color) { Shape.setOutlineColor(_color); };

	void Display();
};

class Button_Sprite
{
private:
	RectangleShape Shape;
	string Name;
	Color color;
	
	float Rotate;

public:
	Button_Sprite() = default;
	Button_Sprite(string _name, float _rotate, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color);
	~Button_Sprite() = default;

	inline string Get_Name() { return Name; };
	inline RectangleShape& Get_Shape() { return Shape; };
	inline Color Get_Color() { return color; };
	inline float Get_Rotate() { return Rotate; };

	void Set_ColorShape(Color _color) { color = _color; };

	void Display();
};

class Box
{
private:
	RectangleShape Outline;
	RectangleShape Rod;
	Text Texte;

public:
	Box() = default;
	Box(string _max, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color);
	~Box() = default;

	void Display(string _currentstat);
};