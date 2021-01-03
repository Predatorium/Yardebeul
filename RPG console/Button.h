#pragma once
#include "Tools.h"

class Button_Text
{
protected :
	RectangleShape shape;
	Text Texte;
	string Name;

public :
	Button_Text() = default;
	Button_Text(string _name, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color);
	~Button_Text() = default;

	inline string Get_Name() { return Name; };
	inline Text& Get_Texte() { return Texte; };
	inline RectangleShape& Get_Shape() { return shape; };
	void Set_String(string _string);

	void Set_Color(Color _color);
	void Set_ColorText(Color _color) { Texte.setFillColor(_color); };
	void Set_ColorShape(Color _color) { shape.setOutlineColor(_color); };

	void Display();
};

class Button_Sprite
{
private:
	RectangleShape shape;
	string Name;
	Color color;
	Sprite sprite;
	float Rotate;

public:
	Button_Sprite() = default;
	Button_Sprite(string _name, float _rotate, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color);
	~Button_Sprite() = default;

	inline string Get_Name() { return Name; };
	inline RectangleShape& Get_Shape() { return shape; };
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
	Vector2f Position;
	Vector2f Size;
	int Max;
	Text Texte;

public:
	Box() = default;
	Box(int _max, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color);
	~Box() = default;

	inline RectangleShape& Get_Shape() { return Outline; };

	void Display(string _currentstat);
};