#include "color.h"
#include <math.h>

float minim(float a, float b, float c)
{
    if(a<b&&a<c)
    {
        return a;
    }
    else
    {
        if(b<c)
            return b;
    }
    return c;
}

float minimum(float a, float b)
{
    if(a < b)
        return a;
    return b;
}

float maxim(float a, float b, float c)
{
    if(a>b&&a>c)
    {
        return a;
    }
    else
    {
        if(b>c)
            return b;
    }
    return c;
}


Color::Color()
{
    argb=0;
}

Color::Color(int setargb)
{
    argb = setargb;
}

Color::Color(int r, int g, int b)
{
    argb = 0;
    argb = argb | r;
    argb = argb << 8;
    argb= argb | g;
    argb = argb << 8;
    argb = argb | b;
}

int Color::HsvToRgb(int _H, float _S, float _V)
{
    float R = 0, G = 0, B = 0;
    if(_H > 360)
        _H -= 360;
    float h = (1.0 * _H) / 60.0;
    float s = _S / 100.0;
    float v = _V / 100.0;
    int inti = (int)floor(h);
    float int1, int2, int3;
    int1 = v * (1.0 - s);
    int2 = v * (1.0 - s * (h - inti));
    int3 = v * (1.0 - s * (1.0 - (h - inti)));
    if (s < 0.01)
    {
        R = v;
        G = v;
        B = v;
    }
    else
    {
        switch (inti)
        {
            case 0:
                R = v;
                G = int3;
                B = int1;
                break;
            case 1:
                R = int2;
                G = v;
                B = int1;
                break;
            case 2:
                R = int1;
                G = v;
                B = int3;
                break;
            case 3:
                R = int1;
                G = int2;
                B = v;
                break;
            case 4:
                R = int3;
                G = int1;
                B = v;
                break;
            default:
                R = v;
                G = int1;
                B = int2;
                break;
        }
    }
    R = (int)floor(255 * R);
    G = (int)floor(255 * G);
    B = (int)floor(255 * B);
    return RgbToArgb(R ,G ,B);
}

int Color::RgbToArgb(int R, int G, int B)
{
    int argb = 0;
    argb = argb | R;
    argb = argb << 8;
    argb= argb | G;
    argb = argb << 8;
    argb = argb | B;
    return argb;
}

void Color::RgbToHsv(int R, int G, int B, int& H, float& S, float& V)
{
    float r =(float)R/255;
    float g =(float)G/255;
    float b =(float)B/255;
    float h = 0,s = 0,v = 0;
    float minVal = minim(r, g, b);
    float maxVal = maxim(r, g, b);
    float delta = maxVal - minVal;
    v = maxVal;
    if (fabs(delta) < 0.001)
    {
        h = 0;
        s = 0;
    }
    else
    {
        s = delta / maxVal;
        float del_R = (((maxVal - r) / 6) + (delta / 2)) / delta;
        float del_G = (((maxVal - g) / 6) + (delta / 2)) / delta;
        float del_B = (((maxVal - b) / 6) + (delta / 2)) / delta;
        if (fabs(r - maxVal) < 0.001)
        {
            h = del_B - del_G;
        }
        else
            if (fabs(g - maxVal) < 0.001)
            {
                 h = (1.0 / 3.0) + del_R - del_B;
            }
            else
            {
                if (fabs(b - maxVal) < 0.001)
                 {
                     h = (2.0 / 3.0) + del_G - del_R;
                 }
                 if (h < 0)
                 {
                    h += 1;
                 }
                 if (h > 1)
                 {
                    h -= 1;
                 }
            }
    }
    H=h*360;
    if (H < 0) {H = 360-H;}
    S=s;
    V=v;
}

void Color::RgbToCmyk(int R, int G, int B, int &C, int &M, int &Y, int &K)
{
     float newC = 0;
     float newM = 0;
     float newY = 0;
     float newK = 0;
     if (R<0 || G<0 || B<0)
     {
         if(R < 0)
             R = 0;
         if (G < 0)
             G = 0;
         if(B < 0)
             B = 0;

     }
     if(R > 255 || G > 255 || B > 255)
     {
         if(R > 255)
             R = 255;
         if(G > 255)
             G = 255;
         if(B > 255)
             B = 255;
     }
     if (R==0 && G==0 && B==0)
     {
        K = 1;
        return;
     }
     newC = 1 - (float)((float)R/255);
     newM = 1 - (float)((float)G/255);
     newY = 1 - (float)((float)B/255);
     float minCMY = minimum(newC, minimum(newM,newY));
     newC = (newC - minCMY) / (1 - minCMY) ;
     newM = (newM - minCMY) / (1 - minCMY) ;
     newY = (newY - minCMY) / (1 - minCMY) ;
     newK = minCMY;
     C = (int)floor(newC * 255);
     M = (int)floor(newM * 255);
     Y = (int)floor(newY * 255);
     K = (int)floor(newK * 255);
}

