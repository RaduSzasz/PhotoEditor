#include "formatplugin.h"

FormatPlugin::FormatPlugin()
{
}

std::string FormatPlugin::getExtension(const std::string& fileName)
{
    char* newstr = new char[fileName.size()+1];
    memset(newstr, 0, sizeof(char)* (fileName.size()+1));
    memcpy(newstr, fileName.c_str(), fileName.size());

    int a = fileName.size();
    a--;
    while(newstr[a] != '.' && newstr >= 0)
    {
        newstr[a] = tolower(newstr[a]);
        a--;
    }

    char* extension = &newstr[a+1];
    return std::string(extension);
}
