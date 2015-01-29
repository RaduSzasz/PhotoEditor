#ifndef PNGPLUGIN_H
#define PNGPLUGIN_H

#include "formatplugin.h"

class PNGPlugin : public FormatPlugin
{
public:
    PNGPlugin();
    virtual bool loadPicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual bool savePicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual std::string getSupportedExtensions();
    virtual std::string getFormatName();
};

#endif // PNGPLUGIN_H
