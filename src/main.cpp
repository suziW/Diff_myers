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

using namespace std;
using json = nlohmann::json; //json for morden c++

int main() {
    // est ns get from piano roll
    vector<vector<float>> frame = readArrayFromeFile("frame.txt");
    vector<vector<float>> onset = readArrayFromeFile("onset.txt");
    pianoRoll piano_roll(onset, frame);
    vector<note> est_ns = piano_roll.noteSequence();
    nsAscendingSort(est_ns);
    vector<note> est_ns_cut(est_ns.begin() + 12, est_ns.begin() + 32);
//    vector<note> est_ns_cut = est_ns;

    // ref ns read from file
    json ref_json;
    ifstream i("2.json");
    i >> ref_json;
    vector<note> ref_ns = ref_json["notes"].get<vector<note>>();
    nsAscendingSort(ref_ns);
    vector<note> ref_ns_cut(ref_ns.begin() + 7, ref_ns.begin() + 17);
//    vector<note> ref_ns_cut = ref_ns;

    // cmp
    IntoMyers into(ref_ns_cut, est_ns_cut, 1);
    MyersOverlapPoll myers(ref_ns_cut, est_ns_cut, &into);
//    MyersTree myers(ref_ns_cut, est_ns_cut, &into);
    myers.process();
    PlotCmp plot(ref_ns_cut, est_ns_cut, 0, 1);
    cout << ref_ns.size() << "::" << est_ns.size() << endl;
}
