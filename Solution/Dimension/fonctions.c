#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"

void SDL_ExitWithError(const char* message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void quitIfNull(parametre, renderer, window)
{
    if (parametre == NULL)
    {
        quitWithError(renderer, window);
    }
}

void quitWithError(SDL_Renderer* renderer, SDL_Window* window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_ExitWithError("Une erreur est survenue");
}

void ajoutBlock(SDL_Renderer* renderer, SDL_Window* window, SDL_DisplayMode DM, POSITION position, SDL_Texture* texture)
{
    SDL_Rect rectangle;
    if (SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0) quitWithError(renderer, window); //sauegarder les textures
    rectangle.w = size;
    rectangle.h = size;

    rectangle.x = position.x;
    rectangle.y = position.y;

    if (SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0) quitWithError(renderer, window);
}

void ajoutTextures(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* textures[])
{
    SDL_Surface* image = NULL;
    char* path = NULL;

    for (int i = 0; i < textureAmount; i++)
    {
        switch (i)
        {
        case 0:
            path = "textures/BMP/Hero.bmp";
            break;
        case 1:
            path = "textures/BMP/Black.bmp";
            break;
        case 2:
            path = "textures/BMP/GreyDEFAULT.bmp";
            break;
        case 3:
            path = "textures/BMP/GRASS3x3.bmp";
            break;
        case 4:
            path = "textures/BMP/LAVA.bmp";
            break;
        case 5:
            path = "textures/BMP/ICE.bmp";
            break;
        case 6:
            path = "textures/BMP/MobileOFF.bmp";
            break;
        case 7:
            path = "textures/BMP/MobileON.bmp";
            break;
        case 8:
            path = "textures/BMP/ButtonOFF.bmp";
            break;
        case 9:
            path = "textures/BMP/ButtonON.bmp";
            break;
        case 10:
            path = "textures/BMP/GOAL.bmp";
            break;
        case 11:
            path = "textures/BMP/GreyRIGHT.bmp";
            break;
        case 12:
            path = "textures/BMP/GreyLEFT.bmp";
            break;
        case 13:
            path = "textures/BMP/GreyUP.bmp";
            break;
        case 14:
            path = "textures/BMP/GreyDOWN.bmp";
            break;
        case 15:
            path = "textures/BMP/GreyDOWN.bmp";
            break;
        case 16:
            path = "textures/BMP/HorizontalShot.bmp";
            break;
        case 17:
            path = "textures/BMP/VerticalShot.bmp";
            break;
        case 18:
            path = "textures/BMP/DeadHero.bmp";
            break;
        default:
            path = "textures/BMP/Black.bmp";
        }
        image = SDL_LoadBMP(path);
        quitIfNull(image, renderer, window);

        textures[i] = SDL_CreateTextureFromSurface(renderer, image);
        quitIfNull(textures, renderer, image);
    }
}

void majMap(SDL_Renderer* renderer, SDL_Window* window, SDL_DisplayMode DM, int tab[], int tab2[], SDL_Texture* textures[])
{
    int ligne = 0;
    POSITION position;
    POSITION hero;

    char* path;
    for (int i = 0; i < lignes*colones; i++)
    {
        if (i % colones == 0) ligne++;
        position.x = i % colones * size;
        position.y = ligne * size;
        if (tab[i] == 0)
        {
            hero = position;
            if (tab2[i] < textureAmount)
            {
                ajoutBlock(renderer, window, DM, position, textures[tab2[i]]);
            }
            else if (tab2[i] > 599 && tab2[i] < 800)
            {
                ajoutBlock(renderer, window, DM, position, textures[tab2[i] / 100]);
            }
            else if (tab2[i] > 79 && tab2[i] < 100)
            {
                ajoutBlock(renderer, window, DM, position, textures[tab2[i] / 10]);
            }
        }
        else if (tab[i] < textureAmount)
        {
            ajoutBlock(renderer, window, DM, position, textures[tab[i]]);
        }
        else if (tab[i] > 599)
        {
            ajoutBlock(renderer, window, DM, position, textures[tab[i]/100]);
        }
        else if (tab[i] > 79)
        {
            ajoutBlock(renderer, window, DM, position, textures[tab[i]/10]);
        }

    }
    if (Death == 1) {
        ajoutBlock(renderer, window, DM, hero, textures[18]);
        Death = 0;
    }
    else {
        ajoutBlock(renderer, window, DM, hero, textures[0]);
    }
    SDL_RenderPresent(renderer);

}

void deplacement(SDL_Renderer* renderer, SDL_Window* window, SDL_DisplayMode DM, int tab[], int tab2[], int Deathmap[], SDL_Texture* textures[])
{
    SDL_Event event;
    int PP = HeroOriginalPos; // Position du joueur à l'origine
    bool alive = true;
    while (alive) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                if ((tab[PP + 1] != 1) && (tab[PP + 1] != 2) && (tab[PP + 1] != 4) && (tab[PP + 1]/100 != 6) && (tab[PP + 1]/100 != 7 && tab2[PP + 1] != 4) || (tab2[PP + 1] == 3 && tab[PP + 1] == 4)) {
                JumpR:
                    tab[PP] = tab2[PP];
                    tab[PP + 1] = 0;
                    PP = PP + 1;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                }
                else if ((tab[PP + 1] == 4) && ((tab[PP + 2] == 5) || tab[PP + 2] == 3)) {
                    tab[PP] = tab2[PP];
                    tab[PP + 1] = 0;
                    PP = PP + 1;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                    goto JumpR;
                }
                else if ((tab2[PP + 1] == 4 && tab[PP + 2] != 5)) {
                    tab[PP] = tab2[PP];
                    tab[PP + 1] = 0;
                    PP = PP + 1;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);

                    for (int i = 0; i < lignes * colones; i++)
                    {
                        Deathmap[i] = tab[i];
                    }
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        tab[i] = 4;
                    }
                    tab[PP] = 0;
                    Death = 1;
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(500);
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        tab[i] = Deathmap[i];
                    }
                    tab[PP] = 4;
                    PP = HeroOriginalPos;
                    tab[PP] = 0;
                    majMap(renderer, window, DM, tab, tab2, textures);

                }
            }
            if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
                if ((tab[PP - 1] != 1) && (tab[PP - 1] != 2) && (tab[PP - 1] != 4) && (tab[PP - 1]/100 != 6) && (tab[PP - 1]/100 != 7) && (tab2[PP - 1] != 4 || (tab2[PP - 1] == 3 && tab[PP - 1] == 4))) {
                JumpL:
                    tab[PP] = tab2[PP];
                    tab[PP - 1] = 0;
                    PP = PP - 1;
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                }
                else if ((tab[PP - 1] == 4) && ((tab[PP - 2] == 5) || (tab[PP - 2] == 3))) {
                    tab[PP] = tab2[PP];
                    tab[PP - 1] = 0;
                    PP = PP - 1;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                    goto JumpL;
                }
                else if ((tab2[PP - 1] == 4 && tab[PP - 2] != 5)) {
                    tab[PP] = tab2[PP];
                    tab[PP - 1] = 0;
                    PP = PP - 1;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        Deathmap[i] = tab[i];
                    }
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        tab[i] = 4;
                    }
                    tab[PP] = 0;
                    Death = 1;
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(500);
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        tab[i] = Deathmap[i];
                    }
                    tab[PP] = 4;
                    PP = HeroOriginalPos;
                    tab[PP] = 0;
                    majMap(renderer, window, DM, tab, tab2, textures);
                }
            }
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) {
                if ((PP - colones >= 0) && ((tab[PP - colones] != 1) && (tab[PP - colones] != 2) && (tab[PP - colones] != 4) && (tab[PP - colones]/100 != 6) && (tab[PP - colones]/100 != 7) && tab2[PP - colones] != 4) || (tab2[PP - colones] == 3 && tab[PP - colones] == 4)) {
                JumpU:
                    tab[PP] = tab2[PP];
                    tab[PP - 11] = 0;
                    PP = PP - 11;
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                }
                else if ((tab[PP - colones] == 4) && ((tab[PP - colones * 2] == 5) || (tab2[PP - colones * 2] == 3))) {
                    tab[PP] = tab2[PP];
                    tab[PP - 11] = 0;
                    PP = PP - 11;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                    goto JumpU;
                }
                else if ((tab2[PP - colones] == 4 && tab[PP - colones * 2] != 5)) {
                    tab[PP] = tab2[PP];
                    tab[PP - colones] = 0;
                    PP = PP - colones;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        Deathmap[i] = tab[i];
                    }
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        tab[i] = 4;
                    }
                    tab[PP] = 0;
                    Death = 1;
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(500);
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        tab[i] = Deathmap[i];
                    }
                    tab[PP] = 4;
                    PP = HeroOriginalPos;
                    tab[PP] = 0;
                    majMap(renderer, window, DM, tab, tab2, textures);
                }
            }
            if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                if ((PP + colones <= 109) && ((tab[PP + colones] != 1) && (tab[PP + colones] != 2) && (tab[PP + colones] != 4) && (tab[PP + colones]/100 != 6) && (tab[PP + colones]/100 != 7) && tab2[PP + colones] != 4 || (tab2[PP + colones] == 3 && tab[PP + colones] == 4))) {
                JumpD:
                    tab[PP] = tab2[PP];
                    tab[PP + colones] = 0;
                    PP = PP + colones;
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                }
                else if ((tab[PP + colones] == 4) && ((tab[PP + colones * 2] == 5) || (tab[PP + colones * 2] == 3))) {
                    tab[PP] = tab2[PP];
                    tab[PP + colones] = 0;
                    PP = PP + colones;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                    goto JumpD;
                }
                else if ((tab2[PP + colones] == 4 || tab2[PP + colones] == 4 && tab[PP + colones * 2] != 5)) {
                    tab[PP] = tab2[PP];
                    tab[PP + colones] = 0;
                    PP = PP + colones;//Déplacement dans le tableau de la map
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(200);
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        Deathmap[i] = tab[i];
                    }
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        tab[i] = 4;
                    }
                    tab[PP] = 0;
                    Death = 1;
                    majMap(renderer, window, DM, tab, tab2, textures);
                    SDL_Delay(500);
                    for (int i = 0; i < lignes * colones; i++)
                    {
                        tab[i] = Deathmap[i];
                    }
                    tab[PP] = 4;
                    PP = HeroOriginalPos;
                    tab[PP] = 0;
                    majMap(renderer, window, DM, tab, tab2, textures);
                }
            }
            if (tab2[PP] > 79 && tab2[PP] < 100 && tab[PP] == 0)
            {
                if (tab2[PP] < 90) tab2[PP] = tab2[PP] + 10;
                else tab2[PP] = tab2[PP] - 10;
                fonctionBouttons(PP, tab, tab2);
                majMap(renderer, window, DM, tab, tab2, textures);
            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
                goto end;
        }
    }
end:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}



int fonctionBouttons(int indice, int tab[], int tab2[])
{
    int adjust;
    int idx = -1;
    for (int i = 0; i < colones * lignes; i++)
    {
        if (tab[i] > 599 && tab[i] < 800)
        {
            if (tab2[indice] % 10 == tab[i] % 100 / 10)
            {
                idx = i;
            }
        }
    }
    if (idx == -1) return -1; 
    if (tab[idx] < 700) adjust = 100;
    else adjust = -100;
    switch (tab[idx] % 10)
    {
    case 1:
        tab[idx + 1] = tab[idx] + adjust + 1;
        tab2[idx + 1] = tab[idx + 1];

        break;
    case 2:
        tab[idx - 1] = tab[idx] + adjust - 1;
        tab2[idx - 1] = tab[idx - 1];
        break;
    case 3:
        tab[idx + colones] = tab[idx] + adjust + 1;
        tab2[idx + colones] = tab[idx + colones];
        break;
    case 4:
        tab[idx - colones] = tab[idx] + adjust - 1;
        tab2[idx - colones] = tab[idx - colones];

        break;
    default:
        tab[idx + 1] = tab[idx] + adjust + 1;
    }
    tab[idx] = 3;
    tab2[idx] = 3;
    return 0;
}