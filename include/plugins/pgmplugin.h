#ifndef PGMPLUGIN_H
#define PGMPLUGIN_H

#include <formatplugin.h>

class PGMPlugin : public FormatPlugin
{
public:
    PGMPlugin();
    virtual bool loadPicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual bool savePicture(Picture& pic, const std::string& fileName, std::string& errorMessage);
    virtual std::string getSupportedExtensions();
    virtual std::string getFormatName();
};

#endif // PGMPLUGIN_H
