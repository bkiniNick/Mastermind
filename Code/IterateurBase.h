#include "Noeud.h"
#pragma once
template <class T>
class IterateurBase{
public:

	//m�thodes usuelles vues en classe pour un it�rateur
	virtual void operator++() = 0;
	virtual void operator--() = 0;
	virtual T* operator->() = 0;
	virtual T& operator*() = 0;
	//un ajout pratique dans le cadre de ce TP
	virtual Noeud<T>* getCourant() = 0;
};
