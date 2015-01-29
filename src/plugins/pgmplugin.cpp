#include "pgmplugin.h"

PGMPlugin::PGMPlugin()
{
}

bool PGMPlugin::loadPicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "pgm")
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
        int width = 0, height = 0;
        char header[24] = {0}, possibleComment[1024] = {0};
        int bpp = 0;
        fgets(header, 24, f);
        while(!bpp)
        {
            memset(possibleComment, 0 , 1024*sizeof(char));
            fgets(possibleComment, 1024, f);
            if(possibleComment[0] != '#')
            {
               if(!(width && height))
                     sscanf(possibleComment,"%d %d",&width, &height);
               else
                     sscanf(possibleComment,"%d", &bpp);
            }
        }
        pic.resize(width, height);
        if(bpp == 255)
        {
             for(int j = 0; j < height; j++)
            {
               for(int i = 0; i < width; i++)
                {
                    unsigned char greyValue;
                    fread(&greyValue, 1, 1, f);
                    Color pixel;
                    pixel.setR(greyValue);
                    pixel.setB(greyValue);
                    pixel.setG(greyValue);
                    pic.setPixel(i, j, pixel);
                }
            }
            fclose(f);
        }
        else if(bpp == 65535)
        {
            for(int j = 0; j < height; j++)
            {
                for(int i = 0; i < width; i++)
                {
                    unsigned short greyValue;
                    fread(&greyValue, 2, 1, f);
                    greyValue /= 256;
                    Color pixel;
                    pixel.setR(greyValue);
                    pixel.setB(greyValue);
                    pixel.setG(greyValue);
                    pic.setPixel(i, j, pixel);
                }
            }
        }
    }
    return true;
}

bool PGMPlugin::savePicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "pgm")
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
        fprintf(f,"P5\n%d %d\n255\n", pic.getWidth(), pic.getHeight());
        for (int j = 0; j < pic.getHeight(); j++)
        {
            for (int i = 0; i < pic.getWidth(); i++)
            {
                Color pixel = pic.getPixel(i,j);
                unsigned char greyValue = (unsigned char)pixel.getV();
                fwrite(&greyValue, 1, 1, f);
            }
        }

        fclose(f);
    }
    return true;

}

std::string PGMPlugin::getSupportedExtensions()
{
    return "*.pgm";
}

std::string PGMPlugin::getFormatName()
{
    return "Portable Graymap";
}
