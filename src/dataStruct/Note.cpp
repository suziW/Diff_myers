//
// Created by admin1 on 2020/7/3.
//

#include "Note.h"


ostream &operator<<(ostream &output, note &n) {
    output << to_string(n);
    return output;
}

// this is the note instance before ==, n is the note instance after ==
bool note::operator==(const note &n) const {
    return pitch == n.pitch;
}

string note::get_notation() {
    try {
        notation = PITCH2NOTATION.at(pitch);
    } catch (exception e) {
        cout << "Note.cpp:22, get notation found error: " << e.what() << endl;
    }
    return notation;
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
    j.at("pitch").get_to(n.pitch);
//    j.at("start_time").get_to(n.start_time);
    n.start_time = float(j.at("start_time")) * 4 *60 / float(j.at("measure_bpm"));
//    j.at("duration").get_to(n.duration);
    n.duration = float(j.at("duration")) * 4 *60 / float(j.at("measure_bpm"));
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

string to_string(note &n) {
    if (n.notation.empty()) {
        n.get_notation();
    }
    return "notation:" + n.notation +
           " pitch:" + to_string(n.pitch) +
           " start_time:" + to_string(n.start_time) +
           " id:" + to_string(n.id) +
           " match_id:" + to_string(n.match_id) +
           " status:" + to_string(n.status) +
           ", ";
}
