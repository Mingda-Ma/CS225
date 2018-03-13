#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}
ImageTraversal::Iterator::Iterator(){};

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(PNG& png, Point& pt, double tol, ImageTraversal* next) {
  /** @todo [Part 1] */
  pointer = next;
  picture = png;
  start_point = pt;
  curr_point = pt;
  vector<bool> temp;
  t = tol;
  for (unsigned i = 0; i< picture.height(); i++){
    temp.push_back(false);
  }
  for (unsigned i=0; i< picture.width(); i++){
    isvisited.push_back(temp);
  }
  isvisited[start_point.x][start_point.y] = true;
  unsigned width = picture.width();
  unsigned height = picture.height();
  HSLAPixel& start_pixel = picture.getPixel(start_point.x, start_point.y);
  if (curr_point.x+1 < width ){
    HSLAPixel& curr_pixel = picture.getPixel(curr_point.x+1,curr_point.y);
    if (calculateDelta(curr_pixel,start_pixel) < t){
      pointer->add(Point(curr_point.x+1,curr_point.y));
    }
  }
  if (curr_point.y+1 < height ){
    HSLAPixel& curr_pixel = picture.getPixel(curr_point.x,curr_point.y+1);
    if (calculateDelta(curr_pixel,start_pixel) < t){
      pointer->add(Point(curr_point.x,curr_point.y+1));
    }
  }
  if ( int(curr_point.x) -1 >=0){
    HSLAPixel& curr_pixel = picture.getPixel(curr_point.x-1,curr_point.y);
    if (calculateDelta(curr_pixel,start_pixel) < t){
      pointer->add(Point(curr_point.x-1,curr_point.y));
    }
  }
  if ( int(curr_point.y) -1 >=0){
    HSLAPixel& curr_pixel = picture.getPixel(curr_point.x,curr_point.y-1);
    if (calculateDelta(curr_pixel,start_pixel) < t){
      pointer->add(Point(curr_point.x,curr_point.y-1));
    }
  }  
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (pointer->empty()){
      pointer = NULL;
      return *this;
  }
  Point temp = pointer->pop();
  while (isvisited[temp.x][temp.y]){
    if (pointer->empty()){
      pointer = NULL;
      return *this;
    }
    temp = pointer->pop();
  }
  isvisited[temp.x][temp.y] = true;
  curr_point = temp;
  unsigned width = picture.width();
  unsigned height = picture.height();
  HSLAPixel& start_pixel = picture.getPixel(start_point.x, start_point.y);
  if (curr_point.x+1 < width ){
    HSLAPixel& curr_pixel = picture.getPixel(curr_point.x+1,curr_point.y);
    if (calculateDelta(curr_pixel,start_pixel) < t){
      pointer->add(Point(curr_point.x+1,curr_point.y));
    }
  }
  if (curr_point.y+1 < height ){
    HSLAPixel& curr_pixel = picture.getPixel(curr_point.x,curr_point.y+1);
    if (calculateDelta(curr_pixel,start_pixel) < t){
      pointer->add(Point(curr_point.x,curr_point.y+1));
    }
  }
  if ( int(curr_point.x) -1 >=0){
    HSLAPixel& curr_pixel = picture.getPixel(curr_point.x-1,curr_point.y);
    if (calculateDelta(curr_pixel,start_pixel) < t){
      pointer->add(Point(curr_point.x-1,curr_point.y));
    }
  }
  if ( int(curr_point.y) -1 >=0){
    HSLAPixel& curr_pixel = picture.getPixel(curr_point.x,curr_point.y-1);
    if (calculateDelta(curr_pixel,start_pixel) < t){
      pointer->add(Point(curr_point.x,curr_point.y-1));
    }
  }
  if (pointer->empty())
    pointer = NULL;
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_point;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return pointer != NULL;
}

