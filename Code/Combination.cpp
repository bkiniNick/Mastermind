#include "Combination.h"
using namespace std;

Combination::Combination(Color c1, Color c2, Color c3, Color c4)
{
	tabColors[0] = c1;
	tabColors[1] = c2;
	tabColors[2] = c3;
	tabColors[3] = c4;
}

Color Combination::getColor(int index) const
{
	if (index < 0 || index > 3) throw invalid_argument("Votre index n'est pas entre 0 et 3");

	return tabColors[index];
}

Combination::~Combination()
{
}

bool Combination::operator< (const Combination& _combination) const
{
	return true;
}

bool Combination::operator > (const Combination& _combination) const
{
	return true;
}

bool Combination::operator == (const Combination& _combination) const
{
	//TODO : Compléter
	bool IsOnTheRightPosition = false;
	for (int i = 0; i < NB_COLORS; i++)
	{
		Color c = getColor(i);
		if (c == _combination.tabColors[i])
		{
			IsOnTheRightPosition = true;
		}
		else
		{
			IsOnTheRightPosition = false;
			break;
		}
	}
	return IsOnTheRightPosition;
}

bool Combination::operator != (const Combination& _combination) const
{
	return !(*this == _combination);
}

void Combination::display() const
{
	cout << tabColors[0] << endl;
	cout << tabColors[1] << endl;
	cout << tabColors[2] << endl;
	cout << tabColors[3] << endl;
}
