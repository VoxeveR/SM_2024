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

#define tytul "SM2024 - Lab 7 - Zietek Piotr"


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

struct slowo {
    Uint16 kod = 0;
    Uint8 dlugosc = 0;
    Uint8 element[4096];
    bool wSlowniku = false;
};

int rozmiarSlownika = 0;
slowo slownik[65535];

slowo noweSlowo(){
    slowo noweSlowo;
    noweSlowo.kod = 0;
    noweSlowo.dlugosc = 0;
    noweSlowo.wSlowniku = false;
    return noweSlowo;
}

slowo noweSlowo(Uint8 znak){
    slowo noweSlowo;
    noweSlowo.kod = 0;
    noweSlowo.dlugosc = 1;
    noweSlowo.element[0] = znak;
    noweSlowo.wSlowniku = false;
    return noweSlowo;
}

slowo polaczSlowo(slowo aktualneSlowo, Uint8 znak){
    slowo noweSlowo;

    if(aktualneSlowo.dlugosc < 4096){
        noweSlowo.kod = 0;
        noweSlowo.dlugosc = aktualneSlowo.dlugosc + 1;
        noweSlowo.wSlowniku = false;
        copy(begin(aktualneSlowo.element), end(aktualneSlowo.element), begin(noweSlowo.element));
        noweSlowo.element[aktualneSlowo.dlugosc] = znak;
        return noweSlowo;
    } else {
        std::cout << "UWAGA! Przepelnienie rozmiar uznakow w pojedynczym slowie" << std::endl;
        noweSlowo.kod = 0;
        noweSlowo.dlugosc = 0;
        noweSlowo.wSlowniku = false;
        noweSlowo.element[0] = znak;
        return noweSlowo;
    }
}

bool porownajSlowa(slowo slowo1, slowo slowo2){
    if (slowo1.dlugosc != slowo2.dlugosc) return false;
    for (int s = 0; s < slowo1.dlugosc; s++){
        if(slowo1.element[s] != slowo2.element[s]) return false;
    }
    return true;
}

int znajdzWSlowniku(slowo szukany){
    for (int nr = 0; nr < rozmiarSlownika; nr++){
        if (porownajSlowa(slownik[nr], szukany)) return nr;
    }
    return -1;
}

