#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
int main() {

  Image i;
  i.readFromFile("alma.png");
  StickerSheet res(i,4);
  Image sk1;
  Image sk2;
  Image sk3;
  Image sk4;
  Image i1;
  i1.readFromFile("i.png");
  sk1.readFromFile("stk6.png");sk1.resize(450,600);
  // sk2.readFromFile("sk1.png");sk2.resize(600,400);
  sk3.readFromFile("123.png");sk3.resize(450,600);
  res.addSticker(sk1,0,0);
  res.addSticker(sk3,450,0);
  res.addSticker(i1,700,400);
  // res.addSticker(sk2,600,1);
  // res.addSticker(sk3,1,400);
  // res.addSticker(sk4,601,401);
  Image temp = res.render();
  temp.writeToFile("fuck.png");
  return 0;
}
