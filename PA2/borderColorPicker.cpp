/**
 * @file borderColorPicker.cpp
 * @description Implements the BorderColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */
#include "borderColorPicker.h"
#include <cstdlib>

/**
 * Constructs a new BorderColorPicker.
 *
 * @param width        Number of pixels to color around border.
 * @param inputimage   Image for referencing original image colors.
 * @param bcolor       Color to be used for painting the fill border.
 * @param tol          Tolerance used to determine the border of the fill.
 */
BorderColorPicker::BorderColorPicker(unsigned int width, PNG &inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol) {
    // Complete your implementation below
    borderwidth = width;
    img = inputimage;
    seedcolor = scolor;
    bordercolor = bcolor;
    tolerance = tol;
}

/**
 * Picks the color for pixel at point. If the x or y coordinate is
 * at or within an Euclidean radius of borderwidth pixels from the border of
 * the fill region, it will be colored with the required border color.
 * Otherwise, its color will not be changed.
 *
 * @param p   The point for which you're picking a color.
 * @return    The color chosen for (p).
 */
RGBAPixel BorderColorPicker::operator()(PixelPoint p) {
    // Replace the line below with your implementation

    for (int x = -borderwidth; x <= (int)borderwidth; x++) {
        for (int y = -borderwidth; y <= (int)borderwidth; y++) {
            unsigned int squared_distance = x * x + y * y;
            if (squared_distance <= borderwidth * borderwidth) {
                int true_x = p.x + x;
                int true_y = p.y + y;
                // bounds checking before continuing
                if (true_x < 0 || true_y < 0 || true_x >= (int)img.width() || true_y >= (int)img.height()) {
                    return bordercolor;
                }
                RGBAPixel *curPixel = img.getPixel(true_x, true_y);
                if (curPixel->distanceTo(seedcolor) > tolerance) {
                    return bordercolor;
                }
            }
        }
    }
    return p.color;
}

/**
 * Add your private BorderColorPicker function implementations below
 */
