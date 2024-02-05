/**
 *  @file        imglist.cpp
 *  @description Contains partial implementation of ImgList class
 *               for CPSC 221 PA1
 *               Function bodies to be completed by student
 *
 *  THIS FILE WILL BE SUBMITTED
 */

#include "imglist.h"

#include <math.h> // provides fmax, fmin, and fabs functions

// TODO: Determine if map is allowed as library
#include <map>

/*********************
 * CONSTRUCTORS, ETC. *
 *********************/

/**
 * Default constructor. Makes an empty list
 */
ImgList::ImgList() {
    // set appropriate values for all member attributes here
    northwest = NULL;
    southeast = NULL;
}

/**
 * Creates a list from image data
 * @pre img has dimensions of at least 1x1
 */
ImgList::ImgList(PNG &img) {

    ImgNode *curNode;

    // Alternative constructor if PNG height 1
    if (img.height() < 2) {
        ImgNode *tmpNode = new ImgNode();
        tmpNode->colour = *img.getPixel(0, 0);
        northwest = tmpNode;

        for (unsigned int i = 1; i < img.width(); i++) {
            curNode = new ImgNode();
            curNode->colour = *img.getPixel(i, 0);
            curNode->west = tmpNode;
            tmpNode->east = curNode;
            tmpNode = curNode;
        }

        southeast = tmpNode;
        return;
    }

    map<pair<int, int>, ImgNode *> cache;

    unsigned int x = 0;
    unsigned int y;
    bool offByOne = true;
    while (true) {
        (offByOne) ? y = 1 : y = 0;
        while (true) {
            curNode = new ImgNode();
            curNode->colour = *img.getPixel(x, y);
            cache[make_pair(x, y)] = curNode;
            y += 2;
            if (y >= img.height()) {
                break;
            }
        }
        offByOne = !offByOne;
        x++;
        if (x >= img.width()) {
            break;
        }
    }

    x = 0;
    offByOne = false;
    while (true) {
        (offByOne) ? y = 1 : y = 0;
        while (true) {
            curNode = new ImgNode();
            curNode->colour = *img.getPixel(x, y);
            try {
                curNode->south = cache.at(make_pair(x, y + 1));
                curNode->south->north = curNode;
            } catch (const out_of_range &e) {
            }
            try {
                curNode->east = cache.at(make_pair(x + 1, y));
                curNode->east->west = curNode;
            } catch (const out_of_range &e) {
            }
            try {
                curNode->north = cache.at(make_pair(x, y - 1));
                curNode->north->south = curNode;
            } catch (const out_of_range &e) {
            }
            try {
                curNode->west = cache.at(make_pair(x - 1, y));
                curNode->west->east = curNode;
            } catch (const out_of_range &e) {
            }
            cache[make_pair(x, y)] = curNode;

            y += 2;
            if (y >= img.height()) {
                break;
            }
        }
        offByOne = !offByOne;
        x++;
        if (x >= img.width()) {
            break;
        }
    }

    // entry point to the list; the upper-left corner of the image
    northwest = cache.at(make_pair(0, 0));
    // last node in the list; the lower-right corner of the image
    southeast = cache.at(make_pair(img.width() - 1, img.height() - 1));
    // Clear keys and pointers from map
    cache.clear();
}

/************
 * ACCESSORS *
 ************/

/**
 * Returns the horizontal dimension of this list (counted in nodes)
 * Note that every row will contain the same number of nodes, whether or not
 *   the list has been carved.
 * We expect your solution to take linear time in the number of nodes in the
 *   x dimension.
 */
unsigned int ImgList::GetDimensionX() const {
    if (northwest == nullptr) {
        return 0;
    }

    int lengthX = 1;
    ImgNode *curNode = northwest;
    while (curNode->east != nullptr) {
        lengthX++;
        curNode = curNode->east;
    }
    return lengthX;
}

