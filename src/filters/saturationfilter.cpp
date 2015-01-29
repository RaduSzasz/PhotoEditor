#include "saturationfilter.h"

SaturationFilter::SaturationFilter(QObject *parent)  :
    Filter(parent)
{
    this->_value = 0;
}

void SaturationFilter::setValue(const int value)
{
    this->_value = value;
}

int SaturationFilter::getValue() const
{
    return this->_value;
}

Picture* SaturationFilter::apply()
{
    Picture *result = new Picture(this->pic->getWidth(), this->pic->getHeight());
    Color pix; int i, j, progress = 0;
    for(i = 0; i < this->pic->getWidth(); i++)
    {
        for(j = 0; j < this->pic->getHeight(); j++)
        {
            pix = this->pic->getPixel(i, j);
            int val = pix.getS() + this->_value;
            pix.setS(val);
            result->setPixel(i, j, pix);
        }
        progress += 1;
        emit onProgress(progress);
    }
    return result;
}
