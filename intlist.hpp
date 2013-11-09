// -*- c++ -*-
//
//  File:         intlist.hpp
//
//  Description:  C++ interface to the class intList, a list of integers.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#ifndef _intlist_hpp
#define _intlist_hpp

#include <iostream>
//#include "util.hpp"
  
// a list element
typedef struct intListElem {
  int    x;   
} intListElem;

// creates an element of the list
void make_intlistelem( intListElem &elem, int x );

// a list node (contains an element and a pointer to the next element)
class intListNode {
    friend class intList;
  private:
    intListNode( intListElem e, intListNode *u = 0 ) { elem = e; next = u; }
  public:
    intListElem elem;     
    intListNode *next;    
};

// class list of nodes
class intList
{
  private:
    int size; 
    intListNode *list;

  public:
    intList() { size = 0; list = 0; }
    ~intList();
    intList & operator=(intList &L);
  
    int length() { return size; }
    void insert( intListElem elem );
    void insert( int x );
    void insertAtEnd( intListElem elem );
    void insertAtEnd( int x );
    intListElem get();
    intListElem remove();
    void remove(int x);
    bool is_empty();
    void asArray( int *A );
    void display();
    friend std::ostream &operator<< (std::ostream &out, intList &L);
    void intersection( intList &L1, intList &L2 );
    bool hasMember( intListElem elem );
};


#endif











