/**
 * @file stripeColorPicker.h
 * Definition of a stripe color picker.
 *
 */
#ifndef _STRIPECOLORPICKER_H_
#define _STRIPECOLORPICKER_H_

#include "colorPicker.h"

 /**
  * StripeColorPicker: a functor that determines the color that should be
  * used given an x and y coordinate using a diagonal stripe pattern. You can create
  * private helper functions inside this class, as well as local storage, if
  * necessary. Remember to overload a destructor if you need to.
  */
class StripeColorPicker : public ColorPicker
{
public:
    /**
     * Constructs a new StripeColorPicker.
     *
	 * @param stripe_width The width of each alternating stripe, in pixels
	 * @param stripe_color1 Color of the main stripe
	 * @param stripe_color2 Color of the alternate stripe
     */
    StripeColorPicker(unsigned int stripe_width, RGBAPixel stripe_color1, RGBAPixel stripe_color2);

    /**
     * Picks the color for pixel (x, y).
     *
     * The stripe pattern to be drawn consists of alternating stripes each of stripewidth pixels,
	 * in a 45-degree forward slash orientation.
	 * e.g.  / / / / / 
	 *        / / / / /
	 *       / / / / / 
	 *        / / / / /
	 *
	 * For reference, coordinate (0, 0) will be the left-most pixel of a color1 stripe.
     */
    virtual RGBAPixel operator()(PixelPoint p);

private:

    unsigned int stripewidth;
	RGBAPixel color1;
	RGBAPixel color2;

    /**
     * @todo Define any additional private member variables or helper
     *	functions in stripeColorPicker_private.h as you see fit.
     */
    #include "stripeColorPicker_private.h"
};

#endif
