//
// Created by admin1 on 2020/7/22.
//

#ifndef MSTT_TREE_H
#define MSTT_TREE_H

#include <vector>
#include <list>
#include "Coord.h"

using namespace std;

class treeNode {
public:
    treeNode(coord c, int d, int k) : c(c), d(d), k(k) {}

//    treeNode() : c(coord(0, 0)), d(0), k(0) {}
    ~treeNode() = default;

    coord c;
    int d;
    int k;
    treeNode *left = nullptr;
    treeNode *right = nullptr;
    treeNode **sibling = nullptr;
    treeNode *parent = nullptr;
};

class tree {
public:
    tree() = default;;

    void init(int max_leaves, const treeNode &rootNode);

    treeNode *root = nullptr;
    vector<treeNode *> leaves; // TODO:change vector to heap or priority queue later
    int current_d = -1;
    list<treeNode> all_nodes;

    int get_k_leave_x(int k);

    void emplace_back(const treeNode &node, int parent_leave_num);

};

#endif //MSTT_TREE_H
