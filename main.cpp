#include <SDL2/SDL.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SLD Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            std::cout << "Window could not be created! SDL_Error:  " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
           //Create renderer for window
           gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

           if (gRenderer == NULL)
           {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
           }
           else
           {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
           }
        
        }
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Nothing to load
    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[])
{
    //Start up SDL and create window
    if (!init())
    {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else
    {
        //Load media
        if(!loadMedia())
        {
            std::cout << "Failed to load media!" << std::endl;
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while(!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }    

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);   
                SDL_RenderClear(gRenderer);

                //Render red filled quad
                SDL_Rect SDL_FillRect = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 10, 10};
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(gRenderer, &SDL_FillRect);

                //Update the screen
                 SDL_RenderPresent(gRenderer);
               
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
