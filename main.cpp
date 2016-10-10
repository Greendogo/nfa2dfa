/**
*	@file : main.cpp
*	@author :  Paul McElroy
*	@date : 2016.OCT.07
*	Purpose: Implements the nfa to dfa function, utilizing the DoubleLinkedList and Node classes.
*	Proper usage is:
* ./project1 < input.txt > output.txt
*	or
*	./project1 < input.txt
*/


#include <iostream>
#include "DoubleLinkedList.h"
#include "NFA.h"
#include "DoubleLinkedList.h"
#include "Node.h"
#include <stdexcept>
#include <regex>

//opens the file and reads in the input
DoubleLinkedList<std::string> open();
//performs the mark operation and stores this in the marks and mark_transistion structures
void mark(NFA* m_NFA, DoubleLinkedList<int>* a, DoubleLinkedList<DoubleLinkedList<int>*>* marks, NFA* mark_transitions);
//returns the mark ID of a given e-closure set (if it's already known)
int getMark(DoubleLinkedList<int>* a, DoubleLinkedList<DoubleLinkedList<int>*>* marks);
//This is the opening funtion for the mark functionality
void mark(NFA* m_NFA, DoubleLinkedList<DoubleLinkedList<int>*>* marks, NFA* mark_transitions);
//prints the Marks in order
void printMarks(NFA* m_NFA, DoubleLinkedList<DoubleLinkedList<int>*>* marks);

//main function
int main()
{
//all data is stored in a few finite automata "cubes" like this one:
NFA* myNFA = new NFA();
//opening the file
DoubleLinkedList<std::string> file = open();


//Using REGEX expressions the following part is why this program takes a few seconds to build.
//add the number of states
std::string str3 = file.get(2)->getValue();
std::string subject3(str3);
{
	try {
		std::regex re("[\\d]+");
		std::sregex_iterator next(subject3.begin(), subject3.end(), re);
		std::sregex_iterator end;
		while (next != end) {
			std::smatch match = *next;
			std::string temp = match.str();
			if(temp.length() > 0)
				myNFA->addValue(2,0,std::stoi(temp));
			next++;
		}
	} catch (std::regex_error& e) {
		std::cout << "ERROR\n";// Syntax error in the regular expression
	}
}



//add the transitional characters
std::string str4 = file.get(3)->getValue();
std::string subject4(str4);
{
	try {
		std::regex re("\\t[[:lower:]]");
		std::sregex_iterator next(subject4.begin(), subject4.end(), re);
		std::sregex_iterator end;
		while (next != end) {
			std::smatch match = *next;
			std::string temp = match.str().substr(1);
			if(temp.length() > 0)
				myNFA->addValue(3,0,(int)temp[0]);
			next++;
		}
	} catch (std::regex_error& e) {
		std::cout << "ERROR\n";// Syntax error in the regular expression
	}
}

//Add e to the NFA
myNFA->addValue(3,0,(int)'E');

//add all the transitions to the transition diagram
for(int j = 0; j < file.size(); j++)
{
		std::string str = file.get(j)->getValue();
		DoubleLinkedList<std::string> sublists;
		std::string subject(str);
		try {
		  std::regex re("[\\x7B][\\d,]*[\\x7D]");//comma separated whole numbers surrounded by brackets
		  std::sregex_iterator next(subject.begin(), subject.end(), re);
		  std::sregex_iterator end;
		  while (next != end) {
		    std::smatch match = *next;
		    sublists.pushBack(match.str());
		    next++;
		  }
		} catch (std::regex_error& e) {
		  // Syntax error in the regular expression
		}
		for(int i = 0; i < sublists.size(); i++)
		{
			std::string str2 = sublists.get(i)->getValue();
			std::string subject2(str2);
			try {
			  std::regex re("[\\x7B\\x2C][\\d]*(?=[\\x7D\\x2C])");//a bracket or comma, then a number then a bracket or comma
			  std::sregex_iterator next(subject2.begin(), subject2.end(), re);
			  std::sregex_iterator end;
			  while (next != end) {
			    std::smatch match = *next;
					std::string temp = match.str().substr(1);
					if(temp.length() > 0)
			    	myNFA->addValue(j,i,std::stoi(temp));
			    next++;
			  }
			} catch (std::regex_error& e) {
			  std::cout << "ERROR\n";// Syntax error in the regular expression
			}

		}
	}
	DoubleLinkedList<DoubleLinkedList<int>*>* marks = new DoubleLinkedList<DoubleLinkedList<int>*>;
	NFA* mark_transitions = new NFA;
	mark(myNFA, marks, mark_transitions); //builds the mark steps
	std::cout << "\n";
	printMarks(myNFA, marks); //prints the mark walk through
	mark_transitions->print(); //prints the new DFA transitions
	delete myNFA; //attempt some sort of memory management
	delete mark_transitions;
	for(int s = 0; s < marks->size(); s++)
	{
		delete marks->get(s)->getValue();
	}
	delete marks;
	return (0);
}

//the opening function
DoubleLinkedList<std::string> open()
{
	DoubleLinkedList<std::string> file;
	std::string temp = "";
	while(std::getline(std::cin, temp))
	{
		temp += "\n";
		file.pushBack(temp);
		std::cout << temp;
	}
	return file;
}

