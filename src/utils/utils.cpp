//
// Created by admin1 on 2020/7/25.
//

#include <dataStruct/PianoRoll.h>
#include <cmp/Myers.hpp>
#include <plot/PlotCmp.h>
#include "utils.hpp"

vector<vector<float>> readArrayFromeFile(const string &file) {
//    vector<vector<float>> array;
//    ifstream i(file);
//    string line;
//    while (getline(i, line)) {
//        string::size_type start = 0;
//        string::size_type end = 0;
//        vector<float> frame;
//        float active = 0;
//
//        while (end != string::npos) {
//            end = line.find(' ', start);
//            active = stof(line.substr(start, end - start));
//            frame.emplace_back(active);
//            start = end + 1;
//        }
//        array.emplace_back(frame);
//    }
//    return array;
    vector<vector<float>> array;
    ifstream i(file);
    string string_arr;
    i >> string_arr;

    int line_start = 0;
    int line_end = 1;
    while (true) {
        line_start = string_arr.find('[', line_end) + 1;
        if (line_start == 0) { break;}
        line_end = string_arr.find(']', line_start);
        string line = string_arr.substr(line_start, line_end - line_start);

        vector<float> frame;
        int float_start = 0;
        int float_end = 0;
        float active;
        while (float_end != string::npos) {
            float_end = line.find(',', float_start);
            active = stof(line.substr(float_start, float_end - float_start));
            frame.emplace_back(active);
            float_start = float_end + 1;
        }
        array.emplace_back(frame);
    }
    return array;
}

bool noteAscendingCmp(note &n1, note &n2) {
    if (n1.start_time < n2.start_time) {
        return true;
    } else if (n1.start_time > n2.start_time) {
        return false;
    } else { return n1.pitch < n2.pitch; }
}

void nsAscendingSort(vector<note> &ns) {
    sort(ns.begin(), ns.end(), noteAscendingCmp);
    for (int i = 0; i < ns.size(); i++) {
        ns[i].id = i;
    }
}

void logAnalyze(string file) {
    string onsetfile = file + "/onset.txt";
    string framefile = file + "/frame.txt";
    string jsonfile = file + "/reference.json";

    // est ns parsed from onset frame
    vector<vector<float>> onset = readArrayFromeFile(onsetfile);
    vector<vector<float>> frame = readArrayFromeFile(framefile);
    pianoRoll piano_roll(onset, frame);
    vector<note> est_ns = piano_roll.noteSequence();
    nsAscendingSort(est_ns);
//    vector<note> est_ns_cut(est_ns.begin() + 283, est_ns.begin() + 400);
    vector<note> est_ns_cut = est_ns;

    // ref ns read from file
    json ref_json;
    ifstream i(jsonfile);
    i >> ref_json;
    vector<note> ref_ns = ref_json["notes"].get<vector<note>>();
    nsAscendingSort(ref_ns);
//    vector<note> ref_ns_cut(ref_ns.begin() + 202, ref_ns.begin() + 290);
    vector<note> ref_ns_cut = ref_ns;

    // cmp
    IntoMyers into(ref_ns_cut, est_ns_cut, 0.3);
    MyersOverlapPoll myers(ref_ns_cut, est_ns_cut, &into);
    myers.process();
    isAllMatchCorrect(ref_ns_cut, est_ns_cut, myers.match);
    PlotCmp plot(ref_ns_cut, est_ns_cut, -ref_ns_cut[0].start_time, -est_ns_cut[0].start_time, 0.6);
    cout << ref_ns.size() << "::" << est_ns.size() << endl;
}

void isAllMatchCorrect(vector<note> &ref_ns, vector<note> &est_ns, vector<coord> &match) {
    for (auto &i: match){
        if (not (ref_ns.at(i.x) == est_ns.at(i.y))){
            cout << BOLDRED << "======================================" << endl;
            cout << "a: " << ref_ns.at(i.x) << endl
                 << "b: " << est_ns.at(i.y) << RESET << endl;
        }
    }
}
