#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <iostream>

#include <filesystem>

using namespace std;

void renderImage(SDL_Renderer* rend, string filename);
void renderBackground(SDL_Renderer*);
void main2();
void main3();
const int SCREEN_WIDTH  = 1000;
const int SCREEN_HEIGHT = 1000;

int main(int argc, char* argv[])
{
	/*main2();
	return 0;*/

	bool close = false;

	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window* window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);

	// triggers the program that controls your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);

	// clears the screen
	SDL_RenderClear(rend);

	//renderBackground(rend);
	string filename = "images/boards/board.jpg";
	renderImage(rend, filename);

	SDL_RenderPresent(rend);

	while (!close) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				// handling of close button
				close = true;
				break;
			}
		}

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}


	// destroy texture
	//SDL_DestroyTexture(tex);

	// destroy renderer
	SDL_DestroyRenderer(rend);

	// destroy window
	SDL_DestroyWindow(window);

	// close SDL
	SDL_Quit();
	
	return 0;

}

void renderImage(SDL_Renderer* rend, string filename) {

	SDL_Surface* image = IMG_Load(filename.c_str());

	if (image == NULL) {
		std::cout << "couldnt load " << filename << std::endl;
		cout << IMG_GetError() << endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, image);

	// loads image to our graphics hardware memory.
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, image);

	SDL_RenderCopy(rend, texture, NULL, NULL);
	SDL_RenderPresent(rend);

}

void renderBackground(SDL_Renderer* rend)
{
	bool white = true;
	SDL_SetRenderDrawColor(rend , 255, 255, 255, 255);

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (white){
				SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
			}else{
				SDL_SetRenderDrawColor(rend, 155, 103, 60, 255);
			}
			white = !white;
			SDL_Rect rectangle ={ i * SCREEN_WIDTH / 8,
								  j * SCREEN_HEIGHT / 8,
								  SCREEN_WIDTH / 8,
								  SCREEN_HEIGHT / 8 };
			SDL_RenderFillRect(rend, &rectangle);
		}
		white = !white;
	}
}

void main2() {

//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_timer.h>

		// returns zero on success else non-zero
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			printf("error initializing SDL: %s\n", SDL_GetError());
		}

		IMG_Init(IMG_INIT_JPG);

		SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1000, 1000, 0);

		// triggers the program that controls
		// your graphics hardware and sets flags
		Uint32 render_flags = SDL_RENDERER_ACCELERATED;

		// creates a renderer to render our images
		SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

		// creates a surface to load an image into the main memory
		SDL_Surface* surface = NULL;

		SDL_RenderClear(rend);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderPresent(rend);

		// please provide a path for your image
		filesystem::path path = filesystem::absolute("images/pieces/wq.png");
		string filename = path.string();

		surface = IMG_Load(filename.c_str());

		if (surface == NULL)
		{
			std::cout << "couldnt load " << filename << std::endl;
			cout << IMG_GetError() << endl;
		}

		// loads image to our graphics hardware memory.
		SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

		// clears main-memory
		SDL_FreeSurface(surface);

		// let us control our image position
		// so that we can move it with our keyboard.
		SDL_Rect dest = { SCREEN_WIDTH / 8 ,
					  SCREEN_HEIGHT / 8 ,
					  SCREEN_WIDTH / 8,
					  SCREEN_HEIGHT / 8 };

		// connects our texture with dest to control position
		SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

		//// adjust height and width of our image box.
		//dest.w /= 6;
		//dest.h /= 6;

		// sets initial x-position of object
		dest.x = (1000 - dest.w) / 2;

		// sets initial y-position of object
		dest.y = (1000 - dest.h) / 2;

		// controls animation loop
		int close = 0;

		// speed of box
		int speed = 300;

		// animation loop
		while (!close) {
			SDL_Event event;

			// Events management
			while (SDL_PollEvent(&event)) {
				switch (event.type) {

				case SDL_QUIT:
					// handling of close button
					close = 1;
					break;

				case SDL_KEYDOWN:
					// keyboard API for key pressed
					switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_UP:
						dest.y -= speed / 30;
						break;
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT:
						dest.x -= speed / 30;
						break;
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_DOWN:
						dest.y += speed / 30;
						break;
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT:
						dest.x += speed / 30;
						break;
					default:
						break;
					}
				}
			}

			// right boundary
			if (dest.x + dest.w > 1000)
				dest.x = 1000 - dest.w;

			// left boundary
			if (dest.x < 0)
				dest.x = 0;

			// bottom boundary
			if (dest.y + dest.h > 1000)
				dest.y = 1000 - dest.h;

			// upper boundary
			if (dest.y < 0)
				dest.y = 0;

			//// clears the screen
			//SDL_RenderClear(rend);
			//SDL_RenderCopy(rend, tex, NULL, &dest);

			//// triggers the double buffers
			//// for multiple rendering
			//SDL_RenderPresent(rend);

			/**********************/
			SDL_Rect src = { 0, 0, 60, 60 };

			SDL_Rect dest = { SCREEN_WIDTH / 8 ,
							  SCREEN_HEIGHT / 8 ,
							  SCREEN_WIDTH / 8,
							  SCREEN_HEIGHT / 8 };
			SDL_RenderCopy(rend, tex, &src, &dest);
			SDL_RenderPresent(rend);
			SDL_UpdateWindowSurface(win);
			/**********************/

			// calculates to 60 fps
			SDL_Delay(1000 / 60);
		}

		// destroy texture
		SDL_DestroyTexture(tex);

		// destroy renderer
		SDL_DestroyRenderer(rend);

		// destroy window
		SDL_DestroyWindow(win);

		// close SDL_Image
		IMG_Quit();

		// close SDL
		SDL_Quit();

}

void main3() {


	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);

	SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	//SDL_Surface* image = IMG_Load("images/boards/board.png");
	SDL_Surface* image = IMG_Load("images/test.jpg");
	

	if (image == NULL)
	{
		std::cout << "couldnt load " << std::endl;
		cout << filesystem::current_path() << endl;
		cout << IMG_GetError() << endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

}