// -*- c++ -*-
//
//  File:         intlist.cpp
//
//  Description:  C++ implementation of the class intList, a list of integers.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#include "intlist.hpp"
#include <iostream>
#include <assert.h>

// creates an element of the list
void make_intlistelem( intListElem &elem, int x )
{
   elem.x    = x;
}

// destructor
intList::~intList()
{
  intListNode *pt = list;
  while( pt )
    {
      intListNode *tmp = pt;
      pt = pt->next;
      delete tmp;
    }
  list = 0;
}

// assignment operator
intList & intList::operator=(intList &L)
{
  if (this == &L)
    return *this;

  // deallocate memory
  intListNode *pt = list;
  while( pt )
    {
      intListNode *tmp = pt;
      pt = pt->next;
      delete tmp;
    }
  list = 0;
  size = 0;

  // copy elements of list L
  for( pt=L.list; pt; pt=pt->next )
    insertAtEnd( pt->elem.x );
  
  return *this;
}

// check if list is empty
bool intList::is_empty()
{
  return list == 0;
}

// get an element from the list
intListElem intList::get()
{
  assert( !this->is_empty() );
  return list->elem;
}


// remove the head of the list
intListElem intList::remove()
{
  assert( !this->is_empty() );
  intListNode *pt=list;
  intListElem x = list->elem;
  list = list->next;
  delete pt;
  size--;

  return x;
}

// remove element x from the list
void intList::remove(int x)
{
  assert( !this->is_empty() );
  intListNode *pt=list;
  intListNode *pt_prev = NULL;
  intListElem elem = pt->elem;
  while( elem.x != x )
    {
      pt_prev = pt;
      pt = pt->next;
      if( pt == NULL ) return; // element not found
      elem = pt->elem;
    }
  if( pt_prev == NULL )
    // x is the first element of the list
    list = list->next;
  else
    // x is not the first element
    pt_prev->next = pt->next;
  size--;

  delete pt;
}

// insert an element in the list
void intList::insert( intListElem elem )
{
  intListNode *pt = new intListNode( elem, list );
  assert( pt != 0 );
  list = pt;
  size++;
}

// insert an element at the end of the list
void intList::insertAtEnd( intListElem elem )
{
  intListNode *p = new intListNode( elem );
  intListNode *pt=list;
  if( pt == 0 )
    {
      //cout<< "empty"<<endl;
      list = p;
    }
  else
    {
      //cout<< "not empty, size="<<size<<endl;
      for( int i=0; i < size-1; i++, pt=pt->next );
      pt->next = p;
    }
  size++;
}

// insert an element in the list
void intList::insert( int x )
{
  intListElem elem;
  make_intlistelem( elem, x );
  insert( elem );
}

// insert an element at the end of the list
void intList::insertAtEnd( int x )
{
  intListElem elem;
  make_intlistelem( elem, x );
  insertAtEnd( elem );
}

// returns the intersection of the two lists
void intList::intersection( intList &L1, intList &L2 )
{
  if( L1.size < L2.size )
    {
      intListNode *ptr = L1.list;
      while( ptr != NULL )
	{
	  intListElem elem = ptr->elem;
	  if( L2.hasMember( elem ) )
	    this->insert( elem );
	  ptr = ptr->next;
	}
    }
  else
    {
      intListNode *ptr = L2.list;
      while( ptr != NULL )
	{
	  intListElem elem = ptr->elem;
	  if( L1.hasMember( elem ) )
	    this->insert( elem );
	  ptr = ptr->next;
	}
    }
}

bool intList::hasMember( intListElem elem )
{
  intListNode *ptr = list;
  while( ptr != NULL )
    {
      if( ptr->elem.x == elem.x ) return true;
      else ptr = ptr->next;
    }
  return false;
}
   
// convert the list to an array. 
// caller must allocate space for array A
void intList::asArray( int *A )
{
  int i=0;
  for( intListNode *pt=list; pt; pt=pt->next )
    {
      A[i] = pt->elem.x;
      i++;
    }
}
  
// print the elements of the list
void intList::display()
{
  //cout << "size: " << size << endl;
  for( intListNode *pt=list; pt; pt=pt->next )
    //cout << "<" << pt->elem.x << ">" << "  ";
    std::cout << pt->elem.x << " ";
  std::cout << std::endl;
}

// print the elements of the list
std::ostream &operator<< (std::ostream &out, intList &L)
{
  for( intListNode *pt=L.list; pt; pt=pt->next )
    out << pt->elem.x << " ";
  return out;
}


