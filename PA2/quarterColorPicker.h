/**
 * @file quarterColorPicker.h
 * Definition of a quarter color picker.
 *
 */
#ifndef _QUARTERCOLORPICKER_H_
#define _QUARTERCOLORPICKER_H_

#include "colorPicker.h"

 /**
  * QuarterColorPicker: a functor that determines the color that should be
  * used given an x and y coordinate using a quartered image pattern (the original image
  * is scaled down and tiled over itself). You can create
  * private helper functions inside this class, as well as local storage, if
  * necessary. Remember to overload a destructor if you need to.
  */
class QuarterColorPicker : public ColorPicker
{
public:
    /**
     * Constructs a new QuarterColorPicker.
     *
     * @param inputimg The original image to be filled
     * @param b_amount The amount to increase each R/G/B channel after scaling
     * @pre inputimg is the same image which will be painted
     * @pre inputimg width and height are both even
     */
    QuarterColorPicker(PNG& inputimg, unsigned char b_amount);

    /**
     * Picks the color for pixel (x, y).
     *
     * Using the private reference image, scale each dimension by half
     * and tile the smaller image in a 2 x 2 grid over the original dimensions
     * of the image, and return the pixel at the appropriate coordinate from
     * the tiled image, brightened on each R/G/B channel by the required amount.
     * 
     * The value of each pixel in the scaled image will be a bilinear interpolation
     * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
     * processed individually. Interpolate over the x-axis before the y-axis.
	 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
     * as the final step.
     * 
     * @pre referenceimg width and height are both even
     */
    virtual RGBAPixel operator()(PixelPoint p);

private:

    PNG referenceimg;            // original image used in the flood fill algorithm
    unsigned char brightamount; // amount to increase each R/G/B channel

    /**
     * @todo Define any additional private member variables or helper
     *	functions in quarterColorPicker_private.h as you see fit.
     */
    #include "quarterColorPicker_private.h"
};

#endif
