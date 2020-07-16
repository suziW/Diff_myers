//
// Created by admin1 on 2020/7/9.
//

#include "Analyze.h"

string analyze(vector<vector<float>> onset, vector<vector<float>> frame, const string &file) {
    pianoRolll piano_roll(onset, frame);

    // est ns get from piano roll
    vector<note> est_ns = piano_roll.noteSequence();

    // ref ns read from file
    json ref_json;
    ifstream i("2.json");
    i >> ref_json;
    vector<note> ref_ns = ref_json["notes"].get<vector<note>>();

    // cmp
    MyersStandard<note> myers(ref_ns, est_ns);
    json diff = ref_ns; // correct or error ref notes
    for (auto bd:myers.bDiff){
        diff.emplace_back(est_ns[bd]); // add error est notes
    }
    cout << myers.aDiff.size() << endl;
    cout << myers.bDiff.size() << endl;
    cout << myers.match.size() << endl;
    return diff.dump(4);
}