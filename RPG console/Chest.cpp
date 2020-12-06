#include "Chest.h"

Chest::Chest()
{
	Probabilité = 0;
}

void Chest::Take_Objet(Hero& _hero, int x)
{
	int i = 0;
	for (Item* Objet_actuel : Objet)
	{
		i++;
		if (i == x)
		{
			Weapon* tmpweapon = dynamic_cast<Weapon*>(Objet_actuel);
			if (tmpweapon)
			{
				if (Objet_actuel == NULL)
					throw Erreur(1, "L'objet est Null", 1);
				else
					_hero.Set_Weapon(*tmpweapon);
			}

			Armor* tmpArmor = dynamic_cast<Armor*>(Objet_actuel);
			if (tmpArmor)
			{
				if (Objet_actuel == NULL)
					throw Erreur(1, "L'objet est Null", 1);
				else
					_hero.Set_Armor(*tmpArmor);
			}

			Consumable* tmpConsumable = dynamic_cast<Consumable*>(Objet_actuel);
			if (tmpConsumable)
			{
				if (Objet_actuel == NULL)
					throw Erreur(1, "L'objet est Null", 1);
				else
					_hero.Set_Consumable(*tmpConsumable);
			}

			break;
		}
	}
}

void Chest::display_coffre()
{
	cout << "Dans le Coffre il y a" << endl;
	for (Item* Objet_actuel : Objet)
	{
		Weapon* tmpweapon = dynamic_cast<Weapon*>(Objet_actuel);
		if (tmpweapon)
		{
			cout << "Epee :" << endl;
		}

		Armor* tmpArmor = dynamic_cast<Armor*>(Objet_actuel);
		if (tmpArmor)
		{
			cout << "armor :" << endl;
		}

		Consumable* tmpConsumable = dynamic_cast<Consumable*>(Objet_actuel);
		if (tmpConsumable)
		{
			cout << "Consommable :" << endl;
		}
		cout << endl;
	}
	system("pause");
	system("CLS");
}