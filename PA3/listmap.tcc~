// $Id: listmap.tcc,v 1.1 2014-04-24 18:02:55-07 - - $

#include "listmap.h"
#include "trace.h"

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (const value_type& pair):
            pair(pair), prev(NULL), next(NULL) {
}

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::listmap (): head(NULL), tail (NULL) {
}

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap () {
   iterator iter;
   while (!this->empty()){
      iter = this->begin();
      iter.erase();
   }
   TRACE ('l', (void*) this);
}

template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::insert (const xpair<Key,Value>& pair) {
   Less less;
   cout << pair.first << " = " << pair.second << endl;
   if (head == NULL){
      head = tail = new node(pair);
   }else if (head == tail){
      if (head->pair.first == pair.first){
         head->pair = pair;
      }else if (less (pair.first, head->pair.first)){
         head = new node(pair);
         tail->prev = head;
         head->next =  tail;
      }else{
         tail = new node(pair);
         tail->prev = head;
         head->next =  tail;
      }
   }else{
      node* tp = head;
      while (tp != NULL){
         if (tp->pair.first == pair.first){
            tp->pair = pair;
            return;
         }else if (less (pair.first, tp->pair.first)){
            node* np_new = new node(pair);
            if (tp->prev != NULL)
               tp->prev->next = np_new;
            else
               head = np_new;
            np_new->prev = tp->prev;
            np_new->next = tp;
            tp->prev = np_new;
            return;
         }
         if (tp == tail){
            tail->next = new node(pair);
            tail->next->prev = tail;
            tail = tail->next;
         }
         tp = tp->next;
      }
   }

   TRACE ('l', &pair << "->" << pair);
}


//----------------Iterator-------------------
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) {
   node* iter_p = this->head;
   while (iter_p->pair.first != that){
      if (iter_p->next ==  NULL)
         break;
      else
         iter_p = iter_p->next;
   }

   TRACE ('l', that);
   return iterator(this, iter_p);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::begin () {
   return iterator (this, head);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::end () {
   return iterator (this, NULL);
}

template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::empty () const {
   return head == NULL;
}


template <typename Key, typename Value, class Less>
xpair<Key,Value>& listmap<Key,Value,Less>::iterator::operator* () {
   TRACE ('l', where->pair);
   return where->pair;
}

template <typename Key, typename Value, class Less>
xpair<Key,Value> *listmap<Key,Value,Less>::iterator::operator-> () {
   TRACE ('l', where->pair);
   return &(where->pair);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++ () {
   TRACE ('l', "First: " << map << ", " << where);
   TRACE ('l', "Second: " << map->head << ", " << map->tail);
   where = where->next;
   return *this;
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator-- () {
   where = where->prev;
   return *this;
}

template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::iterator::iterator (listmap *map,
            node *where): map (map), where (where){
}

template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::iterator::erase () {
   if (this->where->prev != NULL){
       this->where->prev->next = this->where->next;
   }
   if (this->where->next != NULL){
       this->where->next->prev = this->where->prev;
   }
   delete this->where;


   TRACE ('l', "map = " << map << ", where = " << where << endl);
}

