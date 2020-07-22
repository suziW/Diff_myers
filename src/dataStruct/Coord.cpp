//
// Created by admin1 on 2020/7/2.
//

#include "Coord.h"

ostream &operator<<(ostream &output, coord &c) {
    output << "coord: x=" << c.x << ", y=" << c.y << "; ";
    return output;
}
