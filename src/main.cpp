//
// Created by admin1 on 2020/6/30.
//

#include "cmp/Myers.hcc"
#include <vector>
#include <fstream>
#include <iomanip>
#include "dataStruct/Note.h"
#include "json.hpp"
#include "config.h"
#include "dataStruct/PianoRolll.h"
#include "cmp/Analyze.h"

using namespace std;
using json = nlohmann::json; //json for morden c++

int main() {
    vector<vector<float>> frame = readArrayFromeFile("frame.txt");
    vector<vector<float>> onset = readArrayFromeFile("onset.txt");
    auto r = analyze(onset, frame, "");
    cout << r << endl;
    return 0;
}

