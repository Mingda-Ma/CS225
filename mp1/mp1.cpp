#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <iostream>
#include <vector>
#include "mp1.h"
using namespace cs225;
using namespace std;



void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
	PNG input;
	input.readFromFile(inputFile);
	PNG output(input.width(),input.height());
	for (unsigned i=0; i< input.width(); i++){
		for (unsigned j=0; j<input.height(); j++){

				 *output.getPixel(i,j) = *input.getPixel(output.width()-i-1,output.height()-j-1);
         // output.getPixel(i,j)->s = input.getPixel(output.width()-i-1,output.height()-j-1)->s;
         // output.getPixel(i,j)->l = input.getPixel(output.width()-i-1,output.height()-j-1)->l;
         // output.getPixel(i,j)->a = input.getPixel(output.width()-i-1,output.height()-j-1)->a;
      }
	}
	output.writeToFile(outputFile);
}

static unsigned char iteration(int x, int y, unsigned w, unsigned h)
{

	static const float orig_x = w * 2 / 3;
	static const float orig_y = h * 1 / 2;
	int i;

	complex<double> c((x-orig_x)/(w/3),(y-orig_y)/(h/2));
	complex<double> z = 0.0;

	for (i = 0; i < 360; i++) {
		z = z*z + c;
		if (real(z) > 2 || imag(z) > 2)
			break;
	}

	return (unsigned char)(i == 360 ? 0 : i);

}



PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
  HSLAPixel gray(25,1,0.5,1);//default gray
  // HSLAPixel orange(11,1,0.5,1);
  // HSLAPixel blue(216,1,0.5,1);
  // HSLAPixel green(90,1,0.5,1);
  // HSLAPixel pink(315,0.5,0.5,1);
  // HSLAPixel purple(230,1,0.5,1);
  for (unsigned i=0; i<height; i++){
  	for (unsigned j=0;j<width;j++){
  		unsigned char iter=iteration(i,j,width,height);
  		if (iter){
  			// if (iter >0 && iter<=2)
  			// 	*png.getPixel(i,j) = pink;
  			// else if(iter >2 && iter <=5)
  			// 	*png.getPixel(i,j) = blue;
  			// else if (iter >5 && iter<=8)
  			// 	*png.getPixel(i,j) = green;
  			// else if (iter>8 && iter<=15)
  			// 	*png.getPixel(i,j) = orange;
  			// else 
  			// 	*png.getPixel(i,j) = purple;
  			// vector<double,double,double> pixel(iter,(float) abs(j - orig_x) / width_size * Maxval)
  			HSLAPixel rv(iter,float(j)/width,float(i)/width,1); 
  			*png.getPixel(i,j) = rv;
  		}
  		else{
  			*png.getPixel(i,j) = gray;//default  
  		}
  	}
  }
  return png;
}
