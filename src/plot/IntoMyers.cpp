//
// Created by admin1 on 2020/7/20.
//

#include "IntoMyers.h"

#include <utility>

IntoMyers::IntoMyers(vector<note> &ref, vector<note> &est, float zoom) {
    for (auto &i: ref) {
        a.emplace_back(to_string(a.size()) + "--" + i.get_notation());
    }
    for (auto &i: est) {
        b.emplace_back(to_string(b.size()) + "--" + i.get_notation());
    }
    for (int i = 0; i < ref.size(); i++) {
        for (int j = 0; j < est.size(); j++) {
            if (ref[i].pitch == est[j].pitch) {
                diagonal.emplace_back(i, j);
            }
        }
    }
    this->zoom(zoom);
    init();
    renderGrid();
}

IntoMyers::IntoMyers(vector<char> &ref, vector<char> &est, float zoom) {
    for (auto &i: ref) {
        a.emplace_back(to_string(a.size()) + "--" + string(1, i));
    }
    for (char &i: est) {
        b.emplace_back(to_string(b.size()) + "--" + string(1, i));
    }
    for (int i = 0; i < ref.size(); i++) {
        for (int j = 0; j < est.size(); j++) {
            if (ref[i] == est[j]) {
                diagonal.emplace_back(i, j);
            }
        }
    }
    this->zoom(zoom);
    init();
    renderGrid();
}

IntoMyers::~IntoMyers() {
    close();
}

void IntoMyers::zoom(float zoom) {
    side_length = int(side_length * zoom);
}

void IntoMyers::init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    TTF_Init();

    window = SDL_CreateWindow("how myers work, ref(x), est(y)", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    font = TTF_OpenFont("etl14-unicode.bdf", fontSize);
}

void IntoMyers::renderLine(coord c1, coord c2, Uint8 w, Uint8 r, Uint8 g, Uint8 b) {
    thickLineRGBA(renderer, c1.x * side_length + start_x, c1.y * side_length + start_y,
                  c2.x * side_length + start_x, c2.y * side_length + start_y, w, r, g, b, 255);
}

void IntoMyers::renderText() {
    textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    textSquare.w = textSurface->w;
    textSquare.h = textSurface->h;
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, texture, nullptr, &textSquare);
}

void IntoMyers::renderGrid(string info) {
    // 背景render
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // grid render
    for (int i = 0; i < a.size(); i++) {
        renderLine(coord(i, 0), coord(i, b.size()));
        text = a.at(i);
        textSquare.x = start_x + side_length * i;
        textSquare.y = start_y - fontSize;
        renderText();
    }
    renderLine(coord(a.size(), 0), coord(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) {
        renderLine(coord(0, i), coord(a.size(), i));
        text = b.at(i);
        textSquare.x = start_x - fontSize * 2;
        textSquare.y = start_y + side_length * i;
        renderText();
    }
    renderLine(coord(0, b.size()), coord(a.size(), b.size()));

    // render diagonal
    for (auto &i:diagonal) {
        renderLine(i, coord(i.x + 1, i.y + 1), 1, 0, 255, 0);
    }

    // render paths
    int k = -1; // init
    for (auto i = paths.rbegin(); i != paths.rend(); i++) {
        if (k == -1) {
            k = ((*i).second.x - (*i).second.y) & 1; // set odd even
        } else if (k != -2 and k != (((*i).second.x - (*i).second.y) & 1)) { // if odd even changed
            k = -2;
        }

        if (k == -2) { // odd even changed
            renderLine((*i).first, (*i).second, 2, 0, 0, 255);
        } else {
            renderLine((*i).first, (*i).second, 2, 255, 0, 0);
        }
    }

    // render final trace
    for (auto i = final_trace.begin(); i != final_trace.end(); i++) {
        if (i+1 == final_trace.end()){ break;}
        renderLine((*i), (*(i + 1)), 2, 0, 255, 0);
    }

    // render info
    text = move(info);
    textSquare = {0, 0, 0, 0};
    renderText();

    // render
    SDL_RenderPresent(renderer);
}

void IntoMyers::next(coord c1, coord c2, const string &info) {
    bool reRender = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                paths.emplace_back(c1, c2);
                renderGrid(info);
                reRender = true;
            }
        }
        if (reRender) {
            break; // break, so go to next loop, show next line.
        }
    }
}

void IntoMyers::close() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void IntoMyers::trace(vector<coord> &traceCoords) {
    final_trace = traceCoords;
    renderGrid();

    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}
