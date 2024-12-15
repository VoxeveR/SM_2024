#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 640
#define wysokosc 400

#define tytul "SM2024 - Lab 8 - Zietek Piotr"


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


struct TokenLZ77 {
    int przesuniecie;    
    int dlugość;          
    char następnyZnak;    
};

#include <iostream>
#include <vector>
#include <tuple>

template <typename T>
void wypiszWektor(const std::vector<T>& wektor) {
    for (const T& element : wektor) {
        std::cout << element << " ";
    }
    //std::cout << std::endl;
}

std::pair<int, int> longest_match(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    int m = vec1.size(), n = vec2.size();
    
    // Create a 2D table to store the lengths of the longest common suffixes of substrings
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    int longest_len = 0;
    int end_pos = 0;  // To track the ending position of the longest match in vec1
    int start_index = -1;  // To store the index of the first element of the longest match in vec1
    
    // Fill the DP table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (vec1[i - 1] == vec2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > longest_len) {
                    longest_len = dp[i][j];
                    end_pos = i;
                    start_index = i - longest_len;  // Calculate the start index of the match in vec1
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    // Check if the longest match is equal in size to vec2
    if (longest_len == vec2.size()) {
        // Return the length of the match and the start index of the match in vec1
        return {longest_len, start_index + 1 };
    } else {
        // Return 0 if no match is equal to the size of vec2
        return {0, 0};  // -1 indicates no match
    }
}

void LZ77Kompresja(int data[], int dlugosc) {
    std::vector<int> okno;
    std::vector<int> poszukiwane;
    int pozycja = 0;

    while(pozycja < dlugosc){
         if(pozycja == dlugosc - 1){ 
                std::cout << "ostatni " << std::endl;
                std::cout << "na wyjscie: (" << 0 << ", " << 0 << ", " << data[pozycja - 1] << ")" << std::endl; 
                okno.insert(okno.begin(), data[pozycja - 1]);
                break;
            }
        std::cout<<"okno: ";
        for(int i = 0; i < okno.size(); i++){
            std::cout << okno[i] << ", ";
        }
        poszukiwane.insert(poszukiwane.begin(), data[pozycja]);
        
        int last_match, last_index;
        int max_dopasowanie = 0;
        int start_index = 0;
        int offset = -1;
        while (true) 
        {
            last_match = max_dopasowanie;
            last_index = start_index;
            
            std::cout << std:: endl << "poszukujemy: ";
            wypiszWektor(poszukiwane);
            std::cout << std::endl;

            std::pair result = longest_match(okno, poszukiwane);
            max_dopasowanie = result.first;
            start_index = result.second;

           if (max_dopasowanie == 0) {
                pozycja++;

                okno.insert(okno.begin(), poszukiwane.begin(), poszukiwane.end());
                std::cout << "Brak dopasowania. Dodano poszukiwane do okna." << std::endl;
                if(offset == -1) offset = 0;
                std::cout << "na wyjscie: (" << last_match << ", " << last_index + offset << ", " << data[pozycja - 1] << ")" << std::endl; 
                break;
            } else {
                std::cout << "Znaleziono dopasowanie o dlugosci " << max_dopasowanie
                        << " na pozycji " << start_index << std::endl;
                
                pozycja++;
                poszukiwane.insert(poszukiwane.begin(), data[pozycja]);
                offset++;
            }
        }
    
        poszukiwane = {};

    
    }
    wypiszWektor(okno);
std::cout << "koniec danych\n";
}




void Funkcja1() {
    int nieskompresowane[] = {0, 0, 0, 1, 1, 1, 1, 2, 0, 0, 3, 1, 3, 2, 2, 0, 0, 0, 3, 3, 3, 3, 1, 2, 1, 2, 3, 1, 2, 0, 0, 1, 1, 1, 3, 3};
    int dlugosc = 36;
    std::cout << "wejscie:" << std::endl;
    for(int c = 0; c < dlugosc; c++){
        std::cout << (int)nieskompresowane[c] << ", ";
    }
    std::cout << std::endl;
    LZ77Kompresja(nieskompresowane, dlugosc);
    cout << std::endl;

    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {
    
    //...

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
