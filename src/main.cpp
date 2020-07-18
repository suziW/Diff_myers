//
// Created by admin1 on 2020/6/30.
//

#include "cmp/Myers.hcc"
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

using namespace std;
using json = nlohmann::json; //json for morden c++

int main() {
    // est ns get from piano roll
    vector<vector<float>> frame = readArrayFromeFile("frame.txt");
    vector<vector<float>> onset = readArrayFromeFile("onset.txt");
    pianoRoll piano_roll(onset, frame);
    vector<note> est_ns = piano_roll.noteSequence();

    // ref ns read from file
    json ref_json;
    ifstream i("2.json");
    i >> ref_json;
    vector<note> ref_ns = ref_json["notes"].get<vector<note>>();

    // cmp
    MyersStandard<note> myers(ref_ns, est_ns);
    PlotCmp plot(ref_ns, est_ns, 0, 1.5);
    cout << ref_ns.size() << "::" << est_ns.size() << endl;
}

