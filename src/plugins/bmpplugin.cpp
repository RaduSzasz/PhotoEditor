#include "bmpplugin.h"

BMPPlugin::BMPPlugin()
{
}

bool BMPPlugin::loadPicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "bmp")
    {
        return false;
    }
    FILE* f = fopen(fileName.c_str(),"rb");
    if (f == 0)
    {
        errorMessage = "Could not open file " + fileName;
    }
    else
    {
        int width;
        int height;
        short zero;
        int zeroFourBytes = 0;
        char b;
        fread(&b, 2, 1, f);
        int size;
        fread(&size, 4, 1, f);
        fread(&zero , 2, 2, f);
        int adress;
        fread(&adress, 4, 1, f);
        int dibHeaderSize;
        fread(&dibHeaderSize, 4, 1, f);
        fread(&width, 4, 1, f);
        fread(&height, 4, 1, f);
        short planeNumber;
        fread(&planeNumber, 2, 1, f);
        int colorDepth;
        fread(&colorDepth, 2, 1, f);
        fread(&zero, 4, 1, f);
        int sizeOfData;
        fread(&sizeOfData, 4, 1, f);
        int resolution;
        fread(&resolution, 4, 2, f);
        fread(&zeroFourBytes, 4, 2, f);
        int bytesAddition = (width * 3) % 4;
        pic.resize(width, height);
        for(int i = pic.getHeight() - 1; i >= 0; i--)
        {
            for(int j = 0; j < pic.getWidth(); j++)
            {
                Color currentPixel;
                unsigned char red, green, blue;
                fread(&red, 1, 1, f);
                fread(&green, 1, 1, f);
                fread(&blue, 1, 1, f);
                currentPixel.setR(red);
                currentPixel.setG(green);
                currentPixel.setB(blue);
                pic.setPixel(j, i, currentPixel);
            }
            fwrite(&zero, bytesAddition, 1, f);
        }
        fclose(f);
    }
    return true;
}

bool BMPPlugin::savePicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "bmp")
    {
        return false;
    }
    FILE* f = fopen(fileName.c_str(),"wb");
    if (f == 0)
    {
        errorMessage = "Could not open file " + fileName;
    }
    else
    {
        int width = pic.getWidth();
        int height = pic.getHeight();
        int bytesAddition = (width * 3) % 4;
        short zero = 0;
        int zeroFourBytes = 0;
        fwrite("BM", 2, 1, f);
        int size = width * height * 3 + 54 + bytesAddition;
        fwrite(&size, 4, 1, f);
        fwrite(&zero , 2, 2, f);
        int adress = 54;
        fwrite(&adress, 4, 1, f);
        int dibHeaderSize = 40;
        fwrite(&dibHeaderSize, 4, 1, f);
        fwrite(&width, 4, 1, f);
        fwrite(&height, 4, 1, f);
        short planeNumber = 1;
        fwrite(&planeNumber, 2, 1, f);
        int colorDepth = 24;
        fwrite(&colorDepth, 2, 1, f);
        fwrite(&zero, 4, 1, f);
        int sizeOfData = 16;
        fwrite(&sizeOfData, 4, 1, f);
        int resolution = 2835;
        fwrite(&resolution, 4, 2, f);
        fwrite(&zeroFourBytes, 4, 2, f);
        for(int i = pic.getHeight() - 1; i >= 0; i--)
        {
            for(int j = 0; j < pic.getWidth(); j++)
            {
                Color currentPixel = pic.getPixel(j ,i);
                unsigned char red = currentPixel.getR();
                unsigned char green = currentPixel.getG();
                unsigned char blue = currentPixel.getB();
                fwrite(&red, 1, 1, f);
                fwrite(&green, 1, 1, f);
                fwrite(&blue, 1, 1, f);
            }
            fwrite(&zero, bytesAddition, 1, f);
        }
    }
    return true;
}


std::string BMPPlugin::getSupportedExtensions()
{
    return "*.bmp";
}

std::string BMPPlugin::getFormatName()
{
    return "Windows Bitmap";
}
