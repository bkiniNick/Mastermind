#include "Mastermind.h"

/// <summary>
/// le constructeur de mastermind s'occupe du remplissage de la liste cha�n�e list par tout les combinaisons possibles
/// et le tableau de combinaisons possibles (qui contient les pointeurs des combinaisons cr��es )sera rempli en deuxi�me temps 
/// gr�ce � la liste 
/// </summary>
/// <param name="_list"></param>
Mastermind::Mastermind(LinkedList<Combination>* _list)
{
	list = _list;
	Color colorsForACombination[COMBINATION_LENGTH];
	int x = 0;
	int addedCombination = 0;

	GetColorCombinations(colorsForACombination, x, addedCombination);
	addedCombination = 0;

	Iterator<Combination> iter = list->begin();
	for (int i = 0; i < NB_POSSIBLE_COMBINATIONS; ++i) {
		tabCombinations[addedCombination] = &iter;
		++iter;
		++addedCombination;
	}
	
}

/// <summary>
/// le destructeur s'occupe de lib�rer la m�moire alou�e pour les combinaisons 
/// </summary>
Mastermind::~Mastermind()
{


	for (int i = 0; i < NB_POSSIBLE_COMBINATIONS; ++i) {
		if (tabCombinations[i] != nullptr) {
			delete (tabCombinations[i]);
			tabCombinations[i] = nullptr;  
		}
	}




}

/// <summary>
/// la m�thode parcours la liste cha�n�e � l'aide d'un it�rateur 
/// tout en incr�mentant un compteur pour savoir le nombre d'�lements de la liste 
/// </summary>
/// <returns>le nombre de combinaisons se trouvant dans la liste </returns>

int Mastermind::getNbElements() const
{

	Iterator<Combination> iter = list->begin();
	int x = 0;

	
	while (iter != list->end())
	{
		x++;
		iter = ++iter;

	}
	return x;

}

/// <summary>
/// Retourne un �l�ment de la liste en position index
/// </summary>
/// <param name="index">La position de l'�l�ment � retourner</param>
/// <returns>L'�l�ment qui est � la position index</returns>
Combination* Mastermind::getElement(int index) const
{
	
	Iterator<Combination> iter = list->begin();
	int x = 0;
	Combination* combi = nullptr;


	
	while (x <= index)
	{

		if (x == index)
		{
			combi = &iter;
		}
		x++;

	}
	return combi;


}
/// <summary>
/// V�rifie si une combinaison candidate (_toValidate) est une combinaison possible
/// en se basant sur une combinaison d�j� essay�e (_tried) et un tableau de verdicts (_tabVerdicts).
/// Le tableau de verdicts repr�sente les �valuations pour chaque couleur de la combinaison tent�e.
///
/// La m�thode renvoie true si la combinaison est valide selon les verdicts, sinon false.
/// </summary>
/// <param name="_toValidate">Combinaison candidate � valider.</param>
/// <param name="_tried">Combinaison pr�c�demment essay�e.</param>
/// <param name="_tabVerdicts">Tableau contenant les verdicts pour chaque couleur de _tried.</param>
/// <returns>Retourne true si la combinaison candidate respecte les crit�res de validation, sinon false.</returns>
bool Mastermind::isPossibleCombination(Combination* _toValidate, Combination* _tried, short* _tabVerdicts)
{
	
	bool keepCombination = true;

	// Parcours de chaque position de la combinaison.
	int n = 0;
	while (n < COMBINATION_LENGTH)
	{
		// V�rification des conditions selon les verdicts :

		// Si la couleur � la position n est correcte (m�me couleur et m�me position), 
		// mais le verdict est "Mauvaise couleur" (3), la combinaison n'est pas valide.
		if (_toValidate->getColor(n) == _tried->getColor(n) && _tabVerdicts[n] == 3)
		{
			keepCombination = false;
		}

		// Si la couleur � la position n est incorrecte mais le verdict est "Bonne couleur, bonne place" (1),
		// la combinaison n'est pas valide.
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 1)
		{
			keepCombination = false;
		}

		// Si la couleur � la position n est correcte, mais le verdict est "Bonne couleur, mauvaise place" (2),
		// la combinaison n'est pas valide.
		if (_toValidate->getColor(n) == _tried->getColor(n) && _tabVerdicts[n] == 2)
		{
			keepCombination = false;
		}

		// Si la couleur � la position n est incorrecte, mais le verdict est "Bonne couleur, mauvaise place" (2),
		// v�rifier si cette couleur existe ailleurs dans la combinaison.
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 2)
		{
			int x = 0;
			bool isColorExists = false;

			// V�rifie si la couleur existe � une autre position.
			while (x < COMBINATION_LENGTH)
			{
				if (_toValidate->getColor(x) == _tried->getColor(n))
				{
					isColorExists = true;
					break;
				}
				x++;
			}

			// Si la couleur n'existe pas ailleurs dans la combinaison, elle est invalide.
			if (isColorExists == false)
			{
				keepCombination = false;
			}
		}

		// Si la couleur � la position n est incorrecte, mais le verdict est "Mauvaise couleur" (3),
		// v�rifier si cette couleur n'existe pas dans la combinaison.
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 3)
		{
			int x = 0;
			bool isColorExists = false;

			// Parcours pour v�rifier si la couleur est pr�sente ailleurs dans la combinaison.
			while (x < COMBINATION_LENGTH)
			{
				if (_toValidate->getColor(x) == _tried->getColor(n))
				{
					isColorExists = true;
					break;
				}
				x++;
			}

			// Si la couleur existe ailleurs, la combinaison est invalide.
			if (isColorExists == true)
			{
				keepCombination = false;
			}
		}

		
		n++;
	}

	// Retourne true si la combinaison est valide, sinon false.
	return keepCombination;
}

