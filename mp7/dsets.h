#ifndef DSET_H
#define  DSET_H
#include <algorithm>
#include <vector>
using namespace std;
class DisjointSets{
public:
  void setunion(int r1,int r2);
  void addelements(int num);
  int find(int x);
private:
  vector<int> arr;
 };
#endif
