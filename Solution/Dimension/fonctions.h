#pragma once
#define colones 11
#define lignes 10
#define HeroOriginalPos 89
#define size 50
#define textureAmount 19

typedef struct POSITION POSITION;
struct POSITION
{
    int x;
    int y;
};
int Death;
void SDL_ExitWithError(const char* message);
void quitIfNull(parametre, renderer, window);
void quitWithError(SDL_Renderer* renderer, SDL_Window* window);
void ajoutTextures(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* textures[]);
void ajoutBlock(SDL_Renderer* renderer, SDL_Window* window, SDL_DisplayMode DM, POSITION position, SDL_Texture* texture);
void majMap(SDL_Renderer* renderer, SDL_Window* window, SDL_DisplayMode DM, int tab[], int tab2[], SDL_Texture* textures[]);
void deplacement(SDL_Renderer* renderer, SDL_Window* window, SDL_DisplayMode DM, int tab[], int tab2[], int Deathtab[], SDL_Texture* textures[]);
int fonctionBouttons(int indice, int tab[], int tab2[]);