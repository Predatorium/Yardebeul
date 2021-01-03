#include "Character.h"

Character::Character(string _name, int _life, int _mana, int _endurance, int _speed, Armor _armor, Weapon _weapon)
	: Entity(_name)
{
	Name = _name;
	Level = 1;
	Speed = _speed;
	Speed_Max = Speed;
	Life_Point = _life;
	Life_Max = Life_Point;
	Mana = _mana;
	Mana_Max = Mana;
	Endurance = _endurance;
	Endurance_Max = Endurance;

	Right = false;
	Left = false;
	Down = false;
	Up = false;

	armor = new Armor(_armor);
	weapon = new Weapon(_weapon);

	Orientation = Direction::Right;

	if(armor->Get_Effect().Get_Affectation() == Affect_Stat::ENDURANCE)
		Endurance += armor->Get_Effect().Get_Power();
	if (armor->Get_Effect().Get_Affectation() == Affect_Stat::LIFE_POINT)
	{
		Life_Point += armor->Get_Effect().Get_Power();
		Life_Max = Life_Point;
	}
	if (armor->Get_Effect().Get_Affectation() == Affect_Stat::MANA)
		Mana += armor->Get_Effect().Get_Power();
	if (armor->Get_Effect().Get_Affectation() == Affect_Stat::SPEED)
		Speed += armor->Get_Effect().Get_Power();
}

Sort* Character::Get_OneSpell(string _name)
{
	for (Sort* Current : Spell)
		if (Current->Get_Name() == _name)
			return Current;
}

Sort* Character::Get_OneSpell(int _it)
{
	int i = 0;
	for (Sort* Current : Spell)
	{
		i++;
		if (i == _it)
			return Current;
	}
}

void Character::Add_Life(int _life)
{
	Life_Point += _life;
	if (Life_Point > Life_Max)
		Life_Point = Life_Max;
	if (Life_Point < 0)
		Life_Point = 0;
}

void Character::Set_Life(int _life)
{
	Life_Point = _life;
	Life_Max = _life;
}

void Character::Add_Mana(int _mana)
{
	Mana += _mana;
	if (Mana > Mana_Max)
		Mana = Mana_Max;
	if (Mana < 0)
		Mana = 0;
}

void Character::Add_Endurance(int _endurance)
{
	Endurance += _endurance;
	if (Endurance > Endurance_Max)
		Endurance = Endurance_Max;
	if (Endurance < 0)
		Endurance = 0;
}

void Character::Add_Speed(int _speed)
{
	Speed += _speed;
	if (Speed > Speed_Max)
		Speed = Speed_Max;
	if (Speed < 0)
		Speed = 0;
}

int Character::Attack(Character* _c)
{
	static int Calcul_Damage = 0;
	Calcul_Damage = (weapon->Damage() * Get_Affinité(weapon->Get_Effect().Get_Element(), _c->Get_Armor()->Get_Effect().Get_Element())) * (1 - (_c->Get_Armor()->Get_Defense() / 100));
	_c->Add_Life(-Calcul_Damage);
	_c->Add_Effect(weapon->Get_Effect());
	return Calcul_Damage;
}

pair<string, int> Character::Use_Spell(Character* _c, Sort _s)
{
	if (_s.Get_Affectation() == Target::Passif)
	{
		static pair<string, int> Calcul = pair("0", 0);
		Calcul = pair("Buff", _s.Get_Effect().Get_Power());
		Effect_Received(_s.Get_Effect());
		return Calcul;
	}
	if (_s.Get_Affectation() == Target::Actif)
	{
		static pair<string, int> Calcul = pair("0",0);
		Calcul = pair("Damage", (_s.Get_Damage() * Get_Affinité(_s.Get_Effect().Get_Element(), _c->Get_Armor()->Get_Effect().Get_Element())) * (1 - (_c->Get_Armor()->Get_Defense() / 100)));
		_c->Add_Life(-Calcul.second);
		_c->Add_Effect(_s.Get_Effect());
		return Calcul;
	}
}

map<string, int> Character::Effect_Update()
{
	static map<string, int> tmp;
	tmp["Pv"] = int(0);
	tmp["Mana"] = int(0);
	tmp["Speed"] = int(0);
	tmp["Endurance"] = int(0);

	for (Effect& Current : Current_Effect)
	{
		if (Current.Get_Affectation() == Affect_Stat::LIFE_POINT)
		{
			Add_Life(-Current.Get_Power() * Current.Get_Level());
			tmp["Pv"] += Current.Get_Power() * Current.Get_Level();
		}

		if (Current.Get_Affectation() == Affect_Stat::MANA)
		{
			Add_Mana(-Current.Get_Power() * Current.Get_Level());
			tmp["Mana"] += Current.Get_Power() * Current.Get_Level();
		}

		if (Current.Get_Affectation() == Affect_Stat::SPEED)
		{
			Add_Speed(-Current.Get_Power() * Current.Get_Level());
			tmp["Speed"] += Current.Get_Power() * Current.Get_Level();
		}

		if (Current.Get_Affectation() == Affect_Stat::ENDURANCE)
		{
			Add_Endurance(-Current.Get_Power() * Current.Get_Level());
			tmp["Endurance"] += Current.Get_Power() * Current.Get_Level();
		}

		Current.Set_Duration(Current.Get_Duration() - 1);
	}

	Current_Effect.remove_if(Effect());

	return tmp;
}

void Character::Effect_Received(Effect _effect)
{
	if (_effect.Get_Affectation() == Affect_Stat::LIFE_POINT)
		Add_Life(_effect.Get_Power() * _effect.Get_Level());

	if (_effect.Get_Affectation() == Affect_Stat::MANA)
		Add_Mana(_effect.Get_Power() * _effect.Get_Level());

	if (_effect.Get_Affectation() == Affect_Stat::SPEED)
		Add_Speed(_effect.Get_Power() * _effect.Get_Level());

	if (_effect.Get_Affectation() == Affect_Stat::ENDURANCE)
		Add_Endurance(_effect.Get_Power() * _effect.Get_Level());
}