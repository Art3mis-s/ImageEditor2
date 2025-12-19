//
//  ImageEditor.cpp
//  ImageEditor
//
//  Created by Shabana Qasemi on 10/6/25.
//
#include "ImageEditor.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

ImageEditor::ImageEditor(string inFileName)
{
    pic = Picture(inFileName);
}

void ImageEditor::save(string outFileName)
{
    pic.save(outFileName);
}
//Invert all colors and return *this (image negative)
// returning each color into its opposite
ImageEditor& ImageEditor::operator-()
{
    for (int i = 0; i < pic.width(); i++)
    {
        for (int j = 0; j < pic.height(); j++)
        {
            int r = pic.red(i, j);
            int g = pic.green(i, j);
            int b = pic.blue(i, j);
            
            r = 255 - r;
            g = 255 - g;
            b = 255 - b;
            
            pic.set(i, j, r, g, b);
        }
    }
    return *this;
}

// darkening the image,
ImageEditor& ImageEditor::operator-=(const Color& c) //subract c from all pixels
{
    for (int i = 0; i < pic.width(); i++)
    {
        for (int j = 0; j < pic.height(); j++)
        {
            int r = pic.red(i, j);
            int g = pic.green(i, j);
            int b = pic.blue(i, j);

            // subtracting from the color's objects (r, g, b)
            int newR = r - c.r;
            int newG = g - c.g;
            int newB = b - c.b;
            
            // clipping the values using max so it returns 0 even if value is less than 0
            newR = max(0, newR);
            newG = max(0, newG);
            newB = max(0, newB);
            
            // updating the pixel with the new values
            pic.set(i, j, newR, newG, newB);
        }
    }
    return *this;
}

// c is the object that the user provides
// lightening 
ImageEditor& ImageEditor::operator+=(const Color& c) //add c to all pixels
{
    for (int i = 0; i < pic.width(); i++)
    {
        for (int j = 0; j < pic.height(); j++)
        {
            int r = pic.red(i, j);
            int g = pic.green(i, j);
            int b = pic.blue(i, j);

            // subtracting from the color's objects (r, g, b)
            int newR = r + c.r;
            int newG = g + c.g;
            int newB = b + c.b;
            
            // clipping the values using max so it returns 0 even if value is less than 0
            newR = min(255, newR);
            newG = min(255, newG);
            newB = min(255, newB);
            
            // updating the pixel with the new values
            pic.set(i, j, newR, newG, newB);
        }
    }
    return *this;
}

bool ImageEditor::operator==(const ImageEditor& ie) const  //compare to another image
{
    if (ie.pic.width() != pic.width() || ie.pic.height() != pic.height())
    {
        return false;
    }
    for (int i = 0; i < pic.width(); i++)
    {
        for (int j = 0; j < pic.height(); j++)
        {
            if (ie.pic.red(i, j) != pic.red(i, j) ||
                ie.pic.green(i, j) != pic.green(i, j) ||
                ie.pic.blue(i, j) != pic.blue(i, j))
            {
                return false;
            }
        }
    }
    return true;
}

bool ImageEditor::operator!=(const ImageEditor& ie) const  //compare to another image
{
    // *this is the pikachu image itself
    // if its not equal to the second image then return true
    return !(*this == ie);
}

ImageEditor& ImageEditor::operator*=(unsigned int n)//expand by factor of n by n
{
    // Checking if n is valid
    if (n < 1 || n > 10)
    {
        throw runtime_error("Whoa there, I can't handle that level of zoom - n must be between 1 - 10!");
    }
    
    // Creating a new Picture object with expanded size
    Picture picOut(pic.width() * n, pic.height() * n);
    
    // Counters
    
    // Quadruple nested loop
    for (int i = 0; i < pic.width(); i++)
    {
        for (int j = 0; j < pic.height(); j++)
        {
            int r = pic.red(i, j);
            int g = pic.green(i, j);
            int b = pic.blue(i, j);
            
            // iOut and jOut loop through 0 → 2 (3 times each) for each pixel
            for (int iOut = 0; iOut < n; iOut++)
            {
                for (int jOut = 0; jOut < n; jOut++)
                {
                    // So the pixel (0,0) becomes a nxn square that fills (0,0), (1,0), (0,1), (1,1) in the new image — all with the same color (r, g, b)
                    picOut.set(i * n + iOut, j * n + jOut, r, g, b);
                }
            }
        }
    }
    pic = picOut;
    return *this;
}

void ImageEditor::overlay(string fileName)
{
    Picture pic2(fileName);
    for (int y = 0; y < pic2.height() && y < pic.height(); y++)
    {
        for (int x = 0; x < pic2.width() && x < pic.width(); x++)
        {
            if (x % 2 == 0)
            {
                pic.set(x, y, pic2.red(x, y), pic2.green(x, y), pic2.blue(x,y));
            }
        }
    }
}

 // EXTRA CREDIT
/* void ImageEditor::addShadow(int offsetX, int offsetY, float darkness)
{
    int newWidth = pic.width() + offsetX;
    int newHeight = pic.height() + offsetY;
    Picture shadowPic(newWidth, newHeight, 255, 255, 255); // start white

    for (int x = 0; x < pic.width(); x++)
    {
        for (int y = 0; y < pic.height(); y++)
        {
            int r = pic.red(x, y);
            int g = pic.green(x, y);
            int b = pic.blue(x, y);

            if ((r + g + b) > 60)
            {
                int newR = (int)(r * darkness);
                int newG = (int)(g * darkness);
                int newB = (int)(b * darkness);

                if (x + offsetX < newWidth && y + offsetY < newHeight)
                    shadowPic.set(x + offsetX, y + offsetY, newR, newG, newB);
            }
        }
    }

    // Overlay original image safely
    for (int x = 0; x < pic.width(); x++)
        for (int y = 0; y < pic.height(); y++)
            shadowPic.set(x, y, pic.red(x, y), pic.green(x, y), pic.blue(x, y));

    pic = shadowPic;
}

*/



