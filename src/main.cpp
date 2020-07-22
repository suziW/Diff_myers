//
// Created by admin1 on 2020/6/30.
//

#include "cmp/Myers.hpp"
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <SDL2/SDL.h>
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
    vector<vector<int>> t;
    vector<int> u(3, 1);
    vector<int> j(2, 1);
    t.push_back(u);
    t.push_back(j);

    // est ns get from piano roll
    vector<vector<float>> frame = readArrayFromeFile("frame.txt");
    vector<vector<float>> onset = readArrayFromeFile("onset.txt");
    pianoRoll piano_roll(onset, frame);
    vector<note> est_ns = piano_roll.noteSequence();
    nsAscendingSort(est_ns);
    vector<note> est_ns_cut(est_ns.begin(), est_ns.end());

    // ref ns read from file
    json ref_json;
    ifstream i("2.json");
    i >> ref_json;
    vector<note> ref_ns = ref_json["notes"].get<vector<note>>();
    nsAscendingSort(ref_ns);
    vector<note> ref_ns_cut(ref_ns.begin(), ref_ns.end());

    // cmp
    IntoMyers into(ref_ns_cut, est_ns_cut, 0.24);
    MyersStandard<note> myers(ref_ns_cut, est_ns_cut, &into);
    into.trace(myers.traceCoords);
    PlotCmp plot(ref_ns_cut, est_ns_cut, 0, 0.8);
    cout << ref_ns.size() << "::" << est_ns.size() << endl;

//    const char a[] = "ABAB";
//    const char b[] = "CAABA";
//    vector<char> a_(a, a + sizeof(a) - 1);
//    vector<char> b_(b, b + sizeof(b) - 1);
//    IntoMyers plot(a_, b_, 1);
//    MyersStandard<char> myers(a_, b_, &plot);
//    plot.trace(myers.traceCoords);
 }
