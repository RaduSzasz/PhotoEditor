#include "ppmplugin.h"

PPMPlugin::PPMPlugin()
{
}

bool PPMPlugin::loadPicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "ppm")
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
                    unsigned char redValue;
                    unsigned char greenValue;
                    unsigned char blueValue;
                    fread(&redValue, 1, 1, f);
                    fread(&greenValue, 1, 1, f);
                    fread(&blueValue, 1, 1, f);
                    Color pixel;
                    pixel.setR(redValue);
                    pixel.setB(greenValue);
                    pixel.setG(blueValue);
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
                    unsigned short redValue;
                    unsigned short greenValue;
                    unsigned short blueValue;
                    fread(&redValue, 2, 1, f);
                    fread(&greenValue, 2, 1, f);
                    fread(&blueValue, 2, 1, f);
                    Color pixel;
                    pixel.setR(redValue);
                    pixel.setB(greenValue);
                    pixel.setG(blueValue);
                    pic.setPixel(i, j, pixel);
                }
            }
        }
    }
    return true;
}

bool PPMPlugin::savePicture(Picture &pic, const std::string &fileName, std::string &errorMessage)
{
    if (getExtension(fileName) != "ppm")
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
        fprintf(f,"P6\n%d %d\n65535\n", pic.getWidth(), pic.getHeight());
        for (int j = 0; j < pic.getHeight(); j++)
        {
            for (int i = 0; i < pic.getWidth(); i++)
            {
                Color pixel = pic.getPixel(i,j);
                unsigned short redValue = pixel.getR();
                unsigned short greenValue = pixel.getG();
                unsigned short blueValue = pixel.getB();
                fwrite(&redValue, 2, 1, f);
                fwrite(&greenValue, 2, 1, f);
                fwrite(&blueValue, 2, 1, f);
            }
        }

        fclose(f);
    }
    return true;

}

std::string PPMPlugin::getSupportedExtensions()
{
    return "*.ppm";
}

std::string PPMPlugin::getFormatName()
{
    return "Portable Pixelmap";
}
