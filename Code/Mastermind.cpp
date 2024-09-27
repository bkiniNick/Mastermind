#include "Mastermind.h"

/// <summary>
/// le constructeur de mastermind s'occupe du remplissage de la liste chaînée list par tout les combinaisons possibles
/// et le tableau de combinaisons possibles (qui contient les pointeurs des combinaisons créées )sera rempli en deuxième temps 
/// grâce à la liste 
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
/// le destructeur s'occupe de libérer la mémoire alouée pour les combinaisons 
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
/// la méthode parcours la liste chaînée à l'aide d'un itérateur 
/// tout en incrémentant un compteur pour savoir le nombre d'élements de la liste 
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
/// Retourne un élément de la liste en position index
/// </summary>
/// <param name="index">La position de l'élément à retourner</param>
/// <returns>L'élément qui est à la position index</returns>
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
/// Vérifie si une combinaison candidate (_toValidate) est une combinaison possible
/// en se basant sur une combinaison déjà essayée (_tried) et un tableau de verdicts (_tabVerdicts).
/// Le tableau de verdicts représente les évaluations pour chaque couleur de la combinaison tentée.
///
/// La méthode renvoie true si la combinaison est valide selon les verdicts, sinon false.
/// </summary>
/// <param name="_toValidate">Combinaison candidate à valider.</param>
/// <param name="_tried">Combinaison précédemment essayée.</param>
/// <param name="_tabVerdicts">Tableau contenant les verdicts pour chaque couleur de _tried.</param>
/// <returns>Retourne true si la combinaison candidate respecte les critères de validation, sinon false.</returns>
bool Mastermind::isPossibleCombination(Combination* _toValidate, Combination* _tried, short* _tabVerdicts)
{
	
	bool keepCombination = true;

	// Parcours de chaque position de la combinaison.
	int n = 0;
	while (n < COMBINATION_LENGTH)
	{
		// Vérification des conditions selon les verdicts :

		// Si la couleur à la position n est correcte (même couleur et même position), 
		// mais le verdict est "Mauvaise couleur" (3), la combinaison n'est pas valide.
		if (_toValidate->getColor(n) == _tried->getColor(n) && _tabVerdicts[n] == 3)
		{
			keepCombination = false;
		}

		// Si la couleur à la position n est incorrecte mais le verdict est "Bonne couleur, bonne place" (1),
		// la combinaison n'est pas valide.
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 1)
		{
			keepCombination = false;
		}

		// Si la couleur à la position n est correcte, mais le verdict est "Bonne couleur, mauvaise place" (2),
		// la combinaison n'est pas valide.
		if (_toValidate->getColor(n) == _tried->getColor(n) && _tabVerdicts[n] == 2)
		{
			keepCombination = false;
		}

		// Si la couleur à la position n est incorrecte, mais le verdict est "Bonne couleur, mauvaise place" (2),
		// vérifier si cette couleur existe ailleurs dans la combinaison.
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 2)
		{
			int x = 0;
			bool isColorExists = false;

			// Vérifie si la couleur existe à une autre position.
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

		// Si la couleur à la position n est incorrecte, mais le verdict est "Mauvaise couleur" (3),
		// vérifier si cette couleur n'existe pas dans la combinaison.
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 3)
		{
			int x = 0;
			bool isColorExists = false;

			// Parcours pour vérifier si la couleur est présente ailleurs dans la combinaison.
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
/// Nettoie la liste des combinaisons en supprimant celles qui ne sont pas considérées comme possibles.
/// 
/// </summary>
/// <param name="_ref">Combinaison de référence utilisée pour comparer les autres combinaisons.</param>
/// <param name="_tabVerdicts">Tableau contenant les verdicts pour chaque couleur de la combinaison de référence.</param>
/// <returns>Retourne le nombre total de combinaisons supprimées de la liste.</returns>


int Mastermind::cleanList(Combination* _ref, short* _tabVerdicts)
{
	
	//compteur des combinaisons supprimées 
	int RemovedCombination = 0;
	// Initialiser un itérateur pour parcourir la liste des combinaisons.
	Iterator<Combination> iter = list->begin();
	while (iter != list->end())
	{

		// Vérifier si la combinaison actuelle (pointée par l'itérateur) est une combinaison possible.
		if (isPossibleCombination((&iter), _ref, _tabVerdicts) == false)
		{
			//Si la combinaison n'est pas valide, préparer l'itérateur pour suppression.
			Iterator<Combination> toRemove = iter;
			++iter;
			if (list->remove((&toRemove)))
			{
				RemovedCombination++;


			}

		}
		else

		{
			++iter;  // Si la combinaison est valide, passer à la combinaison suivante.
		}


	}

	return RemovedCombination;
}
/// <summary>
/// Génère toutes les combinaisons de couleurs possibles pour une longueur de combinaison de 4 couleurs ,
/// en se basant sur la notion d'arrangements avec répétition. Chaque combinaison est ajoutée à une liste.
/// </summary>
/// <param name="combinaison">Tableau de couleurs représentant la combinaison actuelle en cours de génération.</param>
/// <param name="x">Indice actuel dans la combinaison où une couleur doit être ajoutée.</param>
/// <param name="addedCombinations">Nombre de combinaisons déjà générées et ajoutées à la liste.</param>

void Mastermind::GetColorCombinations(Color combinaison[], int x, int addedCombinations)
{

	/// Cette méthode utilise un processus récursif pour parcourir toutes les possibilités de couleurs à chaque position dans la combinaison.
	/// La méthode suit la notion d'arrangement avec répétition, où chaque position de la combinaison peut contenir une couleur parmi un ensemble de couleurs prédéfinies,
	/// et chaque couleur peut apparaître plusieurs fois dans une même combinaison.


	// Lorsque la combinaison atteint la longueur maximale définie (COMBINATION_LENGTH), elle est ajoutée à la liste.
	if (x == COMBINATION_LENGTH)
	{
		list->add(new Combination(combinaison[0], combinaison[1], combinaison[2], combinaison[3]));

		addedCombinations++;  // à chaque combinaisons ajoutées  on incremente de 1 le compteur de combinaisons ajoutées

		x = 0;

		// Si le nombre maximal de combinaisons possibles est atteint, arrêter la récursion.
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
		GetColorCombinations(combinaison, x + 1, addedCombinations);  // Récurse pour générer la combinaison suivante.
	}
}


