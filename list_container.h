#ifndef LIST_CONTAINER_H
#define LIST_CONTAINER_H

#include <iostream>
#include <exception>
#include <list>
#include "strategy.h"
#include "container.h"
#include "component.h"

class noSortFunction: public std::exception
{
	public:
	virtual const char* what() const throw()
	{
		return "\nYou need to call the set_sort_function.\n";
	}
} mynosort;

bool checkSort(Sort* sort_function) {
	if (sort_function == 0) {
//		throw noSortFunction("\nYou need to call the set_sort_function\n");
		throw mynosort;
		return(0);
	}
	return(1);

}

class ListContainer : public Container
{
	public:
		std::list<Base*> cList;
		ListContainer() {} 
		
		void add_element(Base* element) { cList.push_back(element); }
		
		void print() {
			for (std::list<Base*>::iterator it = cList.begin(); it != cList.end(); it++)
			{
				std::cout << (*it)->evaluate() << ' ';
			}
		}
		
		void set_sort_function(Sort* sort_function) { this->sort_function = sort_function; }
		
		void sort() {
			try {
				if (checkSort(sort_function)) {
					sort_function->sort(this);
				}
			}
			catch (const noSortFunction& e)
			{
				std::cout << e.what();
			}
		}
		
		void swap(int i, int j) {
			Base* temp;
			std::list<Base*>::iterator it1 = cList.begin();
			std::list<Base*>::iterator it2 = cList.begin();
			std::advance(it1, i);
			std::advance(it2, j);
			temp = *it1;
			*it1 = *it2;
			*it2 = temp;			
		}

		Base* at(int i) {
			std::list<Base*>::iterator it = cList.begin();
			std::advance(it, i);
			return *it;
		}
		
		int size() { return cList.size(); }
		
};


#endif //LIST_CONTAINER_H
