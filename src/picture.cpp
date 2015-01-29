#include "Picture.h"
#include "gd.h"
#include "color.h"
#include <cstring>


using namespace std;

Picture::Picture()
{
    pic = null;
}

Picture::~Picture()
{
    if(this->pic != null)
        gdFree(this->pic);

}

Picture::Picture(int x, int y)
{
    this->pic = 0;
    this->pic = gdImageCreateTrueColor(x, y);
}

Picture::Picture(gdImagePtr x)
{
    copyFromGdImage(x);
}

Picture::Picture(const Picture& picture)
{
    Picture* _cpy = picture.clone();
    this->pic = _cpy->pic;
}

Picture* Picture::clone() const
{
    Picture *pic = new Picture;
    pic->copyFromGdImage(this->pic);
    return pic;
}

void Picture::close()
{
    if(this->pic > 0)
    {
        gdImageDestroy(this->pic);
        this->pic=0;
    }
}

int Picture::getHeight()
{
    if(this->pic==0)
        return 0;
    return this->pic->sy;
}

int Picture::getWidth()
{
    if(this->pic==0)
        return 0;
    return this->pic->sx;
}

void Picture::copyFromGdImage(const gdImagePtr img)
{
    int x = img->sx;
    int y = img->sy;
    this->pic = gdImageCreateTrueColor(x, y);
    gdImageCopy(this->pic,img,0,0,0,0,x,y);
}

void Picture::resize(int x,int y)
{
    gdImagePtr a = gdImageCreateTrueColor(x, y);
    if (this->pic)
    {
        gdImageCopyResized(a,this->pic,0,0,0,0,x,y,this->pic->sx,this->pic->sy);
        gdFree(this->pic);
    }
    this->pic = a;
}

Picture Picture::getResizedVersion(int x,int y)
{
    gdImagePtr a = gdImageCreateTrueColor(x, y);
	gdImageCopyResized(a,this->pic,0,0,0,0,x,y,this->pic->sx,this->pic->sy);
	return Picture(a);
}

void Picture::crop(int x, int y, int width, int height)
{
    gdImagePtr a = gdImageCreateTrueColor(width,height);
    gdImageCopy (a, this->pic, 0, 0, x, y, width, height);
	gdFree(this->pic);
	this->pic = a;
}

Picture Picture::getCroppedVersion(int xStart, int yStart, int Width, int Height)
{
    gdImagePtr a = gdImageCreateTrueColor(Width,Height);
    gdImageCopy (a, this->pic, 0, 0, xStart, yStart, Width, Height);
    return Picture(a);
}

Color Picture::getPixel(int x, int y)
{
    return Color(gdImageGetPixel (this->pic, x, y));
}

void Picture::setPixel(int x,int y, Color a)
{
    gdImageSetPixel(this->pic, x, y, a.getArgb());
}

gdImagePtr Picture::getGdImagePtr() const
{
    return this->pic;
}

void Picture::setGdImagePtr(gdImagePtr ptr)
{
    if (pic != NULL)
    {
        delete pic;
    }
    pic = ptr;
}

QImage Picture::toQImage()
{
    QImage result(this->getWidth(), this->getHeight(), QImage::Format_ARGB32);
    for (int x = 0; x < this->getWidth(); x++)
    {
        for (int y = 0; y < this->getHeight(); y++)
        {
            result.setPixel(x,y,gdImageGetPixel (this->pic, x, y) & 0xFFFFFF | 0xFF000000);
        }
    }
    return result;
}
