#ifndef _IMAGE_HPP
#define _IMAGE_HPP

#include<string>
#include<cassert>
#include<algorithm> // for std::clamp

class Point
{
  // Member variables
  public:
    int x,y;

  // Member functions
  public:
    Point();
    Point(int,int);

    Point operator +(const Point &) const;
    Point operator -() const;
    Point operator -(const Point &) const;
    Point operator *(float) const;
    Point operator /(float) const;

    // Compound assignment operators (in-place)
    Point &operator +=(const Point &);
    Point &operator -=(const Point &);
    Point &operator *=(float);
    Point &operator /=(float);
};

// Product of real number and Point
Point operator *(float, const Point &);

class PixelRGB
{
  // Member variables
  public:
    float red, green, blue;

  // Member functions
  public:
    PixelRGB();
    PixelRGB(float, float, float);

    PixelRGB operator +(const PixelRGB &) const;
    PixelRGB operator -() const;
    PixelRGB operator -(const PixelRGB &) const;
    PixelRGB operator *(float) const;
    PixelRGB operator /(float) const;

    // Compound assignment operators (in-place)
    PixelRGB &operator +=(const PixelRGB &);
    PixelRGB &operator -=(const PixelRGB &);
    PixelRGB &operator *=(float);
    PixelRGB &operator /=(float);
};

// Product of real number and RGB pixel
PixelRGB operator *(float, const PixelRGB &);

class ImageRGB
{
  // Member variables
  public:
    int width, height;
    PixelRGB *pixels;

  // Member functions
  public:
    ImageRGB();
    ImageRGB(const ImageRGB &);
    ~ImageRGB();
    void Empty();

    int GetWidth() const;
    int GetHeight() const;

    ImageRGB &operator =(const ImageRGB &);

    // Pixel access
    const PixelRGB &At(int x, int y) const;
    PixelRGB &At(int x, int y);
    const PixelRGB &At(const Point &) const;
    PixelRGB &At(const Point &);
    const PixelRGB &operator [](const Point &) const;
    PixelRGB &operator[](const Point &);

    bool Create(int, int);
    //Create sparse RGB image (black)
    bool CreateZeros(int, int);

    bool LoadBMP(const char *);
    bool SaveBMP(const char *) const;

    // Basic processing
    ImageRGB InvertRedBlue() const;

    //Additionner
    ImageRGB operator +(const ImageRGB&);
    ImageRGB operator /(float );
    ImageRGB flip(bool);
};

// CONVOLUTION

class Kernel3x3
{
protected:
    int width, height;
    float *kernels;
public:
    Kernel3x3();
    Kernel3x3(std::string);

    PixelRGB dot(ImageRGB&);
};


/*      Image convolution, zero-padding, unit stride
    Input: Kernel ker
    Output: Convolved image
*/
ImageRGB Convolution(ImageRGB& img, Kernel3x3&);

#endif