void mark(NFA* m_NFA, DoubleLinkedList<int>* a, DoubleLinkedList<DoubleLinkedList<int>*>* marks, NFA* mark_transitions)
{
	std::cout << "\nMark " << getMark(a,marks) << "\n";
	if(a->size() > 0)
	{
		int size = m_NFA->getValues(3,0) - 1;
		for(int i = 0; i < size; i++)
		{
			DoubleLinkedList<int>* moved = new DoubleLinkedList<int>;
			int tempSize = m_NFA->move(a,i)->size();
			for(int s = 0; s < tempSize; s++)
			{
				moved->pushBack(m_NFA->move(a,i)->get(s)->getValue());
			}
			if(moved->size() > 0)
			{
				std::cout << "{";
				a->printList();
				std::cout << "} --" << (char)(m_NFA->getValue(3,0,i)) << "--> {";
				int row = i;
				int column = getMark(a,marks);
				moved->printList();
				std::cout << "}\n";
				tempSize = m_NFA->eclosureSize(moved);
				DoubleLinkedList<int>* eclosure = new DoubleLinkedList<int>;
				for(int s = 0; s < tempSize; s++)
				{
					eclosure->pushBack(m_NFA->eclosureValue(moved,s));
				}
				std::cout << "E-closure{";
				moved->printList();
				std::cout << "} = {";
				eclosure->printList();
				std::cout << "} = ";
				bool addEclosure = true;
				for(int k = 0; k < marks->size(); k++)
				{
					if((marks->get(k)->getValue()->equals(eclosure)))
						addEclosure = false;
				}
				if(addEclosure)
				{
					tempSize = eclosure->size();
					marks->pushBack(new DoubleLinkedList<int>);
					for(int s = 0; s < tempSize; s++)
					{
						marks->get(marks->size()-1)->getValue()->pushBack(eclosure->get(s)->getValue());
					}
				}
				std::cout << getMark(eclosure,marks) << "\n";
				int depth = getMark(eclosure,marks);
				mark_transitions->addValue(column - 1,row,depth);
				delete eclosure;
			}
			delete moved;
		}
	}
}

int getMark(DoubleLinkedList<int>* a, DoubleLinkedList<DoubleLinkedList<int>*>* marks)
{
	int index = 0;
	for(int i = 0; i < marks->size(); i++)
	{
		if(a->equals(marks->get(i)->getValue()))
			index = i;
	}
	return index + 1;
}

//enter the mark algorithm here
void mark(NFA* m_NFA, DoubleLinkedList<DoubleLinkedList<int>*>* marks, NFA* mark_transitions)
{
	std::cout << "E-closure(I0) = {";
	int initial = m_NFA->getValue(0,0,0);
	DoubleLinkedList<int>* a	= new DoubleLinkedList<int>;
	for(int i = 0; i < m_NFA->eclosureSize(initial); i++)
	{
		a->pushBack(m_NFA->eclosureValue(initial,i)); //eclosure gives a DLL*
	}
	marks->pushBack(new DoubleLinkedList<int>);
	for(int i = 0; i < a->size(); i++)
	{
		marks->get(marks->size()-1)->getValue()->pushBack(a->get(i)->getValue());
	}
	a->printList();
	std::cout << "} = 1\n";
	mark(m_NFA, a, marks, mark_transitions);
	int i = 1;
	while(i < marks->size())
	{
		mark(m_NFA, marks->get(i)->getValue(), marks, mark_transitions);
		if(marks->size() > i)
			i++;
	}
	for(int i = 0; i < marks->size(); i++)
	{
		while(mark_transitions->getColumns(i) < m_NFA->getValues(3,0)-1)
		{
			mark_transitions->getRow(i)->pushBack(new DoubleLinkedList<int>);
		}
	}
	delete a;
}

//prints the new dfa diagram
void printMarks(NFA* m_NFA, DoubleLinkedList<DoubleLinkedList<int>*>* marks)
{
	DoubleLinkedList<int>* tempCol = nullptr;
	tempCol = m_NFA->getColumn(1,0);
	int tempSize = tempCol->size();
	DoubleLinkedList<int>* originalFinal = new DoubleLinkedList<int>;
	for(int s = 0; s < tempSize; s++)
	{
		originalFinal->pushBack(tempCol->get(s)->getValue());
	}
	DoubleLinkedList<int>* newFinal = new DoubleLinkedList<int>;
	// originalFinal->printList();
	for(int i = 0; i < marks->size(); i++)
	{
		for(int j = 0; j < originalFinal->size(); j++)
		{
			if(marks->get(i)->getValue()->find(originalFinal->get(j)->getValue()))
				newFinal->pushBack(i+1);
		}
	}
	std::cout << "Initial State: {1}\n";
	std::cout << "Final States: {";
	newFinal->printList();
	std::cout << "}\nState";
	for(int i = 0; i < m_NFA->getColumn(3,0)->size() - 1;i++)
		std::cout << "\t" << (char)(m_NFA->getValue(3,0,i));
	std::cout << "\n";
	delete tempCol;
	delete originalFinal;
	delete newFinal;
}
