#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 640
#define wysokosc 400

#define tytul "SM2024 - Lab 9 - Zietek Piotr"


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

const int rozmiarBloku = 16;

struct macierz {
    float dct[rozmiarBloku][rozmiarBloku];
    Uint8 dane[rozmiarBloku][rozmiarBloku];
};


void wyswietlDane(macierz blok)
{
    cout << "Dane pikselowe w macierzy:"<<endl;
    for(int i = 0; i < rozmiarBloku; i++)
    {
        for(int j = 0; j < rozmiarBloku; j++)
        {
            cout << setw(4) << (int)blok.dane[j][i]<<" ";
        }
        cout << endl;
    }
}


void wyswietlDCT(macierz blok)
{
    cout << "Wspolczynniki transformaty w macierzy:" << endl;
    for(int i = 0; i < rozmiarBloku; i++)
    {
        for(int j = 0; j < rozmiarBloku; j++)
        {
            cout << fixed << setw(6) << setprecision(2) << blok.dct[j][i]<<" ";
        }
        cout << endl;
    }
}

macierz dct(Uint8 wartosci[rozmiarBloku][rozmiarBloku])
{
    float wynik[rozmiarBloku][rozmiarBloku];

    for(int v = 0; v < rozmiarBloku; ++v)
    {
        for(int u = 0; u < rozmiarBloku; ++u)
        {
            const double cu = (u == 0) ? 1.0 / sqrt(2) : 1.0;
            const double cv = (v == 0) ? 1.0 / sqrt(2) : 1.0;
            double wspolczynnikDCT = 0;

            for(int y = 0; y < rozmiarBloku; ++y)
            {
                for(int x = 0; x < rozmiarBloku; ++x)
                {
                    double uCosFactor = cos( (double)(2*x+1)*M_PI*(double)u / (2*(double)rozmiarBloku) );
                    double vCosFactor = cos( (double)(2*y+1)*M_PI*(double)v / (2*(double)rozmiarBloku) );
                    double pixel = (double)wartosci[x][y];
                    wspolczynnikDCT += pixel*uCosFactor*vCosFactor;
                }

            }
            wspolczynnikDCT *= ( 2.0 / (double)rozmiarBloku ) * cu* cv;
            wynik[u][v] = wspolczynnikDCT;
        }
    }
    macierz rezultat;
    for( int j = 0; j < rozmiarBloku; j++)
    {
        for(int i = 0; i < rozmiarBloku; i++)
        {
            rezultat.dct[i][j] = wynik[i][j];
            rezultat.dane[i][j] = wartosci[i][j];
        }
    }
    return rezultat;
}

macierz idct(float DCT[rozmiarBloku][rozmiarBloku])
{
    int wynik[rozmiarBloku][rozmiarBloku];

    for(int x = 0; x < rozmiarBloku; ++x)
    {
        for(int y = 0; y < rozmiarBloku; ++y)
        {
            double pixel = 0;
            for(int u = 0; u < rozmiarBloku; ++u)
            {
                for(int v = 0; v < rozmiarBloku; ++v)
                {
                    const double cu = (u == 0) ? 1.0 / sqrt(2) : 1.0;
                    const double cv = (v == 0) ? 1.0 / sqrt(2) : 1.0;
                    double uCosFactor = cos( (double)(2*x+1)*M_PI*(double)u / (2*(double)rozmiarBloku) );
                    double vCosFactor = cos( (double)(2*y+1)*M_PI*(double)v / (2*(double)rozmiarBloku) );
                    double wspolczynnikDCT = DCT[u][v];
                    pixel += wspolczynnikDCT * uCosFactor * vCosFactor *cu * cv;
                }
            }
            pixel*= (2.0/(double)rozmiarBloku);
            wynik[x][y] = round(pixel);
        }
    }


    macierz rezultat;
    for(int j = 0; j < rozmiarBloku; j++)
    {
        for(int i = 0; i < rozmiarBloku; i++)
        {
            if(wynik[i][j] > 255) wynik[i][j] = 255;
            else if(wynik[i][j] < 0) wynik[i][j] = 0;

            rezultat.dane[i][j] = wynik[i][j];
            rezultat.dct[i][j] = DCT[i][j];
        }
    }
    return rezultat;
}

