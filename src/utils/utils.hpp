//
// Created by admin1 on 2020/7/23.
//

#ifndef MSTT_UTILS_HPP
#define MSTT_UTILS_HPP

#include <vector>
using namespace std;

// support negative index
template<typename T>
inline T &at(vector<T> &a, int i) {
    return i < 0 ? a.at(i + a.size()) : a.at(i);
}

#endif //MSTT_UTILS_HPP
