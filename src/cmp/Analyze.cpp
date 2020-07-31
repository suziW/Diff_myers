//
// Created by admin1 on 2020/7/9.
//

#include "Analyze.h"

string analyze(vector<vector<float>> onset, vector<vector<float>> frame, const string &file) {
    clock_t start, end;
    start = clock();
    pianoRoll piano_roll(onset, frame);

    // est ns get from piano roll
    vector<note> est_ns = piano_roll.noteSequence();
    nsAscendingSort(est_ns);
    end = clock();
    cout << YELLOW << "=====================time: " << float(end - start)/CLOCKS_PER_SEC << endl;

    // ref ns read from file
    json ref_json;
//    ifstream i("2.json");
    ifstream i(file);
    i >> ref_json;
    vector<note> ref_ns = ref_json["notes"].get<vector<note>>();
    nsAscendingSort(ref_ns);
    end = clock();
    cout << YELLOW << "=====================time: " << float(end - start)/CLOCKS_PER_SEC << endl;

    // cmp
    MyersOverlapPoll myers(ref_ns, est_ns);
    myers.process();
    end = clock();
    cout << YELLOW << "=====================time: " << float(end - start)/CLOCKS_PER_SEC << endl;


    // return serialized results
    json diff = ref_ns; // correct or error ref notes
    for (auto bd:myers.bDiff){
        diff.emplace_back(est_ns[bd]); // add error est notes
    }
    cout << "aDiff size: " << myers.aDiff.size() << endl;
    cout << "bDiff size: " << myers.bDiff.size() << endl;
    cout << "match size: " << myers.match.size() << endl;
    return diff.dump(4);
}