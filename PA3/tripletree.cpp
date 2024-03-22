/**
 * @file        tripletree.cpp
 * @description Student-implemented functions of a ternary tree for CPSC 221 PA3.
 *
 *              THIS FILE WILL BE SUBMITTED FOR GRADING
 */

#include "tripletree.h"

/**
 * Constructor that builds a TripleTree out of the given PNG.
 *
 * The TripleTree represents the subimage from (0,0) to (w-1, h-1) where
 * w-1 and h-1 are the largest valid image coordinates of the original PNG.
 * Every node corresponds to a rectangle of pixels in the original PNG,
 * represented by an (x,y) pair for the upper left corner of the
 * square and two integers for the number of pixels on the width and
 * height dimensions of the rectangular region the node defines.
 *
 * The node's three children correspond to a partition
 * of the node's rectangular region into three approximately equal-size strips.
 *
 * If the rectangular region is taller than it is wide, the region is divided
 * into horizontal strips:
 *  +-------+
 *  |   A   |
 *  |       |
 *  +-------+
 *  |   B   |
 *  |       |    (Split tall)
 *  +-------+
 *  |   C   |
 *  |       |
 *  +-------+
 *
 * If the rectangular region is wider than it is tall, the region is divided
 * into vertical strips:
 *  +---------+---------+---------+
 *  |    A    |    B    |    C    |
 *  |         |         |         |    (Split wide)
 *  +---------+---------+---------+
 *
 * Your regions are not guaranteed to have dimensions exactly divisible by 3.
 * If the dimensions of your rectangular region are 3p x q or q x 3p where 3p
 * represents the length of the long side, then your rectangular regions will
 * each have dimensions p x q (or q x p)
 *
 * If the dimensions are (3p+1) x q, subregion B gets the extra pixel of size
 * while subregions A and C have dimensions p x q.
 *
 * If the dimensions are (3p+2) x q, subregions A and C each get an extra pixel
 * of size, while subregion B has dimensions p x q.
 *
 * If the region to be divided is a square, then apply the Split wide behaviour.
 *
 * Every leaf in the constructed tree corresponds to a pixel in the PNG.
 *
 * @param imIn - the input image used to construct the tree
 */
TripleTree::TripleTree(PNG &imIn) {
    // add your implementation below

    // Should be constructed recursively, assigning avg color on the way up
    pair<unsigned int, unsigned int> entry_pixel = make_pair(0, 0);
    root = BuildNode(imIn, entry_pixel, imIn.width(), imIn.height());
}

/**
 * Render returns a PNG image consisting of the pixels
 * stored in the tree. It may be used on pruned trees. Draws
 * every leaf node's rectangle onto a PNG canvas using the
 * average color stored in the node.
 *
 * You may want a recursive helper function for this.
 */
PNG TripleTree::Render() const {
    // replace the line below with your implementation
    if (root == nullptr) {
        return PNG();
    }
    PNG returnPNG(root->width, root->height);
    RenderHelper(root, returnPNG);

    return returnPNG;
}

void TripleTree::RenderHelper(const Node *n, PNG &render_img) const {
    if (n == nullptr) {
        return;
    }
    if (HasThreeChildren(n)) {
        RenderHelper(n->A, render_img);
        RenderHelper(n->B, render_img);
        RenderHelper(n->C, render_img);
    } else if (HasTwoChildren(n)) {
        RenderHelper(n->A, render_img);
        RenderHelper(n->C, render_img);
    } else {
        // Leaf, must draw rectangle
        for (unsigned int x = n->upperleft.first; x < n->upperleft.first + n->width; x++) {
            for (unsigned int y = n->upperleft.second; y < n->upperleft.second + n->height; y++) {
                RGBAPixel *toEdit = render_img.getPixel(x, y);
                *toEdit = n->avg;
            }
        }
    }
}

bool TripleTree::HasThreeChildren(const Node *n) const {
    return (
        n->A != nullptr &&
        n->B != nullptr &&
        n->C != nullptr);
}

