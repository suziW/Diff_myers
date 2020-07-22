//
// Created by admin1 on 2020/7/3.
//

#include "Note.h"


ostream &operator<<(ostream &output, note &n) {
    output << "notation:" << n.get_notation() << " pitch:" << n.pitch << " start_time:" << n.start_time << " id:"
           << n.id;
    return output;
}

// this is the note instance before ==, n is the note instance after ==
bool note::operator==(const note &n) const {
    return pitch == n.pitch;
}

string note::get_notation() {
    notation = PITCH2NOTATION.at(pitch);
    return notation;
}

bool noteAscendingCmp(note &n1, note &n2) {
    if (n1.start_time < n2.start_time) {
        return true;
    } else if (n1.start_time > n2.start_time) {
        return false;
    } else { return n1.pitch < n2.pitch; }
}

void nsAscendingSort(vector<note> & ns) {
    sort(ns.begin(), ns.end(), noteAscendingCmp);
    for (int i=0; i<ns.size();i++){
        ns[i].id = i;
    }
}

void to_json(json &j, const note &n) {
    j = json{{"pitch",       n.pitch},
             {"start_time",  n.start_time},
             {"duration",    n.duration},
             {"id",          n.id},
             {"osmd_id",     n.osmd_id},
             {"measure_bpm", n.measure_bpm},
             {"measure",     n.measure},
             {"speed",       n.speed},
             {"status",      n.status},
             {"rhythm",      n.rhythm},
             {"match_id",    n.match_id},
             {"notation",    n.notation}};
}

void from_json(const json &j, note &n) {
//    n = note(j.at("pitch"), j.at("onset"));
    j.at("pitch").get_to(n.pitch);
    j.at("start_time").get_to(n.start_time);
    j.at("duration").get_to(n.duration);
    j.at("id").get_to(n.id);
    j.at("osmd_id").get_to(n.osmd_id);
    j.at("measure_bpm").get_to(n.measure_bpm);
    j.at("measure").get_to(n.measure);

    try {
        j.at("speed").get_to(n.speed);
        j.at("status").get_to(n.status);
        j.at("rhythm").get_to(n.rhythm);
        j.at("match_id").get_to(n.match_id);
        j.at("notation").get_to(n.notation);
    } catch (nlohmann::detail::out_of_range &e) {
    }
}
