#ifndef NFA_H
#define NFA_H

#include "DoubleLinkedList.h"

class NFA
{
public:
  //NFA constructor
  NFA();
  //NFA destructor
  ~NFA();
  //Returns the rows
  int getRows();
  //Adds a new row
  void addRow();
  //Adds a new column
  void addColumn(int row);
  //Adds a new value and expands the cube to fit
  void addValue(int row, int column, int value);
  //Returns a row
  DoubleLinkedList<DoubleLinkedList<int>*>* getRow(int row);
  //Returns a column
  DoubleLinkedList<int>* getColumn(int row, int column);
  //returns a value
  int getValue(int row, int column, int index);
  //prints the Finite Automata
  void print();

  //eclosure functions
  DoubleLinkedList<int>* eclosure(int state);
  DoubleLinkedList<int>* eclosure(DoubleLinkedList<int>* states);
  DoubleLinkedList<int>* eclosure(int state, DoubleLinkedList<int>* list, DoubleLinkedList<int>* passedStates);

  //move function
  DoubleLinkedList<int>* move(DoubleLinkedList<int>* eclosure, int transition);

private:
  DoubleLinkedList<DoubleLinkedList<DoubleLinkedList<int>*>*>* m_list;
  int m_adds;
};


#endif
