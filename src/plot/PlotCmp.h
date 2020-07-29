//
// Created by admin1 on 2020/7/17.
//

#ifndef MSTT_PLOTCMP_H
#define MSTT_PLOTCMP_H

#ifdef PLOT
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <string>
#include "dataStruct/Note.h"

class NotePlot {

public:
    //Initializes internal variables
    NotePlot(note &n, float shift_seconds, int y_base, float zoom);

    //Sets top left position
    void zoom(float, int);

    //Handles mouse event
    string handleEvent(int, int);

    //Shows button sprite
    void render(SDL_Renderer *);

private:
    //Top left position
    string info;
    int color_status;
    int x;
    int y;
    int w = 20;
    int h = 10;
};

// window size: w* h = 1800 * 1000, compatible to draw 18 s * 200 pitch piano roll
// shift_seconds: set the start seconds of piano roll, left shift show be negative value
// zoom: zoom in when zoom < 1, zoom out when zoom > 1
class PlotCmp {
public:
    PlotCmp(vector<note> &ref, vector<note> &est, float ref_shift_seconds, float est_shift_seconds, float zoom);

    ~PlotCmp();

    void init();

    void noteRender();

    void textRender();

    void setText(SDL_Event &e);

    void render();

    void close();

private:
    int SCREEN_WIDTH = 1800;
    int SCREEN_HEIGHT = 1000;

    vector<NotePlot> refNotePlots;
    vector<NotePlot> estNotePlots;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    TTF_Font *font = nullptr;
    SDL_Texture *texture = nullptr;

    string text = "click a note to see its information";
    int fontSize = 20;
    SDL_Color textColor = {0, 0, 0, 0xFF};
    SDL_Rect textSquare = {0, 0, 0, 0};
    SDL_Surface *textSurface = nullptr;
};


#else

#include <vector>
#include "dataStruct/Note.h"

class PlotCmp{
public:
    PlotCmp(vector<note> &ref, vector<note> &est, float shift_seconds, float zoom){}
};
#endif

#endif //MSTT_PLOTCMP_H
