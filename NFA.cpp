#include "NFA.h"
// #include "DoubleLinkedList.h"

NFA::NFA()
{
  m_list = new DoubleLinkedList<DoubleLinkedList<DoubleLinkedList<int>*>*>(); //declares the DoubleLinkedList object, myDLL
  m_adds = 0;
}

//delete function
NFA::~NFA()
{
  for(int i = 0; i < m_list->size(); i++)
  {
    for(int j = 0; j < m_list->get(i)->getValue()->size(); j++)
      delete m_list->get(i)->getValue()->get(j)->getValue();
  }
  for(int i = 0; i < m_list->size(); i++)
  {
    delete m_list->get(i)->getValue();
  }
  delete m_list;
}

//returns the number of rows
int NFA::getRows()
{
  return m_list->size();
}

//adds a row
void NFA::addRow()
{
  m_list->pushBack(new DoubleLinkedList<DoubleLinkedList<int>*>());
  m_adds++;
}

//adds a column
void NFA::addColumn(int row)
{
  for(int i = 0; i <= row; i++)
    if(m_list->get(row)->getValue() == nullptr)
      ;//addRow();
  m_list->get(row)->getValue()->pushBack(new DoubleLinkedList<int>());
}

//adds a value at as specific point in the Finite Automata cube
//expands the cube as needed to fit the desired location.
void NFA::addValue(int row, int column, int value)
{
  for(int i = 0; i <= row; i++)
  {
      if(m_list->get(i) == nullptr)
      {
        addRow();
      }
  }

  for(int i = 0; i <= column; i++)
  {
    if(m_list->get(row) != nullptr)
    if(m_list->get(row)->getValue()->get(i) == nullptr)
      addColumn(row);
  }
  m_list->get(row)->getValue()->get(column)->getValue()->pushBack(value);
}

//returns a pointer to a row in a Finite Automata cube
DoubleLinkedList<DoubleLinkedList<int>*>* NFA::getRow(int row)
{
  DoubleLinkedList<DoubleLinkedList<int>*>* temp = nullptr;
  if(m_list->get(row) != nullptr)
    temp = m_list->get(row)->getValue();
  return temp;
}

//returns a pointer to a dolumn in a finite Automata cube
DoubleLinkedList<int>* NFA::getColumn(int row, int column)
{
  DoubleLinkedList<int>* temp = nullptr;
  if(m_list->get(row) != nullptr)
  {
    if(m_list->get(row)->getValue()->get(column) != nullptr)
    {
      int tempSize = m_list->get(row)->getValue()->get(column)->getValue()->size();
      temp = new DoubleLinkedList<int>;
      for(int s = 0; s < tempSize; s++)
      {
        temp->pushBack(m_list->get(row)->getValue()->get(column)->getValue()->get(s)->getValue());
      }
    }
  }
  return temp;
}

//returns the integer value at row/column/index in the FA cube
int NFA::getValue(int row, int column, int index)
{
  int temp = 0;
  if(m_list->get(row) != nullptr)
  if(m_list->get(row)->getValue()->get(column) != nullptr)
  if(m_list->get(row)->getValue()->get(column)->getValue()->get(index) != nullptr)
    temp = m_list->get(row)->getValue()->get(column)->getValue()->get(index)->getValue();
  return temp;
}

//prints the NFA/DFA
void NFA::print()
{
  int m_i = m_list->size();
  int m_j;
  int m_k;
  for(int i = 0; i < m_i; i++)
  {
    m_j = m_list->get(i)->getValue()->size();
    std::cout << (i + 1);
    if(m_j > 0)
    {
      for(int j = 0; j < m_j; j++)
      {
        m_k = m_list->get(i)->getValue()->get(j)->getValue()->size();
        std::cout << "\t{";
        for(int k = 0; k < m_k; k++)
        {

          if((m_list->get(i)->getValue()->get(j)->getValue()->get(k) != nullptr))
            m_list->get(i)->getValue()->get(j)->getValue()->printList();

        }
        std::cout << "}";
      }
    };
    std::cout << "\n";
  }
}

