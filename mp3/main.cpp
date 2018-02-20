#include "list.h"

int main() {
  List<int> l,l1;
  l.insertBack(0);
  l.insertBack(1);
  l.insertBack(2);
  l1.insertBack(3);
  l1.insertBack(4);
  l1.insertBack(5);
  l1.insertBack(6);
  l1.insertBack(7);
  l1.insertBack(8);
  l1.insertBack(9);
  l.mergeWith(l1);

  l.print(cout);
  l1.print(cout);
  cout <<endl;
  return 0;
}
