//
//  myTrailCoreInKernelAtCFilter.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef myTrailCoreInKernelAtCFilter_hpp
#define myTrailCoreInKernelAtCFilter_hpp
//#include "translationsymmetry.h"
#include "MyTrailCoreInKernelAtCStructureConstruct.hpp"

using namespace std;

struct KnotAtBInfo{
    SliceValue sliceValue;
    vector<BitPosition> bitsChain;
    unsigned int nrBits;
    bool isInKernelAtC;
    ValuePatternmultiset valuePattern;
};

struct CoreInfo{
    vector<SliceValue> stateAtB;
    vector<SliceValue> minimalStateAtB;
    vector<SliceValue> partialStateAtC;
    unsigned int partialWeight;
    unsigned int weightAtB;
};

class InKernelAtCFilter : public InKernelAtCStructureConstruct{
public:
    InKernelAtCFilter(unsigned int aMaxWeight, KeccakFDCLC& aParent, KeccakFPropagation::DCorLC aDCorLC);

    bool filterOnPeerRhoOffset_XPeers2Slices();
    bool filterOnPeerRhoOffset_422();
    bool filterOnPeerRhoOffset_332();
    bool filterOnPeerRhoOffset_532();
    bool filterOnPeerRhoOffset_442();
    bool filterOnPeerRhoOffset_433();
    bool filterOnPeerRhoOffset_4222();
    bool filterOnPeerRhoOffset_3322A();
    bool filterOnPeerRhoOffset_3322B();
    bool filterOnPeerRhoOffset_3322C();
    bool checkMappedToSameSlice3322C();
    bool checkKnotsAtBInKernelAtC();
    bool populateKnotsAtBStep1();
    bool populateKnotsAtBStep2();

    bool updateSetOfMinimalStatesUpToNow();

    void prepareOutputTrailCore();
    void outputTrailCore(const string& fileName);

    SliceValue myGetMinimumInKernelSliceAfterChi(const SliceValue sliceBeforeChi);
    bool updateIndex(vector<unsigned int>& index, const vector<vector<RowValue>> rowsDiff);
protected:
    unsigned int weightAtB;
    unsigned int partialWeight;
    unsigned int minWeightBAndC;

    vector<SliceValue> stateAtB;
    vector<SliceValue> stateAtA;
    vector<SliceValue> partialStateAtD;

    map<unsigned int, KnotAtBInfo> knotsAtB;

    set<BitPosition> bitSetForMinimalStateB;
    set<set<BitPosition>> setOfBitSetForMinimalStateBUpToNow;

    vector<CoreInfo> workCore;
};

#endif /* myTrailCoreInKernelAtCFilter_hpp */
