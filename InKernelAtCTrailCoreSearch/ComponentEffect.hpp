//
//  ComponentEffect.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by Liu Guozhen on 2018/9/28.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef ComponentEffect_hpp
#define ComponentEffect_hpp

#include <stdio.h>

#include "Keccak-fParts.h"

class RhoPiEffect : public KeccakF{
protected:
    vector<unsigned int> aSlice;
public:
    RhoPiEffect(unsigned int aWidth);
    /**
      * This function prints the index of slices(e.g., 0, 1, ..., 63) each bit are transferred to through 𝜌.
      */
    void rhoEffectOnSlices();
    /**
      * The function prints the index of rows(y+5*z) that each bit position will be placed after 𝜌 and 𝜋 to the screen.
      */
    void rhoPiEffectOnRows();
};

class ChiEffect : RhoPiEffect {
    ;
    
public:
    ;
};

#endif /* ComponentEffect_hpp */
