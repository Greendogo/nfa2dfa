/**
*	@file : Node.h
*	@author :  Paul McElroy
*	@date : 2014.02.23
*	Purpose: The header file for the Node class.  This class stores a value of type T and pointers to the previous and
* 	next Nodes.
* 	Also contains a constructor, and methods to set values, get values, set Node pointers and get Node pointers stored
* 	by the Node object.
*/

#ifndef NODE_H
#define NODE_H


template <typename T>
class Node
{
	public:
		/**
		*  @pre none
		*  @post Creates and initializes a Node instance
		*  @return Initialized Node with m_value = T() and m_next = nullptr, m_prev = nullptr
		*/
		Node();
		/**
		*  @pre none
		*  @post none
		*  @return m_value
		*/
		T getValue();
		/**
		*  @pre value is of type T.
		*  @post sets m_value to value
		*  @return none
		*/
		void setValue(T value);
		/**
		*  @pre none
		*  @post none
		*  @return m_next
		*/
		Node<T>* getNext();
		/**
		*  @pre none
		*  @post Sets m_next = next
		*  @return none
		*/
		void setNext(Node<T>* next);
		/**
		*  @pre none
		*  @post none
		*  @return m_prev
		*/
		Node<T>* getPrevious();
		/**
		*  @pre none
		*  @post Sets m_prev = prev
		*  @return none
		*/
		void setPrevious(Node<T>* prev);

	private:
		T m_value;
		Node<T>* m_next;
		Node<T>* m_previous;

};

#include "Node.hpp"
#endif