#include "vp_algorithm.h"

void VpAlgorithm::Init(std::vector<Point *> *points,
                       double (*distance)(Point *p1, Point *p2),
                       double (*dimension_distance)(double p1, double p2, int dimension)) {
    if (points == nullptr || points->empty())
        return;
    if (VpAlgorithm::root != nullptr)
        VpTree::FreeNodes(root);
    std::vector<Point *> copy(*points);
    VpAlgorithm::metric = distance;
    VpAlgorithm::root = VpTree::BuildTree(&copy, metric);
}

Point *VpAlgorithm::Ann(Point *point) {
    std::pair<VpNode *, double> result{nullptr, std::numeric_limits<double>::max()};
    NnsProblem(VpAlgorithm::root, point, &result);
    return result.first->get_point();
}

void VpAlgorithm::InsertPoint(Point *point) {
    VpTree::InsertPoint(root, point, metric);
}

void VpAlgorithm::RemovePoint(Point *point) {
    VpTree::RemovePoint(root, point, metric);
}

bool VpAlgorithm::Contains(Point *point) {
    return VpTree::Contains(root, point, metric);
}

void VpAlgorithm::NnsProblem(VpNode *root, Point *q, std::pair<VpNode *, double> *best) {
    if (root == nullptr) {
        return;
    }
    double distance = metric(root->get_point(), q);
    if (!root->is_dead() && root->get_point() != q && (best->first == nullptr || distance < best->second)) {
        best->first = root;
        best->second = distance;
    }
    if (root->get_inside_node() == nullptr && root->get_outside_node() == nullptr) {
        return;
    }
    if (distance < root->get_radius()) {
        if (distance - best->second <= root->get_radius()) {
            VpAlgorithm::NnsProblem(root->get_inside_node(), q, best);
        }
        if (distance + best->second >= root->get_radius()) {
            VpAlgorithm::NnsProblem(root->get_outside_node(), q, best);
        }
    } else {
        if (distance + best->second >= root->get_radius()) {
            VpAlgorithm::NnsProblem(root->get_outside_node(), q, best);
        }
        if (distance - best->second <= root->get_radius()) {
            VpAlgorithm::NnsProblem(root->get_inside_node(), q, best);
        }
    }
}

VpAlgorithm::~VpAlgorithm() {
    VpTree::FreeNodes(root);
}
