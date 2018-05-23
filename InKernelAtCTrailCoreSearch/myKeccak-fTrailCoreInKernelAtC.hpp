//
//  myKeccak-fTrailCoreInKernelAtC.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 21/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef myKeccak_fTrailCoreInKernelAtC_hpp
#define myKeccak_fTrailCoreInKernelAtC_hpp

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include "misc.h"
#include <bitset>
#include <iterator>
//#include "Keccak-fPositions.h"
#include "types.h"
#include "myParts.hpp"
#include "myPositions.hpp"

using namespace std;
//typedef unsigned char RowValue;
//typedef UINT32 SliceValue;
typedef std::vector<std::vector<RowValue>> DualVector;
typedef std::vector<std::vector<std::vector<RowValue>>> TriVector;
typedef multiset <RowValue, greater <RowValue>> ValuePatternmultiset;
typedef set <ValuePatternmultiset> multisetSet;

struct StartingKnotInfo{
//    bool isStartingKnot;
    vector<myBitPosition> knotPoints;
    vector<unsigned int> yOffset;
};

struct CoreInfo{
    vector<SliceValue> stateAtA;
    vector<SliceValue> minimalStateAtB;
    unsigned int weightAtB;
};

struct KnotAtBInfo{
    SliceValue sliceValue;
    vector<myBitPosition> bitPointsChain;
    unsigned int nrBitPoints;
    bool isInKernelAtC;
    ValuePatternmultiset valuePattern;
};

struct KnotAtAInfo{
    vector<myBitPosition> bitPointsChain;
    unsigned int nrPeers;
    bool isPeerCollision;
};


class myTrailCoreInKernelAtC{
public:
    myTrailCoreInKernelAtC(){
        initializeValuePatterns();
    }
    /** This method generate all the input differences candidates for the slice indicated by the slice pattern.
     * @param slicePatternCase store all the slice possiblities of a specific active bits, e.g., {{1,2},{1,1,1}} for 3 bits.
     * @param activeSboxAllCase stores all input differences for each slice possiblities
     */
    void genInputforAllActiveSbox(DualVector slicePatternCase,
                                  TriVector& activeSboxAllCase);

    /** This method print all the valid slice value patterns to the screen.
     * @param valuePattern The Set of a Multiset that stores the valid slice value pattens.
     */
    void printValueSlicePattern(multisetSet valuePattern);

    /** This method generate the valid value slice patterns for the slice that contains two sboxes.
     * @param activeSboxAllCase The 3D vector stores the input differences of all the cases of two sboxes.
     * @param DDTOutput[32][32] The DDT of the 5-bit Sbox with DDTOutput[i][0] stores the number of compatible output differences of input i.
     * @param valuePattern2 The set of multiset that stores all the valid value patterns of two sboxes.
     */
    void twoSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern2);
    void threeSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern3);
    void fourSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern4);
    void fiveSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern5);

    /** This method generate all the valid value patterns of a slice with a specific number of active bits.
     * @param nBit The number of active bits of this active slice to be checked.
     * @param patternSet The set of multiset that stores all the valid value patterns for the slice with nBit bits.
     */
    void generateValidSliceValuePattern(unsigned int nBit, multisetSet& patternSet);
    /** Compute the value patterns and store them.
      */
    void initializeValuePatterns(void);

    void obtainAllSlicePatternsFromAValuePattern(const ValuePatternmultiset aValuePattern, set<SliceValue> & aAllSlicePatternSet);

    void printSingleValuePattern_ForTest(const vector<RowValue> aRowChainOfValuePattern);

    void test3Peers2Slices();

    void getKnotFromSlice(const SliceValue aSlice, StartingKnotInfo& aStartingKnot);

    void addPeerParameterOnRho(vector<myBitPosition> aPeerAtA);

    void nextStructure_test();
    bool recursiveYOffsetOfStartingKnot(vector<unsigned int>& yOffset);

    void completeStructure_test();
    bool filterOnPeerRhoOffset_test();
    bool checkKnotsAtBInKernelAtC();
    bool updateSetOfMinimalStatesUpToNow();
    bool populateKnotsAtBStep1();
    bool populateKnotsAtBStep2();
    bool valuePatternInKernelAtCCheck(const unsigned nrBits, const ValuePatternmultiset aValuePattern);
    SliceValue getSliceValueFromBitChain(vector<myBitPosition> aBitPointsChain);
    ValuePatternmultiset  getValuePatternFromSlice(const SliceValue aSliceValue);
