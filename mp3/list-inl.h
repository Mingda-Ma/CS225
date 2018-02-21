/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  while (head_ != NULL){
    ListNode* curr= head_;
    head_ = head_->next;
    delete curr;
  }
  length_ = 0;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* temp = new ListNode(ndata);
  if (head_==NULL){
    head_ = temp;
    tail_ = head_;
    length_++;
  }
  else{
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
    length_++;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* temp = new ListNode(ndata);
  if (tail_ == NULL){
    tail_ = temp;
    head_ = tail_;
  }
  else{
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;
  }
  // temp = NULL;
  length_++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  // if (head_==NULL or tail_==NULL or tail_==head_){
  //   cout << "here"<<endl;
  //   return;
  // }
  // else
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
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {

  if (startPoint == NULL or endPoint==NULL or startPoint==endPoint)
    return;
  ListNode* st = startPoint;
  ListNode* ed = endPoint;
  ListNode* stprev = startPoint->prev;
  ListNode* ednext = endPoint->next;
  while (startPoint != ednext){
    ListNode* temp = startPoint->next;
    startPoint->next = startPoint->prev;
    startPoint->prev = temp;
    startPoint = startPoint->prev;
  }
  endPoint->prev = stprev;
  endPoint = st;
  endPoint->next = ednext;
  if (stprev==NULL and ednext==NULL){
    head_ = ed;
    tail_ = st;
  }
  else if (stprev==NULL){
    ednext->prev = st;
    head_ = ed;
  }
  else if (ednext == NULL){
    stprev->next = ed;
    tail_ = st;
  }
  else{
    stprev->next = ed;
    ednext->prev = st;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (head_ ==NULL)
    return;
  ListNode* st = head_;
  ListNode* stnext = head_;
  while (stnext->next != NULL && st->next != NULL){
    int ct =0;
    stnext = st;
    while (ct<n-1 && stnext->next != NULL){
      stnext = stnext->next;
      ct++;
    }
    reverse(st,stnext);
    st = stnext->next;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  if (head_ == NULL || head_==tail_ || tail_==NULL)
    return;
  while(curr->next != tail_ and curr->next != NULL){
    ListNode* currnext = curr->next;
    ListNode* temp = curr->next->next;
    temp->prev = curr;
    curr->next = temp;
    currnext->next = NULL;
    currnext->prev = tail_;
    tail_->next = currnext;
    tail_ = currnext;
    curr = curr->next;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
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
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode* st = start;
  ListNode* end = start;
  int ct=0;
  while (ct < splitPoint-1){
    if (end == NULL)
      return NULL;
    else{
      end = end->next;
    }
    ct++;
  }
  ListNode* temp = end;
  end = end->next;
  temp->next = NULL;
  end->prev = NULL;
  
  return end;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
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
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL){
    return second;
  }
  else if (second == NULL){
    return first;
  }
  else if (second == first){
    return first;
  }
  ListNode* rv;
  if (first->data < second->data){
    rv = first;
    first = first->next;
  }
  else{
    rv = second;
    second = second->next;
  }
  ListNode* h = rv;
  while (first != NULL and second != NULL){
    if (first->data < second->data){
      rv->next = first;
      first->prev = rv;
      first = first->next;
    }
    else{
      rv->next = second;
      second->prev = rv;
      second = second->next;
    }
    rv = rv->next;
  }
  if (first == NULL){
    rv->next = second;
    second->prev = rv;
  }
  else{
    rv->next = first;
    first->prev = rv;
  }
  // while (rv != NULL){
  //   rv = rv->next;
  // }
  // tail_ = rv;
  // second = NULL;
  return h;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode* hd = start;
  if (chainLength == 1){
    start->next = NULL;
    start->prev = NULL;
    return start;
  }
  else{
    int ct = chainLength/2;
    ListNode* temp = start;
    for (int i=0;i< ct; i++){
      temp= temp->next;
    }
    temp->prev->next = NULL;
    temp->prev = NULL;
    ListNode* temp1 = mergesort(start,chainLength/2);
    ListNode* temp2 = mergesort(temp,chainLength - chainLength/2);
    hd = merge(temp1,temp2);
  }
  return hd;
}
