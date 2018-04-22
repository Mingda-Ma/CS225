/* Your code here! */
#ifndef _DSET_H_
#define _DSET_H_

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
class DisjointSets  {
public:
  void addelements(int num);
  int find(int elem);
  void setunion(int a, int b);
  int size(int elem);
  vector<int> setsArr;
};

#endif
