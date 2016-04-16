#ifndef NNCO_VP_TREE_H
#define NNCO_VP_TREE_H


#include <c++/cstdlib>
#include <c++/vector>
#include <c++/algorithm>
#include <c++/unordered_map>
#include "point.h"
#include "vp_node.h"
#include "metrics.h"

class VpTree {
public:
    static VpNode *BuildTree(std::vector<Point *> *points);

    static void InsertPoint(VpNode *root, Point *point);

    static void RemovePoint(VpNode *root, Point *point);

    static std::pair<double, double *> FindDistances(std::vector<Point *> *points, Point *median);

    static void FreeNodes(VpNode *root);
};


#endif //NNCO_VP_TREE_H