void Funkcja1() {

    float kolor = 0;
    for(int y = 0; y < rozmiarBloku; y++)
    {
        for(int x = 0; x < rozmiarBloku; x++)
        {
            setPixel(x+rozmiarBloku, y+rozmiarBloku, kolor, kolor, kolor);
            kolor += 256.0/(rozmiarBloku*rozmiarBloku);
        }
    }

    for(int y = 1; y < rozmiarBloku; y+=2)
    {
        for(int x = 1; x < rozmiarBloku; x+=2)
        {
            setPixel(x+3*rozmiarBloku, y+rozmiarBloku, 255, 255, 255);
            setPixel(x+3*rozmiarBloku-1, y+rozmiarBloku-1, 128, 128, 128);
            setPixel(x+3*rozmiarBloku, y+rozmiarBloku-1, 0,0,0);
            setPixel(x+3*rozmiarBloku-1, y+rozmiarBloku, 0, 0, 0);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {

    macierz blokDCT;
    macierz blokDane;
    macierz noweDane;

    for(int y = 0; y < rozmiarBloku; y++)
    {
        for(int x = 0; x < rozmiarBloku; x++)
        {
            blokDane.dane[x][y] = getPixel(x+rozmiarBloku, y+rozmiarBloku).r;
            blokDane.dct[x][y] = 0;
        }
    }
    wyswietlDane(blokDane);
    cout << endl;
    blokDCT = dct(blokDane.dane);
    wyswietlDCT(blokDCT);
    cout << endl;
    noweDane = idct(blokDCT.dct);
    wyswietlDane(noweDane);
    cout << endl;
    for(int y = 0; y < rozmiarBloku; y++)
    {
        for(int x = 0; x < rozmiarBloku; x++)
        {
            setPixel(x + rozmiarBloku, y + 3*rozmiarBloku, noweDane.dane[x][y], noweDane.dane[x][y], noweDane.dane[x][y]);
        }
    }

    cout << "Drugi blok" << endl;
    for(int y = 0; y < rozmiarBloku; y++)
    {
        for(int x = 0; x < rozmiarBloku; x++)
        {
            blokDane.dane[x][y] = getPixel(x+3*rozmiarBloku, y+rozmiarBloku).r;
            blokDane.dct[x][y] = 0;
        }
    }
    wyswietlDane(blokDane);
    cout << endl;
    blokDCT = dct(blokDane.dane);
    wyswietlDCT(blokDCT);
    cout << endl;
    noweDane = idct(blokDCT.dct);
    wyswietlDane(noweDane);
    cout << endl;
    for(int y = 0; y < rozmiarBloku; y++)
    {
        for(int x = 0; x < rozmiarBloku; x++)
        {
            setPixel(x + 3*rozmiarBloku, y + 3*rozmiarBloku, noweDane.dane[x][y], noweDane.dane[x][y], noweDane.dane[x][y]);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    SDL_Color kolor;
    uint8_t szary;
    for(int y = 0; y < wysokosc; y++)
    {
        for(int x = 0; x < szerokosc; x++)
        {
            kolor = getPixel(x,y);
            szary = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;
            setPixel(x, y, szary, szary, szary);

        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    for(int y = 0; y < wysokosc/2; y+=rozmiarBloku)
    {
        for(int x = 0; x < szerokosc/2; x+=rozmiarBloku)
        {
            macierz blokDCT;
            macierz blokDane;
            macierz noweDane;

            for(int i = 0; i < rozmiarBloku; i++)
            {
                for(int j = 0; j < rozmiarBloku; j++)
                {
                    blokDane.dane[j][i] = getPixel(x+j, y+i).r;
                    blokDane.dct[j][i] = 0;
                }
            }
            blokDCT = dct(blokDane.dane);
            for(int i = 0; i < rozmiarBloku; i++)
            {
                for(int j = 0; j < rozmiarBloku; j++)
                {
                    if(i > rozmiarBloku*0.75 && j > rozmiarBloku*0.75) blokDCT.dct[j][i] = 0;
                    else if(blokDCT.dct[j][i] != 0) blokDCT.dct[j][i] = round(blokDCT.dct[j][i]);

                }
            }
            noweDane = idct(blokDCT.dct);
            for(int i = 0; i < rozmiarBloku; i++)
            {
                for(int j = 0; j < rozmiarBloku; j++)
                {
                    setPixel(x + j + szerokosc/2, y + i, noweDane.dane[j][i], noweDane.dane[j][i], noweDane.dane[j][i]);
                }
            }
        }
    }

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
