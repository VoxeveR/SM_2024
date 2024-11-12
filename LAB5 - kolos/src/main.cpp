#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <bitset>
using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 640
#define wysokosc 400

#define tytul "SM2024 - Test 1 - Zietek Piotr"

struct HSL{
    Uint8 H;
    Uint8 S;
    Uint8 L;
};

struct YUV{
    float Y;
    float U;
    float V;
};

struct YIQ{
    float Y;
    float I;
    float Q;
};

struct YCbCr{
    float Y;
    float Cb;
    float Cr;
};


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
void setHSL(int xx, int yy, float h, float s, float l);

Uint16 getHSL556(int xx, int yy);
void setHSL556(int xx, int yy, Uint16 hslColor);

SDL_Color HSLtoRGB(Uint8 h, Uint8 s, Uint8 l);
HSL getHSL(int xx, int yy);

void setYUV(int xx, int yy, float y, float u, float v);

void setYIQ(int xx, int yy, float y, float i, float q);

void setYCbCr(int xx, int yy, float y, float cb, float cr);

SDL_Color YUVtoRGB(float y, float u, float v);

SDL_Color YIQtoRGB(float y, float u, float v);

SDL_Color YCbCrtoRGB(float y, float u, float v);

YUV getYUV(int xx, int yy);

YIQ getYIQ(int xx, int yy);

YCbCr getYCbCr(int xx, int yy);

void YUVSampling_411();

void YCbCrSampling_411();

void YIQSampling_411();


// ZAD 2
void Funkcja1() {

    for(int x = 0; x < szerokosc/2; x++){
        for(int y = 0; y < wysokosc/2; y++){
            Uint16 value = getHSL556(x, y);
            setHSL556(x + szerokosc/2, y, value);
        }
    }

    SDL_UpdateWindowSurface(window);
}

// ZAD 3
void Funkcja2() {

    std::cout<<"YIQ" << std::endl;
    YIQSampling_411();

    SDL_UpdateWindowSurface(window);
}

// ZAD 3
void Funkcja3() {

    std::cout<<"YUV" << std::endl;
    YUVSampling_411();

    SDL_UpdateWindowSurface(window);
}

// ZAD 3
void Funkcja4() {

    std::cout<<"YCbCr" << std::endl;
    YCbCrSampling_411();

    SDL_UpdateWindowSurface(window);
}

