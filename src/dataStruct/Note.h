//
// Created by admin1 on 2020/7/3.
//

#ifndef MSTT_NOTE_H
#define MSTT_NOTE_H

#include <string>
#include <cmath>
#include <iostream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class note {
public:
    explicit note(int pitch = -1, float start_time = -1) :
            pitch(pitch), start_time(start_time) {}

    int pitch;
    float start_time;
    int id = -1;
    vector<int> osmd_id = {-1, -1, -1, -1, -1};
    int measure_bpm = -1;
    float end_time = -1;
    int velocity = -1;
    float duration = -1;
    int measure = -1;
    int line = -1;
    int track = -1;

    float speed = 100;
    int status = -1; //0:correct, 1:lost, 2:addition
    int rhythm = -1;
    string notation = "-1";

    friend ostream &operator<<(ostream &, const note &);

    bool operator==(const note &) const;
};

void to_json(json &, const note &);

void from_json(const json &, note &);

vector<note> parseArray();
#endif //MSTT_NOTE_H
