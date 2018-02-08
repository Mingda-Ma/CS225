/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
#include "Image.h"
#include <vector>
#include <stdlib.h>
using namespace std;
typedef pair<unsigned, unsigned> Coord;
class StickerSheet: public Image{
private:
	Image canvas;
	vector<Image*> stickers;
	vector<Coord> coord;
public:
	StickerSheet(Image const& c, unsigned max);
	~StickerSheet();
	StickerSheet(StickerSheet const& other);
	StickerSheet& operator=(StickerSheet const& other);
	void changeMaxStickers(unsigned max);
	int addSticker(Image& sticker,unsigned x,unsigned y);
	bool translate(unsigned index,unsigned x,unsigned y);
	void removeSticker(unsigned index);
	Image* getSticker(unsigned index)const;
	Image render()const;
};

#endif
 