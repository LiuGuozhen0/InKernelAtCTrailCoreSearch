//
//  myParts.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 21/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef myParts_hpp
#define myParts_hpp

#include <bitset>
#include <iostream>
#include "types.h"

using namespace std;

typedef unsigned char RowValue;
typedef UINT32 SliceValue;

inline SliceValue getSliceFromRow(const RowValue row, const unsigned int y){
    return (SliceValue)row << (5*y);
}
inline RowValue getRowFromSlice(const SliceValue slice, unsigned int y){
    return ((slice >> (5*y)) & 0x1f);
}

void printSliceRowByRow(const SliceValue slice);

#endif /* myParts_hpp */
