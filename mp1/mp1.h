#ifndef MP1_H_
#define MP1_H_

#include <string>
#include "cs225/PNG.h"
#include <complex>

void rotate(std::string inputFile, std::string outputFile);
static unsigned char iteration(int x,int y, unsigned w, unsigned h);
cs225::PNG myArt(unsigned int width, unsigned int height);

#endif
