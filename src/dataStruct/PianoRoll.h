//
// Created by admin1 on 2020/7/7.
//

#ifndef MSTT_PIANOROLL_H
#define MSTT_PIANOROLL_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "config.h"
#include "Note.h"

using namespace std;

class pianoRoll {
public:
    pianoRoll(vector<vector<int>> &onset, vector<vector<int>> &frame) : onset(onset), frame(frame) {}

    pianoRoll(vector<vector<float>> &raw_onset, vector<vector<float>> &raw_frame) : onset(raw2binary(raw_onset)),
                                                                                    frame(raw2binary(raw_frame)) {}

    vector<vector<int>> onset; // (t, 88)
    vector<vector<int>> frame;

//    vector<vector<float>> raw_onset;
//    vector<vector<float>> raw_frame;
    static vector<vector<int>> raw2binary(vector<vector<float>>& array, float threshold = 0);

    vector<note> noteSequence();

private:
//    void check();
};

vector<vector<float>> readArrayFromeFile(const string&);

#endif //MSTT_PIANOROLL_H