/**
 * Returns the vertical dimension of the list (counted in nodes)
 * It is useful to know/assume that the grid will never have nodes removed
 *   from the first or last columns. The returned value will thus correspond
 *   to the height of the PNG image from which this list was constructed.
 * We expect your solution to take linear time in the number of nodes in the
 *   y dimension.
 */
unsigned int ImgList::GetDimensionY() const {
    if (northwest == nullptr) {
        return 0;
    }

    int lengthY = 1;
    ImgNode *curNode = northwest;
    while (curNode->south != nullptr) {
        lengthY++;
        curNode = curNode->south;
    }
    return lengthY;
}

/**
 * Returns the horizontal dimension of the list (counted in original pixels, pre-carving)
 * The returned value will thus correspond to the width of the PNG image from
 *   which this list was constructed.
 * We expect your solution to take linear time in the number of nodes in the
 *   x dimension.
 */
unsigned int ImgList::GetDimensionFullX() const {
    if (northwest == nullptr) {
        return 0;
    }

    int lengthX = 1;
    ImgNode *curNode = northwest;
    while (curNode->east != nullptr) {
        lengthX += curNode->skipright + 1;
        curNode = curNode->east;
    }
    return lengthX;
}

/**
 * Returns a pointer to the node which best satisfies the specified selection criteria.
 * The first and last nodes in the row cannot be returned.
 * @pre rowstart points to a row with at least 3 physical nodes
 * @pre selectionmode is an integer in the range [0,1]
 * @param rowstart - pointer to the first node in a row
 * @param selectionmode - criterion used for choosing the node to return
 *          0: minimum "brightness" across row, not including extreme left or right nodes
 *          1: node with minimum total of "colour difference" with its left neighbour and with its right neighbour.
 *        In the (likely) case of multiple candidates that best match the criterion,
 *        the left-most node satisfying the criterion (excluding the row's starting node)
 *        will be returned.
 * A note about "brightness" and "colour difference":
 * For PA1, "brightness" will be the sum over the RGB colour channels, multiplied by alpha.
 * "colour difference" between two pixels can be determined
 * using the "distanceTo" function found in RGBAPixel.h.
 */
ImgNode *ImgList::SelectNode(ImgNode *rowstart, int selectionmode) {
    // skip first node
    ImgNode *curNode = rowstart->east;
    ImgNode *selectedNode = rowstart->east;
    switch (selectionmode) {
    case 0: {
        double lowestBrightness = 756.0;
        while (curNode->east != nullptr) {
            // while in the loop you will always have access to left and right nodes
            double curBrightness = ((curNode->colour.r + curNode->colour.g +
                                     curNode->colour.b) *
                                    curNode->colour.a);
            // < ensures that the left most node is removed
            if (curBrightness < lowestBrightness) {
                lowestBrightness = curBrightness;
                selectedNode = curNode;
            }
            curNode = curNode->east;
        }
        break;
    }
    case 1: {
        double bestDifference = 756.0;
        while (curNode->east != nullptr) {
            // while in the loop you will always have access to left and right nodes
            double curDifference = (curNode->colour.distanceTo(curNode->west->colour)) +
                                   (curNode->colour.distanceTo(curNode->east->colour));
            // < ensures that the left most node is removed
            if (curDifference < bestDifference) {
                bestDifference = curDifference;
                selectedNode = curNode;
            }
            curNode = curNode->east;
        }
        break;
    }
    }

    return selectedNode;
}

/**
 * Renders this list's pixel data to a PNG, with or without filling gaps caused by carving.
 * @pre fillmode is an integer in the range of [0,2]
 * @param fillgaps - whether or not to fill gaps caused by carving
 *          false: render one pixel per node, ignores fillmode
 *          true: render the full width of the original image,
 *                filling in missing nodes using fillmode
 * @param fillmode - specifies how to fill gaps
 *          0: solid, uses the same colour as the node at the left of the gap
 *          1: solid, using the averaged values (all channels) of the nodes at the left and right of the gap
 *          2: linear gradient between the colour (all channels) of the nodes at the left and right of the gap
 *             e.g. a gap of width 1 will be coloured with 1/2 of the difference between the left and right nodes
 *             a gap of width 2 will be coloured with 1/3 and 2/3 of the difference
 *             a gap of width 3 will be coloured with 1/4, 2/4, 3/4 of the difference, etc.
 *             Like fillmode 1, use the smaller difference interval for hue,
 *             and the smaller-valued average for diametric hues
 */
