#include "bmp24bpp.h"

Bmp24bpp::Bmp24bpp(const char *Path): BmpImage(Path){

    PixelMap = new unsigned char**[height];

    FILE *file;
    //Apertura del file e controllo esistenza
    if ((file=fopen(Path,"rb"))==NULL ){
        exit(1);
    }

    fseek(file,offBytes,0);

    char paddingByte;
    //Leggo i pixel dell'immagine e li inserisco in una mappa tridimensionale
    for(int j=0; j<height; j++){
        PixelMap[j] = new unsigned char *[width];
        for(int i=0; i<width; i++){
            PixelMap[j][i]= new unsigned char[3];
            for(int p=0; p<3; p++){
                fread(&PixelMap[j][i][p],sizeof(char),1,file);
            }
        }
        fread(&paddingByte,sizeof(char),getPadding(),file);
    }
    fclose(file);
}

void Bmp24bpp::save(const char *Path){
    //Scrivo l'header della nuova immagine
    BmpImage::save(Path);
    //Apro la nuova immagine in modalità append, così da poter scrivere di seguito all'header
    FILE *file = fopen(Path, "ab");
    if(file == NULL) {
        cout << "Can't create file" << endl;
        exit(1);
    }

    //Byte di padding
    char paddingByte = 0;

    //Scrivo la nuova immagine inserendo un byte di padding in caso fosse necessario
    for(int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            for(int p=0; p<3; p++){
                fwrite(&PixelMap[j][i][p],sizeof(char),1,file);
            }
        }
        fwrite(&paddingByte,sizeof(char),getPadding(),file);
    }
    fclose(file);
}

Bmp8bpp *Bmp24bpp::to8bpp(){
    // creo una mappa di pixel a 2 dimensioni
    unsigned char **Map8 = new unsigned char*[height];
    for(int j=0; j<height; j++){
        Map8[j] = new unsigned char[width];
        for(int i=0; i<width; i++){
            // il valore è la media delle tre componenti che compongono il pixel
            Map8[j][i] = (PixelMap[j][i][0]*0.11)+(PixelMap[j][i][1]*0.59)+(PixelMap[j][i][2]*0.3);
        }
    }

    // costruisco un'immagine monocromatica
    Bmp8bpp *p = new Bmp8bpp(*this,Map8);
    // ritorno il puntatore
    return p;
}



