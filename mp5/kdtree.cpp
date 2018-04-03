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
  // if (curDim < Dim && curDim >= 0)
  // {
  //   if (first[curDim] != second[curDim])
  //   {
  //     return first[curDim] < second[curDim];
  //   }
  //   else
  //   {
  //     return first < second;
  //   }
  // }

  //   return false;
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
  //cout<<37<<endl;
  // double firstD = getD(target, currentBest);
  // double secondD = getD(target, potential);
  // //cout<<firstD<<" "<<secondD<<endl;
  // if (secondD != firstD) {
  //   return secondD < firstD;
  // }
  // else {
  //   return potential < currentBest;
  // }
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
/**
 function partition(list, left, right, pivotIndex)
     pivotValue := list[pivotIndex]
     swap list[pivotIndex] and list[right]  // Move pivot to end
     storeIndex := left
     for i from left to right-1
         if list[i] < pivotValue
             swap list[storeIndex] and list[i]
             increment storeIndex
     swap list[right] and list[storeIndex]  // Move pivot to its final place
     return storeIndex
*/

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

  //Points = rhs.Points;
  //size = rhs.size;
  //clear(root);
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

// template <int Dim>
// Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
// {
//     /**
//      * @todo Implement this function!
//      */
//   Point<Dim> best = find(query, 0, 0, (int)size - 1, root->point);
//   return best;
// }

// template <int Dim>
// Point<Dim> KDTree<Dim>::find(const Point<Dim>& query, int curDim, int left, int right,const Point<Dim>& best) const{

//   int mid = (left+right)/2;
//   Point<Dim> result = best;

//   if (smallerDimVal(best, query, curDim))
//   {

//   }



//   return best;

// }
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return find(query, 0, 0, Points.size()-1, Points[(Points.size()-1)/2]);
    //return findcurrbest(Points, 0, Points.size()-1, query, 0);
}


template<int Dim>
Point<Dim> KDTree<Dim>::find(const Point<Dim> &query, int curDim, int left, int right, const Point<Dim> &currentBest) const
{
    int median = (left + right)/2;
    int sMedian;
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
    if(smallerDimVal(Points[median], query, curDim) && right > median){
        ret = find(query, (curDim+1)%Dim, median+1, right, currentBest);
        target_left = false;
        sMedian = (left+median-1)/2;
    }
    //if the nearest exists at the left
    if(smallerDimVal(query, Points[median], curDim) && left < median){   
        ret = find(query, (curDim+1)%Dim, left, median-1, currentBest);
        target_left = true;
        sMedian = (median+1+right-1)/2;
    }
    //determine whether to replace
    if(shouldReplace(query, ret, Points[median]))
        ret = Points[median];
     
    if (pow(temp[curDim] - query[curDim],2) <= getDistance(query, ret)){
        if (target_left && right > median)
            ret = find(query, (curDim+1) % Dim, median+1, right, ret);
        if (!target_left && left < median)
            ret = find(query, (curDim+1) % Dim, left, median-1, ret);
    }
    return ret;

}

// template <int Dim>
// Point<Dim> KDTree<Dim>::findcurrbest( const vector<Point<Dim>>& list, int left, int right, const Point<Dim>& query, int dim)const {
//   Point<Dim> currbest,curr;
//   if (left >= right){
//     currbest=list[left];
//     return currbest;

//   }
//   int mid = (left+right)/2;
//   curr=list[mid];
//   if (smallerDimVal(query,list[mid],dim)){

//       currbest = findcurrbest(list, mid+1, right, query, (dim+1)%Dim);

//     if (shouldReplace(query, currbest, curr))
//       currbest=curr;
//     if (getD(currbest,query)> fabs(curr[dim]-query[dim]) || getD(currbest,query) == fabs(curr[dim]-query[dim])){
//       Point<Dim> otherside=findcurrbest(list, left, mid-1, query, (dim+1)%Dim);
//       if (shouldReplace(query, currbest, otherside))
//         currbest=otherside;
//       }
//              return currbest;
//     }
// else {

//       currbest = findcurrbest(list, left, mid-1, query, (dim+1)%Dim);

//   if (shouldReplace(query, currbest, curr))
//      currbest=curr;
//   if (getD(currbest,query)> fabs(curr[dim]-query[dim]) || getD(currbest,query)== fabs(curr[dim]-query[dim])){
//      Point<Dim> otherside = findcurrbest(list, mid+1, right, query, (dim+1)%Dim);
//      if (shouldReplace(query, currbest, otherside))
//        currbest=otherside;
//      }
//             return currbest;
//     }

// }

template <int Dim>
void KDTree<Dim>::clear(typename KDTree<Dim>::KDTreeNode* subRoot) {
  if (subRoot == NULL) return;
 
    /* first delete both subtrees */
  clear(subRoot->left);
  clear(subRoot->right);

  delete subRoot;

}

template<int Dim>
int KDTree<Dim>::getDistance(const Point<Dim> &point1, const Point<Dim>&point2) const
{
    int ret = 0;
    for (int i = 0; i < Dim; i++){
        ret += (point1[i]-point2[i])*(point1[i]-point2[i]);
    }
    return ret;
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







