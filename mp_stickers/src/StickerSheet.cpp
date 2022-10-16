#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    max_stickers_ = max;
    sheet_ = new Image();
    sheet_->resize(picture.width(), picture.height());
    for (unsigned x = 0; x < picture.width(); x++) {
        for (unsigned y = 0; y < picture.height(); y++) {
            sheet_->getPixel(x, y) = picture.getPixel(x, y);
        }
    }
}

StickerSheet::~StickerSheet() {
    delete sheet_;
}

StickerSheet::StickerSheet(const StickerSheet& other) {
    max_stickers_ = other.max_stickers_;
    unsigned v_size = other.stickers_.size();
    for (unsigned i = 0; i < v_size; i++) {
        stickers_.push_back(other.stickers_.at(i));
        x_coordinates_.push_back(other.x_coordinates_.at(i));
        y_coordinates_.push_back(other.y_coordinates_.at(i));
    }
    sheet_ = new Image();
    sheet_->resize(other.sheet_->width(), other.sheet_->height());
    for (unsigned x = 0; x < other.sheet_->width(); x++) {
        for (unsigned y = 0; y < other.sheet_->height(); y++) {
            sheet_->getPixel(x, y) = other.sheet_->getPixel(x, y);
        }
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    if (this != &other) {
        max_stickers_ = other.max_stickers_;

        if (stickers_.size() != 0) {
            // stickers_.erase(stickers_.begin(), stickers_.end());
            // x_coordinates_.erase(x_coordinates_.begin(), x_coordinates_.end());
            // y_coordinates_.erase(y_coordinates_.begin(), y_coordinates_.end());
            stickers_.clear();
            x_coordinates_.clear();
            y_coordinates_.clear();
        }

        unsigned stickers_size = other.stickers_.size();
        for (unsigned i = 0; i < stickers_size; i++) {
            stickers_.push_back(other.stickers_.at(i));
            x_coordinates_.push_back(other.x_coordinates_.at(i));
            y_coordinates_.push_back(other.y_coordinates_.at(i));
        }

        if (sheet_ != NULL) {
            delete sheet_;
        }

        sheet_ = new Image();
        sheet_->resize(other.sheet_->width(), other.sheet_->height());
        for (unsigned x = 0; x < other.sheet_->width(); x++) {
            for (unsigned y = 0; y < other.sheet_->height(); y++) {
                sheet_->getPixel(x, y) = other.sheet_->getPixel(x, y);
            }
        }
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    unsigned v_size = stickers_.size();
    if (max < max_stickers_ && v_size > max) {
        stickers_.erase(stickers_.begin() + max, stickers_.end());
        x_coordinates_.erase(x_coordinates_.begin() + max, x_coordinates_.end());
        y_coordinates_.erase(y_coordinates_.begin() + max, y_coordinates_.end());
    }
    // resize is not working
    // stickers_.resize(max);
    // x_coordinates_.resize(max);
    // y_coordinates_.resize(max);
    max_stickers_ = max;
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
    if (stickers_.size() + 1 > max_stickers_) {
        return -1;
    }
    stickers_.push_back(&sticker);
    x_coordinates_.push_back(x);
    y_coordinates_.push_back(y);
    return 0;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < 0 || index >= stickers_.size()) {
        return false;
    }
    x_coordinates_[index] = x;
    y_coordinates_[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    unsigned v_size = stickers_.size();
    if (index >= 0 && index < v_size) {
        stickers_.erase(stickers_.begin() + index);
        x_coordinates_.erase(x_coordinates_.begin() + index);
        y_coordinates_.erase(y_coordinates_.begin() + index);
    }
}

Image* StickerSheet::getSticker (unsigned index) {
    if (index >= stickers_.size() || index < 0) {
        return NULL;
    }
    return stickers_.at(index);
}

Image StickerSheet::render() const {
    unsigned v_size = stickers_.size();
    for (unsigned k = 0; k < v_size; k++) {

        unsigned x = x_coordinates_[k];
        unsigned y = y_coordinates_[k];
        Image* sticker = stickers_[k];
        unsigned width = sticker->width();
        unsigned height = sticker->height();

        if (x + width > sheet_->width()) {
            sheet_->resize(x + width, sheet_->height());
        }
        if (y + height > sheet_->height()) {
            sheet_->resize(sheet_->width(), y + height);
        }
        for (unsigned i = 0; i < width; i++) {
            for (unsigned j = 0; j < height; j++) {
                if (sticker->getPixel(i, j).a != 0) {
                    sheet_->getPixel(x + i, y + j) = sticker->getPixel(i, j);
                }
            }
        }
    }
    return *sheet_;
}

unsigned StickerSheet::width() {
    return sheet_->width();
}