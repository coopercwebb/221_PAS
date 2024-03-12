/**
 * @file filler_private.h
 * @description student declarations of private functions
 *              for Filler, CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below

#include "filler.h"

pair<int, int> MakePixelCoordPair(PixelPoint p);

void AddNeighbors(FillerConfig &config, OrderingStructure<PixelPoint> &os, set<pair<int, int>> &visited_coords, PixelPoint p);
