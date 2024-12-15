#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 640
#define wysokosc 400

#define tytul "SM2024 - Lab 6 - Zietek Piotr"


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

//int nieskompresowane[] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 8, 8, 8, 8, 8, 2, 2, 1, 3};
void ByteRunKompresja(int wejscie[], int dlugosc){
    
    int i = 0;

    while (i < dlugosc){
        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1])){
            int j = 0;
            while((i+  j < dlugosc - 1) && (wejscie[i + j] == wejscie[i + 1 + j])
            && (j < 127)){
                j++;
            }

            cout<<"("<< -j << "), " << (int)wejscie[i + j] << ", ";
            
            i += (j+1);
        } else {
            int j = 0;
            while((i + j < dlugosc - 1) && ((wejscie[i + j] != wejscie[i + j + 1])) 
            && (j < 128)){
                j++;
            }

            if((i+j == dlugosc - 1) && (j < 128)){
                j++;
            }

            cout<<"("<< (j - 1) << "), ";
            for(int k = 0; k < j; k++){
                cout << (int)wejscie[i + k] << ", ";
            }

            i += j;
        }
    }
}

void ByteRunDekompresja(int wejscie[], int dlugosc){
    int j = 0;
    while (j < dlugosc){
        if(wejscie[j] < 0){
            int iters = (-1) * wejscie[j] + 1;
            j++;
            for(int i = 0; i < iters; i ++){
                std::cout << wejscie[j] << ", ";
            }
        } else {
            int iters = wejscie[j] + 1;
            for(int i = 0; i < iters; i ++){
                j++;
                std::cout << wejscie[j] << ", ";
            }
        }
        j++;
    }
}

//int nieskompresowane[] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 7, 7, 8, 8, 8, 8, 8, 8, 2, 2, 1, 3, 1, 2};
void RLEKompresja(int wejscie[], int dlugosc){
    
    int i = 0;

    while (i < dlugosc) {

        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1])){
            
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] == wejscie[i + j + 1]) 
            && (j < 254)){
                j++;
            }

            cout<<"("<<(j + 1)<<"), " << wejscie[i+j]<<", ";

            i += (j+1);
        } else {
            
            int j = 0;

            while ((i + j < dlugosc - 1) && (wejscie[i + j] != wejscie[i + j + 1]) 
            && (j < 254)){
                j++;
            }

            if( (i+j == dlugosc - 1) && (j < 254)){
                j++;
            }

            cout << (int) 0 << ", " << j << ", ";
            
            for(int k = 0; k < j; k++){
                cout << wejscie[i + k] << ", ";
            }

            if (j % 2 != 0){
                cout << (int) 0 << ", ";
            }

            i += j;
        }
    }
}

//int skompresowane[] = {5, 0, 0, 5, 1, 2, 3, 4, 5, 0, 3, 7, 6, 8, 2, 2, 0, 4, 1, 3, 1, 2};
void RLEDekompresja(int wejscie[], int dlugosc){
    int j = 0;
    while (j < dlugosc){
        //std::cout <<"W" << wejscie[j] << " ";
        if(wejscie[j] > 0){
            int iter = wejscie[j];
           // std::cout <<"I" << iter << " ";
            j++;
            for(int i = 0; i < iter; i++){
                std::cout << wejscie[j] << ", ";
            }
        } else if ( wejscie[j] == 0){
            j++;
            int iter = wejscie[j];
            for(int i = 0; i < iter; i++){
                j++;
                std::cout << wejscie[j] << ", ";
            }

            if(iter % 2 != 0){
                j++;
            }
        }
        j++;
    }
}

