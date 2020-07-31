//
// Created by admin1 on 2020/7/23.
//

#ifndef MSTT_UTILS_HPP
#define MSTT_UTILS_HPP

#include <vector>
#include <fstream>
#include "dataStruct/Note.h"

using namespace std;

// support negative index
template<typename T>
inline T &at(vector<T> &a, int i) {
    return i < 0 ? a.at(i + a.size()) : a.at(i);
}

vector<vector<float>> readArrayFromeFile(const string &);

bool noteAscendingCmp(note &n1, note &n2);

void nsAscendingSort(vector<note> &ns);

void logAnalyze(string file);

void isAllMatchCorrect(vector<note> &ref_ns, vector<note> &est_ns, vector<coord> &match);

#endif //MSTT_UTILS_HPP
