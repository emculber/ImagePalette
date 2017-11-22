#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    int pollingDelay = 100;
  int quit = 0;
  SDL_Event event;

  int width = 640;
  int height = 480;

  SDL_Rect top_image;
  top_image.w = width;
  top_image.h = height/2;
  top_image.x = 0;
  top_image.y = 0;

  SDL_Rect bottom_image;
  bottom_image.w = width;
  bottom_image.h = height/2;
  bottom_image.x = 0;
  bottom_image.y = height/2;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  //SDL_Surface * image = SDL_LoadBMP("image.bmp");
  SDL_Surface * image = IMG_Load("sample.jpg");
  //SDL_Surface * new_image = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  SDL_Surface * new_image = IMG_Load("sample.jpg");
  Uint32 *pixels = (Uint32 *)new_image->pixels;
  
  int h = image->h;
  int w = image->w;
  int w0 = image->pitch * image->format->BytesPerPixel;

  uint8_t r;
  uint8_t g;
  uint8_t b;

  fprintf(stderr, "Width: %i (%i), Height: %i\n", w, w0, h);

    return 0;
  SDL_LockSurface(new_image);
   for(int y=0; y<h; y++) {
    for(int x=0; x<w; x++) {
      int index = (y*w) + x;
      SDL_GetRGB(pixels[index], new_image->format ,  &r, &g, &b);
      //b += 100;
      //if(b > 255) {
      //  b=255;
      //}
      //fprintf(stderr, "Set Pixel\n");
      pixels[index] = SDL_MapRGB(new_image->format, g, b, r);
      fprintf(stderr, "(%i,%i) Access Point: %i, Red: %i, Green: %i, Blue: %i\n",x, y, index, r, g, b);
      //usleep(pollingDelay*100);
    }
       if(y==800) {
           break;
       }
  }
    
    fprintf(stderr, "(%i,%i)\n",h, (h * w0));
  SDL_UnlockSurface(new_image);

  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_Texture * texture2 = SDL_CreateTextureFromSurface(renderer, new_image);

  while (!quit)
  {
    SDL_WaitEvent(&event);

    switch (event.type)
    {
      case SDL_QUIT:
        quit = 1;
        break;
    }

    //SDL_Rect dstrect = { 5, 5, 320, 240 };
    //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderCopy(renderer, texture, NULL, &top_image);
    SDL_RenderCopy(renderer, texture2, NULL, &bottom_image);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}



/*
#include <stdio.h>
#include <stdlib.h>

int main (int argc , char * argv [] ){
  FILE *file;
  FILE *fptr;
  unsigned char *buffer;
  unsigned long fileLen;

  //Open file
  file = fopen("./sample.jpg", "rb");
  fptr = fopen("test.jpg", "wb");
  if (!file) { 
    fprintf(stderr, "Unable to open file %s", "simple.jpg");
    return 0;
  }

  //Get file length
  fseek(file, 0, SEEK_END);
  fileLen=ftell(file);
  fseek(file, 0, SEEK_SET);

  fprintf(stderr, "File Length:%lu\n", fileLen);

  //Allocate memory
  buffer=(unsigned char *)malloc(fileLen);
  if (!buffer) {
    fprintf(stderr, "Memory error!");
    fclose(file);
    return 1;
  }

  fread(buffer,fileLen,sizeof(unsigned char),file);
  fclose(file);

  unsigned int x, y;
  for(y = 0; y < h; ++y)
  {
    for(x = 0; x < w; ++x, pixel += 3)
    {
      const byte red = pixel[0], green = pixel[1], blue = pixel[2];

      /* Do something with the current pixel. /
    }
  }

  int i=0;
  while (i < fileLen) {
    printf("%02X ",((unsigned char)buffer[i]));
    i++;
    if( ! (i % 32) ) {
      //printf( "\n");
    }
  }
  /*
     i = 100;
     while (i < 110) {
     i++;
     }
     /

  fwrite(buffer,1, fileLen,fptr); 

  printf("Buffer Size: %lu\n", sizeof(buffer));
  printf("Buffer 0: %d\n", buffer[0]);
  printf("Buffer 1: %d\n", buffer[1]);

  printf("\nTotal number of pixels: %d\n", i);
  fclose(fptr);

  file = fopen("test.jpg", "rb");
  fseek(file, 0, SEEK_END);
  fileLen=ftell(file);
  fseek(file, 0, SEEK_SET);
  fprintf(stderr, "File Length:%lu\n", fileLen);

  printf("Buffer Size: %lu\n", sizeof(buffer));
  printf("Buffer: %d\n", buffer[0]);
  printf("Buffer: %d\n", buffer[1]);
  return 0;
}
*/
