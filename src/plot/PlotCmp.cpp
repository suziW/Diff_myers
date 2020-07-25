//

#include "PlotCmp.h"

PlotCmp::PlotCmp(vector<note> &ref, vector<note> &est, float shift_seconds, float zoom) {
    for (auto &n:ref) {
        refNotePlots.emplace_back(n, shift_seconds, SCREEN_HEIGHT / 2 + fontSize, zoom);
    }
    for (auto &n:est) {
        estNotePlots.emplace_back(n, shift_seconds, SCREEN_HEIGHT , zoom);
    }

    init();
    render();
}

void PlotCmp::init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    TTF_Init();

    window = SDL_CreateWindow("ref(up) est(down) note sequence compare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    font = TTF_OpenFont("etl14-unicode.bdf", fontSize);
}

// Created by admin1 on 2020/7/17.
void PlotCmp::noteRender() {
    // ref render
    for (auto &i:refNotePlots) {
        i.render(renderer);
    }

    // mid line
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2 + fontSize, SCREEN_WIDTH, SCREEN_HEIGHT / 2 + fontSize);

    // est render
    for (auto &i:estNotePlots) {
        i.render(renderer);
    }
}

void PlotCmp::textRender() {
    textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    textSquare.w = textSurface->w;
    textSquare.h = textSurface->h;
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, texture, nullptr, &textSquare);
}

//          触发note事件，set txt
void PlotCmp::setText(SDL_Event &e) {
    int x_, y_;
    string tmp;
    SDL_GetMouseState(&x_, &y_);
    if (y_ < SCREEN_HEIGHT / 2 + fontSize) {
        // ref area
        for (auto &i:refNotePlots) {
            tmp = i.handleEvent(x_, y_);
            if (!tmp.empty()) {
                text = tmp;
                break;
            }
        }
    } else {
        // est area
        for (auto &i:estNotePlots) {
            tmp = i.handleEvent(x_, y_);
            if (!tmp.empty()) {
                text = tmp;
                break;
            }
        }
    }
}

void PlotCmp::render() {
    bool quit = false;
    bool reRender = true;

    // show note info
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                reRender = true;
                setText(e);
            }
        }

        // render
        if (reRender) {
            // 背景render
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);
            // note render
            noteRender();
            // text render
            textRender();

            SDL_RenderPresent(renderer);
            reRender = false;
        }
        SDL_Delay(100);
    }
}

void PlotCmp::close() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

PlotCmp::~PlotCmp() {
    close();
}

NotePlot::NotePlot(note &n, float shift_seconds, int y_base, float zoom) {
    x = (int) ((n.start_time + shift_seconds) * 100);
    y = -(n.pitch - MIN_PITCH + 1) * 5 + y_base;
    color_status = n.status;
    info = to_string(n);
    this->zoom(zoom, y_base);
}

void NotePlot::zoom(float zoom, int y_base) {
    x = (int) ((float) (x) * zoom);
    y = (int) ((float) ((y - y_base) * zoom + y_base));
    w = (int) ((float) (w) * zoom);
    h = (int) ((float) (h) * zoom);
}

string NotePlot::handleEvent(int x_, int y_) {
    //If mouse event happened
    //Get mouse position

    //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if (x_ < x) {
        inside = false;
    }
        //Mouse is right of the button
    else if (x_ > x + w) {
        inside = false;
    }
        //Mouse above the button
    else if (y_ < y) {
        inside = false;
    }
        //Mouse below the button
    else if (y_ > y + h) {
        inside = false;
    }

    //Mouse is outside button
    if (!inside) {
        return "";
    } else {
        return info;
    }
}

void NotePlot::render(SDL_Renderer *gRenderer) {
    //Show current button sprite
    SDL_Rect fillRect = {x, y, w, h};
    if (color_status == 0) { // 0 means match. color blue
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
    } else if (color_status == 1) { // 1 means miss. color red
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    } else if (color_status == 2) { // 2 means extra, color green
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    } else {
        throw "color status error";
    }
    SDL_RenderFillRect(gRenderer, &fillRect);
}
