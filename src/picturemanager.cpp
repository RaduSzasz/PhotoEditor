#include "picturemanager.h"

PictureManager* PictureManager::_instance = NULL;

PictureManager::PictureManager()
{
    _instance = NULL;
}

PictureManager::~PictureManager()
{
    if (_instance != NULL)
    {
        delete _instance;
    }
    for (int i = 0; i < _plugins.size(); i++)
    {
        delete _plugins[i];
    }
}

PictureManager* PictureManager::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new PictureManager;
    }
    return _instance;
}

void PictureManager::registerPlugin(FormatPlugin *plugin)
{
    _plugins.push_back(plugin);
}

bool PictureManager::loadPicture(Picture &picture, const std::string &fileName, std::string &errorMessage)
{
    bool loaded = false;
    for(int i = 0; i < _plugins.size(); i++)
    {
        if (_plugins[i]->loadPicture(picture, fileName, errorMessage))
        {
            loaded = true;
            break;
        }
    }
    return loaded;
}

bool PictureManager::savePicture(Picture &picture, const std::string &fileName, std::string &errorMessage)
{
    bool saved = false;
    for(int i = 0; i < _plugins.size(); i++)
    {
        if (_plugins[i]->savePicture(picture, fileName, errorMessage))
        {
            saved = true;
            break;
        }
    }
    return saved;
}

ExtensionList PictureManager::getSupportedFileTypes()
{
    ExtensionList result;
    for(int i = 0; i < _plugins.size(); i++)
    {
        result.push_back(make_pair(_plugins[i]->getFormatName(), _plugins[i]->getSupportedExtensions()));
    }
    return result;
}

void PictureManager::setFileName(std::string fileName)
{
    this->_fileName = fileName;
}

std::string PictureManager::getFileName()
{
    return this->_fileName;
}