PNG ImgList::Render(bool fillgaps, int fillmode) const {
    PNG outpng(GetDimensionX(), GetDimensionY());
    ImgNode *curRow = northwest;
    ImgNode *curNode;

    if (fillgaps) {
        outpng.resize(GetDimensionFullX(), GetDimensionY());
        int y = 0;
        while (curRow != nullptr) {
            curNode = curRow;
            int x = 0;
            while (curNode != nullptr) {
                RGBAPixel *pixelToAlter = (outpng).getPixel(x, y);
                *pixelToAlter = curNode->colour;
                for (unsigned int i = 1; i <= curNode->skipright; i++) {
                    switch (fillmode) {
                    case 0: {
                        pixelToAlter = (outpng).getPixel(x + i, y);
                        *pixelToAlter = curNode->colour;
                        break;
                    }
                    case 1: {
                        pixelToAlter = (outpng).getPixel(x + i, y);
                        pixelToAlter->r = (curNode->colour.r + curNode->east->colour.r) / 2;
                        pixelToAlter->g = (curNode->colour.g + curNode->east->colour.g) / 2;
                        pixelToAlter->b = (curNode->colour.b + curNode->east->colour.b) / 2;
                        pixelToAlter->a = (curNode->colour.a + curNode->east->colour.a) / 2;
                        break;
                    }
                    case 2: {
                        pixelToAlter = (outpng).getPixel(x + i, y);

                        if (curNode->colour.r <= curNode->east->colour.r) {
                            pixelToAlter->r = curNode->colour.r + ((curNode->east->colour.r - curNode->colour.r) * i / (curNode->skipright + 1));
                        } else {
                            pixelToAlter->r = curNode->east->colour.r + ((curNode->colour.r - curNode->east->colour.r) * (curNode->skipright - i + 1) / (curNode->skipright + 1));
                        }
                        if (curNode->colour.g <= curNode->east->colour.g) {
                            pixelToAlter->g = curNode->colour.g + ((curNode->east->colour.g - curNode->colour.g) * i / (curNode->skipright + 1));
                        } else {
                            pixelToAlter->g = curNode->east->colour.g + ((curNode->colour.g - curNode->east->colour.g) * (curNode->skipright - i + 1) / (curNode->skipright + 1));
                        }
                        if (curNode->colour.b <= curNode->east->colour.b) {
                            pixelToAlter->b = curNode->colour.b + ((curNode->east->colour.b - curNode->colour.b) * i / (curNode->skipright + 1));
                        } else {
                            pixelToAlter->b = curNode->east->colour.b + ((curNode->colour.b - curNode->east->colour.b) * (curNode->skipright - i + 1) / (curNode->skipright + 1));
                        }
                        if (curNode->colour.a <= curNode->east->colour.a) {
                            pixelToAlter->a = curNode->colour.a + ((curNode->east->colour.a - curNode->colour.a) * i / (curNode->skipright + 1));
                        } else {
                            pixelToAlter->a = curNode->east->colour.a + ((curNode->colour.a - curNode->east->colour.a) * (curNode->skipright - i + 1) / (curNode->skipright + 1));
                        }
                    }
                    }
                }
                x += curNode->skipright + 1;
                curNode = curNode->east;
            }
            curRow = curRow->south;
            y++;
        }
    } else {
        int y = 0;
        while (curRow != nullptr) {
            curNode = curRow;
            int x = 0;
            while (curNode != nullptr) {
                RGBAPixel *pixelToAlter = (outpng).getPixel(x, y);
                *pixelToAlter = curNode->colour;
                x++;
                curNode = curNode->east;
            }
            curRow = curRow->south;
            y++;
        }
    }

    return outpng;
}

