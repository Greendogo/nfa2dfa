/**
*	@file : DoubleLinkedList.hpp
*	@author :  Paul McElroy
*	@date : 2015.02.23
*	Purpose: Implements the DoubleLinkedList class.
*/
#include <iostream>
#include <stdexcept>

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	m_front = nullptr;
	m_back = nullptr;
	m_size = 0;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	while(!isEmpty())
	{
			Node<T>* temp;
			temp = m_front;
			m_front = m_front -> getNext();
			delete temp;
			m_size--;
	}
}

template<typename T>
bool DoubleLinkedList<T>::isEmpty() const
{
	if(m_size == 0)
		return true;
	else
		return false;
}

template<typename T>
int DoubleLinkedList<T>::size() const
{
	return m_size;
}

template<typename T>
void DoubleLinkedList<T>::pushFront(T value)
{

	if(isEmpty())
	{
		m_front = new Node<T>();
		m_front->setValue(value);
		m_back = m_front;
		m_size++;
	}
	else
	{
		Node<T>* temp = new Node<T>();
		temp->setValue(value);
		m_front->setPrevious(temp);
		temp->setNext(m_front);
		m_front = temp;
		m_size++;
	}

}

template<typename T>
void DoubleLinkedList<T>::pushBack(T value)
{

	if(isEmpty())
	{
		m_front = new Node<T>();
		m_front->setValue(value);
		m_back = m_front;
		m_size++;
	}
	else
	{
		Node<T>* temp = new Node<T>();
		temp->setValue(value);
		m_back->setNext(temp);
		temp->setPrevious(m_back);
		m_back = temp;
		m_size++;
	}

}

template<typename T>
void DoubleLinkedList<T>::printList() const
{

	if(!isEmpty())
	{
		for(int i = 0; i < m_size; i++)
		{
			std::cout << get(i)->getValue();
			if(i != m_size - 1)
				std::cout << ",";
		}
	}
}

template<typename T>
bool DoubleLinkedList<T>::remove(T value)
{
	Node<T>* temp = find(value);
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;

	if(temp != nullptr)
	{
			if(temp == m_front && temp == m_back)
			{
				m_front = nullptr;
				m_back = nullptr;
			}
			else if (temp == m_front)
			{
				m_front = m_front -> getNext();
				m_front ->setPrevious(nullptr);
			}
			else if(temp == m_back)
			{
				m_back = m_back -> getPrevious();
				m_back -> setNext(nullptr);
			}
			else
			{
				prev = (temp->getPrevious());
				next = (temp->getNext());
				prev->setNext(next);
				next->setPrevious(prev);
			}
			delete temp;
			m_size--;
			return true;


	}
	else
	{
		return false;
	}
}

template<typename T>
void DoubleLinkedList<T>::insertAhead(T listValue, T newValue) throw (std::runtime_error)
{
	if(find(listValue) != nullptr)
	{

		if(find(listValue) == m_front)
		{
			pushFront(newValue);
		}
		else
		{
			Node<T>* newNode = new Node<T>();
			newNode->setValue(newValue);
			m_size++;
			Node<T>* next = find(listValue);
			Node<T>* prev = next->getPrevious();
			next->setPrevious(newNode);
			prev->setNext(newNode);
			newNode->setNext(next);
			newNode->setPrevious(prev);
		}

	}
	else
		throw (std::runtime_error ("value is not in the list!\n"));
}

template<typename T>
void DoubleLinkedList<T>::insertBehind(T listValue, T newValue) throw (std::runtime_error)
{
	if(find(listValue) != nullptr)
	{

		if(find(listValue) == m_back)
		{
			pushBack(newValue);
		}
		else
		{
			Node<T>* newNode = new Node<T>();
			newNode->setValue(newValue);
			m_size++;
			Node<T>* prev = find(listValue);
			Node<T>* next = prev->getNext();
			next->setPrevious(newNode);
			prev->setNext(newNode);
			newNode->setNext(next);
			newNode->setPrevious(prev);
		}
	}
	else
		throw (std::runtime_error ("value is not in the list!\n"));
}

template<typename T>
Node<T>* DoubleLinkedList<T>::find(T value) const
{
	Node<T>* temp = nullptr;
	if(!isEmpty())
	{
		temp = m_front;
		do
		{
			if(temp->getValue() == value)
				return temp;
			temp = temp -> getNext();
		}while(temp != nullptr);
	}
	return temp;
}

template<typename T>
Node<T>* DoubleLinkedList<T>::get(int index) const
{
	Node<T>* temp = m_front;
	for(int i = 0; i < m_size && i < index; i++)
	{
		temp = temp->getNext();
	}
	return temp;
}

template<typename T>
bool DoubleLinkedList<T>::equals(DoubleLinkedList<T>* m_DLL)
{
	bool equal = true;
	for(int i = 0; i < size(); i++)
	{
		if(!(m_DLL->find(get(i)->getValue())))
			equal = false;
	}
	for(int i = 0; i < m_DLL->size(); i++)
	{
		if(!(find(m_DLL->get(i)->getValue())))
			equal = false;
	}
	return equal;
}

template<typename T>
DoubleLinkedList<T>* DoubleLinkedList<T>::sort()
{
	for(int i = 0; i < m_size; i++)
		sort(m_front);
	return this;
}

template<typename T>
void DoubleLinkedList<T>::sort(Node<T>* n)
{
	if(n->getNext())
	{
		if(n->getNext()->getValue() < n->getValue())
		{
			T temp = n->getValue();
			n->setValue(n->getNext()->getValue());
			n->getNext()->setValue(temp);
		}
		sort(n->getNext());
	}
}
