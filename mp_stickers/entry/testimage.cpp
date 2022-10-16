#include "Image.h"

#include <iostream>

int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.lighten(0.5);
  alma.writeToFile("../lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.saturate(0.8);
  alma.writeToFile("../saturate.png");

  std::cout << "Using Image::grayscale to create `saturate.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.grayscale();
  alma.writeToFile("../grayscale.png");

  std::cout << "Using Image::rotateColor to create `saturate.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.rotateColor(180);
  alma.writeToFile("../rotateColor.png");

  std::cout << "Using Image::illinify to create `saturate.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.illinify();
  alma.writeToFile("../illinify.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.scale(0.5);
  alma.writeToFile("../scale2x.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.scale(100, 100);
  alma.writeToFile("../scale100x100.png");

  return 0;
}
