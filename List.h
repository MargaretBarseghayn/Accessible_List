#pragma once
#include <iostream>
using namespace std;

class List {
   struct Node {
      int info_;
      bool isLeaf_;
      Node *parent_;
      Node *llink_;
      Node *rlink_;

      Node( int info = 0,
            bool isLeaf = true,
            Node *parent = 0,
            Node *llink = 0,
            Node *rlink = 0 )
         : info_( info )
         , isLeaf_( isLeaf )
         , parent_( parent )
         , llink_( llink )
         , rlink_( rlink )
      {}
   };

   // Auxiliary functions
   static void clear( Node *&tree );
   static void print( const Node *tree );
   pair< Node *, int > find( int pos ) const;

public:
   List()
      : tree_( 0 ){};
   ~List() { clear( tree_ ); }
   void print() const { print( tree_ ); }

   // precondition: 1<=pos<=sizeOfList
   // Returns a reference to the element at position pos
   /*1*/ int &operator[]( int pos ) { return find( pos ).first->info_; }

   // If 1<=pos<=sizeOfList, then the element is inserted at position pos
   // Else, if pos>sizeOfList, then the element is inserted at the end of the list
   /*2*/ void insert( int pos, int element );   //... should be implemented ...

   // If 1<=pos<=sizeOfList, then the element is removed at position pos
   // Else, nothing is done
   /*3*/ void remove( int pos );   //... should be implemented ...

private:
   Node *tree_;
};
