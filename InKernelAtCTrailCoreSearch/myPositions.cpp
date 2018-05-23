//
//  myPositions.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 21/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "myPositions.hpp"
#include <iomanip>

myBitPosition::myBitPosition(unsigned int ax, unsigned int ay, unsigned int az)
: x(ax), y(ay), z(az)
{
}

myBitPosition::myBitPosition(const myBitPosition& aPoint)
: x(aPoint.x) , y(aPoint.y) , z(aPoint.z)
{
}

ostream& operator<<(ostream& fout, const myBitPosition& point)
{
    fout << "(" << dec << point.x << "," << point.y << ","<< std::setw(2) << point.z << ") ";
    return fout;
}

bool myBitPosition::operator==(const myBitPosition& otherPoint) const
{
    return (x==otherPoint.x && y==otherPoint.y && z==otherPoint.z);
}

bool myBitPosition::operator<(const myBitPosition& otherPoint) const
{
    if (z <  otherPoint.z) return true;
    else if (z == otherPoint.z) {
        if (y <  otherPoint.y) return true;
        else if (y == otherPoint.y) {
            if (x < otherPoint.x) return true;
        }
    }
    return false;
}

bool myBitPosition::nextXY()
{
    if(y<4) {
        y++;
        return true;
    }
    if (x<4){
        y=0;
        x++;
        return true;
    }
    return false;
}

void myBitPosition::set(unsigned int ax, unsigned int ay, unsigned int az)
{
    x = ax;
    y = ay;
    z = az;
}

void myBitPosition::xTranslate(int dx)
{
    x = ((((int)x+dx)%5)+5)%5;
}

void myBitPosition::yTranslate(int dy)
{
    y = ((((int)y+dy)%5)+5)%5;
}


void myBitPosition::zTranslate(int dz, unsigned int aLaneSize)
{
    z = ((((int)z+dz)%aLaneSize)+aLaneSize)%aLaneSize;
}

void myBitPosition::directXYPi(){
    unsigned int X = x;
    unsigned int Y = y;
    x = (0*X + 1*Y)%5;
    y = (2*X + 3*Y)%5;
}

void myBitPosition::inverseXYPi(){
    unsigned int X = x;
    unsigned int Y = y;
    x = (1*X + 3*Y)%5;
    y = (1*X + 0*Y)%5;
}

void myBitPosition::directRhoPi(){
    unsigned int offset[5][5] = {//[x][y] fashion, my state is [y][x]fashion
        {0, 36, 3, 41, 18},
        {1, 44, 10, 45, 2},
        {62, 6, 43, 15, 61},
        {28, 55, 25, 21, 56},
        {27, 20, 39, 8, 14}
    };
    unsigned int Z = z;
    unsigned int X = x;
    unsigned int Y = y;
    z = (640 + Z + offset[X][Y])%64;
    x = (0*X + 1*Y)%5;
    y = (2*X + 3*Y)%5;
    return;
}

void myBitPosition::inverseRhoPi(){
    unsigned int offset[5][5] = {//[x][y] fashion, my state is [y][x]fashion
        {0, 36, 3, 41, 18},
        {1, 44, 10, 45, 2},
        {62, 6, 43, 15, 61},
        {28, 55, 25, 21, 56},
        {27, 20, 39, 8, 14}
    };
    unsigned int X = x;
    unsigned int Y = y;
    unsigned int Z = z;
    x = (1*X + 3*Y)%5;
    y = (1*X + 0*Y)%5;
    z = (640 + Z - offset[x][y])%64;
    return;
}

bool operator<(const myColumnPosition& aCP, const myColumnPosition& bCP)
{
    return (aCP.getXplus5Z() < bCP.getXplus5Z());
}

ostream& operator<<(ostream& fout, const myColumnPosition& aCP)
{
    fout << "(" << aCP.x << ",-," << aCP.z << ") ";
    return fout;
}

bool operator<(const myRowPosition& aRP, const myRowPosition& bRP)
{
    return (aRP.getYplus5Z() < bRP.getYplus5Z());
}

ostream& operator<<(ostream& fout, const myRowPosition& aRP)
{
    fout << "(-," << aRP.y << "," << aRP.z << ") ";
    return fout;
}
