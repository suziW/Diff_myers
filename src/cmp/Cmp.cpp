//
// Created by admin1 on 2020/7/9.
//

#include "Cmp.h"

void CmpRealTime::init(const string& ref_json_file) {
    get_ref_ns(ref_json_file);
    piano_roll = pianoRoll();
    myers = new MyersRealTime(ref_ns, est_ns);
}

void CmpRealTime::get_ref_ns(const string& ref_json_file) {
    json ref_json;
    ifstream i(ref_json_file);
    i >> ref_json;
    ref_ns = ref_json["notes"].get<vector<note>>();
    nsAscendingSort(ref_ns);
}

string CmpRealTime::update(vector<vector<float>> onset, vector<vector<float>> frame) {
    piano_roll.update(onset, frame);
    return myers->update();
}

string cmpAll(vector<vector<float>> onset, vector<vector<float>> frame, const string &file) {
    clock_t start, end;
    start = clock();

    // est ns get from piano roll
    pianoRoll piano_roll(onset, frame);
    vector<note> est_ns = piano_roll.ns;
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
    MyersTrim myers(ref_ns, est_ns);
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
