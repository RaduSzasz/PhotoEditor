#ifndef BMPPLUGIN_H
#define BMPPLUGIN_H

#include <formatplugin.h>

class BMPPlugin : public FormatPlugin
{
public:
    BMPPlugin();
    virtual bool loadPicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual bool savePicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual std::string getSupportedExtensions();
    virtual std::string getFormatName();
};

#endif // BMPPLUGIN_H
