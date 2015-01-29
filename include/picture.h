#ifndef Picture_H
#define Picture_H
#include "gd.h"
#include "color.h"
#include <string>
#include <QImage>

#ifndef null
#define null 0
#endif

class Picture
{
protected:
    gdImagePtr pic;
    void copyFromGdImage(const gdImagePtr x);
    void close();
public:
    Picture();
    Picture(int x,int y);
    Picture(gdImagePtr x);
    Picture(const Picture& picture);
    ~Picture();
    int getHeight();
    int getWidth();
    void resize(int x, int y);
    Picture* clone() const;
    Picture getResizedVersion(int x, int y);
    void crop(int xStart, int yStart, int Width, int Height);
    Picture getCroppedVersion(int xStart, int yStart, int Width, int Height);
    Color getPixel(int x, int y);
    void setPixel(int x, int y, Color a);
    gdImagePtr getGdImagePtr() const;
    void setGdImagePtr(gdImagePtr ptr);
    QImage toQImage();
};

#endif // Picture_H
