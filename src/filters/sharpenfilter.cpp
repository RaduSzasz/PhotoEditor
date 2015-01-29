#include "sharpenfilter.h"

SharpenFilter::SharpenFilter(QObject *parent) :
    Filter(parent)
{
    this->_value = 1;
}

void SharpenFilter::setValue(const int &val)
{
    this->_value = val;
}

int SharpenFilter::getValue() const
{
    return this->_value;
}

Picture* SharpenFilter::apply()
{
    Picture *result = new Picture(pic->getWidth(), pic->getHeight());
    Color pixel; int r, g, b, k;
    int kernel[3][3] = {{-1, -1, -1},
                        {-1, 8, -1},
                        {-1, -1, -1}};
    for(int i = 0; i < pic->getWidth(); i++)
    {
        for(int j = 0; j < pic->getHeight(); j++)
        {
            r = b = g = k = 0;
            for(int row = -1; row <= 1; row++)
            {
                for(int column = -1; column <= 1; column++)
                {
                    pixel = this->pic->getPixel(i, j);
                    if(i + row >= 0 && i + row < pic->getWidth())
                    {
                        if(j + column >= 0 && j + column < pic->getHeight())
                        {
                            r += pixel.getR() * kernel[row + 1][column + 1];
                            g += pixel.getG() * kernel[row + 1][column + 1];
                            b += pixel.getB() * kernel[row + 1][column + 1];
                            k += kernel[row + 1][column + 1];
                        }
                    }
                }
            }
            if(k)
            {
                r /=k;
                g /= k;
                b /= k;
            }
            pixel.setR(r); pixel.setG(g); pixel.setB(b);
            result->setPixel(i, j, pixel);
        }
    }
    return result;
}
