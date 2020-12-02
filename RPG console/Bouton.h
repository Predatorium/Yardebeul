#pragma once
#include "Tools.h"

class Bouton
{
private :
	RectangleShape RShape;
	Text Texte;
	string Name;

public :
	Bouton() = default;
	Bouton(string _name, string _nameFont, float _sizeTexte, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color);
	~Bouton() = default;

	inline string Get_Name() { return Name; };
	inline Text& Get_Texte() { return Texte; };
	inline RectangleShape& Get_Shape() { return RShape; };

	void Set_Color(Color _color);
	void Set_ColorText(Color _color) { Texte.setFillColor(_color); };
	void Set_ColorShape(Color _color) { RShape.setOutlineColor(_color); };

	void Display();
};

class RShape
{
private:
	RectangleShape Shape;
	string Name;
	Color color;
	
	float Rotate;

public:
	RShape() = default;
	RShape(string _name, float _rotate, Vector2f _sizeShape, float _outlinesize, Vector2f _Position, Color _color);
	~RShape() = default;

	inline string Get_Name() { return Name; };
	inline RectangleShape& Get_Shape() { return Shape; };
	inline Color Get_Color() { return color; };
	inline float Get_Rotate() { return Rotate; };

	void Set_ColorShape(Color _color) { color = _color; };

	void Display();
};