void Funkcja1() {
    int nieskompresowane[] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 8, 8, 8, 8, 8, 2, 2, 1, 3};
    int dlugosc = 24;
    std::cout << "Wejscie" << std::endl;
    for(int c = 0; c < dlugosc; c++){
        std::cout << (int)nieskompresowane[c]<<", ";
    }
    std::cout << "\n";

    std::cout << "Skompresowane wyjscie (ByteRun)" << std::endl;
    ByteRunKompresja(nieskompresowane, dlugosc);
    std::cout << "\n";

    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {
    int nieskompresowane[] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 7, 7, 8, 8, 8, 8, 8, 8, 2, 2, 1, 3, 1, 2};
    int dlugosc = 25;
    std::cout << "Wejscie" << std::endl;
    for(int c = 0; c < dlugosc; c++){
        std::cout << (int)nieskompresowane[c]<<", ";
    }
    std::cout << "\n";

    std::cout << "Skompresowane wyjscie (RLE)" << std::endl;
    RLEKompresja(nieskompresowane, dlugosc);
    std::cout << "\n";

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {
    int skompresowane[] = {-4, 0, 5, 1, 2, 3, 4, 5, 6, -2, 7, -5, 8, -1, 2, 0, 1};
    int dlugosc = 17;
    std::cout << "Skompresowane wejscie: (ByteRun)" << std::endl;
    
    for (int c = 0; c < dlugosc; c++){
        std::cout << (int) skompresowane[c] << ", ";
    }

    std::cout << "\n";
    std::cout << "Wyjscie: " << std::endl;
    ByteRunDekompresja(skompresowane, dlugosc);
    std::cout << "\n";
    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {
    int skompresowane[] = {5, 0, 0, 5, 1, 2, 3, 4, 5, 0, 3, 7, 6, 8, 2, 2, 0, 4, 1, 3, 1, 2};
    int dlugosc = 22;
    std::cout << "Skompresowane wejscie: (RLE)" << std::endl;
    
    for (int c = 0; c < dlugosc; c++){
        std::cout << (int) skompresowane[c] << ", ";
    }

    std::cout << "\n";
    std::cout << "Wyjscie: " << std::endl;
    RLEDekompresja(skompresowane, dlugosc);
    std::cout << "\n";
    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {

    //...

    SDL_UpdateWindowSurface(window);
}




void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B) {

    int dx = x2-x1;
    int dy = y2-y1;

    int kx = 1;
    int ky = 1;

    if (dx<0) {
        dx = x1-x2;
        kx = -1;
    }

    if (dy<0) {
        dy = y1-y2;
        ky = -1;
    }

    int d = 0;

    int x = x1; //
    int y = y1; //

    setPixel(x, y, R, G, B);

    if (dx >= dy) {
        d = 2*dy - dx;

        while (x != x2) {
            if (d >=0) {
                x+=kx;
                y+=ky;
                d = d + 2*(dy-dx);
            }
            else {
                x+=kx;
                d = d + 2*dy;
            }
            setPixel(x, y, R, G, B);
        }
    }
    else {
        d = 2*dx - dy;
        while (y != y2) {
            if (d >= 0) {
                y+=ky;
                x+=kx;
                d = d + 2*(dx-dy);
            }
            else {
                y+=ky;
                d = d + 2*dx;
            }
            setPixel(x, y, R, G, B);
        }

    }

    SDL_UpdateWindowSurface(window);
}


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y)
{
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc*2, wysokosc*2, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
    return false;
    }
    SDL_UpdateWindowSurface(window);


    bool done = false;
    SDL_Event event;
    // główna pętla programu
    while (SDL_WaitEvent(&event)) {
        // sprawdzamy czy pojawiło się zdarzenie
        switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;

            // sprawdzamy czy został wciśnięty klawisz
            case SDL_KEYDOWN: {
                // wychodzimy, gdy wciśnięto ESC
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                if (event.key.keysym.sym == SDLK_1)
                    Funkcja1();
                if (event.key.keysym.sym == SDLK_2)
                    Funkcja2();
                if (event.key.keysym.sym == SDLK_3)
                    Funkcja3();
                if (event.key.keysym.sym == SDLK_4)
                    Funkcja4();
                if (event.key.keysym.sym == SDLK_5)
                    Funkcja5();
                if (event.key.keysym.sym == SDLK_6)
                    Funkcja6();
                if (event.key.keysym.sym == SDLK_7)
                    Funkcja7();
                if (event.key.keysym.sym == SDLK_8)
                    Funkcja8();
                if (event.key.keysym.sym == SDLK_9)
                    Funkcja9();
                if (event.key.keysym.sym == SDLK_a)
                    ladujBMP("obrazek1.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_s)
                    ladujBMP("obrazek2.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_d)
                    ladujBMP("obrazek3.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_f)
                    ladujBMP("obrazek4.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_g)
                    ladujBMP("obrazek5.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_h)
                    ladujBMP("obrazek6.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_b)
                    czyscEkran(0, 0, 0);
                else
                    break;
               }
        }
        if (done) break;
    }

    if (screen) {
        SDL_FreeSurface(screen);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }


    SDL_Quit();
    return 0;
}
