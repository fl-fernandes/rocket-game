#include <SDL2/SDL.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The rectangle that represents our rocket
class Rocket
{
    public:
        //Dimensions of the rocket
        static const int ROCKET_WIDTH = 10;
        static const int ROCKET_HEIGHT = 10;

        //Maximum axis velocity of the rocket
        static const int ROCKET_VEL = 1;

        //Initializes the variables
        Rocket();

        //Takes key presses and adjusts the rocket's velocity
        void handleEvent(SDL_Event& e);

        //Moves the rocket
        void move();

        //Shows the rocket on the screen
        void render();

    private:
        //The X and Y offsets of the dot
        int mPosX, mPosY;

        //The velocity of the dot
        int mVelX, mVelY;
};

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

Rocket::Rocket()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Rocket::handleEvent(SDL_Event& e)
{
    //If a key is pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= ROCKET_VEL;
            break;
        
        case SDLK_DOWN:
            mVelY += ROCKET_VEL;
            break;

        case SDLK_LEFT:
            mVelX -= ROCKET_VEL;
            break;
        
        case SDLK_RIGHT:
            mVelX += ROCKET_VEL;
            break;
        
        default:
            break;
        }
    } //If a key was released 
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
            mVelY += ROCKET_VEL;
            break;
        
        case SDLK_DOWN:
            mVelY -= ROCKET_VEL;
            break;

        case SDLK_LEFT:
            mVelX += ROCKET_VEL;
            break;
        
        case SDLK_RIGHT:
            mVelX -= ROCKET_VEL;
            break;
        
        default:
            break;
        }
    }
}

void Rocket::move()
{
    //move the rocket left or right
    mPosX += mVelX;

    //If the rocket went too far to the left or right
    if ((mPosX < 0) || (mPosX + ROCKET_WIDTH > SCREEN_WIDTH))
    {
        //move back
        mPosX -= mVelX;
    }

    //move the rocket up or down
    mPosY += mVelY;

    //If the rocket went too far to the left or right
    if ((mPosY < 0) || (mPosY + ROCKET_HEIGHT > SCREEN_HEIGHT))
    {
        //move back
        mPosY -= mVelY;
    }

}

void Rocket::render()
{
    SDL_Rect rect = {mPosX, mPosY, ROCKET_WIDTH, ROCKET_HEIGHT};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &rect);
}

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

            //The rocket that will be moving around the screen
            Rocket rocket;

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

                    //Handle input for the rocket
                    rocket.handleEvent(e);
                }    

                //move the rocket
                rocket.move();  

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);   
                SDL_RenderClear(gRenderer);

                //Render red filled rectangle (which will be our rocket in the future)
                rocket.render();

                //Update the screen
                 SDL_RenderPresent(gRenderer);
               
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
