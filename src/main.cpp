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
#include "cmp/Analyze.h"
#include "plot/PlotCmp.h"
#include "plot/IntoMyers.h"
#include <ctime>

using namespace std;
using json = nlohmann::json; //json for morden c++

int main() {
//    logAnalyze(file);
//    string file = "2020-07-30_14-06-11_678_小步舞曲";
//    string file = "2020-07-30_14-12-00_650_萨拉班德舞曲";
//    string file = "2020-07-30_14-11-06_679_欢乐颂";
    string file = "2020-07-30_14-14-04_652_天空之城";
    string onsetfile = file + "/onset.txt";
    string framefile = file + "/frame.txt";
    string jsonfile = file + "/reference.json";

    // est ns parsed from onset frame
    vector<vector<float>> onset = readArrayFromeFile(onsetfile);
    vector<vector<float>> frame = readArrayFromeFile(framefile);
    pianoRoll piano_roll(onset, frame);
    vector<note> est_ns = piano_roll.noteSequence();
    nsAscendingSort(est_ns);
//    vector<note> est_ns_cut(est_ns.begin() + 32, est_ns.begin() + 65);
    vector<note> est_ns_cut = est_ns;

    // ref ns read from file
    json ref_json;
    ifstream i(jsonfile);
    i >> ref_json;
    vector<note> ref_ns = ref_json["notes"].get<vector<note>>();
    nsAscendingSort(ref_ns);
//    vector<note> ref_ns_cut(ref_ns.begin() + 22, ref_ns.begin() + 47);
    vector<note> ref_ns_cut = ref_ns;

    clock_t start, end;
    start = clock();
    // cmp
//    IntoMyers into(ref_ns_cut, est_ns_cut, 0.2);
//    MyersTrim myers(ref_ns_cut, est_ns_cut, &into);
    MyersTrim myers(ref_ns_cut, est_ns_cut);
//    MyersOverlapPoll myers(ref_ns_cut, est_ns_cut);
    myers.process();
    end = clock();
    cout << YELLOW << "=====================time: " << float(end - start)/CLOCKS_PER_SEC << endl;
    isAllMatchCorrect(ref_ns_cut, est_ns_cut, myers.match);
    PlotCmp plot(ref_ns_cut, est_ns_cut, -ref_ns_cut[0].start_time, -est_ns_cut[0].start_time, 0.5);
    cout << ref_ns.size() << "::" << est_ns.size() << endl;
}
