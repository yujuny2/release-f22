#include "Image.h"

Image::Image() {};

void Image::lighten() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double inc_l = getPixel(x, y).l + 0.1;
            if (inc_l > 1.0) {
                getPixel(x,y).l = 1.0;
            } else {
                getPixel(x,y).l = inc_l;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double inc_l = getPixel(x, y).l + amount;
            if (inc_l > 1.0) {
                getPixel(x,y).l = 1.0;
            } else {
                getPixel(x,y).l = inc_l;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double inc_l = getPixel(x, y).l - 0.1;
            if (inc_l < 1.0) {
                getPixel(x,y).l = 0.0;
            } else {
                getPixel(x,y).l = inc_l;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double inc_l = getPixel(x, y).l - amount;
            if (inc_l < 0.0) {
                getPixel(x,y).l = 0.0;
            } else {
                getPixel(x,y).l = inc_l;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double inc_s = getPixel(x, y).s + 0.1;
            if (inc_s > 1.0) {
                getPixel(x,y).s = 1.0;
            } else {
                getPixel(x,y).s = inc_s;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double inc_s = getPixel(x, y).s + amount;
            if (inc_s > 1.0) {
                getPixel(x,y).s = 1.0;
            } else {
                getPixel(x,y).s = inc_s;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double inc_s = getPixel(x, y).s - 0.1;
            if (inc_s > 1.0) {
                getPixel(x,y).s = 1.0;
            } else {
                getPixel(x,y).s = inc_s;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double inc_s = getPixel(x, y).s + amount;
            if (inc_s > 1.0) {
                getPixel(x,y).s = 1.0;
            } else {
                getPixel(x,y).s = inc_s;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            getPixel(x,y).s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double rotated = getPixel(x, y).h + degrees;
            if (rotated > 360.0) {
                getPixel(x,y).h = rotated - 360.0;
            } else if (rotated < 0) {
                getPixel(x,y).h = rotated + 360.0;
            } else {
                getPixel(x,y).h = rotated;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            double orange_diff = std::abs(getPixel(x, y).h - 11);
            double blue_diff = std::abs(getPixel(x, y).h - 216);
            if (orange_diff < blue_diff) {
                getPixel(x,y).h = 11;
            } else {
                getPixel(x,y).h = 216;
            }
        }
    }
}

void Image::scale(double factor) {
    PNG copyImage(width(), height());
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            copyImage.getPixel(x,y) = getPixel(x,y);
        }
    }
    resize(factor*width(), factor*height());
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            getPixel(x,y) = copyImage.getPixel(x/factor, y/factor);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double factor = ((double)w / width()) > ((double)h / height()) ? ((double)h / height()) : ((double)w / width());
    PNG copyImage(width(), height());
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            copyImage.getPixel(x,y) = getPixel(x,y);
        }
    }
    resize(factor*width(), factor*height());
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            getPixel(x,y) = copyImage.getPixel(x/factor, y/factor);
        }
    }
}

