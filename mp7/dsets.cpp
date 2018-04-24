#include "dsets.h"
#include <algorithm>
#include <vector>
using namespace std;

int DisjointSets::find(int x){
  if (arr[x]<0)
    return x;
  else
    return arr[x]=find(arr[x]);
}

void DisjointSets::setunion(int a,int b){
//a,b has to be roots.
  int r1=find(a);
  int r2=find(b);
  int newsize=arr[r1]+arr[r2];
  if (r1==r2) return;
  if (arr[r1]<=arr[r2]){//find the root with bigger absolute value, points to it.
    arr[r2]=r1;
    arr[r1]=newsize;
  }
  else{
    arr[r1]=r2;
    arr[r2]=newsize;
  }
}

void DisjointSets::addelements(int num){
  for (int i=0;i<num;i++){
    arr.push_back(-1);
  }
}
