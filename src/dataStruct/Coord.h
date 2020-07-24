//
// Created by admin1 on 2020/7/2.
//

#ifndef MSTT_COORD_H
#define MSTT_COORD_H

#include <iostream>

using namespace std;

class coord {
public:
    explicit coord(int x, int y) : x(x), y(y) {}

    int x;
    int y;

//    int &a = x;
//    int &b = y;
    friend ostream &operator<<(ostream &, coord &);

    bool horizontal_with(coord &n) const;

    bool vertical_with(coord &n) const;

    bool diagonal_with(coord &n) const;
};

string to_string(coord &c);

#endif //MSTT_COORD_H
