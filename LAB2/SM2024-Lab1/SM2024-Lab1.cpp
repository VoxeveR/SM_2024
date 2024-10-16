#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <cmath>
using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 640
#define wysokosc 400

#define tytul "SM2024 - Lab 2 - Zietek Piotr"

struct HSL{
    float H;
    float S;
    float L;
};

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void setHSL(int xx, int yy, float h, float s, float l);
SDL_Color HSLtoRGB(float h, float s, float l);
HSL getHSL(int xx, int yy);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();


void Funkcja1() {

    for(int x = 0; x < szerokosc/2; x++){
        for(int y = 0; y < wysokosc/2; y++){
            HSL color = getHSL(x, y);

            setHSL(x+szerokosc/2,y+wysokosc/2, color.H, color.S, color.L);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {

    for(int x = 0; x < szerokosc/2; x++){
        for(int y = 0; y < wysokosc/2; y++){
            //HSL color = getHSL(x, y);

            setHSL(x+szerokosc/2,y, 197, 67, 28);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    //...

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

void setHSL(int xx, int yy, float h, float s, float l){
    SDL_Color colorRGB = HSLtoRGB(h, s, l);

    setPixel(xx, yy, colorRGB.r, colorRGB.g, colorRGB.b);
}

SDL_Color HSLtoRGB(float h, float s, float l){
    SDL_Color RGBret;
    float zmienna1, zmienna2, barwa;
    float zmiennaR, zmiennaG, zmiennaB;

    if(s == 0){
        RGBret.r = (l) * 255;
        RGBret.g = (l) * 255;
        RGBret.b = (l) * 255;
    } else {
            if (l < 50){
                zmienna1 = l * (1.0 + s);
            } else if (l >= 50){
                zmienna1 = l + s - l * s;
            }

            zmienna2 = 2 * l - zmienna1;
            barwa = h/360;

            zmiennaR = barwa + 0.333;
            if (zmiennaR > 1){
                zmiennaR -= 1;
            } else if (zmiennaR < 0){
                zmiennaR += 1;
            }

            zmiennaG = barwa;
            if (zmiennaG > 1){
                zmiennaG -= 1;
            } else if (zmiennaG < 0){
                zmiennaG += 1;
            }

            zmiennaB = barwa - 0.333;
            if (zmiennaB > 1){
                zmiennaB -= 1;
            } else if (zmiennaB < 0){
                zmiennaB += 1;
            }

            float czerwony;
            if((6 * zmiennaR) < 1){
                czerwony = zmienna2 + (zmienna1 - zmienna2) * 6 * zmiennaR;
            } else if((2 * zmiennaR) < 1 ){
                    czerwony = zmienna1;
            } else if((3 * zmiennaR) < 2) {
                    czerwony = zmienna2 + (zmienna1 - zmienna2) * (0.666 - zmiennaR) * 6;
            } else {
                    czerwony = zmienna2;
            }

            float zielony;
             if((6 * zmiennaG) < 1){
               zielony = zmienna2 + (zmienna1 - zmienna2) * 6 * zmiennaG;
            } else if((2 * zmiennaG) < 1 ){
                    zielony = zmienna1;
            } else if((3 * zmiennaG) < 2) {
                    zielony = zmienna2 + (zmienna1 - zmienna2) * (0.666 - zmiennaG) * 6;
            } else {
                    zielony = zmienna2;
            }


            float niebieski;
             if((6 * zmiennaB) < 1){
                niebieski = zmienna2 + (zmienna1 - zmienna2) * 6 * zmiennaB;
            } else if((2 * zmiennaB) < 1 ){
                    niebieski = zmienna1;
            } else if((3 * zmiennaB) < 2) {
                    niebieski = zmienna2 + (zmienna1 - zmienna2) * (0.666 - zmiennaB) * 6;
            } else {
                    niebieski = zmienna2;
            }
            //std::cout<<h<<" "<< s << " " << l<< std::endl;

            float roundedR = (int)(czerwony * 100 + .5);
            float roundedG = (int)(zielony * 100 + .5);
            float roundedB = (int)(niebieski * 100 + .5);

            RGBret.r = std::ceil(czerwony * 255);
            RGBret.g = std::ceil(zielony * 255);
            RGBret.b = std::ceil(niebieski * 255);
    }

    //std::cout<<"PO " <<(int)RGBret.r << " " << (int)RGBret.g << " " << (int)RGBret.b << std::endl;

    return RGBret;
}

HSL getHSL(int xx, int yy){
    SDL_Color colorRGB = getPixel(xx, yy);
    float r, g, b, mmin, mmax;
    HSL HSLret;
   //std::cout<<"PRZED "<< " "<< (int)colorRGB.r << " " << (int)colorRGB.g << " " << (int)colorRGB.b << std::endl;
    r = colorRGB.r*1.0/255;
    g = colorRGB.g*1.0/255;
    b = colorRGB.b*1.0/255;

   // std::cout << "PRZED: " << r << " " << g << " " << b << std::endl;

    mmin = min(r,(min(g,b)));
    mmax = max(r,(max(g,b)));

   // std::cout<< mmin << " " << mmax << std::endl;
    HSLret.L = (mmin+mmax)/2;
  //  HSLret.L = (int) HSLret.L * 100 + .5;

    if(mmin==mmax){
        HSLret.S = 0;
    } else if(HSLret.L <= 0.5){
        HSLret.S = (mmax-mmin) / (mmax+mmin);
    } else if (HSLret.L > 0.5){
        HSLret.S = (mmax-mmin) / (2.0 - mmax - mmin);
    }

    if(r == mmax){
        HSLret.H = (g - b) / (mmax-mmin);
    } else if(g = mmax){
        HSLret.H = 2.0 + (b - r) / (mmax-mmin);
    } else{
        HSLret.H = 4.0 + (r - b) / (mmax-mmin);
    }

    HSLret.H *= 60;

    if(HSLret.H < 0){
        HSLret.H += 360;
    }
   // std::cout << "PO: " << HSLret.H << " " << HSLret.S << " " << HSLret.L << std::endl;

   // std::cout<< HSLret.H << " " << HSLret.S << " " << HSLret.L << std::endl;

    return HSLret;
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
    /* Zamieniamy poszczeg�lne sk�adowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informacj� ile bajt�w zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy warto�� piksela, w zale�no?ci od formatu powierzchni*/
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
    /* Zamieniamy poszczeg�lne sk�adowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informacj� ile bajt�w zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy warto�� piksela, w zale�no�ci od formatu powierzchni*/
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
        //okre�lamy pozycj�
        char* pPosition=(char*)screen->pixels ;

        //przesuni�cie wzgl�dem y
        pPosition+=(screen->pitch*y*2) ;

        //przesuni�cie wzgl�dem x
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
        //okre�lamy pozycj�
        char* pPosition=(char*)surface->pixels ;

        //przesuni�cie wzgl�dem y
        pPosition+=(surface->pitch*y) ;

        //przesuni�cie wzgl�dem x
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
    // g��wna p�tla programu
    while (SDL_WaitEvent(&event)) {
        // sprawdzamy czy pojawi�o si� zdarzenie
        switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;

            // sprawdzamy czy zosta� wci�ni�ty klawisz
            case SDL_KEYDOWN: {
                // wychodzimy, gdy wci�ni�to ESC
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
