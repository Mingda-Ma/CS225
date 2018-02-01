/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#ifndef IMAGE_H_
#define IMAGE_H_
using namespace cs225;
class Image: public PNG{
public:
	Image():PNG(){};
	Image(unsigned w,unsigned h):PNG(w,h){};
	void lighten(){
		for (unsigned i=0;i< width();i++){
			for (unsigned j=0;j<height();j++){
				if (getPixel(i,j).l <= 0.9)
					getPixel(i,j).l += 0.1;
				else
					getPixel(i,j).l = 1;
			}
		}
	}
	void lighten(double amount){
		for (unsigned i=0;i< width();i++){
			for (unsigned j=0;j<height();j++){
				if (getPixel(i,j).l <= (1-amount))
					getPixel(i,j).l += amount;
				else
					getPixel(i,j).l = 1;
			}
		}
	}			
	void darken(){
		for (unsigned i=0;i< width();i++){
			for (unsigned j=0;j<height();j++){
				if (getPixel(i,j).l >= 0.1)
					getPixel(i,j).l -= 0.1;
				else
					getPixel(i,j).l = 0;
			}
		}
	}
	void darken(double amount){
		for (unsigned i=0;i< width();i++){
			for (unsigned j=0;j<height();j++){
				if (getPixel(i,j).l >= amount)
					getPixel(i,j).l -= amount;
				else
					getPixel(i,j).l = 0;
			}
		}
	}
	void saturate(){
		for (unsigned i=0;i< width();i++){
			for (unsigned j=0;j<height();j++){
				if (getPixel(i,j).s <= 0.9)
					getPixel(i,j).s += 0.1;
				else
					getPixel(i,j).s = 1;
			}
		}
	}
	void saturate(double amount){
		for (unsigned i=0;i< width();i++){
			for (unsigned j=0;j<height();j++){
				if (getPixel(i,j).s <= (1-amount))
					getPixel(i,j).s += amount;
				else
					getPixel(i,j).s = 1;
			}
		}
	}
	void desaturate(double amount){
		for (unsigned i=0;i< width();i++){
			for (unsigned j=0;j<height();j++){
				if (getPixel(i,j).s >= amount)
					getPixel(i,j).s -= amount;
				else
					getPixel(i,j).s = 0;
			}
		}		
	}
	void desaturate(){
		for (unsigned i=0;i< width();i++){
			for (unsigned j=0;j<height();j++){
				if (getPixel(i,j).s >= 0.1)
					getPixel(i,j).s -= 0.1;
				else
					getPixel(i,j).s = 0;
			}
		}		
	}
	void grayscale(){
	  for (unsigned x = 0; x < width(); x++) {
	    for (unsigned y = 0; y < height(); y++) {
	      HSLAPixel & pixel = getPixel(x, y);
	      pixel.s = 0;
	    }
	  }
	}
	void rotateColor(double degree){
		for (unsigned i=0;i<width();i++){
			for (unsigned j=0;j<height();j++){
				int temp = getPixel(i,j).h + degree;
				if (temp <0)
					temp = 360+temp;
				getPixel(i,j).h = temp%360;
			}
		}
	}
	void illinify(){
	  for (unsigned i =0; i< width(); i++){
	    for (unsigned j=0; j< height(); j++){
	      HSLAPixel& temp = getPixel(i,j);
	      if (temp.h < 216 and temp.h >11)
	        temp.h = (216 - temp.h)<(temp.h - 11)?216:11;
	      else {
	        if (temp.h <11 && temp.h >0)
	          temp.h = temp.h + 360; 
	        temp.h = (temp.h - 216)<(371 - temp.h)?216:11; 
	      }
	    }
	  }
	}
	void scale(double factor){
		PNG temp(*this);
		resize(width()*factor,height()*factor);
		for (unsigned i=0; i<width();i++){
			for (unsigned j=0;j<height();j++){
				getPixel(i,j) = temp.getPixel(i/factor,j/factor);
			}
		}		
	}
	void scale(unsigned w,unsigned h){
		unsigned a = width();
		unsigned b = height();
		unsigned factor = max(w/a,h/b);
		scale(factor);		
	}
};
#endif
 