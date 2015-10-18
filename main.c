#include <stdbool.h>
#include <stdio.h>

#include <SDL_image.h>


int main(int argc, char *argv[])
{
	SDL_Surface *s = NULL;
	SDL_Texture *t = NULL;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	// Check args
	if (argc != 2)
	{
		printf("Usage: sdl2_image_test <filename>\n");
		goto bail;
	}

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init error: %s\n", SDL_GetError());
		goto bail;
	}

	// Load image from file
	s = IMG_Load(argv[1]);
	if (s == NULL)
	{
		printf("Failed to load image from file %s\n", argv[1]);
		goto bail;
	}

	// Create display window based on image size
	window = SDL_CreateWindow(
		argv[1], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		s->w, s->h, 0);
	if (window == NULL)
	{
		printf("Failed to create window: %s\n", SDL_GetError());
		goto bail;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		goto bail;
	}
	SDL_RenderSetLogicalSize(renderer, s->w, s->h);

	// Convert to texture
	t = SDL_CreateTextureFromSurface(renderer, s);
	if (t == NULL)
	{
		printf("Failed to convert surface: %s\n", SDL_GetError());
		goto bail;
	}

	// Blit the texture to screen
	if (SDL_RenderCopy(renderer, t, NULL, NULL) != 0)
	{
		printf("Failed to blit surface: %s\n", SDL_GetError());
		goto bail;
	}

	// Display
	SDL_RenderPresent(renderer);

	// Wait for keypress to exit
	bool quit = false;
	while (!quit)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		SDL_Delay(100);
	}


bail:
	SDL_DestroyTexture(t);
	SDL_FreeSurface(s);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
