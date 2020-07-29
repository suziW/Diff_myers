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
    string file = "2020-07-29_09-56-09_650_萨拉班德舞曲";//2020-07-29_09-55-15_679_欢乐颂"; //2020-07-29_09-58-17_652_天空之城"; //2020-07-28_14-52-31_678_小步舞曲";
    logAnalyze(file);
}