int Color::CmykToRgb(int C, int M, int Y, int K)
{
    int R, G, B;
    C = minim(255, C + K, 255);
    M = minim(255, 255, M + K);
    Y = minim(255, 255, Y + K);
    R = 255 - C;
    G = 255 - M;
    B = 255 - Y;
    return RgbToArgb(R, G, B);
}



Color::Color(int h, float s, float v)
{
    if(s>1)
    {
        s/=100;
    }
    if(v>1)
    {
        v/=100;
    }
    argb=HsvToRgb(h,s,v);
}

int Color::getB()
{
    int B=argb;
    B=B&0xFF;
    return B;
}

int Color::getR()
{
    int R=argb;
    R=R>>16;
    R=R&0xFF;
    return R;
}

int Color::getG()
{
    int G=argb;
    G=G>>8;
    G=G&0xFF;
    return G;
}

Color& Color::setR(int R)
{
    int B = getB();
    int G = getG();
    if(R > 255) R = 255;
    if(R < 0) R = 0;
    argb = RgbToArgb(R ,G ,B);
    return *this;
}

Color& Color::setB(int B)
{
    int R = getR();
    int G = getG();
    if(B > 255) B = 255;
    if(B < 0) B = 0;
    argb = RgbToArgb(R ,G ,B);
    return *this;
}

Color& Color::setG(int G)
{
    int R = getR();
    int B = getB();
    if(G > 255) G = 255;
    if(G < 0) G = 0;
    argb = RgbToArgb(R ,G ,B);
    return *this;
}


int Color::getH()
{
    int R = getR();
    int G = getG();
    int B = getB();
    int H = 0;
    float S, V;
    RgbToHsv(R, G, B, H, S, V);
    return H;
}

int Color::getS()
{
    int R = getR();
    int G = getG();
    int B = getB();
    int H = 0;
    float S, V;
    RgbToHsv(R, G, B, H, S, V);
    return (int)(S*100);
}

int Color::getV()
{
    int R = getR();
    int G = getG();
    int B = getB();
    int H = 0;
    float S, V;
    RgbToHsv(R, G, B, H, S, V);
    return (int)(V*100);
}

int Color::getC()
{
    int R = getR();
    int G = getG();
    int B = getB();
    int C = 0,M, Y, K;
    RgbToCmyk(R, G, B, C, M, Y, K);
    return C;
}

int Color::getM()
{
    int R = getR();
    int G = getG();
    int B = getB();
    int C,M = 0, Y, K;
    RgbToCmyk(R, G, B, C, M, Y, K);
    return M;
}

int Color::getY()
{
    int R = getR();
    int G = getG();
    int B = getB();
    int C ,M , Y = 0, K;
    RgbToCmyk(R, G, B, C, M, Y, K);
    return Y;
}

int Color::getK()
{
    int R = getR();
    int G = getG();
    int B = getB();
    int C ,M , Y , K = 0;
    RgbToCmyk(R, G, B, C, M, Y, K);
    return K;
}

Color& Color::setC(int C)
{
    int M = getM();
    int Y = getY();
    int K = getK();
    argb = CmykToRgb(C, M, Y, K);
    return *this;
}

Color& Color::setM(int M)
{
    int C = getC();
    int Y = getY();
    int K = getK();
    argb = CmykToRgb(C, M, Y, K);
    return *this;
}

Color& Color::setY(int Y)
{
    int C = getC();
    int M = getM();
    int K = getK();
    argb = CmykToRgb(C, M, Y, K);
    return *this;
}

Color& Color::setK(int K)
{
    int C = getC();
    int M = getM();
    int Y = getY();
    argb = CmykToRgb(C, M, Y, K);
    return *this;
}

Color& Color::setH(int _H)
{
    _H = _H % 360;
    int H;
    float S,V;
    int R = getR();
    int G = getG();
    int B = getB();
    RgbToHsv(R, G, B, H, S, V);
    argb = HsvToRgb(_H,S*100,V*100);
    return *this;
}

Color& Color::setS(int _S)
{
    if (_S < 0) {_S = 0;}
    if (_S > 100) {_S = 100;}
    int H;
    float S,V;
    int R = getR();
    int G = getG();
    int B = getB();
    RgbToHsv(R, G, B, H, S, V);
    argb = HsvToRgb(H,_S,V * 100);
    return *this;
}

Color& Color::setV(int _V)
{
    if (_V < 0) {_V = 0;}
    if (_V > 100) {_V = 100;}
    int H;
    float S,V;
    int R = getR();
    int G = getG();
    int B = getB();
    RgbToHsv(R, G, B, H, S, V);
    argb = HsvToRgb(H,S*100,_V);
    return *this;
}

int Color::getArgb()
{
    return this->argb;
}
