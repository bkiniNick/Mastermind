#include <Node.h>
#include <iterator.h>


//Rien � coder dans cette classe, elle est amie (friend) � l'it�rateur,
//Elle a donc acc�s � ses membres priv�s
template <class T>
#pragma once
class IterAccess
{
	public:
		IterAccess(Iterator<T> iter);
		Node<T> * getCurrentNode() const;
	private:
		Iterator<T> iter;

};

template <class T>
IterAccess<T>::IterAccess(Iterator<T> iter)
{
	this->iter = iter;
}


template <class T>
Node<T> * IterAccess<T>::getCurrentNode() const
{
	return iter.current;
}