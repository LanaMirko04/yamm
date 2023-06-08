/*
 *  YAMM, yet another mind mapping tool
 *  Copyright (c) 2023 Lana Mirko
 *
 * */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int init_interface(void);
int load_loading_gif(const char *path);
void close_interface(void);

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *loading_gif;
extern SDL_Rect loading_rect;

#endif