//takes a state and produces the eclosure set.
DoubleLinkedList<int>* NFA::eclosure(int state)
{
  DoubleLinkedList<int>* list = new DoubleLinkedList<int>;
  DoubleLinkedList<int>* templist = new DoubleLinkedList<int>;
  int tempSize = eclosure(state, new DoubleLinkedList<int>, new DoubleLinkedList<int>)->size();
  for(int s = 0; s < tempSize; s++)
  {
    templist->pushBack(eclosure(state, new DoubleLinkedList<int>, new DoubleLinkedList<int>)->get(s)->getValue());
  }
  for(int j = 0; j < templist->size(); j++)
  {
  if(!(list->find(templist->get(j)->getValue())))
    list->pushBack(templist->get(j)->getValue());
  }
  delete templist;
  return list->sort();
}

//takes a set of states and produces their combined eclosure set
DoubleLinkedList<int>* NFA::eclosure(DoubleLinkedList<int>* states)
{
  DoubleLinkedList<int>* list = new DoubleLinkedList<int>;
  DoubleLinkedList<int>* templist = new DoubleLinkedList<int>;
  for(int i = 0; i < states->size(); i++)
  {
    int tempSize = eclosure(states->get(i)->getValue(), new DoubleLinkedList<int>, new DoubleLinkedList<int>)->size();
    for(int s = 0; s < tempSize; s++)
    {
      templist->pushBack(eclosure(states->get(i)->getValue(), new DoubleLinkedList<int>, new DoubleLinkedList<int>)->get(s)->getValue());
    }

    for(int j = 0; j < templist->size(); j++)
    {
      if(!(list->find(templist->get(j)->getValue())))
      {
        list->pushBack(templist->get(j)->getValue());
      }
    }
  }
  delete templist;
  return list->sort();
}

//a helper function to the above eclosure functions
DoubleLinkedList<int>* NFA::eclosure(int state, DoubleLinkedList<int>* list, DoubleLinkedList<int>* passedStates)
{
  int tempSize = 0;
  if(!(passedStates->find(state)))
    passedStates->pushBack(state);
  int symbols = getRow(3)->get(0)->getValue()->size();
  if(!(list->find(state)))
    list->pushBack(state);
  if(m_list->get(state + 3) != nullptr)
  {
    if(m_list->get(state + 3)->getValue()->get(symbols - 1) != nullptr)
    {
      int numEs = m_list->get(state + 3)->getValue()->get(symbols - 1)->getValue()->size();
      for(int i = 0; i < numEs; i++)
      {
        int current = m_list->get(state + 3)->getValue()->get(symbols - 1)->getValue()->get(i)->getValue();
        if(!(list->find(current)))
          list->pushBack(current);
      }
      for(int i = 0; i < numEs; i++)
      {
        int current = m_list->get(state + 3)->getValue()->get(symbols - 1)->getValue()->get(i)->getValue();
        DoubleLinkedList<int>* temp = new DoubleLinkedList<int>;
        if(!(passedStates->find(current)))
        {
          tempSize = eclosure(current,list,passedStates)->size();
          for(int s = 0; s < tempSize; s++)
          {
            temp->pushBack(eclosure(current,list,passedStates)->get(s)->getValue());
          }
        }
        for(int j = 0; j < temp->size(); j++)
        {
          int val = temp->get(j)->getValue();
          if(!(list->find(val)))
            list->pushBack(val);
        }
        delete temp;
      }
    }
  }
  else
    list->sort();
  return list;
}

//performs the move operature returning a DLL* of the results
DoubleLinkedList<int>* NFA::move(DoubleLinkedList<int>* eclosure, int transition)
{
  DoubleLinkedList<int>* m_DLL = new DoubleLinkedList<int>;
  int size = eclosure->size();
  for(int i = 0; i < size; i++)
  {
    int temp = eclosure->get(i)->getValue();
    if(m_list->get(temp+3) != nullptr){
    {
      for(int j = 0; j < m_list->get(temp+3)->getValue()->size();j++) //Play with the 1 to 2 and 3
      if(m_list->get(temp+3)->getValue()->get(transition) != nullptr){
      if(m_list->get(temp+3)->getValue()->get(transition)->getValue()->get(j) != nullptr)
      {
        int temp2 = m_list->get(temp+3)->getValue()->get(transition)->getValue()->get(j)->getValue();
        if(!(m_DLL->find(temp2)))
          m_DLL->pushBack(temp2);
      }}}
    }
  }
  return m_DLL->sort();
}
