#ifndef JPEGPLUGIN_H
#define JPEGPLUGIN_H

#include <formatplugin.h>

class JPEGPlugin : public FormatPlugin
{
public:
    JPEGPlugin();
    virtual bool loadPicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual bool savePicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual std::string getSupportedExtensions();
    virtual std::string getFormatName();
};

#endif // JPEGPLUGIN_H
