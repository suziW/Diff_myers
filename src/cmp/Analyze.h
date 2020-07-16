//
// Created by admin1 on 2020/7/9.
//

#ifndef MSTT_ANALYZE_H
#define MSTT_ANALYZE_H

#include <string>
#include <vector>
#include <fstream>
#include "dataStruct/PianoRolll.h"
#include "Myers.hcc"

using namespace std;

class Analyze {

};

string analyze(vector<vector<float>> onset, vector<vector<float>> frame, const string &file);

#endif //MSTT_ANALYZE_H