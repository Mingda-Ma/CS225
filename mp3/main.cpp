#include "list.h"

int main() {
  List<int> l;
  l.insertBack(0);
  l.insertBack(1);
  l.insertBack(2);
  l.insertBack(3);
  l.insertBack(4);
  l.insertBack(5);
  l.insertBack(6);
  l.insertBack(7);
  l.insertBack(8);
  l.insertBack(9);
  l.waterfall();

  l.print(cout);
  cout <<endl;
  return 0;
}
