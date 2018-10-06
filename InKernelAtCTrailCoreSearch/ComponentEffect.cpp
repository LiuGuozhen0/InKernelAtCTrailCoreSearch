//
//  ComponentEffect.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by Liu Guozhen on 2018/9/28.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "ComponentEffect.hpp"

// -------------------------------------------------------------
//
// RhoPIEffect
//
// -------------------------------------------------------------
RhoPiEffect::RhoPiEffect(unsigned int aWidth) : KeccakF(aWidth){
//    rhoEffectOnSlices();
    rhoPiEffectOnRows();
}

void RhoPiEffect::rhoEffectOnSlices(){
    aSlice.resize(25);
    for (int i=0; i<laneSize; i++) {
        for (int j=0; j<25; j++) {
            //            aSlice[j] = i;
            aSlice[j] = (i + rhoOffsets[j]) % laneSize;
        }
        for (int y=0; y<5; y++) {
            for (int x=0; x<5; x++) {
                cout << aSlice[index(x, y)]<< " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void RhoPiEffect::rhoPiEffectOnRows(){
    for (int z=0; z<laneSize; z++) {
        for (int y=0; y<nrRowsAndColumns; y++) {
            for (int x=0; x<nrRowsAndColumns; x++) {
                BitPosition P(x,y,z);
                P.z = rho(P.x,P.y,P.z);
                pi(x,y,P.x,P.y);
                cout << (P.y+5*P.z) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}



































