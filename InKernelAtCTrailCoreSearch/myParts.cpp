//
//  myParts.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 21/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "myParts.hpp"

void printSliceRowByRow(const SliceValue slice){
    for (unsigned int i = 0; i< 5; i++) {
        bitset<5> output(getRowFromSlice(slice, i));
        cout << " " << output;
    }
    cout << endl;
}
