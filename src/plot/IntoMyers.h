//
// Created by admin1 on 2020/7/20.
//

#ifndef MSTT_INTOMYERS_H
#define MSTT_INTOMYERS_H

#include <vector>
#include <string>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdio>
#include "dataStruct/Coord.h"
#include "dataStruct/Note.h"
#include "dataStruct/Tree.h"


class IntoMyers {
public:
    IntoMyers(vector<note> &ref, vector<note> &est, float zoom = 1);

    IntoMyers(vector<char> &ref, vector<char> &est, float zoom = 1);

    ~IntoMyers();

    void zoom(float zoom);

    void init();

    void renderLine(coord, coord, Uint8 w = 1, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

    void renderText();

    void renderGrid();

    void block();

    void trueBlock();

    void next(coord, coord, const string &);

    void plot_final_path(vector<coord> &);

    void plot_tree(tree &, const string &);

    void close();

private:
    // window setting
    bool quit = false;
    int SCREEN_WIDTH = 1800;
    int SCREEN_HEIGHT = 1000;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    TTF_Font *font = nullptr;
    SDL_Texture *texture = nullptr;

    // text setting
    string text = "press any key to continue!";
    int fontSize = 20;
    SDL_Color textColor = {0, 0, 0, 0xFF};
    SDL_Rect textSquare = {0, 0, 0, 0};
    SDL_Surface *textSurface = nullptr;

    // grid setting
    int start_x = 100;
    int start_y = 100;
    int side_length = 50;
    vector<string> a;
    vector<string> b;
    vector<coord> diagonal;
    vector<pair<coord, coord>> short_paths;
    vector<coord> *final_path = nullptr;
    tree *tr = nullptr;
};


#endif //MSTT_INTOMYERS_H
