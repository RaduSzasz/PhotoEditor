#include "brightnessfilter.h"

BrightnessFilter::BrightnessFilter(QObject *parent) :
    Filter(parent)
{
    this->_value = 0;
}

void BrightnessFilter::setValue(const int val)
{
    this->_value = val;
}

int BrightnessFilter::getValue() const
{
    return this->_value;
}

Picture* BrightnessFilter::apply()
{
    Picture *result = new Picture(pic->getWidth(), pic->getHeight());
    int progress = 0;
    #pragma omp parallel for
    for(int i = 0; i < pic->getWidth(); i++)
    {
        for(int j = 0; j < pic->getHeight(); j++)
        {
            Color pixel;
            pixel = pic->getPixel(i , j);
            int r = pixel.getR();
            int g = pixel.getG();
            int b = pixel.getB();
            r+=this->_value;
            g+=this->_value;
            b+=this->_value;
            if(r > 255)
                r = 255;
            else if(r < 1)
                r = 0;
            if(g > 255)
                g = 255;
            else if(g < 1)
                g = 0;
            if(b > 255)
                b = 255;
            else if(b < 1)
                b = 0;
            pixel.setR(r);
            pixel.setG(g);
            pixel.setB(b);
            result->setPixel(i , j , pixel);
        }
        progress += 1;
        emit onProgress(progress);
    }
    return result;
}

