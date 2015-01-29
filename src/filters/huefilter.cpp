#include "huefilter.h"

HueFilter::HueFilter(QObject *parent)  :
    Filter(parent)
{
    this->_value = 0;
}

void HueFilter::setValue(const int value)
{
    this->_value = value;
}

int HueFilter::getValue() const
{
    return this->_value;
}

Picture* HueFilter::apply()
{
    Picture *result = new Picture(this->pic->getWidth(), this->pic->getHeight());
    int progress = 0;
    Color pix;
    for(int i = 0; i < this->pic->getWidth(); i++)
    {
        for(int j = 0; j < this->pic->getHeight(); j++)
        {
            pix = this->pic->getPixel(i, j);
            int hue = pix.getH();
            hue += this->_value;
            if(hue < 0) hue = 0;
            if(hue > 360) hue = 360;
            pix.setH(hue);
            result->setPixel(i, j, pix);
        }
        progress += 1;
        emit onProgress(progress);
    }
    return result;
}
