//
// Created by admin1 on 2020/7/2.
//

#include "Coord.h"

ostream &operator<<(ostream &output, coord &c) {
    output << to_string(c);
    return output;
}

bool coord::horizontal_with(coord &n) const {
    return y == n.y;
}

bool coord::vertical_with(coord &n) const {
    return x == n.x;
}

bool coord::diagonal_with(coord &n) const {
    return (x == n.x - 1 and y == n.y - 1) or (x == n.x + 1 and y == n.y + 1);
}

string to_string(coord &c) {
    return "[coord: x=" + to_string(c.x) + ", y=" + to_string(c.y) + "] ";
}