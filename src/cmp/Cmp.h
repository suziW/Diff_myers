//
// Created by admin1 on 2020/7/9.
//

#ifndef MSTT_CMP_H
#define MSTT_CMP_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <ctime>
#include "dataStruct/PianoRoll.h"
#include "Myers.hpp"

using namespace std;

class CmpRealTime {
public:
    void init(const string& ref_json_file);

    string update(vector<vector<float>> onset, vector<vector<float>> frame);

private:
    pianoRoll piano_roll;
    vector<note> &est_ns = piano_roll.ns;
    vector<note> ref_ns;
    MyersRealTime *myers;

    void get_ref_ns(const string& ref_json_file);
};

string cmpAll(vector<vector<float>> onset, vector<vector<float>> frame, const string &file);

#endif //MSTT_CMP_H
