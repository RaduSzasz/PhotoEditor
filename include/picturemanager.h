 #ifndef PICTUREMANAGER_H
#define PICTUREMANAGER_H

#ifndef NULL
#define NULL 0
#endif

#include <vector>
#include <string>
#include <formatplugin.h>

typedef std::vector< std::pair <std::string, std::string > > ExtensionList;

class PictureManager
{
private:
    PictureManager();
    ~PictureManager();
    static PictureManager* _instance;
    std::vector<FormatPlugin*> _plugins;
    std::string _fileName;
    bool saved;
public:
    static PictureManager* getInstance();
    void registerPlugin(FormatPlugin* plugin);
    void setFileName(std::string fileName);
    std::string getFileName();
    bool loadPicture(Picture& picture, const std::string& fileName, std::string& errorMessage);
    bool savePicture(Picture& picture, const std::string& fileName, std::string& errorMessage);
    ExtensionList getSupportedFileTypes();
};

#endif // PICTUREMANAGER_H
