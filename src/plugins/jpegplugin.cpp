#include "jpegplugin.h"

JPEGPlugin::JPEGPlugin()
{
}

bool JPEGPlugin::loadPicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "jpg" && getExtension(fileName) != "jpeg")
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
        pic.setGdImagePtr(gdImageCreateFromJpeg(f));
        fclose(f);
    }
    return true;
}

bool JPEGPlugin::savePicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "jpg" && getExtension(fileName) != "jpeg")
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

        fileData = (char*)gdImageJpegPtr(pic.getGdImagePtr(), &fileDataSize, 100);
        if (fileData != NULL)
        {
            fwrite(fileData, fileDataSize, 1, f);
            gdFree(fileData);
        }
        fclose(f);
    }
    return true;

}

std::string JPEGPlugin::getSupportedExtensions()
{
    return "*.jpg *.jpeg";
}

std::string JPEGPlugin::getFormatName()
{
    return "Joint Photographic Experts Group";
}