/************
 * MODIFIERS *
 ************/

/**
 * Removes exactly one node from each row in this list, according to specified criteria.
 * The first and last nodes in any row cannot be carved.
 * @pre this list has at least 3 nodes in each row
 * @pre selectionmode is an integer in the range [0,1]
 * @param selectionmode - see the documentation for the SelectNode function.
 * @param this list has had one node removed from each row. Neighbours of the created
 *       gaps are linked appropriately, and their skip values are updated to reflect
 *       the size of the gap.
 */
void ImgList::Carve(int selectionmode) {

    // skip first row, stopping loop when south is null prevents last row from carving
    ImgNode *curNode = northwest;
    while (curNode != nullptr) {
        ImgNode *selectedNode = SelectNode(curNode, selectionmode);

        if (selectedNode->north == nullptr && selectedNode->south == nullptr) {
            // Do nothing
        } else if (selectedNode->north != nullptr && selectedNode->south != nullptr) {
            selectedNode->north->south = selectedNode->south;
            selectedNode->south->north = selectedNode->north;
            selectedNode->south->skipup += (1 + selectedNode->skipup);
            selectedNode->north->skipdown += (1 + selectedNode->skipup);
        } else if (selectedNode->north == nullptr) {
            selectedNode->south->north = NULL;
            selectedNode->south->skipup += (1 + selectedNode->skipup);
        } else {
            selectedNode->north->south = NULL;
            selectedNode->north->skipdown += (1 + selectedNode->skipup);
        }

        selectedNode->west->east = selectedNode->east;
        selectedNode->east->west = selectedNode->west;
        selectedNode->west->skipright += (1 + selectedNode->skipright);
        selectedNode->east->skipleft += (1 + selectedNode->skipleft);

        delete (selectedNode);

        // iterate
        curNode = curNode->south;
    }
    return;
}

// note that a node on the boundary will never be selected for removal
/**
 * Removes "rounds" number of nodes (up to a maximum of node width - 2) from each row,
 * based on specific selection criteria.
 * Note that this should remove one node from every row, repeated "rounds" times,
 * and NOT remove "rounds" nodes from one row before processing the next row.
 * @pre selectionmode is an integer in the range [0,1]
 * @param rounds - number of nodes to remove from each row
 *        If rounds exceeds node width - 2, then remove only node width - 2 nodes from each row.
 *        i.e. Ensure that the final list has at least two nodes in each row.
 * @post this list has had "rounds" nodes removed from each row. Neighbours of the created
 *       gaps are linked appropriately, and their skip values are updated to reflect
 *       the size of the gap.
 */
void ImgList::Carve(unsigned int rounds, int selectionmode) {
    // TODO: HAVE TO ENSURE THAT THE NUMBER OF ROUNDS DOES NOT EXCEED (width - 2)
    unsigned int dimensionX = GetDimensionX();
    if (dimensionX < 2) {
        dimensionX = 2;
    }

    if (rounds > (dimensionX - 2)) {
        rounds = dimensionX - 2;
    }

    for (unsigned int i = 0; i < rounds; i++) {
        Carve(selectionmode);
    }
}

/*
 * Helper function deallocates all heap memory associated with this list,
 * puts this list into an "empty" state. Don't forget to set your member attributes!
 * @post this list has no currently allocated nor leaking heap memory,
 *       member attributes have values consistent with an empty list.
 */
void ImgList::Clear() {
    ImgNode *curRow = northwest;
    ImgNode *curNode;
    ImgNode *tmpNode;

    while (curRow != nullptr) {
        curNode = curRow;
        curRow = curRow->south;
        while (curNode != nullptr) {
            tmpNode = curNode;
            curNode = curNode->east;
            delete (tmpNode);
        }
    }
    northwest = NULL;
    southeast = NULL;
}

