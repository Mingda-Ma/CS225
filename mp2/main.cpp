#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
int main() {

 Image i;
 i.readFromFile("alma.png");
  StickerSheet res(i,4);
  Image sk1;
  sk1.readFromFile("i.png");
  res.addSticker(sk1,20,300);
  res.addSticker(sk1,100,300);
  res.addSticker(sk1,200,300);

  Image temp = res.render();
  temp.writeToFile("fuck.png");
  return 0;
}