void wyswietlSlowo(slowo aktualneSlowo){
    if(aktualneSlowo.wSlowniku){
        std::cout << "[" << aktualneSlowo.kod << "] ";
    } else {
        std::cout << "[X]";
    }
    for (int s = 0; s < aktualneSlowo.dlugosc; s++){
        std::cout << (int)aktualneSlowo.element[s];
        if(s < aktualneSlowo.dlugosc - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void wyswietlSlownik() {
    std::cout << "Slownik:" << std::endl;
    for (int i = 0; i < rozmiarSlownika; i++) {
        wyswietlSlowo(slownik[i]);
    }
    std::cout << "Liczba slow w slowniku: " << rozmiarSlownika << std::endl;
}

int dodajDoSlownika(slowo nowy, bool czyWyswietlac = true){
    if (rozmiarSlownika < 65536){
        Uint16 nr = rozmiarSlownika;
        slownik[nr].kod = nr;
        slownik[nr].dlugosc = nowy.dlugosc;
        copy(begin(nowy.element), end(nowy.element), begin(slownik[nr].element));
        slownik[nr].wSlowniku = true;
        if (czyWyswietlac) wyswietlSlowo(slownik[nr]);
        rozmiarSlownika++;
        return nr;
    }
    return -1;
}

void LZWinicjalizacja(){
    rozmiarSlownika = 0;

    for(int s = 0; s < 65536; s++){
        slownik[s].kod = 0;
        slownik[s].dlugosc = 0;
        slownik[s].wSlowniku = false;
        memset(slownik[s].element, 0, sizeof(slownik[s].element));
    }

    slowo noweSlowo;
    for(int s = 0; s < 4; s++){
        noweSlowo.dlugosc = 1;
        noweSlowo.element[0] = s;
        noweSlowo.kod = dodajDoSlownika(noweSlowo);
    }
}


void LZWKompresja(int wejscie[], int dlugosc){
    LZWinicjalizacja();
    slowo aktualneSlowo = noweSlowo();
    slowo slowoZnak;
    Uint8 znak;
    int kod;
    int i = 0;

    while (i < dlugosc){
        znak = wejscie[i];
        std::cout << "Pobieramy znak " << (int)znak << " z pozycji " << i << std::endl;
        slowoZnak = polaczSlowo(aktualneSlowo, znak);
        std::cout << "Aktualne slowo: ";
        wyswietlSlowo(aktualneSlowo);
        std::cout << "Slowo + znak: ";
        wyswietlSlowo(slowoZnak);
        kod = znajdzWSlowniku(slowoZnak);
        std::cout << "Czy w slowniku? ";
        if (kod < 0){
            std::cout << "NIE" <<std::endl;
            std::cout << "Na wyjscie: [" << aktualneSlowo.kod << "]" << std::endl;
            dodajDoSlownika(slowoZnak, false);
            if(znajdzWSlowniku(slowoZnak) > 0){
                slowoZnak.kod = znajdzWSlowniku(slowoZnak);
                std::cout << "Dodajemy do slownika ";
                wyswietlSlowo(slownik[slowoZnak.kod]);
            }
            aktualneSlowo = noweSlowo(znak);
            aktualneSlowo.kod = znajdzWSlowniku(aktualneSlowo);
            aktualneSlowo.wSlowniku = true;
        } else {
            std::cout << "TAK: [" << kod << "]" << std::endl;
            aktualneSlowo = slowoZnak;
            aktualneSlowo.kod = znajdzWSlowniku(aktualneSlowo);
            aktualneSlowo.wSlowniku = true;
        }
        i++;
    }
    std::cout << "Koniec danych" << std::endl;
    std::cout << "Na wyjscie: [" << aktualneSlowo.kod << "]" << std::endl;
    std::cout << std::endl;
    std::cout << "Aktualny slownik:" << std::endl;
    wyswietlSlownik();
}

//doesnt work
void LZWDekompresja(int wejscie[], int dlugosc) {
    LZWinicjalizacja();

    slowo poprzednieSlowo;
    slowo aktualneSlowo;

    for (int i = 0; i < dlugosc; i++) {
        int kod = wejscie[i];
        std::cout << "na wyjscie: [" << kod << "] ";

        if (kod < rozmiarSlownika) {
            aktualneSlowo = slownik[kod];
        } else if (kod == rozmiarSlownika && poprzednieSlowo.dlugosc > 0) {
            aktualneSlowo = polaczSlowo(poprzednieSlowo, poprzednieSlowo.element[0]);
        } else {
            std::cout << "Blad: nieprawidlowy kod" << std::endl;
            return;
        }

        for (int j = 0; j < aktualneSlowo.dlugosc; j++) {
            cout << (int)aktualneSlowo.element[j];
            if (j < aktualneSlowo.dlugosc - 1) cout << ", ";
        }
    
        std::cout << std::endl;

        if (poprzednieSlowo.dlugosc > 0) {
            slowo noweSlowo = polaczSlowo(poprzednieSlowo, aktualneSlowo.element[0]);
            std::cout << "Nowy element slownika: ";
            wyswietlSlowo(noweSlowo);
            dodajDoSlownika(noweSlowo, true);
        }
        std::cout << "poprzednieslowo: "; 
        wyswietlSlowo(poprzednieSlowo);
        std::cout << "aktualneSlowo: "; 
        wyswietlSlowo(aktualneSlowo);
        poprzednieSlowo = aktualneSlowo;

        std::cout << std::endl;
    }

    std::cout << "koniec danych" << std::endl;
    std::cout << std::endl;
    std::cout << "aktualny slownik:" << std::endl;
    wyswietlSlownik();
}

void Funkcja1() {
    int nieskompresowane[] = {0, 0, 0, 1, 1, 1, 1, 2, 0, 0, 3, 1, 3,
    2, 2, 0, 0, 0, 3, 3, 3, 3, 1, 2, 1, 2, 3, 1, 2, 0, 0, 1, 1, 1, 3, 3};
    int dlugosc = 36;
    std::cout << "wejscie:" << std::endl;
    for(int c = 0; c < dlugosc; c++){
        std::cout << (int)nieskompresowane[c] << ", ";
    }
    std::cout << std::endl;
    LZWKompresja(nieskompresowane, dlugosc);
    cout << std::endl;

    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {
    int skompresowane[] = {0, 4, 1, 6, 1, 2, 4, 3, 1, 3, 2, 9, 10, 3, 17, 8, 8, 11, 15, 7, 17};
    std::cout << "Skompresowane wejscie (LZW):" << std::endl;
    int dlugosc = 21;
    for (int c = 0; c < dlugosc; c++) std::cout << (int)skompresowane[c] <<", ";
    std::cout << std::endl;
    std::cout << "Wyjscie:" << std::endl;
    LZWDekompresja(skompresowane, dlugosc);
    std::cout << std::endl;
    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {
   
    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {
    
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
