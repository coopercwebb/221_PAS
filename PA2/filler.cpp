// TODO: Remove
#include "filler.h"
#include <set>

/**
 * @file        filler.cpp
 * @description Implementation of functions in the filler namespace.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

/**
 * Performs a flood fill using breadth first search.
 *
 * @param config FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillBFS(FillerConfig &config) {
    // complete your implementation below
    // You should replace the following line with a
    // correct call to fill.

    return Fill<Queue>(config);
}

/**
 * Performs a flood fill using depth first search.
 *
 * @param  config - FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillDFS(FillerConfig &config) {
    // complete your implementation below
    // You should replace the following line with a
    // correct call to fill.

    return Fill<Stack>(config);
}

/**
 * Run a flood fill on an image starting at the seed point
 *
 * @param config FillerConfig struct with data for flood fill of image
 * @return animation object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure>
animation filler::Fill(FillerConfig &config) {
    /**
     * You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is removed
     * from the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.1.  add its unprocessed neighbors (up/down/left/right) whose color values are
     *              within (or equal to) tolerance distance from the seed point,
     *              to the ordering structure, and
     *              mark them as processed.
     *        1.2.  if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels (up/down/left/right) in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        2.1. northern neighbour (up)
     *        2.2. eastern neighbour (right)
     *        2.3. southern neighbour (down)
     *        2.4. western neighbour (left)
     *
     *        If you process the neighbours in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     *
     */

    int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
    animation anim;
    OrderingStructure<PixelPoint> os;

    // complete your implementation below
    // HINT: you will likely want to declare some kind of structure to track
    //       which pixels have already been visited
    set<pair<int, int>> visited_coords;
    visited_coords.insert(MakePixelCoordPair(config.seedpoint));

    os.Add(config.seedpoint);

    while (!os.IsEmpty()) {
        PixelPoint removed = os.Remove();
        AddNeighbors(config, os, visited_coords, removed);
        RGBAPixel *p = config.img.getPixel(removed.x, removed.y);
        *p = (*(config.picker))(removed);
        framecount++;
        if (framecount == config.frameFreq) {
            anim.addFrame(config.img);
            framecount = 0;
        }
    }

    anim.addFrame(config.img);
    return anim;
}

pair<int, int> filler::MakePixelCoordPair(PixelPoint p) {
    return make_pair(p.x, p.y);
}

void filler::AddNeighbors(FillerConfig &config, OrderingStructure<PixelPoint> &os, set<pair<int, int>> &visited_coords, PixelPoint p) {
    // We only want to add to the os, if the RGBAPixel color distanceTo is within the
    // tolerance
    // Add all visited pixels to visited_coords regardless of threshold outcome

    // Need bounds checking on neighboring pixels, check if it is within the img bounds,
    // not less than 0 for x and y
    // not equal to or greater than the width and height of the img

    // Remember x=0, y=0 equals the top left of the img

    RGBAPixel *cur_pixel;
    int cur_x;
    int cur_y;
    // Check North
    if (visited_coords.find(make_pair(p.x, p.y - 1)) == visited_coords.end() &&
        p.y != 0) {
        cur_x = p.x;
        cur_y = p.y - 1;
        visited_coords.insert(make_pair(cur_x, cur_y));
        cur_pixel = config.img.getPixel(cur_x, cur_y);
        if (cur_pixel->distanceTo(config.seedpoint.color) <= config.tolerance) {
            PixelPoint cur_pixel_point(cur_x, cur_y, *cur_pixel);
            os.Add(cur_pixel_point);
        }
    }
    // Check East
    if (visited_coords.find(make_pair(p.x + 1, p.y)) == visited_coords.end() &&
        p.x + 1 < config.img.width()) {
        cur_x = p.x + 1;
        cur_y = p.y;
        visited_coords.insert(make_pair(cur_x, cur_y));
        cur_pixel = config.img.getPixel(cur_x, cur_y);
        if (cur_pixel->distanceTo(config.seedpoint.color) <= config.tolerance) {
            PixelPoint cur_pixel_point(cur_x, cur_y, *cur_pixel);
            os.Add(cur_pixel_point);
        }
    }
    // Check South
    if (visited_coords.find(make_pair(p.x, p.y + 1)) == visited_coords.end() &&
        p.y + 1 < config.img.height()) {
        cur_x = p.x;
        cur_y = p.y + 1;
        visited_coords.insert(make_pair(cur_x, cur_y));
        cur_pixel = config.img.getPixel(cur_x, cur_y);
        if (cur_pixel->distanceTo(config.seedpoint.color) <= config.tolerance) {
            PixelPoint cur_pixel_point(cur_x, cur_y, *cur_pixel);
            os.Add(cur_pixel_point);
        }
    }
    // Check West
    if (visited_coords.find(make_pair(p.x - 1, p.y)) == visited_coords.end() &&
        p.x != 0) {
        cur_x = p.x - 1;
        cur_y = p.y;
        visited_coords.insert(make_pair(cur_x, cur_y));
        cur_pixel = config.img.getPixel(cur_x, cur_y);
        if (cur_pixel->distanceTo(config.seedpoint.color) <= config.tolerance) {
            PixelPoint cur_pixel_point(cur_x, cur_y, *cur_pixel);
            os.Add(cur_pixel_point);
        }
    }
}
