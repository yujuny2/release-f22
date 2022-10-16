/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator();
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_) {
    ListNode* curr = head_->next;
    delete head_;
    head_ = curr;
  }
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }

  tail_ = newNode;
  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (splitPoint == length_) {
    return NULL;
  }

  if (splitPoint == 0) {
    return start;
  }

  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  int count = length_ / 3;
  if (count < 1) return;
  ListNode* curr = head_;
  for (int i = 0; i < count; i++) {
    ListNode* first = curr;
    ListNode* second = curr->next;
    ListNode* third = second->next;

    if (first == head_) {
      head_ = second;
      second->prev = NULL;
    } else {
      second->prev = first->prev;
      first->prev->next = second;
    }

    if (third == tail_) {
      first->next = NULL;
      tail_ = first;
    } else {
      first->next = third->next;
      third->next->prev = first;
    }

    third->next = first;
    first->prev = third;

    if (first->next) {
      curr = first->next;
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) return;
  if (startPoint == NULL || endPoint == NULL) return;

  ListNode* curr = startPoint;
  ListNode* endNext = (endPoint != tail_) ? endPoint->next : NULL;
  ListNode* startPrev = (startPoint != head_) ? startPoint->prev : NULL;

  while (curr != endNext) {
    ListNode* next =  (curr != tail_) ? curr->next : NULL;
    if (curr == startPoint) {
      curr->next = endNext;
      if (startPrev != NULL) {
        startPrev->next = endPoint;
      }
    } else {
      curr->next = curr->prev;
    }

    if (curr == endPoint) {
      curr->prev = startPrev;
      if (endNext != NULL) {
        endNext->prev = startPoint;
      }
    } else {
      curr->prev = next;
    }

    curr = next;
  }

  if (startPoint == head_) {
    head_ = endPoint;
  }
  if (endPoint == tail_) {
    tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  ListNode* curr = head_;
  ListNode* start = head_;
  int count = 0;

  while (curr != NULL) {
    if (count == 0) {
      start = curr;
    }
    if (count >= (n - 1) || curr->next == NULL) {
      reverse(start, curr);
      count = 0;
      curr = start;
    } else {
      count++;
    }
    curr = curr->next;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (!first && !second) {
    return NULL;
  }
  if (!first) {
    return second;
  }
  if (!second) {
    return first;
  }
  // ListNode* curr = first;
  // ListNode* nexthead2 = NULL;
  // while (curr && second) {
  //   if (second->data < curr->data) {
  //     if (curr == first) {
  //       first = second;
  //     } else {
  //       second->prev = curr->prev;
  //       curr->prev->next = second;
  //     }
  //     nexthead2 = second->next;
  //     second->next = curr;
  //     curr->prev = second;
  //     if (nexthead2) {
  //       nexthead2->prev = NULL;
  //     }
  //     second = nexthead2;
  //   } else {
  //     if (curr->next) {
  //       curr = curr->next;
  //     } else {
  //       curr->next = second;
  //       second->prev = curr;
  //       break;
  //     }
  //   }
  // }
  // return first;
  ListNode* tbr = (second->data < first->data) ? second : first;
  ListNode* tbi = (second->data < first->data) ? second : first;
  ListNode* tbm = (second->data < first->data) ? first : second;
  ListNode* next = NULL;
  while (tbi && tbm) {
    if (tbm->data < tbi->data) {
      tbi->prev->next = tbm;
      tbm->prev = tbi->prev;
      while (tbm->next && tbm->next->data < tbi->data) {
        tbm = tbm->next;
      }
      next = tbm->next;
      tbm->next = tbi;
      tbi->prev = tbm;
      tbm = next;
    } else {
      if (tbi->next) {
        tbi = tbi->next;
      } else {
        tbi->next = tbm;
        tbm->prev = tbi;
        tbi = NULL;
      }
    }
  }
  return tbr;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1) {
    return start;
  }
  int cl = (chainLength % 2 == 0) ? chainLength / 2 : chainLength / 2 + 1;
  ListNode* secondHead = split(start, chainLength / 2);
  return merge(mergesort(start, chainLength / 2), mergesort(secondHead, cl));
}
