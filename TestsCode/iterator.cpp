#include "stdafx.h"
#include "CppUnitTest.h"
#include <LinkedList.h>
#include "Book.h"
#include <Node.h>
#include "Iterator.h"
#include "IterAccess.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IteratorTest
{
	TEST_CLASS(Iterator_EN)
	{
	public:

		//Test qui doit compiler SANS ÊTRE MODIFIÉ
		
		TEST_METHOD(IteratorShouldCompile)
		{
			LinkedList<Book> l;
			Book* b1 = new Book(1);
			Node<Book> * node = new Node<Book>();
			node->setContent(b1);
			Iterator<Book> iter(node);
			Iterator<Book> iter1;
			Iterator<Book> iter2;

			iter1 = l.begin();
			iter2 = l.end();

			//IterAccess est une classe amie (friend) à Iterator
			//Elle a accès à ses attributs privés pour insecter le noeud sur lequel l'itérateur est positionné
			//Ceci va vous servir dans vos tests
			IterAccess<Book> ia(iter1);
			ia.getCurrentNode();
			iter1 = l.begin();
			iter1 = l.end();
			++iter1;
			if (iter1 == iter2 || iter1 != iter2)
			{
			}
			Book* test = &iter;
			Assert::IsTrue(true);
		}
		

		//Test du ++
		TEST_METHOD(Iterator_TestIncrementOperateurListeDeuxNoeud)
		{
			LinkedList<Book> l;
			Book* j1 = new Book(1);
			Book* j2 = new Book(2);
			l.add(j1);
			l.add(j2);
			Iterator<Book> iter = l.begin();
			++iter;
			IterAccess<Book> ia(iter);
			Assert::IsTrue(ia.getCurrentNode()->getContent() == j2);
			delete j1;
			delete j2;
		}
		

			
		//Tester autres scénarios de ++ :
		//   Sur liste vide
		 TEST_METHOD(Iterator_TestIncrement_on_empty_list)
		{
			LinkedList<Book> l;
			Book* j1 = new Book(1);
			Book* j2 = new Book(2);
			
			Iterator<Book> iter = l.begin();
			++iter;
			IterAccess<Book> ia(iter);
			Assert::IsTrue(ia.getCurrentNode() == nullptr);
			delete j1;
			delete j2;
		}
		//   Plusieurs en séquence sur liste pleine
		 TEST_METHOD(Iterator_TestIncrement_multiple_times_on_full_list)
		 {
			 LinkedList<Book> l;
			 Book* b1 = new Book(1);
			 Book* b2 = new Book(2);
			 Book* b3 = new Book(3);
			 l.add(b1);
			 l.add(b2);
			 l.add(b3);

			 Iterator<Book> iter = l.begin();
			 ++iter; // Move to second element
			 ++iter; // Move to third element
			 IterAccess<Book> ia(iter);
			 Assert::IsTrue(ia.getCurrentNode()->getContent() == b3);

			 delete b1;
			 delete b2;
			 delete b3;
		 }

		//   Fin de liste
		 TEST_METHOD(Iterator_TestIncrement_past_end_of_list)
		 {
			 LinkedList<Book> l;
			 Book* b1 = new Book(1);
			 l.add(b1);

			 Iterator<Book> iter = l.begin();
			 ++iter; // Move past the only element
			 IterAccess<Book> ia(iter);
			 Assert::IsTrue(ia.getCurrentNode() == nullptr);

			 delete b1;
		 }

		
		//opérateurs  == 
		 TEST_METHOD(Iterator_TestEqualityOperator)
		 {
			 LinkedList<Book> l;
			 Book* b1 = new Book(1);
			 l.add(b1);

			 Iterator<Book> iter1 = l.begin();
			 Iterator<Book> iter2 = l.begin();
			 Assert::IsTrue(iter1 == iter2);

			 delete b1;
		 }
		 // operateur != 
		 TEST_METHOD(Iterator_TestInequalityOperator)
		 {
			 LinkedList<Book> l;
			 Book* b1 = new Book(1);
			 Book* b2 = new Book(2);
			 l.add(b1);
			 l.add(b2);

			 Iterator<Book> iter1 = l.begin();
			 Iterator<Book> iter2 = l.begin();
			 ++iter2;
			 Assert::IsTrue(iter1 != iter2);

			 delete b1;
			 delete b2;
		 }

		 // operateur &
		 TEST_METHOD(Iterator_TestAddressOfOperator)
		 {
			 LinkedList<Book> l;
			 Book* b1 = new Book(1);
			 l.add(b1);

			 Iterator<Book> iter = l.begin();
			 Assert::IsTrue(*(&iter) == *b1);

			 delete b1;
		 }

	};
}

