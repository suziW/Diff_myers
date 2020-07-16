//
// Created by admin1 on 2020/7/7.
//

#include "PianoRolll.h"


vector<vector<int>> pianoRolll::raw2binary(vector<vector<float>>& array, float threshold) {
    vector<vector<int>> arr;
    vector<int> line;
    for (auto & f : array){
        for (float p : f){
            line.emplace_back(p > threshold);
        }
        arr.emplace_back(line);
        line.clear();
    }
    return arr;
}

vector<note> pianoRolll::noteSequence() {
    frame.emplace_back(NUM_PITCHES, 0);
    onset.emplace_back(NUM_PITCHES, 0);

    vector<note> ns;
    int active;
    unordered_map<int, int> pitch_start_step;
    note n;

    for (int f = 0; f < frame.size(); f++) {
        for (int p = 0; p < NUM_PITCHES; p++) {
            active = frame[f][p] & onset[f][p];
            if (active) {
                if (pitch_start_step.count(p)) {
                    if (onset[f][p] and not onset[f - 1][p]) {
                        // 连续的note, frame连着，onset不连着，结束上一个note，开始新的note
                        n.pitch = p + MIN_PITCH;
                        n.start_time = pitch_start_step[p] * SECONDS_PER_FRAME;
                        n.duration = f * SECONDS_PER_FRAME - n.start_time;
                        ns.emplace_back(n);
                        // 开始新的note
                        pitch_start_step[p] = f;
                    }
                } else if (onset[f][p]) {
                    // 新的没在字典里的note, 添加进字典
                    pitch_start_step[p] = f;
                }
            } else if (pitch_start_step.count(p)) {
                // 字典里有的note变成零，结束这个note
                n.pitch = p + MIN_PITCH;
                n.start_time = pitch_start_step[p] * SECONDS_PER_FRAME;
                n.duration = f * SECONDS_PER_FRAME - n.start_time;
                ns.emplace_back(n);
                pitch_start_step.erase(p);
            }
        }
    }
    return ns;
}

//void pianoRolll::check() {
//    if (frame.size() != onset.size() or frame[0].size() != NUM_PITCHES or onset[0].size() != NUM_PITCHES) {
//        throw "onset or frame with wrong size!";
//    }
//}

vector<vector<float>> readArrayFromeFile(const string& file) {
    vector<vector<float>> array;
    ifstream i(file);
    string line;
    while (getline(i, line)) {
        string::size_type start = 0;
        string::size_type end = 0;
        vector<float> frame;
        float active = 0;

        while (end != string::npos) {
            end = line.find(' ', start);
            active = stof(line.substr(start, end - start));
            frame.emplace_back(active);
            start = end + 1;
        }
        array.emplace_back(frame);
    }
    return array;
}
