/*
 *  YAMM, yet another mind mapping tool
 *  Copyright (c) 2023 Lana Mirko
 *
 * */

#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <slog.h>

#include "interface.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *loading_gif = NULL;
SDL_Rect loading_rect;

int init_interface(void) {
  SLOG_DEBUG("SDL inizialization...");
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SLOG_ERROR("SDL couldn't initialize: %s", SDL_GetError());
    return -1;
  }

  SLOG_DEBUG("SDL window creation...");
  window = SDL_CreateWindow(
      "YAMM",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    SLOG_ERROR("Window couldn't be created: %s", SDL_GetError());
    return -1;
  }

  SLOG_DEBUG("SDL renderer creation...");
  renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SLOG_ERROR("Renderer couldn't be created: %s", SDL_GetError());
    return -1;
  }

  SLOG_DEBUG("IMG inizialization...");
  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
    SLOG_ERROR("SDL_image couldn't initialize: %s", IMG_GetError());
    return -1;
  }

  return 0;
}

int load_loading_gif(const char *path) {
  SDL_Surface *loaded_surface;

  SLOG_DEBUG("GIF Loading...");
  loaded_surface = IMG_Load(path);
  if (loaded_surface == NULL) {
    SLOG_ERROR("Unable to load GIF image %s: %s", path, IMG_GetError());
    return -1;
  }

  SLOG_DEBUG("IMG texture creation...");
  loading_gif = SDL_CreateTextureFromSurface(renderer, loaded_surface);
  if (loading_gif == NULL) {
    SLOG_ERROR("Unable to create texture from %s: %s", path, SDL_GetError());
    SDL_FreeSurface(loaded_surface);
    return -1;
  }

  loading_rect.w = loaded_surface->w;
  loading_rect.h = loaded_surface->h;

  SDL_FreeSurface(loaded_surface);

  return 0;
}

void close_interface(void) {
  SDL_DestroyTexture(loading_gif);
  loading_gif = NULL;

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  IMG_Quit();
  SDL_Quit();
}
