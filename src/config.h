//
// Created by admin1 on 2020/7/7.
//

#ifndef MSTT_CONFIG_H
#define MSTT_CONFIG_H

#include <map>
#include <string>

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

// about music and records
const float SAMPLE_RATE = 16000;
const float HOPLENGTH = 512;
const float FRAMES_PER_SECOND = SAMPLE_RATE / HOPLENGTH;
const float SECONDS_PER_FRAME = HOPLENGTH / SAMPLE_RATE;
const int MIN_PITCH = 21;
const int MAX_PITCH = 108;
const int NUM_PITCHES = MAX_PITCH - MIN_PITCH + 1;


// pitch to notation
const std::map<int, std::string> PITCH2NOTATION = {
        {21, "A2"},
        {22, "#A2"},
        {23, "B2"},
        {24, "C1"},
        {25, "#C1"},
        {26, "D1"},
        {27, "#D1"},
        {28, "E1"},
        {29, "F1"},
        {30, "#F1"},
        {31, "G1"},
        {32, "#G1"},
        {33, "A1"},
        {34, "#A1"},
        {35, "B1"},
        {36, "C"},
        {37, "#C"},
        {38, "D"},
        {39, "#D"},
        {40, "E"},
        {41, "F"},
        {42, "#F"},
        {43, "G"},
        {44, "#G"},
        {45, "A"},
        {46, "#A"},
        {47, "B"},
        {48, "c"},
        {49, "#c"},
        {50, "d"},
        {51, "#d"},
        {52, "e"},
        {53, "f"},
        {54, "#f"},
        {55, "g"},
        {56, "#g"},
        {57, "a"},
        {58, "#a"},
        {59, "b"},
        {60, "c1"},
        {61, "#c1"},
        {62, "d1"},
        {63, "#d1"},
        {64, "e1"},
        {65, "f1"},
        {66, "#f1"},
        {67, "g1"},
        {68, "#g1"},
        {69, "a1"},
        {70, "#a1"},
        {71, "b1"},
        {72, "c2"},
        {73, "#c2"},
        {74, "d2"},
        {75, "#d2"},
        {76, "e2"},
        {77, "f2"},
        {78, "#f2"},
        {79, "g2"},
        {80, "#g2"},
        {81, "a2"},
        {82, "#a2"},
        {83, "b2"},
        {84, "c3"},
        {85, "#c3"},
        {86, "d3"},
        {87, "#d3"},
        {88, "e3"},
        {89, "f3"},
        {90, "#f3"},
        {91, "g3"},
        {92, "#g3"},
        {93, "a3"},
        {94, "#a3"},
        {95, "b3"},
        {96, "c4"},
        {97, "#c4"},
        {98, "d4"},
        {99, "#d4"},
        {100, "e4"},
        {101, "f4"},
        {102, "#f4"},
        {103, "g4"},
        {104, "#g4"},
        {105, "a4"},
        {106, "#a4"},
        {107, "b4"},
        {108, "c5"}
};

#endif //MSTT_CONFIG_H
