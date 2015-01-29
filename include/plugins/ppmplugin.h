#ifndef PPMPLUGIN_H
#define PPMPLUGIN_H

#include "formatplugin.h"

class PPMPlugin : public FormatPlugin
{
public:
    PPMPlugin();
    virtual bool loadPicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual bool savePicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual std::string getSupportedExtensions();
    virtual std::string getFormatName();
};

#endif // PPMPLUGIN_H
