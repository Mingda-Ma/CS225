/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> & theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* res=new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    //first intialize the list of theTiles
    vector<Point<3>>tilepixel;
    map<Point<3>, int>idxmap;
    for (size_t i=0;i< theTiles.size();i++){
      HSLAPixel temp=theTiles[i].getAverageColor();
      double arr[3];
      arr[0]=temp.h/360.0;
      arr[1]=temp.s;
      arr[2]=temp.l;
      Point<3> a(arr);
      tilepixel.push_back(a);
    }
    //initialize the map of tilepixel and tilepixel
    for (size_t i =0; i< theTiles.size();i++){
      idxmap[tilepixel[i]]=i;
    }
    KDTree<3> tiletree(tilepixel);
    //use NNS to find the tile to set
    for (int row=0;row<theSource.getRows();row++){
      for(int col=0;col<theSource.getColumns();col++){
        HSLAPixel temp=theSource.getRegionColor(row,col);
        double arr[3];
        arr[0]=temp.h/360.0;
        arr[1]=temp.s;
        arr[2]=temp.l;
        Point<3> tar(arr);
        Point<3> key=tiletree.findNearestNeighbor(tar);
        int idx=idxmap[key];
        res->setTile(row,col,&theTiles[idx]);
      }
    }
    return res;
}
