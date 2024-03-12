/**
 * @file borderColorPicker.h
 * Definition of a border color picker.
 *
 */
#ifndef _BORDERCOLORPICKER_H_
#define _BORDERCOLORPICKER_H_

#include "colorPicker.h"

/**
 * BorderColorPicker: a functor that determines the color that should be used
 * given a `point`. If the given position is near a border of
 * the fill, then it should be colored with the required color. Otherwise, its color
 * should not change.
 *
 * The following criteria should be used to determine if a position p is near
 * a border: if p is within distance `borderwidth` of any cell that will be outside the
 * fill, then the pixel at position p should be colored using the chosen border color.
 *
 * You will use Euclidian distance to judge proximity. That means if p is at
 * location (x,y), its distance to a point at location (a,b) is
 * squareRoot([(x-a)^2 + (y-b)^2]). Note that you should not ever have to
 * compute the square root to solve this problem.
 *
 **/
class BorderColorPicker : public ColorPicker
{
  public:
    /**
     * Constructs a new BorderColorPicker.
     *
     * @param width        Number of pixels to color around border.
     * @param inputimage   Image for referencing original image colors.
     * @param scolor       Color of seed point
	 * @param bcolor       Color to be used for painting the fill border.
     * @param tol          Tolerance used to determine the border of the fill.
     */
    BorderColorPicker(unsigned int width, PNG& inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol);

    /**
     * Picks the color for pixel at point. If the x or y coordinate is
     * at or within an Euclidean radius of borderwidth pixels from the border of
     * the fill region, it will be colored with the required border color.
     * Otherwise, its color will not be changed.
     *
     * @param p   The point for which you're picking a color.
     * @return    The color chosen for (p).
     */
    virtual RGBAPixel operator()(PixelPoint p);

  private:
    unsigned int borderwidth; // Number of pixels to use for border
    PNG img;                  // Original image used in flood fill algorithm
    RGBAPixel seedcolor;      // Color of seed point, for checking fill region
	RGBAPixel bordercolor;    // Color used for painting the fill border
    double tolerance;         // Tolerance used in flood fill algorithm

    /**
     * @todo Define any additional private member variables or helper
     *	functions in borderColorPicker_private.h as you see fit.
     */
    #include "borderColorPicker_private.h"
};

#endif