private:
    /** Store all the value patterns of 2, 3, 4, 5 bits.
      */
    multisetSet valuePatternSet2;
    multisetSet valuePatternSet3;
    multisetSet valuePatternSet4;
    multisetSet valuePatternSet5;

    bool isInitialStructure;
    bool isLastStructure;

    StartingKnotInfo startingKnot;
    map<unsigned int, KnotAtBInfo> knotsSetAtB;
    vector<vector<myBitPosition>> peersSetAtA;
    vector<unsigned int> peerParameterOnRho;
    set<myBitPosition> bitSetForMinimalStateB;
    set<set<myBitPosition>> setOfBitSetForMinimalStateBUpToNow;

    vector<SliceValue> stateAtB;
    vector<SliceValue> stateAtA;

    CoreInfo outCore;

    const DualVector sbox2YPosition {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 0}, {1, 2}, {1,3}, {1, 4}, {2, 0}, {2, 1},
        {2, 3}, {2, 4}, {3, 0}, {3, 1}, {3, 2}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3}
    };
    const DualVector sbox3YPosition {
        {0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 2, 1}, {0, 2, 3}, {0, 2, 4}, {0, 3, 1}, {0, 3, 2}, {0, 3, 4}, {0, 4, 1},
        {0, 4, 2}, {0, 4, 3}, {1, 0, 2}, {1, 0, 3}, {1, 0, 4}, {1, 2, 0}, {1, 2, 3}, {1, 2, 4}, {1, 3, 0}, {1, 3, 2},
        {1, 3, 4}, {1, 4, 0}, {1, 4, 2}, {1, 4, 3}, {2, 0, 1}, {2, 0, 3}, {2, 0, 4}, {2, 1, 0}, {2, 1, 3}, {2, 1, 4},
        {2, 3, 0}, {2, 3, 1}, {2, 3, 4}, {2, 4, 0}, {2, 4, 1}, {2, 4, 3}, {3, 0, 1}, {3, 0, 2}, {3, 0, 4}, {3, 1, 0},
        {3, 1, 2}, {3, 1, 4}, {3, 2, 0}, {3, 2, 1}, {3, 2, 4}, {3, 4, 0}, {3, 4, 1}, {3, 4, 2}, {4, 0, 1}, {4, 0, 2},
        {4, 0, 3}, {4, 1, 0}, {4, 1, 2}, {4, 1, 3}, {4, 2, 0}, {4, 2, 1}, {4, 2, 3}, {4, 3, 0}, {4, 3, 1}, {4, 3, 2}
    };
    const DualVector sbox4YPosition {
        {0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 3, 2}, {0, 1, 3, 4}, {0, 1, 4, 2}, {0, 1, 4, 3},
        {0, 2, 1, 3}, {0, 2, 1, 4}, {0, 2, 3, 1}, {0, 2, 3, 4}, {0, 2, 4, 1}, {0, 2, 4, 3},
        {0, 3, 1, 2}, {0, 3, 1, 4}, {0, 3, 2, 1}, {0, 3, 2, 4}, {0, 3, 4, 1}, {0, 3, 4, 2},
        {0, 4, 1, 2}, {0, 4, 1, 3}, {0, 4, 2, 1}, {0, 4, 2, 3}, {0, 4, 3, 1}, {0, 4, 3, 2},
        {1, 0, 2, 3}, {1, 0, 2, 4}, {1, 0, 3, 2}, {1, 0, 3, 4}, {1, 0, 4, 2}, {1, 0, 4, 3},
        {1, 2, 0, 3}, {1, 2, 0, 4}, {1, 2, 3, 0}, {1, 2, 3, 4}, {1, 2, 4, 0}, {1, 2, 4, 3},
        {1, 3, 0, 2}, {1, 3, 0, 4}, {1, 3, 2, 0}, {1, 3, 2, 4}, {1, 3, 4, 0}, {1, 3, 4, 2},
        {1, 4, 0, 2}, {1, 4, 0, 3}, {1, 4, 2, 0}, {1, 4, 2, 3}, {1, 4, 3, 0}, {1, 4, 3, 2},
        {2, 0, 1, 3}, {2, 0, 1, 4}, {2, 0, 3, 1}, {2, 0, 3, 4}, {2, 0, 4, 1}, {2, 0, 4, 3},
        {2, 1, 0, 3}, {2, 1, 0, 4}, {2, 1, 3, 0}, {2, 1, 3, 4}, {2, 1, 4, 0}, {2, 1, 4, 3},
        {2, 3, 0, 1}, {2, 3, 0, 4}, {2, 3, 1, 0}, {2, 3, 1, 4}, {2, 3, 4, 0}, {2, 3, 4, 1},
        {2, 4, 0, 1}, {2, 4, 0, 3}, {2, 4, 1, 0}, {2, 4, 1, 3}, {2, 4, 3, 0}, {2, 4, 3, 1},
        {3, 0, 1, 2}, {3, 0, 1, 4}, {3, 0, 2, 1}, {3, 0, 2, 4}, {3, 0, 4, 1}, {3, 0, 4, 2},
        {3, 1, 0, 2}, {3, 1, 0, 4}, {3, 1, 2, 0}, {3, 1, 2, 4}, {3, 1, 4, 0}, {3, 1, 4, 2},
        {3, 2, 0, 1}, {3, 2, 0, 4}, {3, 2, 1, 0}, {3, 2, 1, 4}, {3, 2, 4, 0}, {3, 2, 4, 1},
        {3, 4, 0, 1}, {3, 4, 0, 2}, {3, 4, 1, 0}, {3, 4, 1, 2}, {3, 4, 2, 0}, {3, 4, 2, 1},
        {4, 0, 1, 2}, {4, 0, 1, 3}, {4, 0, 2, 1}, {4, 0, 2, 3}, {4, 0, 3, 1}, {4, 0, 3, 2},
        {4, 1, 0, 2}, {4, 1, 0, 3}, {4, 1, 2, 0}, {4, 1, 2, 3}, {4, 1, 3, 0}, {4, 1, 3, 2},
        {4, 2, 0, 1}, {4, 2, 0, 3}, {4, 2, 1, 0}, {4, 2, 1, 3}, {4, 2, 3, 0}, {4, 2, 3, 1},
        {4, 3, 0, 1}, {4, 3, 0, 2}, {4, 3, 1, 0}, {4, 3, 1, 2}, {4, 3, 2, 0}, {4, 3, 2, 1}
    };
    const DualVector sbox5YPosition {
        {0, 1, 2, 3, 4}, {0, 1, 2, 4, 3}, {0, 1, 3, 2, 4}, {0, 1, 3, 4, 2}, {0, 1, 4, 2, 3}, {0, 1, 4, 3, 2},
        {0, 2, 1, 3, 4}, {0, 2, 1, 4, 3}, {0, 2, 3, 1, 4}, {0, 2, 3, 4, 1}, {0, 2, 4, 1, 3}, {0, 2, 4, 3, 1},
        {0, 3, 1, 2, 4}, {0, 3, 1, 4, 2}, {0, 3, 2, 1, 4}, {0, 3, 2, 4, 1}, {0, 3, 4, 1, 2}, {0, 3, 4, 2, 1},
        {0, 4, 1, 2, 3}, {0, 4, 1, 3, 2}, {0, 4, 2, 1, 3}, {0, 4, 2, 3, 1}, {0, 4, 3, 1, 2}, {0, 4, 3, 2, 1},
        {1, 0, 2, 3, 4}, {1, 0, 2, 4, 3}, {1, 0, 3, 2, 4}, {1, 0, 3, 4, 2}, {1, 0, 4, 2, 3}, {1, 0, 4, 3, 2},
        {1, 2, 0, 3, 4}, {1, 2, 0, 4, 3}, {1, 2, 3, 0, 4}, {1, 2, 3, 4, 0}, {1, 2, 4, 0, 3}, {1, 2, 4, 3, 0},
        {1, 3, 0, 2, 4}, {1, 3, 0, 4, 2}, {1, 3, 2, 0, 4}, {1, 3, 2, 4, 0}, {1, 3, 4, 0, 2}, {1, 3, 4, 2, 0},
        {1, 4, 0, 2, 3}, {1, 4, 0, 3, 2}, {1, 4, 2, 0, 3}, {1, 4, 2, 3, 0}, {1, 4, 3, 0, 2}, {1, 4, 3, 2, 0},
        {2, 0, 1, 3, 4}, {2, 0, 1, 4, 3}, {2, 0, 3, 1, 4}, {2, 0, 3, 4, 1}, {2, 0, 4, 1, 3}, {2, 0, 4, 3, 1},
        {2, 1, 0, 3, 4}, {2, 1, 0, 4, 3}, {2, 1, 3, 0, 4}, {2, 1, 3, 4, 0}, {2, 1, 4, 0, 3}, {2, 1, 4, 3, 0},
        {2, 3, 0, 1, 4}, {2, 3, 0, 4, 1}, {2, 3, 1, 0, 4}, {2, 3, 1, 4, 0}, {2, 3, 4, 0, 1}, {2, 3, 4, 1, 0},
        {2, 4, 0, 1, 3}, {2, 4, 0, 3, 1}, {2, 4, 1, 0, 3}, {2, 4, 1, 3, 0}, {2, 4, 3, 0, 1}, {2, 4, 3, 1, 0},
        {3, 0, 1, 2, 4}, {3, 0, 1, 4, 2}, {3, 0, 2, 1, 4}, {3, 0, 2, 4, 1}, {3, 0, 4, 1, 2}, {3, 0, 4, 2, 1},
        {3, 1, 0, 2, 4}, {3, 1, 0, 4, 2}, {3, 1, 2, 0, 4}, {3, 1, 2, 4, 0}, {3, 1, 4, 0, 2}, {3, 1, 4, 2, 0},
        {3, 2, 0, 1, 4}, {3, 2, 0, 4, 1}, {3, 2, 1, 0, 4}, {3, 2, 1, 4, 0}, {3, 2, 4, 0, 1}, {3, 2, 4, 1, 0},
        {3, 4, 0, 1, 2}, {3, 4, 0, 2, 1}, {3, 4, 1, 0, 2}, {3, 4, 1, 2, 0}, {3, 4, 2, 0, 1}, {3, 4, 2, 1, 0},
        {4, 0, 1, 2, 3}, {4, 0, 1, 3, 2}, {4, 0, 2, 1, 3}, {4, 0, 2, 3, 1}, {4, 0, 3, 1, 2}, {4, 0, 3, 2, 1},
        {4, 1, 0, 2, 3}, {4, 1, 0, 3, 2}, {4, 1, 2, 0, 3}, {4, 1, 2, 3, 0}, {4, 1, 3, 0, 2}, {4, 1, 3, 2, 0},
        {4, 2, 0, 1, 3}, {4, 2, 0, 3, 1}, {4, 2, 1, 0, 3}, {4, 2, 1, 3, 0}, {4, 2, 3, 0, 1}, {4, 2, 3, 1, 0},
        {4, 3, 0, 1, 2}, {4, 3, 0, 2, 1}, {4, 3, 1, 0, 2}, {4, 3, 1, 2, 0}, {4, 3, 2, 0, 1}, {4, 3, 2, 1, 0}
    };
};

#endif /* myKeccak_fTrailCoreInKernelAtC_hpp */
