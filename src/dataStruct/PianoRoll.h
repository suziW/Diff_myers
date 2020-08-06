//
// Created by admin1 on 2020/7/7.
//

#ifndef MSTT_PIANOROLL_H
#define MSTT_PIANOROLL_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include "config.h"
#include "Note.h"

using namespace std;

class pianoRoll {
public:
    pianoRoll() = default;

    pianoRoll(vector<vector<int>> &on, vector<vector<int>> &fr);

    pianoRoll(vector<vector<float>> &on, vector<vector<float>> &fr);

    static vector<vector<int>> raw2binary(vector<vector<float>> &array, float threshold = 0);

    void get_note_sequence();

    void update(vector<vector<int>> &on, vector<vector<int>> &fr);

    void update(vector<vector<float>> &on, vector<vector<float>> &fr);

    vector<note> ns;

private:
    vector<vector<int>> onset; // (t, 88)
    vector<vector<int>> frame;
    unordered_map<int, int> pitch_start_step;
};


#endif //MSTT_PIANOROLL_H
