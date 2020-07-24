//
// Created by admin1 on 2020/7/22.
//

#include "Myers.hpp"

void MyersTree::shortest_edit() {
    cout << "in shortest_edit implementation" << endl;
    int x = 0;
    int y = -1;
    int d = -1;
    int k = 1;
    int n = this->a.size();
    int m = this->b.size();
    int maxd = m + n;

    tr.init(2 * maxd + 1, treeNode(coord(x, y), d, k));
    for (d = 0; d <= maxd; d++) {
        tr.current_d = d;
        for (k = -d; k <= d; k += 2) {
            if (k == -d or (k != d and tr.get_k_leave_x(k - 1) < tr.get_k_leave_x(k + 1))) {
                x = tr.get_k_leave_x(k + 1);
                y = x - k;
                tr.emplace_back(treeNode(coord(x, y), d, k), k + 1);
                plotInfo = "downward: d, k = " + to_string(d) + ", " + to_string(k);
                inspect();
            } else {
                x = tr.get_k_leave_x(k - 1) + 1;
                y = x - k;
                tr.emplace_back(treeNode(coord(x, y), d, k), k - 1);
                plotInfo = "rightward: d, k = " + to_string(d) + ", " + to_string(k);
                inspect();
            }

            while (x < n and y < m and this->a[x] == this->b[y]) {
                x = x + 1, y = y + 1; // Moving diagonally
                tr.emplace_back(treeNode(coord(x, y), d, k), k);
                plotInfo = "diagonally: d, k = " + to_string(d) + ", " + to_string(k);
                inspect();
            }

            if (x >= n and y >= m) return; // TODO: 如果不要求a\b匹配完，或者只要求b走完,或者给b一个earlystop
        }
    }
}

void MyersTree::diff() {
    shortest_edit();

    treeNode *current_node = &tr.all_nodes.back();
    while (current_node->parent != tr.root) {
        if (current_node->c.horizontal_with(current_node->parent->c)) {
            aDiff.emplace_back(current_node->parent->c.x);
            cout << RED << "--- " << a.at(aDiff.back()) << endl;
            a.at(aDiff.back()).status = 1;
        } else if (current_node->c.vertical_with(current_node->parent->c)) {
            bDiff.emplace_back(current_node->parent->c.y);
            cout << GREEN << "+++ " << b.at(bDiff.back()) << endl;
            b.at(bDiff.back()).status = 2;
            b.at(bDiff.back()).osmd_id = a.at(max(0, current_node->c.x - 1)).osmd_id;
        } else if (current_node->c.diagonal_with(current_node->parent->c)) {
            match.emplace_back(current_node->parent->c);
            cout << RESET << "    " << a.at(match.back().x) << endl;
            a.at(match.back().x).status = 0;
            a.at(match.back().x).rhythm = 0;
            a.at(match.back().x).match_id = match.back().y;
            b.at(match.back().y).status = 0;
            b.at(match.back().y).rhythm = 0;
            b.at(match.back().y).match_id = match.back().x;
        }
        current_node = current_node->parent;
    }

    plot->trueBlock();
}

void MyersTree::inspect() {
    if (plot) {
        plot->block();
        plot->plot_tree(tr, plotInfo);
    }
}
