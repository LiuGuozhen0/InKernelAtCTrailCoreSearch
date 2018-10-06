//
//  myTrailCoreInKernelAtCFilter.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "translationsymmetry.h"
#include "myTrailCoreInKernelAtCFilter.hpp"

InKernelAtCFilter::InKernelAtCFilter(unsigned int aMaxWeight, KeccakFDCLC& aParent, KeccakFPropagation::DCorLC aDCorLC):InKernelAtCStructureConstruct(aMaxWeight, aParent, aDCorLC){
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_XPeers2Slices(){
    if (peerParameterOnRho.size() > 0) {
        unsigned int lastPeerParameter = peerParameterOnRho.back();
        for (int i = 0; i < peerParameterOnRho.size(); i++) {
            if (lastPeerParameter != peerParameterOnRho[i]) {
                return false;
            }
        }
        return true;
    }
    else {
        cout << "Error! Less than 1 peer parameter!" << endl;
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_422(){
    if (peerParameterOnRho.size() == 4) {
        unsigned int value1 = peerParameterOnRho[0];
        bool find1 = false, find2 = false;
        vector<unsigned int> aParameterSet;
        for (int i=1; i<peerParameterOnRho.size(); i++) {
            if (peerParameterOnRho[i] == value1) {
                find1 = true;
            }
            else {
                aParameterSet.push_back(peerParameterOnRho[i]);
            }
        }
        if (aParameterSet.size() == 2) {
            if (aParameterSet[0] == aParameterSet[1]) {
                find2 = true;
            }
            if (find1 && find2) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        if (!isLastStructureOfStartingKnot) {
            cout << "Error! Less than 1 peer parameter!" << endl;
        }
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_332(){
    if ((peersAtA.size()==4) && (peerParameterOnRho.size()==4)) {
        if (peerParameterOnRho[0] == peerParameterOnRho[1]) {
            if (peerParameterOnRho[2] == ((peerParameterOnRho[0] + 64 -  peerParameterOnRho[3])%64)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        if (!isLastStructureOfStartingKnot) {
            cout << "Error! Less than 1 peer parameter!" << endl;
        }
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_532(){
    if ((peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
        vector<vector<int>> index{{0,1,2,3,4}, {0,1,3,2,4}, {0,2,3,1,4}, {1,2,3,0,4}, {0,1,4,2,3}, {0,2,4,1,3}, {1,2,4,0,3}, {0,3,4,1,2}, {1,3,4,0,2}, {2,3,4,0,1}};
        for (int i=0; i<10; i++) {
            vector<unsigned int> v(5,0);
            for (int j=0; j<5; j++) {
                v[j] = peerParameterOnRho[index[i][j]];
            }
            if (((v[0]==v[1]) && (v[1]==v[2])) && (v[3]==v[4]) && (v[0]!=v[4])) {
                return true;
            }
        }
        return false;
    }
    else {
        if (!isLastStructureOfStartingKnot) {
            cout << "Error! Less than 5 peer parameter!" << endl;
        }
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_442(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[1])) {
        if ((peerParameterOnRho[1]) == (peerParameterOnRho[2])) {
            if ((peerParameterOnRho[0]) == ((peerParameterOnRho[3]+peerParameterOnRho[4])%64)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_433(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[1])) {
        if ((peerParameterOnRho[2]) == (peerParameterOnRho[3])) {
            if ((peerParameterOnRho[2]) == ((peerParameterOnRho[0]+64-peerParameterOnRho[4])%64)) {
                return true;
            }
            else {
                return false;
            }
//            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_4222(){
    if ((peerParameterOnRho[2]) == (peerParameterOnRho[3])) {
        if ((peerParameterOnRho[1]) == ((peerParameterOnRho[0]+peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_3322A(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[1])) {
        if ((peerParameterOnRho[2]) == ((peerParameterOnRho[0]+128-peerParameterOnRho[3]-peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_3322B(){
    if ((peerParameterOnRho[1]) == ((peerParameterOnRho[0]+64-peerParameterOnRho[3])%64)) {
        if ((peerParameterOnRho[2]) == ((peerParameterOnRho[0]+64-peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_3322C(){
    if ((peerParameterOnRho[1]) == (peerParameterOnRho[2])) {
        if ((peerParameterOnRho[3]) == ((64-peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::checkMappedToSameSlice3322C(){
    BitPosition q5B(peersAtA.back().back());//q5 at A
    q5B.directRhoPi();
    BitPosition q1B(peersAtA[0].back());//q1 at A
    q1B.directRhoPi();
    if ((q1B.z) == (q5B.z)) {
        return true;
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::populateKnotsAtBStep1(){
    bitSetForMinimalStateB.clear();
    for (unsigned int nrPeers = 0; nrPeers < peersAtA.size(); nrPeers ++) {
        if (peersAtA[nrPeers].size() != 2) {
            cout << "Error! There aren't 2 bits at one peer!" << endl;
            return false;
        }
        else {
            for (unsigned int nrBits = 0; nrBits < peersAtA[nrPeers].size(); nrBits ++) {
                BitPosition pB(peersAtA[nrPeers][nrBits]);//p
                pB.directRhoPi();//p"
                knotsAtB[pB.z].bitsChain.push_back(pB);
                knotsAtB[pB.z].nrBits++;
                bitSetForMinimalStateB.insert(pB);
            }
        }
    }
    return true;
}

bool InKernelAtCFilter::populateKnotsAtBStep2(){
    map<unsigned int, KnotAtBInfo>::iterator itKnot;
    for (itKnot = knotsAtB.begin(); itKnot != knotsAtB.end(); itKnot++) {
        if ((itKnot->second).nrBits >= 2) {
            itKnot->second.sliceValue = getSliceValueFromBitChain(itKnot->second.bitsChain);
            itKnot->second.valuePattern = getValuePatternFromSlice(itKnot->second.sliceValue);
            itKnot->second.isInKernelAtC = valuePatternInKernelAtCCheck(itKnot->second.nrBits, itKnot->second.valuePattern);
        }
        else {
            cout << "Error! Less than 2 bits in one knot!" << endl;
            return false;
        }
    }
    return true;
}

bool InKernelAtCFilter::checkKnotsAtBInKernelAtC(){
    if (populateKnotsAtBStep1() && populateKnotsAtBStep2()) {
        map<unsigned int, KnotAtBInfo>::iterator itKnot;
        for (itKnot = knotsAtB.begin(); itKnot != knotsAtB.end(); itKnot++) {
            if (!itKnot->second.isInKernelAtC) {
//                cout << "This knot can't lead to at least one inkernel slice after chi!" << endl;
                return false;
            }
        }
        return true;
    }
    else{
        cout << "Error at the populating knots at B stage!" << endl;
        return false;
    }
}

bool InKernelAtCFilter::updateSetOfMinimalStatesUpToNow(){
    set<BitPosition> abitSetForMinimalStateB = bitSetForMinimalStateB;
    for (int dz = 0; dz < 64; dz ++) {
        set<BitPosition> aMin;
        set<BitPosition>::iterator itBitSet;
        for (itBitSet = abitSetForMinimalStateB.begin(); itBitSet != abitSetForMinimalStateB.end(); itBitSet++) {
            BitPosition aBit((*itBitSet));
            aBit.zTranslate(dz, 64);
            aMin.insert(aBit);
        }
        if (aMin < bitSetForMinimalStateB) {
            bitSetForMinimalStateB = aMin;
        }
    }
    if (setOfBitSetForMinimalStateBUpToNow.insert(bitSetForMinimalStateB).second == false) {
//        cout << "Minimal state of this state AtB has already existed!" << endl;
        return false;
    }
    else {
        return true;
    }
}


void InKernelAtCFilter::prepareOutputTrailCore(){
    workCore.clear();
    stateAtA.clear();
    stateAtB.clear();
    partialStateAtD.clear();
    for (int i = 0; i < 64; i ++) {
        stateAtA.push_back(0);
        stateAtB.push_back(0);
        partialStateAtD.push_back(0);
    }

    for (int nrPeer = 0; nrPeer < peersAtA.size(); nrPeer++) {
        if (peersAtA[nrPeer].size() == 2) {
            for (int nrBit = 0; nrBit < peersAtA[nrPeer].size(); nrBit++) {
                setBitToOne(stateAtA, peersAtA[nrPeer][nrBit]);
            }
        }
        else {
            cout << "Error! There aren't 2 bits in oen peer!" << endl;
        }
    }

    vector<SliceValue> partialStateAtC(64);
    map<unsigned int, KnotAtBInfo>::iterator itKnot;
    for (itKnot = knotsAtB.begin(); itKnot != knotsAtB.end(); itKnot ++) {
        stateAtB[itKnot->first] = itKnot->second.sliceValue;
        partialStateAtC[itKnot->first] = getMinimumInKernelSliceAfterChi(itKnot->second.sliceValue);
//        partialStateAtC[itKnot->first] = myGetMinimumInKernelSliceAfterChi(itKnot->second.sliceValue);
    }
    weightAtB = getWeight(stateAtB);
    directLambdaAfterTheta(partialStateAtC, partialStateAtD);
    unsigned int reverseWeightA = getMinReverseWeight(stateAtA);
    unsigned int partialWeightD = getWeight(partialStateAtD);
    partialWeight = getMinReverseWeight(stateAtA) + weightAtB + getWeight(partialStateAtD);

    minWeightBAndC = weightAtB + partialWeightD;

    CoreInfo currentCore;
    currentCore.stateAtB = stateAtB;
    currentCore.partialStateAtC = partialStateAtC;
    currentCore.partialWeight = partialWeight;
    currentCore. weightAtB = weightAtB;
    getSymmetricMinimum(stateAtB, currentCore.minimalStateAtB);
    workCore.push_back(currentCore);

    return;
}

SliceValue InKernelAtCFilter::myGetMinimumInKernelSliceAfterChi(const SliceValue sliceBeforeChi){
    SliceValue minimalsliceAfterChi = maxSliceValue;
    vector<RowValue> rowsBefore;
    vector<vector<RowValue>> outputDiffs;
    vector<unsigned int> index;
    for (unsigned int y = 0; y < 5; y++) {
        RowValue rowBefore = getRowFromSlice(sliceBeforeChi, y);
        if (rowBefore) {
            rowsBefore.push_back(rowBefore);
            vector<RowValue> aValue = directRowOutputListPerInput[rowBefore].values;
            outputDiffs.push_back(aValue);
            index.push_back(0);
        }
    }
    do {
        RowValue parity = 0;
        for (unsigned int i = 0; i < rowsBefore.size(); i++) {
            parity ^= outputDiffs[i][index[i]];
        }
        if (parity == 0) {
            SliceValue sliceAfterChi = 0;
            int nrRows = 0;
            for (unsigned int y = 0; y < 5; y++) {
                RowValue rowBefore = getRowFromSlice(sliceBeforeChi, y);
                if (rowBefore) {
                    sliceAfterChi ^= getSliceFromRow(outputDiffs[nrRows][index[nrRows]], y);
                    nrRows++ ;
                }
            }
            if (getHammingWeightSlice(sliceAfterChi) < getHammingWeightSlice(minimalsliceAfterChi)) {
                minimalsliceAfterChi = sliceAfterChi;
            }
        }
    } while (updateIndex(index, outputDiffs));
    return minimalsliceAfterChi;
}

bool InKernelAtCFilter::updateIndex(vector<unsigned int> & index, const vector<vector<RowValue> > rowsDiff){
    if (index.size() == rowsDiff.size()) {
        if (index.back() < (rowsDiff.back().size() - 1)) {
            index.back()++;
            return true;
        }
        else {
            index.pop_back();
            if (updateIndex(index, rowsDiff)) {
                index.push_back(0);
                return true;
            }
            return false;
        }
    }
    else if((index.size() < rowsDiff.size()) && (index.size() > 1)) {
        if (index.back() < (rowsDiff[index.size()-1].size()-1)) {
            index.back()++;
            return true;
        }
        else {
            index.pop_back();
            if (updateIndex(index, rowsDiff)) {
                index.push_back(0);
                return true;
            }
            return false;
        }
    }
    else if (index.size() == 1){
        if (index.back() < (rowsDiff[0].size()-1)) {
            index.back()++;
            return true;
        }
        else {
            index.pop_back();
            return false;
        }
    }
    else {
        cout << "Unexpected situation!" << endl;
        return false;
    }
}

void InKernelAtCFilter::outputTrailCore(const string& fileName){
    ofstream fout(fileName.c_str(), ios::app);
    Trail trail;
    trail.append(workCore.back().stateAtB, workCore.back().weightAtB);
//    trail.append(workCore.back().minimalStateAtB, workCore.back().weightAtB);
    trail.save(fout);
}
























