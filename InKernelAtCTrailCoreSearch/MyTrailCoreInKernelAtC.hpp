//
//  MyTrailCoreInKernelAtC.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef MyTrailCoreInKernelAtC_hpp
#define MyTrailCoreInKernelAtC_hpp

#include <iostream>
#include "myParts.hpp"
#include "myTrailCoreInKernelAtCFilter.hpp"

using namespace std;

class MyTrailCoreInKernelAtC : public InKernelAtCFilter{
public:
    MyTrailCoreInKernelAtC(unsigned int aMaxWeight, KeccakFDCLC& aParent, KeccakFPropagation::DCorLC aDCorLC);

    void XPeers2Slices(const multisetSet aValuePatternForStartingKnot);

    void Case422(const multisetSet aValuePatternSetForStartingKnot);
    void Case532(const multisetSet aValuePatternSetForStaringKnot);


//    void test4Peers3Slices();

    void Case332();
    void Case442();

    void Case433(const multisetSet aValuePatternSetForStartingKnot);
    void Case4222(const multisetSet aValuePatternSetForStartingknot);
    void Case3322A(const multisetSet aValuePatternSetForStartingknot);
    void Case3322B(const multisetSet aValuePatternSetForStartingknot);
    void Case3322C(const multisetSet aValuePatternSetForStartingknot);

    void test();

protected:
    string fileName = "/Users/liuguozhen/Desktop/Core52-60.txt";
};

#endif /* MyTrailCoreInKernelAtC_hpp */
