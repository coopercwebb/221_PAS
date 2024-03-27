/**
 * @file        tripletree_private.h
 * @description student declarations of private functions
 *              for TripleTree, CPSC 221 PA3
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below
void RenderHelper(const Node *n, PNG &render_img) const;

void ClearHelper(const Node *n);

bool HasThreeChildren(const Node *n) const;

bool HasTwoChildren(const Node *n) const;

void CopyHelper(Node *&node, const Node *copyNode);

void FlipHorizontalHelper(Node *&n, int image_width);

void PruneHelper(double tol, Node *&node);

bool CheckLeaves(double tol, Node *&root_node, Node *&node);

void SpecifiedClear(Node *&node);

int NumLeavesHelper(const Node *n) const;

bool isLeaf(const Node *n) const;