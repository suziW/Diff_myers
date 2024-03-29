//

#include "Tree.h"
#include "utils/utils.hpp"

//
// Created by admin1 on 2020/7/22.
bool treeNode::on_node_trace(treeNode *n) const {
    treeNode *tmp = n;
    while (tmp != nullptr and c < tmp->c){
        tmp = tmp->parent;
    }
    return c == tmp->c;
}

void tree::init(int max_leaves, const treeNode &root_node) {
    all_nodes.emplace_back(root_node);
    root = &all_nodes.back();
    leaves.resize(max_leaves, nullptr);
    leaves[1] = root;

    max_k = max_leaves / 2;
    min_k = -max_leaves / 2;
    current_d = -1;
}

int tree::get_k_leave_x(int k) {
    if (at(leaves, k)) {
        return at(leaves, k)->c.x;
    }
    return -1;
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

void tree::trim(int reserve) {
    int longest_k = 0;
    int max_sum = 0;
    for (int i = min_k; i < max_k; i++) {
        if (at(leaves, i)) {
            if (at(leaves, i)->c.sum() > max_sum) {
                max_sum = at(leaves, i)->c.sum();
                longest_k = i;
            }
        }
    }
    max_k = longest_k + reserve;
    while (max_k >= int(leaves.size()) or !at(leaves, max_k - 1)) {
        max_k--;
    }
    min_k = longest_k - reserve;
    while (min_k <= -int(leaves.size()) or !at(leaves, min_k + 1)) {
        min_k++;
    }
}

treeNode* tree::update(int max_leaves) {
    treeNode *last_node = &all_nodes.back();
    while (last_node->d == current_d and last_node != root){
        last_node = last_node->parent;
    }

    while (all_nodes.back().d == current_d and &all_nodes.back() != root) {
        all_nodes.pop_back();
    }
    leaves.insert(leaves.begin()+leaves.size()/2, max_leaves - leaves.size(), nullptr);

    return last_node;
}
