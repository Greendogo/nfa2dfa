/**
*	@file : Node.hpp
*	@author :  Paul McElroy
*	@date : 2015.02.23
*	Purpose: Implements the Node class.
*/


template<typename T>
Node<T>::Node()
{
	m_previous = nullptr;
	m_next = nullptr;
	m_value = T();
}

template<typename T>
Node<T>* Node<T>::getPrevious()
{
	return m_previous;
}

template<typename T>
Node<T>* Node<T>::getNext()
{
	return m_next;
}

template<typename T>
T Node<T>::getValue()
{
	return m_value;
}

template<typename T>
void Node<T>::setPrevious(Node<T>* newPrev)
{
	m_previous = newPrev;
}

template<typename T>
void Node<T>::setNext(Node<T>* newNext)
{
	m_next = newNext;
}

template<typename T>
void Node<T>::setValue(T newValue)
{
	m_value = newValue;
}