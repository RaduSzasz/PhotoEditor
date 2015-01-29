#ifndef COLOR_H
#define COLOR_H

class Color
{
private:
    int argb;
    int HsvToRgb(int _H,float _S,float _V);
    void RgbToHsv(int R, int G, int B, int& H, float& S, float& V);
    int RgbToArgb(int R,int G,int B);
    void RgbToCmyk(int R, int G, int B, int &C, int &M, int &Y, int &K);
    int CmykToRgb(int C,int M, int Y, int K);
public:
    Color();
    Color(int setargb);
    Color(int r, int g, int b);
    Color(int h, float s, float v);
    Color& setR(int R);
    Color& setG(int G);
    Color& setB(int B);
    Color& setC(int C);
    Color& setM(int M);
    Color& setY(int Y);
    Color& setK(int K);
    Color& setH(int _H);
    Color& setS(int _S);
    Color& setV(int _V);
    int getR();
    int getG();
    int getB();
    int getH();
    int getS();
    int getV();
    int getC();
    int getM();
    int getY();
    int getK();
    int getArgb();


};

#endif // COLOR_H
