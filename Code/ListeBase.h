#pragma once
#include "IterateurBase.h"

template <class T>
class ListeBase
{
public:
	
	//m�thodes usuelles vues en classe pour une liste
	virtual bool ajouter(T* _element) = 0;
	virtual bool retirer(T* _element) = 0;
	virtual int getNbElements() const = 0;
	//indique si la liste est vide
	virtual bool isEmpty() const = 0;
	//vide la liste et la remet dans l'�tat initial
	virtual void vider() = 0;
	
};

