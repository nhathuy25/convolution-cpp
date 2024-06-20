#include "image.hpp"
#include <iostream>
#include <cassert>

using namespace std;

/******************************************************************************
                              Point
******************************************************************************/
Point::Point()
{
}

Point::Point(int px, int py)
{
    x = px;
    y = py;
}

Point Point::operator +(const Point &p) const
{
    Point res;
    res.x = x + p.x;
    res.y = y + p.y;
    return res;
}

Point Point::operator -() const
{
    Point res;
    res.x = -x;
    res.y = -y;
    return res;
}

Point Point::operator -(const Point &p) const
{
    Point res;
    res.x = x - p.x;
    res.y = y - p.y;
    return res;
}

Point Point::operator *(float f) const
{
    Point res;
    res.x = (int)(x*f);
    res.y = (int)(y*f);
    return res;
}

Point Point::operator /(float f) const
{
    assert(f!=0);
    Point res;
    res.x = (int)(x/f);
    res.y = (int)(y/f);
    return res;
}

Point &Point::operator +=(const Point &p)
{
    x += p.x;
    y += p.y;
    return *this;
}

Point &Point::operator -=(const Point &p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}

Point &Point::operator *=(float f)
{
    x = (int)(f*x);
    y = (int)(f*y);
    return *this;
}

Point &Point::operator /=(float f)
{
    assert(f!=0);
    x = (int)(x/f);
    y = (int)(y/f);
    return *this;
}

// Non-member function! Product of real number with point
Point operator *(float f, const Point &p)
{
    return p*f;
}

