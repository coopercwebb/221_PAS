/*
*  @file        pixelpoint.h
*  @description Defines a PixelPoint class, which consists of a (x,y) image coordinate,
*               along with a RGBAPixel color.
* 
*               *************************************************************
*               You should ***NOT*** modify this file, nor its implementation
*               *************************************************************
*/

#ifndef _PIXELPOINT_H_
#define _PIXELPOINT_H_

#include "cs221util/RGBAPixel.h"

using namespace cs221util;
using namespace std;

struct PixelPoint {

	PixelPoint(unsigned int rx = 0, unsigned int ry = 0, RGBAPixel rcolor = RGBAPixel(0, 0, 1)) : x(rx), y(ry), color(rcolor) {}

	unsigned int x;  // image x coordinate of this point
	unsigned int y;  // image y coordinate of this point
	RGBAPixel color; // color value of this point

	//PixelPoint& operator=(const PixelPoint& rhs) {
	//    if (this != &rhs) {
	//        x = rhs.x;
	//        y = rhs.y;
	//        color = rhs.color;
	//    }
	//    return *this;
	//}

	bool operator==(const PixelPoint& rhs) const {
		return (x == rhs.x && y == rhs.y && color == rhs.color);
	}
  
	bool operator!=(const PixelPoint& rhs) const {
		return !(*this == rhs);
	}
};


#endif