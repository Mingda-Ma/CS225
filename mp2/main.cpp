#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
	// Image a,b,out;
	// a.readFromFile("alma.png");
	// b.readFromFile("i.png");
	// StickerSheet s(a,2);
	// s.addSticker(b,900,250);
	// s.addSticker(b,600,600);
	// s.changeMaxStickers(4);
	// s.addSticker(b,700,800);
	// s.addSticker(b,200,100);
	// cout << 19<<endl;
	// s.removeSticker(3);
	// cout << 21 << endl;
	// out = s.render();
	// out.writeToFile("render.png");
 Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 1);
  sheet.addSticker(i, 20, 200);
  // cout << "here"<<endl;
  sheet.changeMaxStickers(2);
  // cout << "addSticker"<<endl;
  sheet.addSticker(i, 40, 200);
  // cout << "hehe"<<endl;
  Image expected;
  expected.readFromFile("tests/expected-2.png");
  sheet.render();
  sheet.writeToFile("hehe.png");
  cout <<"fuck"<<endl;
  return 0;
}
