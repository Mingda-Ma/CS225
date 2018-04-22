/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements (int num) {
  for (int i = 0; i < num; i++) {
    setsArr.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (setsArr[elem] < 0) {
    return elem;
  } else {
    return find(setsArr[elem]);
  }
}

void DisjointSets::setunion(int a, int b) {
  int root1 = find(a);
  int root2 = find(b);
  int new_size = setsArr[root1] + setsArr[root2];
  if (setsArr[root1] < setsArr[root2]) {
    setsArr[root2] = root1;
    setsArr[root1] = new_size;
  } else {
    setsArr[root1] = root2;
    setsArr[root2] = new_size;
  }
}

int DisjointSets::size(int elem) {
  if (setsArr[elem] < 0) {
    return -1 * setsArr[elem];
  } else {
    return 1;
  }
}