/******************************************************************************
                              PixelRGB
******************************************************************************/
PixelRGB::PixelRGB()
{
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

PixelRGB::PixelRGB(float r, float g, float b)
{
    red = r;
    green = g;
    blue = b;
}

//a)
/*
        c = a + b;  ~~ c = a.operator+(b);
*/

PixelRGB PixelRGB::operator +(const PixelRGB &p) const
{
    PixelRGB tmp;
    tmp.red = red + p.red;
    tmp.green = green + p.green;
    tmp.blue = blue + p.blue;
    return tmp;
}

PixelRGB PixelRGB::operator -() const
{
    PixelRGB tmp;
    tmp.red = -red;
    tmp.green = -green;
    tmp.blue = -blue;
    return tmp;
}

PixelRGB PixelRGB::operator -(const PixelRGB &p) const
{
    PixelRGB tmp;
    tmp.red = red - p.red;
    tmp.green = green - p.green;
    tmp.blue = blue - p.blue;
    return tmp;
}

PixelRGB PixelRGB::operator *(float f) const
{
    PixelRGB tmp;
    tmp.red = red*f;
    tmp.green = green*f;
    tmp.blue = blue*f;
    return tmp;
}

PixelRGB PixelRGB::operator /(float f) const
{
    PixelRGB tmp;
    tmp.red = red/f;
    tmp.green = green/f;
    tmp.blue = blue/f;
    return tmp;
}

PixelRGB &PixelRGB::operator +=(const PixelRGB &p)
{
    red += p.red;
    blue += p.blue;
    green += p.green;
    return *this;
}

PixelRGB &PixelRGB::operator -=(const PixelRGB &p)
{
    red -= p.red;
    blue -= p.blue;
    green -= p.green;
    return *this;
}

PixelRGB &PixelRGB::operator *=(float f)
{
    red *= f;
    blue *= f;
    green *= f;
    return *this;
}

PixelRGB &PixelRGB::operator /=(float f)
{
    red /= f;
    blue /= f;
    green /= f;
    return *this;
}


/******************************************************************************
                              ImageRGB
******************************************************************************/

ImageRGB::ImageRGB()
{
    width = 0;
    height = 0;
    pixels = nullptr;
}

ImageRGB::ImageRGB(const ImageRGB &im)
{
    width = im.width;
    height = im.height;

    if (width!=0 && height!=0)
    {
        pixels = new PixelRGB[width*height];
        for (int i=0; i<width*height; i++)
            pixels[i] = im.pixels[i];
    }
    else pixels = nullptr;
}

ImageRGB::~ImageRGB()
{
    Empty();
}

void ImageRGB::Empty()
{
    if (pixels!=nullptr)
        delete[] pixels;

    width = 0;
    height = 0;
    pixels = nullptr;
}

int ImageRGB::GetWidth() const
{
    return width;
}

int ImageRGB::GetHeight() const
{
    return height;
}

const PixelRGB &ImageRGB::At(int x, int y) const
{
    assert(x>=0 && x<width && y>=0 && y<height);
    return pixels[y*width+x];
}

PixelRGB &ImageRGB::At(int x, int y)
{
    assert(x>=0 && x<width && y>=0 && y<height);
    return pixels[y*width+x];
}

const PixelRGB &ImageRGB::At(const Point &p) const
{
    return At(p.x,p.y);
}

PixelRGB &ImageRGB::At(const Point &p)
{
    return At(p.x,p.y);
}

const PixelRGB &ImageRGB::operator[](const Point &p) const
{
    return At(p.x,p.y);
}

PixelRGB &ImageRGB::operator[](const Point &p)
{
    return At(p.x,p.y);
}

ImageRGB &ImageRGB::operator =(const ImageRGB &im)
{
    Empty();

    width = im.width;
    height = im.height;

    if (width!=0 && height!=0)
    {
        pixels = new PixelRGB[width*height];
        for (int i=0; i<width*height; i++)
            pixels[i] = im.pixels[i];
    }

    return *this;
}

bool ImageRGB::Create(int w, int h)
{
    Empty();

    if (w>0 && h>0)
    {
        width = w;
        height = h;
        pixels = new PixelRGB[width*height];
        return true;
    }
    else
        return false;
}

bool ImageRGB::CreateZeros(int w, int h)
{
    Empty();
    if (w>0 && h>0)
    {
        width = w;
        height = h;
        pixels = new PixelRGB[width*height];

        for(int i=0; i<width*height; i++)
            pixels[i] = PixelRGB(0, 0, 0);
        return true;
    }
    else
        return false;
}


ImageRGB ImageRGB::InvertRedBlue() const
{
    ImageRGB imInvert;
    Point p;

    imInvert.Create(width, height);
    for (p.y=0; p.y<height; p.y++)
    {
        for (p.x=0; p.x<width; p.x++)
        {
            imInvert.At(p).red = At(p).blue;
            imInvert.At(p).green = At(p).green;
            imInvert.At(p).blue = At(p).red;
        }
    }

    return imInvert;
}

ImageRGB ImageRGB::operator+(const ImageRGB& img)
{
    assert(width == img.width && height == img.height);

    ImageRGB imSum;
    Point p;

    imSum.Create(width, height);

    for(p.y = 0; p.y<height; p.y++){
        for(p.x = 0; p.x < width; p.x++)
        {
            imSum.At(p) = this->At(p) + img.At(p);
            //ou
        }
    }
    return imSum;
}

ImageRGB ImageRGB::operator /(float f)
{
    ImageRGB img;
    Point p;

    img.Create(width, height);

    for(p.y = 0; p.y < height; p.y++){
        for(p.x = 0; p.x < width; p.x++){
            img.At(p) = this->At(p) / f;
        }
    }
    return img;
}

ImageRGB ImageRGB::flip(bool i)
{
    ImageRGB img;
    Point p;
    img.Create(height, width);
    if(i == 1){
        for(p.x = 0; p.x < width; p.x++){
            for(p.y = 0; p.y < height; p.y++){
                img.At(height - p.y, p.x) = this->At(p);
            }
        }
    }
    return img;
}

/******************************************************************************
                            Convolution method
******************************************************************************/

Kernel3x3::Kernel3x3()
{
    height = 3;
    width = 3;
    kernels = new float[3*3];
    for(int i=0; i<9; i++)
        kernels=0;
}

Kernel3x3::Kernel3x3(string type)
{
    height = 3;
    width = 3;
    kernels = new float[width*height];
    //
    if(type.compare("none") == 0){
        for(int i=0; i<width*height; i++)
            kernels[i] = 1;
    }

/*  Vertical edge detection kernel
    1 0 -1
    2 0 -2
    1 0 -1  */
    if(type.compare("vertical") == 0){
        for(int i=0; i<width; i++){
            if(i==1)
            {
                kernels[i*height] = 2;
                kernels[i*height+2] = -2;
            }
            else{
                kernels[i*height] = 1;
                kernels[i*height+2] = -1;
            }
            kernels[i*height+1] = 0;
        }
    }

    /*  Horizontal edge detection kernel
    1  2  1
    0  0  0
   -1 -2 -1  */
    if(type.compare("horizontal") == 0){
        for(int i=0; i<width; i++){
            if(i==0)
            {
                kernels[i*height] = 1;
                kernels[i*height+1] = 2;
                kernels[i*height+2] = 1;
            }
            else if(i==2){
                kernels[i*height] = -1;
                kernels[i*height+1] = -2;
                kernels[i*height+2] = -1;
            }
            kernels[1*height+i] = 0;
        }
    }
    /*  Blur kernel
    0.111 0.111 0.111
    0.111 0.111 0.111
    0.111 0.111 0.111 */
    if(type.compare("blur") == 0)
        for(int i=0; i<height*width; i++)
            kernels[i] = 1/9;
}

PixelRGB Kernel3x3::dot(ImageRGB& img)
{
    PixelRGB pix;
    assert(img.GetHeight()==height && img.GetWidth()==width);

    for (int x=0; x<width; x++)
    {
        for(int y=0; y<height; y++)
        {
            pix.red += kernels[y*width+x]*(img.At(x,y).red);
            pix.green += kernels[y*width+x]*img.At(x,y).green;
            pix.blue += kernels[y*width+x]*img.At(x,y).blue;
        }
    }
    //pix/=9;
    return pix;
}


ImageRGB Convolution(ImageRGB& img, Kernel3x3& kernel)
{
    int width = img.GetWidth();
    int height = img.GetHeight();

    ImageRGB output, padded_img;
    Point p;

    output.Create(width, height);
    padded_img.CreateZeros(width+2, width+2);

    /*
    // Fill the sparse padded image with input image, create a zero-padding input image
    for(int x=1; x<padded_img.GetWidth() + 1; x++)
    {
        for(int y=1; y<padded_img.GetHeight() + 1; y++)
        {
            padded_img.pixels[y*padded_img.GetWidth() + x] = img.At(x-1, y-1);
        }
    }
    */
    // Doing the cross-correlation (convolution) | with the original image
    for(int x=0; x<width-2; x++)
    {
        for(int y=0; y<height-2; y++)
        {
            // Create a 3x3 micro-image from the current input image to do the convolution with kernel
            ImageRGB img_3x3;
            img_3x3.Create(3, 3);
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; j++)
                    img_3x3.pixels[i*3 + j] = img.At(x+i, y+j);
            }
            // Cross-correlation between the filter and 3x3 mini-image
            output.At(x, y) = kernel.dot(img_3x3);
        }
    }

    return output;
}
