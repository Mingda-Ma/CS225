#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using namespace cs225;
using namespace std;
/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
int w = image.width();
  int h = image.height();
  if (centerY>0 && centerY<h && centerX>0 && centerX<w){
    for(int i=0; i<w; i++){
      for (int j=0; j<h; j++){
        double dist = sqrt(pow((i - centerX),2) + pow((j - centerY),2));
        HSLAPixel& temp = image.getPixel(i,j);
        if (dist <= 160)
          temp.l = (temp.l)*(1-dist*0.005);
        else 
          temp.l = 0.2*temp.l;
      }
    }
  }
  return image;  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  for (unsigned i =0; i< image.width(); i++){
    for (unsigned j=0; j< image.height(); j++){
      HSLAPixel& temp = image.getPixel(i,j);
      if (temp.h < 216 and temp.h >11)
        temp.h = (216 - temp.h)<(temp.h - 11)?216:11;
      else {
        if (temp.h <11 && temp.h >0)
          temp.h = temp.h + 360; 
        temp.h = (temp.h - 216)<(371 - temp.h)?216:11; 
      }

    }
  }
  // return image;
//   for (unsigned x=0;x<image.width();x++){
//     for (unsigned y=0;y<image.height();y++){
//       HSLAPixel pixel=image.getPixel(x,y);
//       if (min(abs(pixel.h-11.0),abs(371.0-pixel.h))<min(abs(pixel.h-216.0),abs(pixel.h+144.0))){
//   pixel.h=11.0;
//       }
//       else{
//   pixel.h=216.0;
//       }
//     }
// }
  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs to be averaged together.
* @param secondImage The second of the two PNGs to be averaged together.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  for (unsigned i=0; i< secondImage.width(); i++){
    for (unsigned j=0; j<secondImage.height();j++){
      HSLAPixel& pixel = secondImage.getPixel(i,j);
      if (pixel.l == 1)
        firstImage.getPixel(i,j).l  =0.2+(firstImage.getPixel(i,j).l); 
    }
  }
  return firstImage;
}
