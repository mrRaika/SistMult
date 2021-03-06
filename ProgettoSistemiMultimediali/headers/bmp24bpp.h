#ifndef BMP24BPP_H
#define BMP24BPP_H

#include "bmpimage.h"
#include "bmp8bpp.h"

class Bmp24bpp : public BmpImage{
private:
    unsigned char*** PixelMap;
public:
    Bmp24bpp(const char *Path);

    void save(const char *Path);

    unsigned char *** getMap(){return PixelMap;}

    void editPMap(unsigned char*** map){PixelMap=map;}

    Bmp8bpp* to8bpp();
};

#endif // BMP24BPP_H
