#include "image.hpp"
#include <iostream>

using namespace std;

int main()
{
        ImageRGB imInput;

    if (imInput.LoadBMP("./picasso.bmp")==false)
    {
        cout<<"Could not read image ./picasso.bmp"<<endl;
        return -1;
    }

    Point p;
    PixelRGB turquoise(0, 0.5, 0.5);

    Kernel3x3 ker("blur");
    ImageRGB imOutput;

    imOutput = Convolution(imInput, ker);
    if (imOutput.SaveBMP("./picasso_convolution.bmp")==true)
        cout<<"Output image written to ./picasso_convolution.bmp"<<endl;
    else
        cout<<"Could not write image to ./picasso_convolution.bmp"<<endl;
    return 0;
}
