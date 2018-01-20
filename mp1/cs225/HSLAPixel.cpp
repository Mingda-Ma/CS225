/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 */

#include "HSLAPixel.h"



namespace cs225 {
	HSLAPixel::HSLAPixel(){
	l=1.0;
	a=1.0;
	h=0;
	s=0;
}
HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
	l = luminance;
	s = saturation;
	h = hue;
	a = 1.0;
}
HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
	h = hue;
	s = saturation;
	l = luminance;
	a = alpha;
}
void HSLAPixel::operator=(HSLAPixel other){
	h = other.h;
	s = other.s;
	l = other.l;
	a = other.a;
}

}