// ZAD 1
void Funkcja5() {

    float L = 0.5f * 255.0f;

    for (int y = 0; y < wysokosc; y++) {
        for (int x = 0; x < szerokosc; x++) {

            float H = (float)x / szerokosc * 255.0f; 
            float S = 255.0f - (float)y / wysokosc * 255.0f;

            setHSL(x, y, H, S, L);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {



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

Uint16 getHSL556(int xx, int yy) {
    HSL HSLcolor = getHSL(xx, yy);
    Uint16 retColor;
    Uint16 h, s, l;

    h = HSLcolor.H;
    s = HSLcolor.S;
    l = HSLcolor.L;

    h = h >> 3;  
    s = s >> 3;  
    l = l >> 2;  


    Uint16 H, S, L;

    retColor = (h << 11) | (s << 6) | l;
    // std::bitset<16> r(retColor);
    // std::cout<< r << std::endl;
    return retColor;
}

void setHSL556(int xx, int yy, Uint16 hslColor) {
    Uint8 h, s, l;

    h = (hslColor >> 11) & 0x1F;
    s = (hslColor >> 6) & 0x1F;  
    l = hslColor & 0x3F;         

    h = std::min(255, h << 3);
    s = std::min(255, s << 3);
    l = std::min(255, l << 2);


    SDL_Color rgbColor = HSLtoRGB(h, s, l);

    setPixel(xx, yy, rgbColor.r, rgbColor.g, rgbColor.b);
}

void setHSL(int xx, int yy, float h, float s, float l){
    SDL_Color colorRGB = HSLtoRGB(h, s, l);

    setPixel(xx, yy, colorRGB.r, colorRGB.g, colorRGB.b);
}

SDL_Color HSLtoRGB(Uint8 h, Uint8 s, Uint8 l){

    SDL_Color RGBret;
    float zmienna1, zmienna2, barwa;
    float zmiennaR, zmiennaG, zmiennaB;

    float H = (h * 360.0) / 255.0;
    float S = s * 1.0 / 255.0;
    float L = l * 1.0 / 255.0;

    if(S == 0){
        RGBret.r = (L) * 255;
        RGBret.g = (L) * 255;
        RGBret.b = (L) * 255;
    } else {
        if (L < 0.5){
            zmienna1 = L * (1.0 + S);
        } else {
            zmienna1 = L + S - (L * S);
        }

        zmienna2 = 2 * L - zmienna1;
        barwa = H / 360;

        if (zmienna1 < 0) zmienna1 += 1;
        if (zmienna1 > 1) zmienna1 -= 1;

        if (zmienna2 < 0) zmienna2 += 1;
        if (zmienna2 > 1) zmienna2 -= 1;

        zmiennaR = barwa + 0.333;
        if (zmiennaR < 0) zmiennaR += 1;
        if (zmiennaR > 1) zmiennaR -= 1;

        zmiennaG = barwa;
        if (zmiennaG < 0) zmiennaG += 1;
        if (zmiennaG > 1) zmiennaG -= 1;

        zmiennaB = barwa - 0.333;
        if (zmiennaB < 0) zmiennaB += 1;
        if (zmiennaB > 1) zmiennaB -= 1;

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

        RGBret.r = czerwony * 255;
        RGBret.g = zielony * 255;
        RGBret.b = niebieski * 255;
    }

    return RGBret;
}

HSL getHSL(int xx, int yy){

    SDL_Color colorRGB = getPixel(xx, yy);
    float r, g, b, h, s, l, mmin, mmax;
    HSL HSLret;

    r = (float)colorRGB.r*1.0/255.0;
    g = (float)colorRGB.g*1.0/255.0;
    b = (float)colorRGB.b*1.0/255.0;

    mmin = std::min(r,(std::min(g,b)));
    mmax = std::max(r,(std::max(g,b)));

    l = (mmin+mmax)/2.0;

    if(mmin == mmax){
        s = 0;
    } else if(l <= 0.5){
        s = (mmax-mmin) / (mmax+mmin);
    } else{
        s = (mmax-mmin) / (2.0 - mmax - mmin);
    }

    if(r == mmax){
        h = (g - b) / (mmax-mmin);
    } else if(g == mmax){
        h = 2.0 + (b - r) / (mmax-mmin);
    } else{
        h = 4.0 + (r - g) / (mmax-mmin);
    }

    h *= 60;
    if(h< 0) h += 360;

    h /= 360;
    h *= 255;
    s *= 255;
    l *= 255;

    HSLret.H = (int)h;
    HSLret.S = (int)s;
    HSLret.L = (int)l;

    return HSLret;
}

void YIQSampling_411() {
    for (int y = 0; y < wysokosc/2; y ++) {
        for (int x = 0; x < szerokosc/2; x += 4) { 

            YIQ yiq00 = getYIQ(x, y);
            YIQ yiq01 = getYIQ(x + 1, y);
            YIQ yiq02 = getYIQ(x + 2, y);
            YIQ yiq03 = getYIQ(x + 3, y);

            float Iavg = (yiq00.I + yiq01.I + yiq02.I + yiq03.I) / 4.0;
            float Qavg = (yiq00.Q + yiq01.Q + yiq02.Q + yiq03.Q) / 4.0;

            setYIQ(x + szerokosc / 2, y, yiq00.Y, Iavg, Qavg);
            setYIQ(x + szerokosc / 2 + 1, y, yiq01.Y, Iavg, Qavg);
            setYIQ(x + szerokosc / 2 + 2, y, yiq02.Y, Iavg, Qavg);
            setYIQ(x + szerokosc / 2 + 3, y, yiq03.Y, Iavg, Qavg);
        }
    }
}

void YUVSampling_411() {
    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x += 4) { 

            YUV yuv00 = getYUV(x, y);
            YUV yuv01 = getYUV(x + 1, y);
            YUV yuv02 = getYUV(x + 2, y);
            YUV yuv03 = getYUV(x + 3, y);

            float Uavg = (yuv00.U + yuv01.U + yuv02.U + yuv03.U) / 4.0;
            float Vavg = (yuv00.V + yuv01.V + yuv02.V + yuv03.V) / 4.0;

            setYUV(x + szerokosc / 2, y, yuv00.Y, Uavg, Vavg);
            setYUV(x + szerokosc / 2 + 1, y, yuv01.Y, Uavg, Vavg);
            setYUV(x + szerokosc / 2 + 2, y, yuv02.Y, Uavg, Vavg);
            setYUV(x + szerokosc / 2 + 3, y, yuv03.Y, Uavg, Vavg);
        }
    }
}

void YCbCrSampling_411() {
    for (int y = 0; y < wysokosc / 2; y ++) {
        for (int x = 0; x < szerokosc / 2; x += 4) { 

            YCbCr ycbcr00 = getYCbCr(x, y);
            YCbCr ycbcr01 = getYCbCr(x + 1, y);
            YCbCr ycbcr02 = getYCbCr(x + 2, y);
            YCbCr ycbcr03 = getYCbCr(x + 3, y);

            float Cbavg = (ycbcr00.Cb + ycbcr01.Cb + ycbcr02.Cb + ycbcr03.Cb) / 4.0;
            float Cravg = (ycbcr00.Cr + ycbcr01.Cr + ycbcr02.Cr + ycbcr03.Cr) / 4.0;

            setYCbCr(x + szerokosc / 2, y, ycbcr00.Y, Cbavg, Cravg);
            setYCbCr(x + szerokosc / 2 + 1, y, ycbcr01.Y, Cbavg, Cravg);
            setYCbCr(x + szerokosc / 2 + 2, y, ycbcr02.Y, Cbavg, Cravg);
            setYCbCr(x + szerokosc / 2 + 3, y, ycbcr03.Y, Cbavg, Cravg);
        }
    }
}


SDL_Color YIQtoRGB(float y, float i, float q){

    SDL_Color RGBret;
    float r, g, b;

    r = y + (i * 0.956) + (q * 0.619);
    g = y + (i * (-0.272)) + (q * (-0.647));
    b = y + (i * (-1.106)) + (q * 1.703);

    RGBret.r = (r<0 ? 0 : (r>255 ? 255 : r));
    RGBret.g = (g<0 ? 0 : (g>255 ? 255 : g));
    RGBret.b = (b<0 ? 0 : (b>255 ? 255 : b));

    return RGBret;
}

void setYIQ(int xx, int yy, float y, float i, float q){
    SDL_Color rgb = YIQtoRGB(y, i, q);

    setPixel(xx, yy, rgb.r, rgb.g, rgb.b);
}

YIQ getYIQ(int xx, int yy){
    YIQ YIQret;

    SDL_Color color = getPixel(xx, yy);

    YIQret.Y = (0.299 * color.r) + (0.587 * color.g) + (0.114 * color.b);
    YIQret.I = (0.5959 * color.r) + (-0.2746 * color.g) + (-0.3213 * color.b);
    YIQret.Q = (0.2115 * color.r) + (-0.5227 * color.g) + (0.3112 * color.b);

    return YIQret;
}

SDL_Color YCbCrtoRGB(float y, float cb, float cr){

    SDL_Color RGBret;
    float r, g, b;

    r = y + 1.402 * (cr - 128);
    g = y - 0.344136 * (cb - 128) - 0.714136 * (cr - 128);
    b = y + 1.772 * (cb - 128);

    RGBret.r = (r<0 ? 0 : (r>255 ? 255 : r));
    RGBret.g = (g<0 ? 0 : (g>255 ? 255 : g));
    RGBret.b = (b<0 ? 0 : (b>255 ? 255 : b));

    return RGBret;
}

void setYCbCr(int xx, int yy, float y, float cb, float cr){
    SDL_Color rgb = YCbCrtoRGB(y, cb, cr);

    setPixel(xx, yy, rgb.r, rgb.g, rgb.b);
}

YCbCr getYCbCr(int xx, int yy){
    YCbCr YCbCrret;

    SDL_Color color = getPixel(xx, yy);

    YCbCrret.Y = 0 + (0.299 * color.r) + (0.587 * color.g) + (0.114 * color.b);
    YCbCrret.Cb = 128 - (0.168736 * color.r) - (0.331264 * color.g) + (0.5 * color.b);
    YCbCrret.Cr = 128 + (0.5 * color.r) - (0.418688 * color.g) - (0.081312 * color.b);

    return YCbCrret;
}

SDL_Color YUVtoRGB(float y, float u, float v){

    SDL_Color RGBret;
    float r, g, b;

    r = y * 1 + u * 0 + v * 1.13983;
    g = y * 1 + u * (-0.39465) + v * (-0.58060);
    b = y * 1 + u * 2.03211 + 0 * v;

    RGBret.r = (r<0 ? 0 : (r>255 ? 255 : r));
    RGBret.g = (g<0 ? 0 : (g>255 ? 255 : g));
    RGBret.b = (b<0 ? 0 : (b>255 ? 255 : b));

    return RGBret;
}

void setYUV(int xx, int yy, float y, float u, float v) {

    SDL_Color rgb = YUVtoRGB(y,u,v);
    setPixel(xx, yy, rgb.r, rgb.g, rgb.b);
}

YUV getYUV(int xx, int yy){
    YUV YUVret;

    SDL_Color color = getPixel(xx, yy);

    YUVret.Y = (0.299 * color.r) + (0.587 * color.g) + (0.114 * color.b);
    YUVret.U = (-0.14713 * color.r) + (-0.28886 * color.g) + (0.436 * color.b);
    YUVret.V = (0.615 * color.r) + (-0.51499 * color.g) + (-0.10001 * color.b);

    return YUVret;
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
