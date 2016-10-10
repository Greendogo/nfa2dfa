/**
*	@file : DoubleLinkedList.h
*	@author :  Paul McElroy
*	@date : 2015.02.09
*	Purpose: Header file for the DoubleLinkedList class.  DoubleLinkedList contains a linked list of Node class objects
* 	which are manipulated by the following functions to add nodes from the back or front of the list, or before or after a specified value.
*	There are functions for removing nodes with specified values and for searching for nodes with specified values.
*	Also contains a print function, as well as a constructor and destructor.
*/
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "Node.h"
#include <stdexcept>

template <typename T>
class DoubleLinkedList
{
private:
	Node<T>* m_front;
	Node<T>* m_back;
	int m_size;
public:
	/**
	*  @pre none
	*  @post Creates and initializes a DoubleLinkedList instance
	*  @return Itizialized DoubleLinkedList with m_front = nullptr, m_prev = nullptr, and m_size = 0;
	*/
	DoubleLinkedList();
	/**
	*  @pre The DLL being referred to exists.
	*  @post Destroys the referred DLL by deleting every Node object it holds.
	*  @return All node objects on the Heap are destroyed
	*/
	~DoubleLinkedList();
	/**
	*  @pre none
	*  @post none
	*  @return returns a true if m_size == 0, and false if m_size > 0;
	*/
	bool isEmpty() const;
	/**
	*  @pre none
	*  @post none
	*  @return m_size
	*/
	int size() const;
	/**
	*  @pre none
	*  @post Adds a Node with value to the front of the linked list
	*  @return none
	*/
	void pushFront(T value);
	/**
	*  @pre none
	*  @post Adds a Node with value to the back of the linked list
	*  @return none
	*/
	void pushBack(T value);
	/**
	*  @pre none
	*  @post Finds the first node with m_value == value and removes/deletes it
	*  @return none
	*/
	bool remove(T value);
	/**
	*  @pre none
	*  @post Finds the first node with m_value == listValue and adds newValue ahead of it
	*  @return none
	*/
	void insertAhead(T listValue, T newValue) throw (std::runtime_error);
	/**
	*  @pre none
	*  @post Finds the first node with m_value == listValue and adds newValue behind it
	*  @return none
	*/
	void insertBehind(T listValue, T newValue) throw (std::runtime_error);
	/**
	*  @pre none
	*  @post Searches for a value in the DLL
	*  @return Returns a pointer to the first node containing the value, nullptr if none is found
	*/
	Node<T>* find(T value) const;

	//returns the node at the specified index
	Node<T>* get(int i) const;

	//implements a simple bubble sort on the nodes in a DLL
	DoubleLinkedList<T>* sort();
	void sort(Node<T>* n);

	/**
	*  @pre none
	*  @post Prints a list of each element in the DLL
	*  @return none
	*/
	void printList() const;

	//Will return true if this and another DLL contain the same elements
	bool equals(DoubleLinkedList<T>* m_DLL);
};

#include "DoubleLinkedList.hpp"
#endif
