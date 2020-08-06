//
// Created by admin1 on 2020/6/30.
//

#include "cmp/Myers.hpp"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include "dataStruct/Note.h"
#include "json.hpp"
#include "config.h"
#include "dataStruct/PianoRoll.h"
#include "cmp/Cmp.h"
#include "plot/PlotCmp.h"
#include "plot/IntoMyers.h"
#include <ctime>

using namespace std;
using json = nlohmann::json; //json for morden c++

int main() {
    clock_t start, end;
    start = clock();
//    logAnalyze(file);
//    string file = "2020-07-30_14-06-11_678_小步舞曲";
//    string file = "2020-07-30_14-12-00_650_萨拉班德舞曲";
//    string file = "2020-07-30_14-11-06_679_欢乐颂";
    string file = "2020-07-30_14-14-04_652_天空之城";
    string onsetfile = file + "/onset.txt";
    string framefile = file + "/frame.txt";
    string jsonfile = file + "/reference.json";

    CmpRealTime progress;
    progress.init(jsonfile);

    vector<vector<float>> onset = readArrayFromeFile(onsetfile);
    vector<vector<float>> frame = readArrayFromeFile(framefile);
    for (int k = 0; k < 102; k++){
        cout << RESET << "=============================================================================" << endl;
        vector<vector<float>> onset_cut(onset.begin() + k * 30, onset.begin() + k * 30 + 30);
        vector<vector<float>> frame_cut(frame.begin() + k * 30, frame.begin() + k * 30 + 30);
        cout << BLUE << progress.update(onset_cut, frame_cut) << endl;
    }
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    // ref ns read from file
//    json ref_json;
//    ifstream i(jsonfile);
//    i >> ref_json;
//    vector<note> ref_ns = ref_json["notes"].get<vector<note>>();
//    nsAscendingSort(ref_ns);
//    vector<note> ref_ns_cut(ref_ns.begin(), ref_ns.begin() + 60);
////    vector<note> ref_ns_cut = ref_ns;
//
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    // est ns parsed from onset frame
//    vector<vector<float>> onset = readArrayFromeFile(onsetfile);
//    vector<vector<float>> frame = readArrayFromeFile(framefile);
//    pianoRoll _piano_roll(onset, frame);
//    vector<note> est_ns(_piano_roll.ns.begin(), _piano_roll.ns.begin()+84);
//
//    pianoRoll piano_roll;
//    vector<note> &est_ns_cut = piano_roll.ns;
//
//    IntoMyers into(ref_ns_cut, est_ns, 0.2);
//    MyersRealTime myers(ref_ns_cut, est_ns_cut, &into);
//    for (int k = 0; k < 17; k++) {
//        cout << "=============================================================================" << endl;
//        vector<vector<float>> onset_cut(onset.begin() + k * 30, onset.begin() + k * 30 + 30);
//        vector<vector<float>> frame_cut(frame.begin() + k * 30, frame.begin() + k * 30 + 30);
//        piano_roll.update(onset_cut, frame_cut);
//        cout << BLUE << myers.update() << endl;
//    }

    end = clock();
    cout << YELLOW << "=====================time: " << float(end - start) / CLOCKS_PER_SEC << endl;
//    PlotCmp plot(ref_ns_cut, est_ns_cut, -ref_ns_cut[0].start_time, -est_ns_cut[0].start_time, 0.5);
//    cout << ref_ns.size() << "::" << est_ns.size() << endl;
}
