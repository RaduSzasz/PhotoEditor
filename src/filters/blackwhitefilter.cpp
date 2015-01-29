#include "blackwhitefilter.h"

BlackWhiteFilter::BlackWhiteFilter(QObject *parent) :
    Filter(parent)
{
    this->R = this->G = this->B = 100;
}

void BlackWhiteFilter::setR(const int value)
{
    this->R = value;
}

void BlackWhiteFilter::setG(const int value)
{
    this->G = value;
}

void BlackWhiteFilter::setB(const int value)
{
    this->B = value;
}

int BlackWhiteFilter::getB() const
{
    return this->B;
}

int BlackWhiteFilter::getR() const
{
    return this->R;
}

int BlackWhiteFilter::getG() const
{
    return this->G;
}

Picture* BlackWhiteFilter::apply()
{
    Picture* result = new Picture(pic->getWidth(), pic->getHeight());
    int progress = 0;
    #pragma omp parallel for
    for(int i = 0; i < this->pic->getWidth(); i++)
    {
        for(int j = 0; j < this->pic->getHeight(); j++)
        {
            Color Pixel;
            Pixel=this->pic->getPixel(i , j);
            int red = Pixel.getR()*this->R; red /= 100;
            int green = Pixel.getG()*this->G; green /= 100;
            int blue = Pixel.getB()*this->B; blue /= 100;
            int mix = red + green + blue;
            mix /= 3;
            Pixel.setB(mix);
            Pixel.setG(mix);
            Pixel.setR(mix);
            result->setPixel(i , j , Pixel);
        }
        progress += 1;
        emit onProgress(progress);
    }
    return result;
}
