//

#include "PianoRoll.h"


//
// Created by admin1 on 2020/7/7.
pianoRoll::pianoRoll(vector<vector<int>> &on, vector<vector<int>> &fr) {
    onset = on;
    frame = fr;
    get_note_sequence();
}

pianoRoll::pianoRoll(vector<vector<float>> &on, vector<vector<float>> &fr) {
    onset = raw2binary(on);
    frame = raw2binary(fr);
    get_note_sequence();
}


vector<vector<int>> pianoRoll::raw2binary(vector<vector<float>> &array, float threshold) {
    vector<vector<int>> arr;
    vector<int> line;
    for (auto &f : array) {
        for (float p : f) {
            line.emplace_back(p > threshold);
        }
        arr.emplace_back(line);
        line.clear();
    }
    return arr;
}

void pianoRoll::get_note_sequence() {
    onset.emplace_back(NUM_PITCHES, 0);
    frame.emplace_back(NUM_PITCHES, 0);

    int active;
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
}

void pianoRoll::update(vector<vector<int>> &on, vector<vector<int>> &fr) {
    int s = onset.size();

    onset.insert(onset.end(), on.begin(), on.end());
    frame.insert(frame.end(), fr.begin(), fr.end());

    int active;
    note n;

    for (int f = s; f < frame.size(); f++) {
        for (int p = 0; p < NUM_PITCHES; p++) {
            active = frame[f][p] & onset[f][p];
            if (active) {
                if (pitch_start_step.count(p)) {
                    if (onset[f][p] and not onset[f - 1][p]) {
                        // 连续的note, frame连着，onset不连着，结束上一个note，开始新的note
                        pitch_start_step[p] = f; // new note

                        n.pitch = p + MIN_PITCH;
                        n.start_time = pitch_start_step[p] * SECONDS_PER_FRAME;
                        n.id = ns.size();
                        ns.emplace_back(n);
                    }
                } else if (onset[f][p]) {
                    // 新的没在字典里的note, 添加进字典
                    pitch_start_step[p] = f;

                    n.pitch = p + MIN_PITCH;
                    n.start_time = pitch_start_step[p] * SECONDS_PER_FRAME;
                    n.id = ns.size();
                    ns.emplace_back(n);
                }
            } else if (pitch_start_step.count(p)) {
                // 字典里有的note变成零，结束这个note
                pitch_start_step.erase(p);
            }
        }
    }
}

void pianoRoll::update(vector<vector<float>> &on, vector<vector<float>> &fr) {
    vector<vector<int>> _on = raw2binary(on);
    vector<vector<int>> _fr = raw2binary(fr);
    update(_on, _fr);
}
