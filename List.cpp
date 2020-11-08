#include "stdafx.h"
#include "List.h"
#include <iostream>
using namespace std;

void List::clear( Node *&tree )
{
   if ( tree == 0 )
      return;

   if ( !tree->isLeaf_ ) {
      clear( tree->llink_ );
      clear( tree->rlink_ );
   }

   delete tree;
   tree = 0;
}

void List::print( const Node *tree )
{
   if ( tree == 0 )
      return;

   if ( tree->isLeaf_ ) {
      cout << tree->info_ << endl;
      return;
   }
   print( tree->llink_ );
   print( tree->rlink_ );
}

pair< List::Node *, int > List::find( int pos ) const
{
   if ( tree_ == 0 )
      return make_pair( tree_, pos );

   Node *ptr = tree_;
   while ( !ptr->isLeaf_ )   // It'd be better to write while ( ptr && !ptr->isLeaf_ )
      if ( pos <= ptr->info_ )
         ptr = ptr->llink_;
      else {
         pos -= ptr->info_;
         ptr = ptr->rlink_;
      }

   return make_pair( ptr, pos );
}

void List::insert( int pos, int element )
{
   if ( !tree_ ) {
      tree_ = new Node( 1, false );
      tree_->llink_ = new Node( element, true, tree_ );
   }
   else {
      if ( pos > tree_->info_ && !tree_->rlink_ ) {
         tree_->rlink_ = new Node( element, true, tree_ );
         return;
      }
      auto p = find( pos );
      if ( p.second == 1 ) {
         int val = p.first->info_;
         p.first->info_ = 1;
         p.first->isLeaf_ = false;
         p.first->llink_ = new Node( element, true, p.first );
         p.first->rlink_ = new Node( val, true, p.first );
         Node *parent = p.first->parent_, *link = p.first;
         while ( parent ) {
            if ( parent->llink_ == link ) {
               ++parent->info_;
            }
            link = parent;
            parent = parent->parent_;
         }
      }
      else {
         int val = p.first->info_;
         p.first->info_ = 1;
         p.first->isLeaf_ = false;
         p.first->rlink_ = new Node( element, true, p.first );
         p.first->llink_ = new Node( val, true, p.first );
         Node *parent = p.first->parent_, *link = p.first;
         while ( parent ) {
            if ( parent->llink_ == link ) {
               ++parent->info_;
            }
            link = parent;
            parent = parent->parent_;
         }
      }
   }
}

void List::remove( int pos )
{
   if ( !tree_ || pos > tree_->info_ && !tree_->rlink_ ) {
      return;
   }
   auto p = find( pos );
   if ( p.second != 1 ) {
      return;
   }
   else {
      Node *parent = p.first->parent_, *link = p.first;
      if ( parent->llink_ == link ) {
         delete link;
         parent->llink_ = nullptr;
         if ( parent != tree_ ) {

            if ( parent->rlink_->isLeaf_ ) {
               parent->info_ = parent->rlink_->info_;
               parent->isLeaf_ = true;
               delete parent->rlink_;
               parent->rlink_ = nullptr;
               link = parent;
            }
            else {
               if ( parent->parent_->llink_ == parent ) {
                  parent->parent_->llink_ = parent->rlink_;
               }
               else {
                  parent->parent_->rlink_ = parent->rlink_;
               }
               parent->rlink_->parent_ = parent->parent_;
               link = parent->rlink_;
               delete parent;
            }
         }
         else {
            --tree_->info_;
            if ( tree_->rlink_ == nullptr ) {
               tree_ = nullptr;
            }
            return;
         }
      }
      else {
         delete link;
         parent->rlink_ = nullptr;
         if ( parent != tree_ ) {
            if ( parent->llink_->isLeaf_ ) {
               parent->info_ = parent->llink_->info_;
               parent->isLeaf_ = true;
               delete parent->llink_;
               parent->llink_ = nullptr;
               link = parent;
            }
            else {
               if ( parent->parent_->llink_ == parent ) {
                  parent->parent_->llink_ = parent->llink_;
               }
               else {
                  parent->parent_->rlink_ = parent->llink_;
               }
               parent->llink_->parent_ = parent->parent_;
               link = parent->llink_;
               delete parent;
            }
         }
         else {
            if ( tree_->llink_ == nullptr ) {
               tree_ = nullptr;
            }
            return;
         }
      }
      parent = link->parent_;
      while ( parent ) {
         if ( parent->llink_ == link ) {
            --parent->info_;
         }
         link = parent;
         parent = parent->parent_;
      }
   }
}