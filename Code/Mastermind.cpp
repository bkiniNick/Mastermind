#include "Mastermind.h"


Mastermind::Mastermind(LinkedList<Combination>* _list)
{
	//TODO: Compl�ter
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

Mastermind::~Mastermind()
{

	//Iterator<Combination> iter = list->begin();
	////TODO: Compl�ter
	//while (iter != list->end())
	//{
	//	Iterator<Combination> toRemove = iter;
	//	++iter;

	//	list->remove(&toRemove);

	//}
	for (int i = 0; i < NB_POSSIBLE_COMBINATIONS; ++i) {
		if (tabCombinations[i] != nullptr) {
			delete (tabCombinations[i]);
			tabCombinations[i] = nullptr;  // Facultatif, mais �vite les double suppressions
		}
	}




}


int Mastermind::getNbElements() const
{

	Iterator<Combination> iter = list->begin();
	int x = 0;

	//TODO: Compl�ter
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
	//TODO: Compl�ter
	Iterator<Combination> iter = list->begin();
	int x = 0;
	Combination* combi = nullptr;


	//TODO: Compl�ter
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

bool Mastermind::isPossibleCombination(Combination* _toValidate, Combination* _tried, short* _tabVerdicts)
{
	//A COMPLETER
	//V�rifiez si la combinaison toValidate doit �tre gard�e ou non de la liste, en fonction d'une combinaison essay�e et d'un tableau de 4 verdicts.
	//Pour chacune des couleurs pr�sentes dans toValidate, 3 verdicts possibles doivent �tre pris en consid�ration pour �l�miner ou non la combinaison, 
	//il s'agit de "Bonne couleur, bonne place" (valeur 1), "Bonne couleur, mauvaise place" (valeur 2) et "Mauvaise couleur" (valeur 3).

	//Voici un �bauche d'algorithme qui devrait vous aider � compl�ter cette m�thode:
	//Pour chacune des couleurs de la combinaison toValidate, v�rifiez:

	//Si le verdict est 1 (Bonne couleur, bonne place) et que la combinaison de couleurs � valider n'a pas la couleur � la m�me place que 
	//la combinaison essay�e, il faut la retirer de la liste.

	//Si le verdict est 2 (Bonne couleur, mauvaise place) et que la combinaison de couleurs � valider n'a pas la couleur � un autre emplacement que
	//celui de la combinaison essay�e, il faut la retirer de la liste.

	//Si le verdict est 3 (Mauvaise couleur) et que la combinaison de couleurs � valider a la couleur, il faut la retirer de la liste.

	//Retournez true si la combinaison est valide (respecte les verdicts) et false dans le cas contraire.


	bool keepCombination = true;

	//TODO: Compl�ter l'algorithme ici


	int n = 0;
	while (n < COMBINATION_LENGTH)
	{
		if (_toValidate->getColor(n) == _tried->getColor(n) && _tabVerdicts[n] == 3)
		{
			keepCombination = false;
		}
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 1)
		{
			keepCombination = false;
		}
		if (_toValidate->getColor(n) == _tried->getColor(n) && _tabVerdicts[n] == 2)
		{
			keepCombination = false;
		}
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 2)
		{
			int x = 0;
			bool isColorExists = false;

			while (x < COMBINATION_LENGTH)
			{
				if (_toValidate->getColor(x) == _tried->getColor(n))
				{
					isColorExists = true;
					break;
				}
				x++;

			}
			if (isColorExists == false)
			{
				keepCombination = false;

			}

		}
		if (_toValidate->getColor(n) != _tried->getColor(n) && _tabVerdicts[n] == 3)
		{
			int x = 0;
			bool isColorExists = false;

			while (x < COMBINATION_LENGTH)
			{
				if (_toValidate->getColor(x) == _tried->getColor(n))
				{
					isColorExists = true;
					break;
				}
				x++;

			}
			if (isColorExists == true)
			{
				keepCombination = false;

			}

		}
		n++;

	}






	return keepCombination;
}


int Mastermind::cleanList(Combination* _ref, short* _tabVerdicts)
{
	//A COMPLETER
	//�pure la liste de combinaisons de couleurs en fonction de la combinaison re�ue et des 4 verdicts (valeurs 1 � 3).
	//Pour chacune des combinaisons de la liste, v�rifier si elle doit �tre retir�e ou non de liste.
	//Le nombre de combinaisons supprim�es doit �tre retourn�.

	//Cette fonction appelle isPossibleCombination pour savoir si la combinaison inspect�e est � garder ou non

	//TODO: Compl�ter

	int RemovedCombination = 0;
	Iterator<Combination> iter = list->begin();
	while (iter != list->end())
	{


		if (isPossibleCombination((&iter), _ref, _tabVerdicts) == false)
		{
			Iterator<Combination> toRemove = iter;
			++iter;
			if (list->remove((&toRemove)))
			{
				RemovedCombination++;


			}

		}
		else

		{
			++iter;
		}


	}

	return RemovedCombination;
}
void Mastermind::GetColorCombinations(Color combinaison[], int x, int addedCombinations)

{

	 
	if (x == COMBINATION_LENGTH)
	{
		
		list->add(new Combination(combinaison[0], combinaison[1], combinaison[2], combinaison[3]));

		addedCombinations++;
		x = 0;
		// si le nombre de combinaison est atteint arr�t forc� 
		if (addedCombinations == NB_POSSIBLE_COMBINATIONS)
		{
			return;

		}
		return;
	}


	for (int i = 0; i < NB_COLORS;i++)
	{


		combinaison[x] = COLORS[i];
		GetColorCombinations(combinaison, x + 1, addedCombinations);


	}


}

