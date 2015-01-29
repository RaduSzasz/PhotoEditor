#include "boxblurfilter.h"

inline int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

inline int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

BoxBlurFilter::BoxBlurFilter(QObject *parent) :
    Filter(parent)
{
    this->_radius = 1;
}

void BoxBlurFilter::setRadius(const int radius)
{
    this->_radius = radius;
}

int BoxBlurFilter::getRadius() const
{
    return this->_radius;
}

Picture* BoxBlurFilter::apply()
{
    if(this->_radius == 0)
        return this->pic;
    Picture *result = new Picture(pic->getWidth(), pic->getHeight());
    long long ***matrice;
    matrice = new long long**[3];
    for(int i = 0; i < 3; i++)
    {
        matrice[i] = new long long*[pic->getWidth()];
    }
    for(int i = 0; i < pic->getWidth(); i++)
    {
        matrice[0][i] = new long long[pic->getHeight()];
        matrice[1][i] = new long long[pic->getHeight()];
        matrice[2][i] = new long long[pic->getHeight()];
    }
    Color x;int contor, L, l, xStop, xStart, yStop, yStart, R, G, B;
    for(int i = 0; i < this->pic->getWidth(); i++)
    {
        for(int j = 0; j < this->pic->getHeight(); j++)
        {
            matrice[0][i][j] = matrice[1][i][j] = matrice[2][i][j] = 0;
            x = this->pic->getPixel(i, j);
            if(i)
            {
                matrice[0][i][j] += matrice[0][i - 1][j];
                matrice[1][i][j] += matrice[1][i - 1][j];
                matrice[2][i][j] += matrice[2][i - 1][j];
            }
            if(j)
            {
                matrice[0][i][j] += matrice[0][i][j - 1];
                matrice[1][i][j] += matrice[1][i][j - 1];
                matrice[2][i][j] += matrice[2][i][j - 1];
            }
            if(i && j)
            {
                matrice[0][i][j] -= matrice[0][i - 1][j - 1];
                matrice[1][i][j] -= matrice[1][i - 1][j - 1];
                matrice[2][i][j] -= matrice[2][i - 1][j - 1];
            }
            matrice[0][i][j] += x.getR();
            matrice[1][i][j] += x.getG();
            matrice[2][i][j] += x.getB();
        }
        emit onProgress(i >> 1);
    }
    for(int i = 0; i < this->pic->getWidth(); i++)
    {
        for(int j = 0; j < this->pic->getHeight(); j++)
        {
            xStop = min(this->pic->getWidth() - 1, i + _radius);
            xStart = max(0, i - _radius);
            yStop = min(this->pic->getHeight() - 1, j + _radius);
            yStart = max(0, j - _radius);
            R = matrice[0][xStop][yStop];
            G = matrice[1][xStop][yStop];
            B = matrice[2][xStop][yStop];
            L = xStop - xStart; l = yStop - yStart;
            contor = L * l;
            if(xStart)
            {
                R -= matrice[0][xStart - 1][yStop];
                G -= matrice[1][xStart - 1][yStop];
                B -= matrice[2][xStart - 1][yStop];
            }
            if(yStart)
            {
                R -= matrice[0][xStop][yStart - 1];
                G -= matrice[1][xStop][yStart - 1];
                B -= matrice[2][xStop][yStart - 1];
            }
            if(xStart && yStart)
            {
                R += matrice[0][xStart - 1][yStart - 1];
                G += matrice[1][xStart - 1][yStart - 1];
                B += matrice[2][xStart - 1][yStart - 1];
            }
            R /= contor; G /= contor; B /= contor;
            x.setR(R);
            x.setG(G);
            x.setB(B);
            result->setPixel(i , j, x);
        }
        emit onProgress((pic->getWidth() + i) >> 1);
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < pic->getWidth(); j++)
        {
            delete matrice[i][j];
        }
        delete matrice[i];
    }
    return result;
}
