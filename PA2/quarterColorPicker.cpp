/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG &inputimg, unsigned char b_amount) {
    // Complete your implementation below
    referenceimg = inputimg;
    brightamount = b_amount;
}

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
RGBAPixel QuarterColorPicker::operator()(PixelPoint p) {
    // Replace the line below with your implementation
    int true_x;
    int true_y;
    if (p.x < referenceimg.width() / 2 && p.y < referenceimg.height() / 2) {
        // top left
        true_x = p.x * 2;
        true_y = p.y * 2;
    } else if (p.x >= referenceimg.width() / 2 && p.y < referenceimg.height() / 2) {
        // top right
        true_x = (p.x - (referenceimg.width() / 2)) * 2;
        true_y = p.y * 2;
    } else if (p.x < referenceimg.width() / 2 && p.y >= referenceimg.height() / 2) {
        // bottom left
        true_x = p.x * 2;
        true_y = (p.y - (referenceimg.height() / 2)) * 2;
    } else {
        // bottom right
        true_x = (p.x - (referenceimg.width() / 2)) * 2;
        true_y = (p.y - (referenceimg.height() / 2)) * 2;
    }

    RGBAPixel *p1 = referenceimg.getPixel(true_x, true_y);
    RGBAPixel *p2 = referenceimg.getPixel(true_x + 1, true_y);
    RGBAPixel *p3 = referenceimg.getPixel(true_x, true_y + 1);
    RGBAPixel *p4 = referenceimg.getPixel(true_x + 1, true_y + 1);
    RGBAPixel resPix;

    resPix.r = static_cast<unsigned char>(((p1->r + p2->r) / 2 + (p3->r + p4->r) / 2) / 2);
    resPix.g = static_cast<unsigned char>(((p1->g + p2->g) / 2 + (p3->g + p4->g) / 2) / 2);
    resPix.b = static_cast<unsigned char>(((p1->b + p2->b) / 2 + (p3->b + p4->b) / 2) / 2);
    resPix.a = (((p1->a + p2->a) / 2 + (p3->a + p4->a) / 2) / 2);

    resPix.r = static_cast<unsigned char>(min((resPix.r) + brightamount, 255));
    resPix.g = static_cast<unsigned char>(min((resPix.g) + brightamount, 255));
    resPix.b = static_cast<unsigned char>(min((resPix.b) + brightamount, 255));

    return resPix;
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