bool TripleTree::HasTwoChildren(const Node *n) const {
    return (
        n->A != nullptr &&
        n->C != nullptr);
}

/*
 * Prune function trims subtrees as high as possible in the tree.
 * A subtree is pruned (cleared) if all of its leaves are within
 * tol of the average color stored in the root of the subtree.
 * Pruning criteria should be evaluated on the original tree, not
 * on a pruned subtree. (we only expect that trees would be pruned once.)
 *
 * You may want a recursive helper function for this.
 *
 * @param tol - maximum allowable RGBA color distance to qualify for pruning
 */
void TripleTree::Prune(double tol) {
    // add your implementation below
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be mirrored horizontally (flipped over a vertical axis).
 * This may be called on pruned trees and/or previously flipped/rotated trees.
 *
 * You may want a recursive helper function for this.
 */
void TripleTree::FlipHorizontal() {
    // add your implementation below
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees counter-clockwise.
 * This may be called on pruned trees and/or previously flipped/rotated trees.
 *
 * You may want a recursive helper function for this.
 */
void TripleTree::RotateCCW() {
    // add your implementation below
}

/*
 * Returns the number of leaf nodes in the tree.
 *
 * You may want a recursive helper function for this.
 */
int TripleTree::NumLeaves() const {
    // replace the line below with your implementation
    return -1;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current TripleTree object. To be completed for PA3.
 * You may want a recursive helper function for this one.
 */
void TripleTree::Clear() {
    // add your implementation below
    if (root != nullptr) {
        ClearHelper(root);
    }
    root = nullptr;
}

void TripleTree::ClearHelper(const Node *n) {
    if (!HasTwoChildren(n)) {
        // Leaf
        delete n;
        return;
    }
    ClearHelper(n->A);
    ClearHelper(n->C);
    if (HasThreeChildren(n)) {
        ClearHelper(n->B);
    }
    delete n;
}

/**
 * Copies the parameter other TripleTree into the current TripleTree.
 * Does not free any memory. Called by copy constructor and operator=.
 * You may want a recursive helper function for this one.
 * @param other - The TripleTree to be copied.
 */
void TripleTree::Copy(const TripleTree &other) {
    // add your implementation below
    CopyHelper(root, other.root);
}

void TripleTree::CopyHelper(Node *&node, const Node *copyNode) {
    if (copyNode == nullptr) {
        return;
    }
    node = new Node(copyNode->upperleft, copyNode->width, copyNode->height);
    node->avg = copyNode->avg;
    CopyHelper(node->A, copyNode->A);
    CopyHelper(node->B, copyNode->B);
    CopyHelper(node->C, copyNode->C);
}

/**
 * Private helper function for the constructor. Recursively builds
 * the tree according to the specification of the constructor.
 * @param im - reference image used for construction
 * @param ul - upper left point of node to be built's rectangle.
 * @param w - width of node to be built's rectangle.
 * @param h - height of node to be built's rectangle.
 */
Node *TripleTree::BuildNode(PNG &im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h) {
    Node *newNode = new Node(ul, w, h);
    if (w == 1 && h == 1) {
        // base case, individual pixel
        newNode->avg = *im.getPixel(ul.first, ul.second);
        // no children
        return newNode;
    }
    if (w >= h) {
        // split wide
        if (w == 2) {
            newNode->A = BuildNode(im, ul, 1, h);
            newNode->C = BuildNode(im, make_pair(ul.first + 1, ul.second), 1, h);
        } else if (w % 3 == 0) {
            // even split of 3
            newNode->A = BuildNode(im, ul, w / 3, h);
            newNode->B = BuildNode(im, make_pair(ul.first + w / 3, ul.second), w / 3, h);
            newNode->C = BuildNode(im, make_pair(ul.first + 2 * (w / 3), ul.second), w / 3, h);
        } else if (w % 3 == 1) {
            // give b extra pixel
            newNode->A = BuildNode(im, ul, w / 3, h);
            newNode->B = BuildNode(im, make_pair(ul.first + w / 3, ul.second), w / 3 + 1, h);
            newNode->C = BuildNode(im, make_pair(ul.first + 2 * (w / 3) + 1, ul.second), w / 3, h);
        } else {
            // give a & b extra pixel
            newNode->A = BuildNode(im, ul, w / 3 + 1, h);
            newNode->B = BuildNode(im, make_pair(ul.first + w / 3 + 1, ul.second), w / 3, h);
            newNode->C = BuildNode(im, make_pair(ul.first + 2 * (w / 3) + 1, ul.second), w / 3 + 1, h);
        }

    } else {
        // split tall
        if (h == 2) {
            newNode->A = BuildNode(im, ul, w, 1);
            newNode->C = BuildNode(im, make_pair(ul.first, ul.second + 1), w, 1);
        } else if (h % 3 == 0) {
            // even split of 3
            newNode->A = BuildNode(im, ul, w, h / 3);
            newNode->B = BuildNode(im, make_pair(ul.first, ul.second + h / 3), w, h / 3);
            newNode->C = BuildNode(im, make_pair(ul.first, ul.second + 2 * (h / 3)), w, h / 3);
        } else if (h % 3 == 1) {
            // give b extra pixel
            newNode->A = BuildNode(im, ul, w, h / 3);
            newNode->B = BuildNode(im, make_pair(ul.first, ul.second + h / 3), w, h / 3 + 1);
            newNode->C = BuildNode(im, make_pair(ul.first, ul.second + 2 * (h / 3) + 1), w, h / 3);
        } else {
            // give a & b extra pixel
            newNode->A = BuildNode(im, ul, w, h / 3 + 1);
            newNode->B = BuildNode(im, make_pair(ul.first, ul.second + h / 3 + 1), w, h / 3);
            newNode->C = BuildNode(im, make_pair(ul.first, ul.second + 2 * (h / 3) + 1), w, h / 3 + 1);
        }
    }

    // Color Assignment
    if (newNode->B != nullptr) {
        newNode->avg.r = (newNode->A->avg.r * newNode->A->height * newNode->A->width +
                          newNode->B->avg.r * newNode->B->height * newNode->B->width +
                          newNode->C->avg.r * newNode->C->height * newNode->C->width) /
                         (newNode->height * newNode->width);
        newNode->avg.g = (newNode->A->avg.g * newNode->A->height * newNode->A->width +
                          newNode->B->avg.g * newNode->B->height * newNode->B->width +
                          newNode->C->avg.g * newNode->C->height * newNode->C->width) /
                         (newNode->height * newNode->width);
        newNode->avg.b = (newNode->A->avg.b * newNode->A->height * newNode->A->width +
                          newNode->B->avg.b * newNode->B->height * newNode->B->width +
                          newNode->C->avg.b * newNode->C->height * newNode->C->width) /
                         (newNode->height * newNode->width);
        // TODO: alpha?
    } else {
        // B is null
        newNode->avg.r = (newNode->A->avg.r * newNode->A->height * newNode->A->width +
                          newNode->C->avg.r * newNode->C->height * newNode->C->width) /
                         (newNode->height * newNode->width);
        newNode->avg.g = (newNode->A->avg.g * newNode->A->height * newNode->A->width +
                          newNode->C->avg.g * newNode->C->height * newNode->C->width) /
                         (newNode->height * newNode->width);
        newNode->avg.b = (newNode->A->avg.b * newNode->A->height * newNode->A->width +
                          newNode->C->avg.b * newNode->C->height * newNode->C->width) /
                         (newNode->height * newNode->width);
    }

    return newNode;
}

/* ===== IF YOU HAVE DEFINED PRIVATE MEMBER FUNCTIONS IN tripletree_private.h, IMPLEMENT THEM HERE ====== */
