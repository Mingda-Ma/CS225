#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
	Image a,b,out;
	a.readFromFile("alma.png");
	b.readFromFile("i.png");
	StickerSheet s(a,2);
	s.addSticker(b,900,250);
	s.addSticker(b,600,600);
	s.changeMaxSticker(4);
	s.addSticker(b,700,800);
	s.addSticker(b,200,100);
	s.removeSticker(3);
	out = s.render();
	out.writeToFile("render.png");
	// Image a,b,out;
	// a.readFromFile("alma.png");
	// a.resize(1200,900);
	// a.writeToFile("test.png");
  return 0;
}
