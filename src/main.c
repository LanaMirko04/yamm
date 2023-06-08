#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <slog.h>
#include <SDL2/SDL.h>
#include "interface.h"

int main(void) {
  if (init_interface()) {
    SLOG_ERROR("Failed to initialize the UI");
    return EXIT_FAILURE;
  }

  if (load_loading_gif("res/loading.gif")) {
    SLOG_ERROR("Failed to load GIF");
    close_interface();
    return EXIT_FAILURE;
  }

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0)
      if (e.type == SDL_QUIT)
        quit = true;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, loading_gif, NULL, &loading_rect);

    SDL_RenderPresent(renderer);
  }

  close_interface();

  return EXIT_SUCCESS;
}
