#include "codec.hpp"
#include <stdio.h>
#include <stdlib.h>
using namespace CDC;

void ColorImage::outputPPM(const char* filename) 
{
    FILE* outFile = fopen(filename, "wb");
    fprintf(outFile, "P6 %d %d 255\n", xRes, yRes);
    fwrite(pPixel, 1, 3 * xRes * yRes, outFile);
    fclose(outFile);
}
ColorImage::ColorImage() 
{
    pPixel = 0;
}
void ColorImage::init(int xSize, int ySize) {
    Pixel p = { 0,0,0 };
    xRes = xSize;
    yRes = ySize;
    pPixel = new Pixel[xSize * ySize];
    clear(p);
}
void ColorImage::clear(Pixel background) {
    int i;

    if (!pPixel) return;
    for (i = 0; i < xRes * yRes; i++) pPixel[i] = background;
}
void ColorImage::writePixel(int x, int y, Pixel p) 
{
    pPixel[x + y * yRes] = p;
}