/// <summary>
/// Nettoie la liste des combinaisons en supprimant celles qui ne sont pas consid�r�es comme possibles.
/// 
/// </summary>
/// <param name="_ref">Combinaison de r�f�rence utilis�e pour comparer les autres combinaisons.</param>
/// <param name="_tabVerdicts">Tableau contenant les verdicts pour chaque couleur de la combinaison de r�f�rence.</param>
/// <returns>Retourne le nombre total de combinaisons supprim�es de la liste.</returns>


int Mastermind::cleanList(Combination* _ref, short* _tabVerdicts)
{
	
	//compteur des combinaisons supprim�es 
	int RemovedCombination = 0;
	// Initialiser un it�rateur pour parcourir la liste des combinaisons.
	Iterator<Combination> iter = list->begin();
	while (iter != list->end())
	{

		// V�rifier si la combinaison actuelle (point�e par l'it�rateur) est une combinaison possible.
		if (isPossibleCombination((&iter), _ref, _tabVerdicts) == false)
		{
			//Si la combinaison n'est pas valide, pr�parer l'it�rateur pour suppression.
			Iterator<Combination> toRemove = iter;
			++iter;
			if (list->remove((&toRemove)))
			{
				RemovedCombination++;


			}

		}
		else

		{
			++iter;  // Si la combinaison est valide, passer � la combinaison suivante.
		}


	}

	return RemovedCombination;
}
/// <summary>
/// G�n�re toutes les combinaisons de couleurs possibles pour une longueur de combinaison de 4 couleurs ,
/// en se basant sur la notion d'arrangements avec r�p�tition. Chaque combinaison est ajout�e � une liste.
/// </summary>
/// <param name="combinaison">Tableau de couleurs repr�sentant la combinaison actuelle en cours de g�n�ration.</param>
/// <param name="x">Indice actuel dans la combinaison o� une couleur doit �tre ajout�e.</param>
/// <param name="addedCombinations">Nombre de combinaisons d�j� g�n�r�es et ajout�es � la liste.</param>

void Mastermind::GetColorCombinations(Color combinaison[], int x, int addedCombinations)
{

	/// Cette m�thode utilise un processus r�cursif pour parcourir toutes les possibilit�s de couleurs � chaque position dans la combinaison.
	/// La m�thode suit la notion d'arrangement avec r�p�tition, o� chaque position de la combinaison peut contenir une couleur parmi un ensemble de couleurs pr�d�finies,
	/// et chaque couleur peut appara�tre plusieurs fois dans une m�me combinaison.


	// Lorsque la combinaison atteint la longueur maximale d�finie (COMBINATION_LENGTH), elle est ajout�e � la liste.
	if (x == COMBINATION_LENGTH)
	{
		list->add(new Combination(combinaison[0], combinaison[1], combinaison[2], combinaison[3]));

		addedCombinations++;  // � chaque combinaisons ajout�es  on incremente de 1 le compteur de combinaisons ajout�es

		x = 0;

		// Si le nombre maximal de combinaisons possibles est atteint, arr�ter la r�cursion.
		if (addedCombinations == NB_POSSIBLE_COMBINATIONS)
		{
			return;
		}
		return;
	}

	// Parcours de toutes les couleurs disponibles  pour les positions restantes dans la combinaison.
	for (int i = 0; i < NB_COLORS; i++)
	{
		combinaison[x] = COLORS[i];
		GetColorCombinations(combinaison, x + 1, addedCombinations);  // R�curse pour g�n�rer la combinaison suivante.
	}
}


