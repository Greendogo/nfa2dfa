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
  //Returns the num of columns
  int getColumns(int row);
  //Returns the num of Values
  int getValues(int row, int column);
  //Checks existence of a row
  bool rowExists(int row);
  //checks existence of a column
  bool columnExists(int row, int column);
  //checks existence of a value
  bool valueExists(int row, int column, int index);
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

  int eclosureSize(int state);
  int eclosureSize(DoubleLinkedList<int>* states);
  int eclosureSize(int state, DoubleLinkedList<int>* list, DoubleLinkedList<int>* passedStates);

  int eclosureValue(int state, int index);
  int eclosureValue(DoubleLinkedList<int>* states, int index);
  int eclosureValue(int state, DoubleLinkedList<int>* list, DoubleLinkedList<int>* passedStates, int index);
  //move function
  DoubleLinkedList<int>* move(DoubleLinkedList<int>* eclosure, int transition);
  int moveSize(DoubleLinkedList<int>* eclosure, int transition);
  int moveValue(DoubleLinkedList<int>* eclosure, int transition, int index);

private:
  DoubleLinkedList<DoubleLinkedList<DoubleLinkedList<int>*>*>* m_list;
  int m_adds;
};


#endif
