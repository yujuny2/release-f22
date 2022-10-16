#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  
  Image alma;
  alma.readFromFile("../alma.png");

  Image illinified_alma;
  illinified_alma.readFromFile("../illinify.png");
  illinified_alma.scale(0.4);

  Image rotated_alma;
  rotated_alma.readFromFile("../rotateColor.png");
  rotated_alma.scale(0.4);

  Image grayscale_alma;
  grayscale_alma.readFromFile("../grayscale.png");
  grayscale_alma.scale(0.4);

  Image rotated_alma2;
  rotated_alma2.readFromFile("../rotateColor.png");
  rotated_alma2.rotateColor(90);
  rotated_alma2.scale(0.4);

  StickerSheet ss(alma, 4);
  ss.addSticker(illinified_alma, 100, 80);
  ss.addSticker(rotated_alma, 440, 80);
  ss.addSticker(grayscale_alma, 100, 310);
  ss.addSticker(rotated_alma2, 440, 310);

  Image res = ss.render();
  res.writeToFile("../myImage.png");

  StickerSheet copyss(ss);
  copyss.translate(1, 8, 10);
  Image copy = copyss.render();
  copy.writeToFile("../copyss.png");

  StickerSheet ss3(alma, 3);
  rotated_alma.scale(0.5);
  grayscale_alma.scale(0.3);
  ss3.addSticker(rotated_alma, 45, 90);
  ss3.addSticker(grayscale_alma, 89, 78);
  Image ss3i = ss3.render();
  ss3i.writeToFile("../ss3.png");

  ss3 = copyss;
  ss3.removeSticker(0);
  Image ss32i = ss3.render();
  ss32i.writeToFile("../ss32.png");


// test assignment operator
/*
  Image alma; alma.readFromFile("../tests/alma.png");
  Image i;    i.readFromFile("../tests/i.png");
  Image expected; expected.readFromFile("../tests/expected.png");
  Image expected2; expected2.readFromFile("../tests/expected-2.png");

  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(alma, 5);
  s2 = s1;
  s2.removeSticker(1);

  s1.render().writeToFile("../testing_l77s1.png");
  s2.render().writeToFile("../testing_l77s2.png");

*/

  // Image alma; alma.readFromFile("../tests/alma.png");
  // Image i;    i.readFromFile("../tests/i.png");

  // StickerSheet sheet(alma, 5);

  // // Image almaDuplicate = alma;

  // // StickerSheet sheetDuplicate(almaDuplicate, 5);
  // // sheet = sheetDuplicate;

  // sheet.render().writeToFile("../testingsheet.png");

  // sheet.addSticker(i, 800, 200);
  // sheet.addSticker(i, 50, 500);

  // sheet.changeMaxStickers(7);
  // sheet.removeSticker(1);
  // sheet.changeMaxStickers(4);

  // sheet.removeSticker(0);

  // // sheetDuplicate.render().writeToFile("../testingsheetDuplicate.png");
  // std::cout << alma.width() << std::endl;
  // std::cout << sheet.width() << std::endl;
  // // REQUIRE( sheet.render() == alma );
  return 0;
}