/**
 * Helper function copies the contents of otherlist and sets this list's attributes appropriately
 * @pre this list is empty
 * @param otherlist - list whose contents will be copied
 * @post this list has contents copied from by physically separate from otherlist
 */
void ImgList::Copy(const ImgList &otherlist) {
    Clear();

    int copyWidth = otherlist.GetDimensionX();
    int copyHeight = otherlist.GetDimensionY();
    ImgNode *curCol = otherlist.northwest;
    ImgNode *tmpNode;
    ImgNode *newNode;

    // Alternative copy if otherList is height 1
    if (copyHeight < 2) {
        newNode = new ImgNode(*curCol);
        northwest = newNode;
        tmpNode = newNode;
        curCol = curCol->east;

        while (curCol != nullptr) {
            newNode = new ImgNode(*curCol);
            newNode->west = tmpNode;
            tmpNode->east = newNode;
            tmpNode = tmpNode->east;
            curCol = curCol->east;
        }

        southeast = tmpNode;
        return;
    }

    map<pair<int, int>, ImgNode *> cache2;
    ImgNode *curNode = curCol;

    int x = 0;
    int y;
    bool offByOne = true;
    while (true) {
        if (offByOne) {
            y = copyHeight - 2;
            curNode = curCol->south;
        } else {
            y = copyHeight - 1;
            curNode = curCol;
        }
        while (true) {
            tmpNode = new ImgNode(*curNode);
            cache2[make_pair(x, y)] = tmpNode;
            y -= 2;
            if (curNode->south == nullptr) {
                break;
            } else if (curNode->south->south == nullptr) {
                break;
            }
            curNode = curNode->south->south;
        }
        x++;
        if (curCol->east == nullptr) {
            break;
        }
        offByOne = !offByOne;
        curCol = curCol->east;
    }

    x = 0;
    curCol = otherlist.northwest;
    offByOne = false;
    while (true) {
        if (offByOne) {
            y = copyHeight - 2;
            curNode = curCol->south;
        } else {
            y = copyHeight - 1;
            curNode = curCol;
        }
        while (true) {
            tmpNode = new ImgNode(*curNode);
            try {
                tmpNode->south = cache2.at(make_pair(x, y - 1));
                tmpNode->south->north = tmpNode;
            } catch (const out_of_range &e) {
            }
            try {
                tmpNode->east = cache2.at(make_pair(x + 1, y));
                tmpNode->east->west = tmpNode;
            } catch (const out_of_range &e) {
            }
            try {
                tmpNode->north = cache2.at(make_pair(x, y + 1));
                tmpNode->north->south = tmpNode;
            } catch (const out_of_range &e) {
            }
            try {
                tmpNode->west = cache2.at(make_pair(x - 1, y));
                tmpNode->west->east = tmpNode;
            } catch (const out_of_range &e) {
            }
            cache2[make_pair(x, y)] = tmpNode;
            y -= 2;
            if (curNode->south == nullptr) {
                break;
            } else if (curNode->south->south == nullptr) {
                break;
            }
            curNode = curNode->south->south;
        }
        x++;
        if (curCol->east == nullptr) {
            break;
        }
        offByOne = !offByOne;
        curCol = curCol->east;
    }

    // entry point to the list; the upper-left corner of the image
    northwest = cache2.at(make_pair(0, copyHeight - 1));
    // last node in the list; the lower-right corner of the image
    southeast = cache2.at(make_pair(copyWidth - 1, 0));
    // Clear keys and pointers from map
    cache2.clear();
}

/*************************************************************************************************
 * IF YOU DEFINED YOUR OWN PRIVATE FUNCTIONS IN imglist-private.h, YOU MAY ADD YOUR IMPLEMENTATIONS BELOW *
 *************************************************************************************************/
