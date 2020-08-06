//
// Created by admin1 on 2020/6/30.
//

#ifndef MSTT_MYERS_HCC
#define MSTT_MYERS_HCC

#include <vector>
#include <iostream>
#include "config.h"
#include "dataStruct/Coord.h"
#include "dataStruct/Note.h"
#include "plot/IntoMyers.h"
#include "utils/utils.hpp"
#include "dataStruct/Tree.h"

using namespace std;

template<class T>
class Myers {
public:
    Myers(vector<T> &a, vector<T> &b) : a(a), b(b) {};

    virtual ~Myers() = default; // 防止内存泄漏

    vector<T> &a; // ground truth
    vector<T> &b; // estimate
    vector<int> aDiff;
    vector<int> bDiff;
    vector<coord> match;
    vector<vector<int>> trace;
    vector<coord> traceCoords;

public:
    virtual void shortest_edit() = 0;

    virtual void backtrack() = 0;

    virtual void diff() = 0;

    virtual void process() = 0;
};


template<class T>
class MyersStandard : public Myers<T> {
public:
//    using Myers<T>::Myers;
    MyersStandard(vector<T> &a, vector<T> &b, IntoMyers *plot = nullptr) : Myers<T>(a, b), plot(plot) {}

    void shortest_edit() override;

    void diff() override;

    void process() override;

    IntoMyers *plot;
    string plotInfo = " ";
private:
    void backtrack() override;

    vector<vector<int>> trace;
    vector<coord> traceCoords;
};

template<class T>
void MyersStandard<T>::shortest_edit() {
    cout << "in shortest_edit implementation" << endl;
    int x;
    int y;
    int n = this->a.size();
    int m = this->b.size();
    int maxd = m + n;
    int k;
    vector<int> v(2 * maxd + 1); //可以弄成指针做成变长的,适应limit k

    for (int d = 0; d <= maxd; d++) {
        this->trace.emplace_back(v);
        for (k = -d; k <= d; k += 2) {
            if (k == -d or (k != d and at(v, k - 1) < at(v, k + 1))) {
                x = at(v, k + 1); // Moving downward
                if (plot) {
                    plotInfo = "downward: d, k = " + to_string(d) + ", " + to_string(k);
                    plot->next(coord(x, x - k - 1), coord(x, x - k), plotInfo);
                }
            } else {
                x = at(v, k - 1) + 1; // Moving rightward
                if (plot) {
                    plotInfo = "rightward: d, k = " + to_string(d) + ", " + to_string(k);
                    plot->next(coord(x - 1, x - 1 - k + 1), coord(x, x - k), plotInfo);
                }
            }
            y = x - k;

            while (x < n and y < m and this->a[x] == this->b[y]) {
                x = x + 1, y = y + 1; // Moving diagonally
                if (plot) {
                    plotInfo = "diagonally: d, k = " + to_string(d) + ", " + to_string(k);
                    plot->next(coord(x - 1, y - 1), coord(x, y), plotInfo);
                }
            }

            at(v, k) = x; //更新v,各个路径的x坐标
            if (x >= n and y >= m) return; // TODO: 如果不要求a\b匹配完，或者只要求b走完,或者给b一个earlystop
        }
    }
}

template<class T>
void MyersStandard<T>::backtrack() {
    cout << "in backtrack implementation " << endl;
    int x = this->a.size();
    int y = this->b.size();
    int k;
    int prevk, prevx, prevy;
    vector<int> v;

    for (int d = this->trace.size() - 1; d >= 0; d--) {
        v = at(this->trace, d);
        k = x - y; //TODO: print all k to see the boundaries, then limit the value k can reach in shortest edit fun

        if (k == -d or (k != d and at(v, k - 1) < at(v, k + 1))) {
            prevk = k + 1;
        } else {
            prevk = k - 1;
        }

        prevx = at(v, prevk);
        prevy = prevx - prevk;

        while (x > prevx and y > prevy) {
            this->traceCoords.emplace_back(x, y);
            x = x - 1, y = y - 1;
        }
        this->traceCoords.emplace_back(x, y);
        x = prevx, y = prevy;
    }
}

