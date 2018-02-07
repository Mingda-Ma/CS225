#include "StickerSheet.h"
#include <cmath>
StickerSheet::StickerSheet(Image const& c, unsigned max){
	stickers.resize(max);
	canvas = c;
	coord.resize(max);
	for (unsigned i=0;i<max;i++){
		stickers[i]=NULL;
		coord[i]=Coord(-1,-1);//overflow
	}
}
StickerSheet::~StickerSheet(){
//nothing
}
StickerSheet::StickerSheet(StickerSheet const& other){
	// for (unsigned i=0;i<other.stickers.size();i++){
	// 	stickers.push_back(other.stickers[i]);
	// 	coord.push_back(other.coord[i]);
	// }
	stickers = other.stickers;
	coord = other.coord;
	canvas = other.canvas;
}
// StickerSheet& StickerSheet::operator=(StickerSheet const& other)const{
// 	delete this;
// 	sticekrs(other.stickers);
// 	canvas(other.canvas);
// 	coord(other.max);
// 	return *this;	
// }
void StickerSheet::changeMaxSticker(unsigned max){
	if (max < stickers.size()){
		for (unsigned i=0; i< (stickers.size()-max);i++){
			stickers.pop_back();
			coord.pop_back();			
		}
	}
	else if (max > stickers.size()){
		for (unsigned i=0; i< (max-stickers.size());i++){
			stickers.push_back(NULL);
			coord.push_back(Coord(0,0));
			cout << stickers.size() <<endl;
		}
	}
}
int StickerSheet::addSticker(Image& sticker,unsigned x,unsigned y){
	Coord temp(x,y);
	unsigned i;
	for ( i=0;i< stickers.size();i++){
		if (stickers[i] == NULL){
			stickers[i] = &sticker;
			coord[i] = temp;
			return i;
		}
		break;
	}
	return -1;

}
bool StickerSheet::translate(unsigned index,unsigned x,unsigned y){
	Coord temp(x,y);
	if (stickers[index] != NULL && (index <= stickers.size())){
		coord[index] = temp;
		return true;
	}
	else
		return false;
}
void StickerSheet::removeSticker(unsigned index){
	stickers[index] = NULL;
	Coord temp(-1,-1);
	coord[index] = temp;
}
Image* StickerSheet::getSticker(unsigned index)const{
	if (stickers[index] != NULL && (index <= stickers.size()))
		return stickers[index];
	else 
		return NULL;
}
Image StickerSheet::render()const{
	unsigned maxheight = canvas.height();
	unsigned maxwidth = canvas.width();
	Image rv = canvas;
	for (unsigned i=0; i< stickers.size();i++){
		if (stickers[i] != NULL){
			maxwidth = max(coord[i].first + stickers[i]->width(),maxwidth);
			maxheight = max(coord[i].second + stickers[i]->height(),maxheight);
		}
	}
	rv.resize(maxwidth,maxheight);
	for (unsigned index=0;index<stickers.size();index++){
		if (stickers[index] != NULL){
			for (unsigned x=coord[index].first;x<(coord[index].first+stickers[index]->width());x++){
				for(unsigned y=coord[index].second;y<(coord[index].second+stickers[index]->height());y++){
					if (stickers[index]->getPixel(x-coord[index].first,y-coord[index].second).a != 0)
						rv.getPixel(x,y) = stickers[index]->getPixel(x-coord[index].first,y-coord[index].second);
				}
			}
		}
	}
	return rv;
}