#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int map[] = {
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 3, 613, 3, 4, 5, 5, 82, 5, 4, 1,
1, 3, 3, 4, 4, 5, 5, 5, 5, 4, 1,
1, 4, 4, 3, 4, 5, 5, 5, 5, 4, 1,
1, 3, 3, 4, 4, 5, 5, 5, 5, 4, 1,
2, 3, 3, 4, 4, 4, 4, 4, 4, 4, 1,
1, 3, 81, 4, 4, 4, 4, 4, 4, 622, 1,
1, 3, 3, 4, 4, 4, 3, 3, 3, 3, 1,
1, 0, 3, 4, 4, 4, 1, 2, 1, 10, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int map2[] = {
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 3, 613, 3, 4, 5, 5, 82, 5, 4, 1,
1, 3, 4, 3, 4, 5, 5, 5, 5, 4, 1,
1, 3, 4, 3, 4, 5, 5, 5, 5, 4, 1,
1, 3, 3, 3, 4, 5, 5, 5, 5, 4, 1,
2, 3, 3, 4, 4, 4, 4, 4, 4, 4, 1,
1, 3, 81, 4, 4, 4, 4, 4, 4, 622, 1,
1, 3, 3, 4, 4, 4, 3, 3, 3, 3, 1,
1, 3, 3, 4, 4, 4, 1, 2, 1, 10, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int Deathmap[] = {
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* textures[textureAmount] = { NULL };
    Death = 0;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("Initialisation de la SDL");
    }
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    if (SDL_CreateWindowAndRenderer(size * (colones), size * (lignes + 1), 0, &window, &renderer) != 0)
    {
        SDL_ExitWithError("Inpossible de creer la fenetre et le rendu");
    }
    ajoutTextures(renderer, window, textures);
    majMap(renderer, window, DM, map, map2, textures);

    deplacement(renderer, window, DM, map, map2, Deathmap, textures);
    SDL_RenderPresent(renderer);
    SDL_DestroyRenderer(renderer);
}