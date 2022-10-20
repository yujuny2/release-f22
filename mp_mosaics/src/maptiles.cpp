/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    // get points from TileImage
    vector<Point<3>> tile_points;
    map<Point<3>, TileImage*> map;
    
    for (unsigned i = 0; i < theTiles.size(); i++) {
        LUVAPixel tile_pixel = theTiles[i].getAverageColor();
        Point<3> tile_point = convertToXYZ(tile_pixel);
        tile_points.push_back(tile_point);
        map[tile_point] = &theTiles[i];
    }
    // create KDTrees
    KDTree<3> tiles(tile_points);

    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    for (int row = 0; row < theSource.getRows(); row++) {
        for (int col = 0; col < theSource.getColumns(); col++) {
            LUVAPixel pixel = theSource.getRegionColor(row, col);
            Point<3> pixel_point = convertToXYZ(pixel);
            Point<3> neighbor = tiles.findNearestNeighbor(pixel_point);
            canvas->setTile(row, col, map[neighbor]);
        }
    }
    return canvas;
}

