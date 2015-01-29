#ifndef FORMATPLUGIN_H
#define FORMATPLUGIN_H

#include <string>
#include <cstring>
#include "picture.h"

class FormatPlugin
{
protected:
    std::string getExtension(const std::string& fileName);
public:
    FormatPlugin();
    virtual bool loadPicture(Picture& pic, const std::string& fileName, std::string& errorMessage) = 0;
    virtual bool savePicture(Picture& pic, const std::string& fileName, std::string& errorMessage) = 0;
    virtual std::string getSupportedExtensions() = 0;
    virtual std::string getFormatName() = 0;
};

#endif // FORMATPLUGIN_H
