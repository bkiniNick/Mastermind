#pragma once



#include "Combination.h"
#include "Color.h"
#include "constants.h"

//Ctrl-click pour aller dans votre
#include <LinkedList.h>

const int NB_POSSIBLE_COMBINATIONS = 4096;
const Color COLORS[] = { Color(1),Color(2), Color(3), Color(4), Color(5), Color(6), Color(7), Color(8) };

class Mastermind
{
public:
  
    Mastermind(LinkedList<Combination>* _list);
    ~Mastermind();

    int getNbElements() const;
    Combination* getElement(int _index) const;

    int cleanList(Combination* _ref, short* _tabVerdicts);

private:

	bool isPossibleCombination(Combination* _toValidate, Combination* _ref, short* _tabVerdicts);
    Combination* tabCombinations[NB_POSSIBLE_COMBINATIONS];
    LinkedList<Combination>* list; //Contient toutes les combinaisons de couleurs possibles, selon le contexte.
   void  GetColorCombinations(Color tab[], int x, int addedCombinations);



    
};
