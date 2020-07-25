//
// Created by admin1 on 2020/7/7.
//

#include "PianoRoll.h"


vector<vector<int>> pianoRoll::raw2binary(vector<vector<float>>& array, float threshold) {
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

vector<note> pianoRoll::noteSequence() {
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
                        n.id = ns.size();
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
                n.id = ns.size();
                ns.emplace_back(n);
                pitch_start_step.erase(p);
            }
        }
    }
    return ns;
}

