#include "pngplugin.h"

PNGPlugin::PNGPlugin()
{
}

bool PNGPlugin::loadPicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "png")
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
        pic.setGdImagePtr(gdImageCreateFromPng(f));
        fclose(f);
    }
    return true;
}

bool PNGPlugin::savePicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "png")
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
        char* fileData;
        int fileDataSize = 0;

        fileData = (char*)gdImagePngPtr(pic.getGdImagePtr(), &fileDataSize);
        if (fileData != NULL)
        {
            fwrite(fileData, fileDataSize, 1, f);
            gdFree(fileData);
        }
        fclose(f);
    }
    return true;
}

std::string PNGPlugin::getSupportedExtensions()
{
    return "*.png";
}

std::string PNGPlugin::getFormatName()
{
    return "Portable Network Graphics";
}
