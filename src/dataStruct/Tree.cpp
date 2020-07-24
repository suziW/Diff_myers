//
// Created by admin1 on 2020/7/22.
//

#include "Tree.h"
#include "utils/utils.hpp"

void tree::init(int max_leaves, const treeNode &rootNode) {
    all_nodes.emplace_back(rootNode);
    leaves.resize(max_leaves, nullptr);

    root = &all_nodes.back();
    leaves[1] = &all_nodes.back();
}

int tree::get_k_leave_x(int k) {
    return at(leaves, k)->c.x;
}

void tree::emplace_back(const treeNode &node, int parent_leave_num) {
    all_nodes.emplace_back(node);

    all_nodes.back().parent = at(leaves, parent_leave_num);
    if (all_nodes.back().k <= parent_leave_num) {
        at(leaves, parent_leave_num)->left = &all_nodes.back();
        all_nodes.back().sibling = &at(leaves, parent_leave_num)->right;
    } else {
        at(leaves, parent_leave_num)->right = &all_nodes.back();
        all_nodes.back().sibling = &at(leaves, parent_leave_num)->left;
    }

    at(leaves, node.k) = &all_nodes.back();
}
