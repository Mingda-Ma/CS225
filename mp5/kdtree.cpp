/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
       if  (curDim<Dim && 0<=curDim){
       if (first[curDim]<second[curDim])
          return true;
      if (first[curDim]>second[curDim])
        return false;
      else
        return first < second;
    }
    else
      return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
      double dist1=0,dist2=0;
    for (int i = 0; i < Dim; i++){
      dist1+=(potential[i]-target[i])*(potential[i]-target[i]);
      dist2+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
    }
    if (dist1<dist2)
      return true;
    if (dist1>dist2)
      return false;
    else
      return potential < currentBest;
     return false;
}

//helper function of partition
template <int Dim>
int KDTree<Dim>::findMedianIndex(int curDim, int left, int right, int pivotIndex) {

  Point<Dim> pivotValue = Points[pivotIndex];
  //cout<<Points[right]<<" "<<Points[pivotIndex]<<endl;
  Point<Dim> temp = Points[pivotIndex];
  Points[pivotIndex] = Points[right];
  Points[right] = temp;
  //cout<<Points[right]<<" "<<Points[pivotIndex]<<endl;
  int storeIndex = left;
  for (int i = left; i <= right - 1; i++) {
    if (smallerDimVal(Points[i], pivotValue, curDim))
    {
      Point<Dim> temp_2 = Points[storeIndex];
      Points[storeIndex] = Points[i];
      Points[i] = temp_2;
      storeIndex++;
    }
  }
  Point<Dim> temp_3 = Points[right];
  Points[right] = Points[storeIndex];
  Points[storeIndex] = temp_3;
  return storeIndex;
}


//helper function of quickselect
template <int Dim>
void KDTree<Dim>::select(int curDim, int left, int right, int k) {
  //cout<<96<<endl;
  if (left >= right) 
  {
    //cout<<99<<endl;
    return;
  }
  int pivotIndex = (left + right) / 2;
  pivotIndex = findMedianIndex(curDim, left, right, pivotIndex);
  if (k == pivotIndex)
  {
    //cout<<106<<endl;
    return;
  }
  else if (k < pivotIndex)
  {
    select(curDim, left, pivotIndex - 1, k);
  }
  else
  {
    select(curDim, pivotIndex + 1, right, k);
  }

}


template <int Dim>
void KDTree<Dim>::build(int curDim, int left, int right) {
  int midIndex = (left + right) / 2;
  select(curDim, left, right, midIndex);
  //cout<<120<<endl;
  if (left < midIndex - 1)
  {
    build((curDim + 1) % Dim, left, midIndex - 1);
  }
  if (right > midIndex + 1)
  {
    build((curDim + 1) % Dim, midIndex + 1, right);
  }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::putPoints(int left, int right) {
  if (left > right) {
    return NULL;
  }
  int pos = (left + right ) / 2;
  if (pos >= 0 && pos < (int)Points.size()) {
    KDTree<Dim>::KDTreeNode* subRoot = new KDTree<Dim>::KDTreeNode(Points[pos]);
    subRoot->left = putPoints(left, pos - 1);
    subRoot->right = putPoints(pos + 1, right);
    return subRoot;

  }
  return NULL;
}



template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  Points = newPoints;
  build(0, 0, Points.size() - 1);
  //cout<<153<<endl;
  size = newPoints.size();
  //cout<<161<<endl;
  root = putPoints(0, (int)size - 1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  Points = other.Points;
  size = other.size;
  root = putPoints(0, (int)size - 1);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  delete *this;
  this = new KDTree(rhs);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  clear(root);
  size = 0;
  Points.clear();
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findhelper( 0, 0, Points.size()-1, Points[(Points.size()-1)/2], query);
}


template<int Dim>
Point<Dim> KDTree<Dim>::findhelper( int curDim, int left, int right, const Point<Dim> &currentBest, const Point<Dim> &query) const
{
    int median = (left + right)/2;
    //int sMedian;
    Point<Dim> ret = currentBest;
    bool target_left = true;
    Point<Dim> temp = Points[median]; //get the temptory point in the middle

    if(left == right){
        //case leaf
       if(shouldReplace(query, currentBest, Points[left])){
            ret = Points[left];
            return ret;
        }
        ret = currentBest;
        return ret;
    }
    //if the nearest exists at the right
    if(smallerDimVal(Points[median], query, curDim)){
      if (right > median){
        ret = findhelper( (curDim+1)%Dim, median+1, right, currentBest, query);
        target_left = false;
      }
    //    sMedian = (left+median-1)/2;
    }
    //if the nearest exists at the left
    if(smallerDimVal(query, Points[median], curDim)){ 
      if (left < median){  
        ret = findhelper( (curDim+1)%Dim, left, median-1, currentBest, query);
        target_left = true;
      }
    //    sMedian = (median+right)/2;
    }
    //determine whether to replace
    if(shouldReplace(query, ret, Points[median]))
        ret = Points[median];
    int retval = 0;
    for (int i = 0; i < Dim; i++){
        retval += (query[i]-ret[i])*(query[i]-ret[i]);
    }
    if (pow(temp[curDim] - query[curDim],2) <= retval){
        if (target_left && right > median)
            ret = findhelper( (curDim+1) % Dim, median+1, right, ret, query);
        else if (!target_left && left < median)
            ret = findhelper( (curDim+1) % Dim, left, median-1, ret, query);
    }
    return ret;

}


template <int Dim>
void KDTree<Dim>::clear(typename KDTree<Dim>::KDTreeNode* subRoot) {
  if (subRoot == NULL) return;
 
    /* first delete both subtrees */
  clear(subRoot->left);
  clear(subRoot->right);

  delete subRoot;

}


template<int Dim>
double KDTree<Dim>::getD(const Point<Dim> &first, const Point<Dim>&second) const {
  double total = 0;
  for (int i = 0; i < Dim; i++) {
    total += pow(first[i]-second[i], 2);
  }
  total = pow(total, 0.5);
  return total;
}







