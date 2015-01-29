#include "contrastfilter.h"
#include <string.h>

ContrastFilter::ContrastFilter(QObject *parent) :
    Filter(parent)
{
    this->_value = 0;
}

void ContrastFilter::setValue(const int val)
{
    this->_value = val;
}

int ContrastFilter::getValue() const
{
    return this->_value;
}

Picture* ContrastFilter::apply()
{
    Picture *result = new Picture(this->pic->getWidth(), this->pic->getHeight());
    float f = (double)(259 * (this->_value + 255)) / (double)(255 * (259 - this->_value));
    int progress = 0;
    #pragma omp parallel for
    for(int i = 0; i < this->pic->getWidth(); i++)
    {
        for(int j = 0; j < this->pic->getHeight(); j++)
        {
            Color x = this->pic->getPixel(i, j);
            int R, G, B;
            R = f * (x.getR() - 128) + 128; x.setR(R);
            G = f * (x.getG() - 128) + 128; x.setG(G);
            B = f * (x.getB() - 128) + 128; x.setB(B);
            result->setPixel(i, j, x);
        }
        progress += 1;
        emit onProgress(progress);
    }
    return result;
}