template<class T>
void MyersStandard<T>::diff() {
    cout << "in diff implementation" << endl;
    shortest_edit();
    backtrack();

    for (auto i = this->traceCoords.rbegin(); i != this->traceCoords.rend() - 1; i++) {
        if ((*i).x == (*(i + 1)).x) {
            this->bDiff.emplace_back((*i).y);
            cout << GREEN << "+++ " << at(this->b, this->bDiff.back()) << endl;
        } else if ((*i).y == (*(i + 1)).y) {
            this->aDiff.emplace_back((*i).x);
            cout << RED << "--- " << at(this->a, this->aDiff.back()) << endl;
        } else {
            this->match.emplace_back(*i);
            cout << RESET << "    " << at(this->a, this->match.back().x) << endl;
        }
    }
}

template<>
inline void MyersStandard<note>::diff() {
    cout << "in diff implementation" << endl;

    for (auto i = this->traceCoords.rbegin(); i != this->traceCoords.rend() - 1; i++) {
        if ((*i).x == (*(i + 1)).x) {
            this->bDiff.emplace_back((*i).y);
            cout << GREEN << "+++ " << at(this->b, this->bDiff.back()) << endl;
            this->b[(*i).y].status = 2;
            this->b[(*i).y].osmd_id = this->a[max((*i).x - 1, 0)].osmd_id;
        } else if ((*i).y == (*(i + 1)).y) {
            this->aDiff.emplace_back((*i).x);
            cout << RED << "--- " << at(this->a, this->aDiff.back()) << endl;
            this->a[(*i).x].status = 1;
        } else {
            this->match.emplace_back(*i);
            cout << RESET << "    " << at(this->a, this->match.back().x) << endl;
            this->a[(*i).x].status = 0;
            this->a[(*i).x].rhythm = 0;
            this->a[(*i).x].match_id = (*i).y;
            this->b[(*i).y].status = 0;
            this->b[(*i).y].rhythm = 0;
            this->b[(*i).y].match_id = (*i).x;
        }
    }
}

template<class T>
void MyersStandard<T>::process() {
    cout << "processing ..." << endl;
    shortest_edit();
    backtrack();
    diff();
}

class MyersTree : public MyersStandard<note> {
public:
    MyersTree(vector<note> &a, vector<note> &b, IntoMyers *plot = nullptr) : MyersStandard<note>(a, b, plot) {
    }

    void shortest_edit() override;

    void diff() override;

    void process() override;

    void inspect();

    tree tr;
};

class MyersOverlapPoll : public MyersTree {
public:
    MyersOverlapPoll(vector<note> &a, vector<note> &b, IntoMyers *plot = nullptr) : MyersTree(a, b, plot) {}

    void shortest_edit() override;

    virtual void deoverlap();

    void process() override;

    unordered_map<float, vector<note *>> overlap_pool;

    void get_overlap_pool();

    bool is_match_in_poll(note &ax, note &by);
};

class MyersTrim : public MyersOverlapPoll {
public:
    MyersTrim(vector<note> &a, vector<note> &b, IntoMyers *plot = nullptr) : MyersOverlapPoll(a, b, plot) {}

    void shortest_edit() override;
};

class MyersEarlyStop : public MyersTrim {
public:
    MyersEarlyStop(vector<note> &a, vector<note> &b, IntoMyers *plot = nullptr) : MyersTrim(a, b, plot) {}

    void shortest_edit() override;
};

class MyersRealTime : public MyersEarlyStop {
public:
    MyersRealTime(vector<note> &a, vector<note> &b, IntoMyers *plot = nullptr) : MyersEarlyStop(a, b, plot) {
        init();
    }

    void shortest_edit() override;

    void init();

    string update();

    void diff() override;

    void deoverlap() override;

    treeNode *last_node = nullptr;
    string result;
};

#endif //MSTT_MYERS_HCC
