//
// Created by admin1 on 2020/7/25.
//

#include "utils.hpp"

vector<vector<float>> readArrayFromeFile(const string &file) {
    vector<vector<float>> array;
    ifstream i(file);
    string line;
    while (getline(i, line)) {
        string::size_type start = 0;
        string::size_type end = 0;
        vector<float> frame;
        float active = 0;

        while (end != string::npos) {
            end = line.find(' ', start);
            active = stof(line.substr(start, end - start));
            frame.emplace_back(active);
            start = end + 1;
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
