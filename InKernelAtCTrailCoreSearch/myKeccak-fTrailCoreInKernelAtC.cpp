//
//  myKeccak-fTrailCoreInKernelAtC.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 21/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "myKeccak-fTrailCoreInKernelAtC.hpp"
void myTrailCoreInKernelAtC::genInputforAllActiveSbox(DualVector slicePatternCase,TriVector& activeSboxAllCase) {
    std::vector<RowValue> set1{1, 2, 4, 8, 16};
    std::vector<RowValue> set2{3, 5, 6, 9, 10, 12, 17, 18, 20, 24};
    std::vector<RowValue> set3{7, 11, 13, 14, 19, 21, 22, 25, 26, 28};
    std::vector<RowValue> set4{15, 23, 27, 29, 30};
    std::vector<RowValue> set5{31};

    int Case, nSbox;
    //each case indicates 1)number of active sboxes 2)number of bits within each Sbox
    //e.g., "slicePatternCase" stores {{1,3},{2,2},{1,1,2},{1,1,1,1}}, 4 possible cases
    for (Case = 0; Case < slicePatternCase.size(); Case++) {
        DualVector activeSbox;
        for (nSbox = 0; nSbox <= slicePatternCase[Case].size(); nSbox++) {
            std::vector<RowValue> Sbox;
            switch (slicePatternCase[Case][nSbox]) {
                case 1:
                    for (int i = 0; i < set1.size(); i++) {
                        Sbox.push_back(set1[i]);
                    }
                    break;
                case 2:
                    for (int i = 0; i < set2.size(); i++) {
                        Sbox.push_back(set2[i]);
                    }
                    break;
                case 3:
                    for (int i = 0; i < set3.size(); i++) {
                        Sbox.push_back(set3[i]);
                    }
                    break;
                case 4:
                    for (int i = 0; i < set4.size(); i++) {
                        Sbox.push_back(set4[i]);
                    }
                    break;
                default:
                    for (int i = 0; i < set5.size(); i++) {
                        Sbox.push_back(set5[i]);
                    }
            }
            activeSbox.push_back(Sbox);
        }
        activeSboxAllCase.push_back(activeSbox);
    }
}

void myTrailCoreInKernelAtC::printValueSlicePattern(multisetSet valuePattern){
    cout << valuePattern.size() << " value patterns in total!" << endl;
    multisetSet :: iterator itSet;
    for ( itSet = valuePattern.begin(); itSet != valuePattern.end(); itSet++) {
        multiset <RowValue, greater <RowValue> > :: iterator it;
        for ( it = (*itSet).begin(); it != (*itSet).end(); it++) {
            bitset<5> input(*it);
            cout << " " << input;
        }
        cout << endl;
    }
}

void myTrailCoreInKernelAtC::twoSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern2){
    int i, j, ii, jj;
    int cases;
    for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
        for (i = 0; i < activeSboxAllCase[cases][0].size(); i++) {//the vector stores all possible input differences of the first active sbox
            for (j = 0; j < activeSboxAllCase[cases][1].size(); j++) {//the vector stores all possible input differences of the second active sbox
                bool flag = 0;
                for (ii = 1; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {//for each of the input difference, check all compatible output differences
                    for (jj = 1; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                        unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                        unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                        if ((output1^output2)==0) {
                            multiset <RowValue, greater <RowValue> > validSlice;
                            validSlice.insert(activeSboxAllCase[cases][0][i]);
                            validSlice.insert(activeSboxAllCase[cases][1][j]);
                            valuePattern2.insert(validSlice);
                            flag = 1;
                            break;
                        }
                    }
                    if (flag) {
                        break;
                    }
                }
            }
        }
    }
    // printValueSlicePattern(valuePattern2);
}

void myTrailCoreInKernelAtC::threeSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern3){
    int i, j, k, ii, jj, kk;
    int cases;
    for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
        for (i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
            for (j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
                for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
                    bool flag = 0;
                    for ( ii = 0; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
                        for ( jj = 0; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                            for ( kk = 0; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                                unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                                unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                                unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                                unsigned int outputvalue = output1 ^ output2 ^ output3;
                                if (outputvalue == 0) {
                                    multiset <RowValue, greater <RowValue> > validSlice;
                                    validSlice.insert(activeSboxAllCase[cases][0][i]);
                                    validSlice.insert(activeSboxAllCase[cases][1][j]);
                                    validSlice.insert(activeSboxAllCase[cases][2][k]);
                                    valuePattern3.insert(validSlice);
                                    flag = 1;
                                    break;
                                }
                            }
                            if (flag) {
                                break;
                            }
                        }
                        if (flag) {
                            break;
                        }
                    }
                }
            }
        }
    }
    // printValueSlicePattern(valuePattern3);
}


void myTrailCoreInKernelAtC::fourSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern4){
    int i, j, k, m, ii, jj, kk, mm;
    int cases;
    for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
        for ( i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
            for ( j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
                for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
                    for ( m = 0; m < activeSboxAllCase[cases][3].size(); m++) {
                        bool flag = 0;
                        for ( ii = 0; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
                            for ( jj = 0; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                                for ( kk = 0; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                                    for ( mm = 0; mm < DDTOutput[activeSboxAllCase[cases][3][m]][0]; mm++) {
                                        unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                                        unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                                        unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                                        unsigned int output4 = DDTOutput[activeSboxAllCase[cases][3][m]][mm];
                                        unsigned int outputvalue = output1 ^ output2 ^ output3 ^ output4;
                                        if (outputvalue==0) {
                                            multiset <RowValue, greater<RowValue> > validSlice;
                                            validSlice.insert(activeSboxAllCase[cases][0][i]);
                                            validSlice.insert(activeSboxAllCase[cases][1][j]);
                                            validSlice.insert(activeSboxAllCase[cases][2][k]);
                                            validSlice.insert(activeSboxAllCase[cases][3][m]);
                                            valuePattern4.insert(validSlice);
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag) {
                                        break;
                                    }
                                }
                                if (flag) {
                                    break;
                                }
                            }
                            if (flag) {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    // printValueSlicePattern(valuePattern4);
}

void myTrailCoreInKernelAtC::fiveSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern5){
    int i, j, k, m, n, ii, jj, kk, mm, nn;
    int cases;
    for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
        for ( i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
            for ( j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
                for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
                    for ( m = 0; m < activeSboxAllCase[cases][3].size(); m++) {
                        for ( n = 0; n < activeSboxAllCase[cases][4].size(); n++) {
                            bool flag = 0;
                            for ( ii = 0; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
                                for ( jj = 0; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                                    for ( kk = 0; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                                        for ( mm = 0; mm < DDTOutput[activeSboxAllCase[cases][3][m]][0]; mm++) {
                                            for ( nn = 0; nn < DDTOutput[activeSboxAllCase[cases][4][n]][0]; nn++) {
                                                unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                                                unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                                                unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                                                unsigned int output4 = DDTOutput[activeSboxAllCase[cases][3][m]][mm];
                                                unsigned int output5 = DDTOutput[activeSboxAllCase[cases][4][n]][nn];
                                                unsigned int outputvalue = output1 ^ output2 ^ output3 ^ output4 ^ output5;
                                                if (outputvalue == 0) {
                                                    multiset <RowValue, greater <RowValue> > validSlice;
                                                    validSlice.insert(activeSboxAllCase[cases][0][i]);
                                                    validSlice.insert(activeSboxAllCase[cases][1][j]);
                                                    validSlice.insert(activeSboxAllCase[cases][2][k]);
                                                    validSlice.insert(activeSboxAllCase[cases][3][m]);
                                                    validSlice.insert(activeSboxAllCase[cases][4][n]);
                                                    valuePattern5.insert(validSlice);
                                                    flag = 1;
                                                    break;
                                                }
                                            }
                                            if (flag) {
                                                break;
                                            }
                                        }
                                        if (flag) {
                                            break;
                                        }
                                    }
                                    if (flag) {
                                        break;
                                    }
                                }
                                if (flag) {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // printValueSlicePattern(valuePattern5);
}

void myTrailCoreInKernelAtC::generateValidSliceValuePattern(unsigned int nBit, multisetSet& patternSet) {
    int DDTOutput[32][32];
    differential_distribution_table_dir(DDTOutput);

    switch (nBit) {
        case 2:
        {
            DualVector twoBitSlice{{1,1}};
            TriVector activeSbox;
            genInputforAllActiveSbox(twoBitSlice,activeSbox);
            twoSboxValuePatternSearch(activeSbox, DDTOutput, patternSet);
        }
            break;

        case 3:
        {
            DualVector twoSboxSlice{{1,2}};
            TriVector activeSbox2;
            DualVector threeSboxSlice{{1,1,1}};
            TriVector activeSbox3;
            genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
            genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
            twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
            threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
        }
            break;

        case 4:
        {
            DualVector twoSboxSlice{{1,3},{2,2}};
            TriVector activeSbox2;
            DualVector threeSboxSlice{{1,1,2}};
            TriVector activeSbox3;
            DualVector fourSboxSlice{{1,1,1,1}};
            TriVector activeSbox4;
            genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
            genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
            genInputforAllActiveSbox(fourSboxSlice, activeSbox4);
            twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
            threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
            fourSboxValuePatternSearch(activeSbox4, DDTOutput, patternSet);
        }
            break;

        case 5:
        {
            DualVector twoSboxSlice{{1,4},{2,3}};
            TriVector activeSbox2;
            DualVector threeSboxSlice{{1,1,3},{1,2,2}};
            TriVector activeSbox3;
            DualVector fourSboxSlice{{1,1,1,2}};
            TriVector activeSbox4;
            DualVector fiveSboxSlice{{1,1,1,1,1}};
            TriVector activeSbox5;
            genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
            genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
            genInputforAllActiveSbox(fourSboxSlice, activeSbox4);
            genInputforAllActiveSbox(fiveSboxSlice, activeSbox5);
            twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
            threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
            fourSboxValuePatternSearch(activeSbox4, DDTOutput, patternSet);
            fiveSboxValuePatternSearch(activeSbox5, DDTOutput, patternSet);
        }
            break;
        default:
            ;
    }
}

void myTrailCoreInKernelAtC:: initializeValuePatterns(void)
{
    generateValidSliceValuePattern(2, valuePatternSet2);
    generateValidSliceValuePattern(3, valuePatternSet3);
    generateValidSliceValuePattern(4, valuePatternSet4);
    generateValidSliceValuePattern(5, valuePatternSet5);
//    printValueSlicePattern(valuePatternSet2);
//    printValueSlicePattern(valuePatternSet3);
//    printValueSlicePattern(valuePatternSet4);
//    printValueSlicePattern(valuePatternSet5);
}

void myTrailCoreInKernelAtC::printSingleValuePattern_ForTest(const vector<RowValue> aRowChainOfValuePattern){
    for (int i = 0; i < aRowChainOfValuePattern.size(); i++) {
        bitset<5> output(aRowChainOfValuePattern[i]);
        cout << " " << output;
    }
    cout << endl;
}

void myTrailCoreInKernelAtC:: obtainAllSlicePatternsFromAValuePattern(const ValuePatternmultiset aValuePattern, set<SliceValue> & aAllSlicePatternSet){

    //Store the value pattern with a vector
    ValuePatternmultiset:: iterator itValuePattern;
    vector<RowValue> rowChainOfValuePattern;
    for (itValuePattern = aValuePattern.begin(); itValuePattern != aValuePattern.end(); itValuePattern ++) {
        rowChainOfValuePattern.push_back(*itValuePattern);
    }
//    printSingleValuePattern_ForTest(rowChainOfValuePattern);

    unsigned int nrActiveRows = aValuePattern.size();
    SliceValue oneSlice;
    unsigned int nrSlicePatterns, nrRows;
    switch (nrActiveRows) {
        case 2:
        {
            for (nrSlicePatterns = 0; nrSlicePatterns < sbox2YPosition.size(); nrSlicePatterns ++) {
                oneSlice = 0;
                for (nrRows = 0; nrRows < nrActiveRows; nrRows++) {
                    oneSlice ^= getSliceFromRow(rowChainOfValuePattern[nrRows], sbox2YPosition[nrSlicePatterns][nrRows]);
                }
//                printSliceRowByRow(oneSlice);
                aAllSlicePatternSet.insert(oneSlice);
            }
        }
            break;

        case 3:
        {
            for (nrSlicePatterns = 0; nrSlicePatterns < sbox3YPosition.size(); nrSlicePatterns ++) {
                oneSlice = 0;
                for (nrRows = 0; nrRows < nrActiveRows; nrRows++) {
                    oneSlice ^= getSliceFromRow(rowChainOfValuePattern[nrRows], sbox3YPosition[nrSlicePatterns][nrRows]);
                }
//                printSliceRowByRow(oneSlice);
                aAllSlicePatternSet.insert(oneSlice);
            }
        }
            break;

        case 4:
        {
            for (nrSlicePatterns = 0; nrSlicePatterns < sbox4YPosition.size(); nrSlicePatterns ++) {
                oneSlice = 0;
                for (nrRows = 0; nrRows < nrActiveRows; nrRows++) {
                    oneSlice ^= getSliceFromRow(rowChainOfValuePattern[nrRows], sbox4YPosition[nrSlicePatterns][nrRows]);
                }
//                printSliceRowByRow(oneSlice);
                aAllSlicePatternSet.insert(oneSlice);
            }
        }
            break;

        case 5:
        {
            for (nrSlicePatterns = 0; nrSlicePatterns < sbox5YPosition.size(); nrSlicePatterns ++) {
                oneSlice = 0;
                for (nrRows = 0; nrRows < nrActiveRows; nrRows++) {
                    oneSlice ^= getSliceFromRow(rowChainOfValuePattern[nrRows], sbox5YPosition[nrSlicePatterns][nrRows]);
                }
//                printSliceRowByRow(oneSlice);
                aAllSlicePatternSet.insert(oneSlice);
            }
        }
            break;

        default:
            cout << "Error!" << endl;
            break;
    }
}

void myTrailCoreInKernelAtC::getKnotFromSlice(const SliceValue aSlice, StartingKnotInfo& aStartingKnot){
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if ((aSlice >> (x+5*y))&0x1) {
                myBitPosition onePoit(x,y,0);
                aStartingKnot.knotPoints.push_back(onePoit);
                aStartingKnot.yOffset.push_back(0);
            }
        }
    }
    return;
}

void myTrailCoreInKernelAtC::test3Peers2Slices(){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = valuePatternSet3.begin(); itOneValuePattern != valuePatternSet3.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        obtainAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnot.knotPoints.clear();
            startingKnot.yOffset.clear();
            getKnotFromSlice((*itOneSlicePattern), startingKnot);
            isInitialStructure = false;
            isLastStructure = false;
            do {
                nextStructure_test();
                knotsSetAtB.clear();
                if (filterOnPeerRhoOffset_test()) {
                    cout << "Pass the filter on rho offsets!" << endl;
                    if (checkKnotsAtBInKernelAtC()) {
                        cout << "Pass the filter on knots at B!" << endl;
                        if (updateSetOfMinimalStatesUpToNow()) {
                            cout << "Pass the duplication of state B test!" << endl;
                        }
                    }

                }
            } while (!isLastStructure);
        }
    }
}


bool myTrailCoreInKernelAtC::updateSetOfMinimalStatesUpToNow(){
    for (int dz = 0; dz < 64; dz ++) {
        set<myBitPosition> aMin;
        set<myBitPosition>:: iterator itBitSet;
        for (itBitSet = bitSetForMinimalStateB.begin(); itBitSet != bitSetForMinimalStateB.end(); itBitSet++) {
            myBitPosition aBit((*itBitSet));
            aBit.zTranslate(dz, 64);
            aMin.insert(aBit);
        }
        if (aMin < bitSetForMinimalStateB) {
            bitSetForMinimalStateB = aMin;
        }
    }
    if (setOfBitSetForMinimalStateBUpToNow.insert(bitSetForMinimalStateB).second == false) {
        cout << "Minimal state of this state AtB has already existed!" << endl;
        return false;
    }
    else
        return true;
}

bool myTrailCoreInKernelAtC::checkKnotsAtBInKernelAtC(){
    if (populateKnotsAtBStep1() && populateKnotsAtBStep2()) {
        map<unsigned int, KnotAtBInfo>::iterator itKnot;
        for (itKnot = knotsSetAtB.begin(); itKnot != knotsSetAtB.end(); itKnot++) {
            if (!itKnot->second.isInKernelAtC) {
                cout << "This knot can't lead to at least one inkernel slice after chi!" << endl;
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

bool myTrailCoreInKernelAtC::populateKnotsAtBStep1(){
    bitSetForMinimalStateB.clear();
    for (unsigned int nrPeers = 0; nrPeers < peersSetAtA.size(); nrPeers ++) {
        if (peersSetAtA[nrPeers].size() != 2) {
            cout << "Error! There aren't 2 bits at one peer!" << endl;
            return false;
        }
        else {
            for (unsigned int nrBits = 0; nrBits < peersSetAtA[nrPeers].size(); nrBits ++) {
                myBitPosition pB(peersSetAtA[nrPeers][nrBits]);
                pB.directRhoPi();
                knotsSetAtB[pB.z].bitPointsChain.push_back(pB);
                knotsSetAtB[pB.z].nrBitPoints++;
                bitSetForMinimalStateB.insert(pB);
            }
        }
    }
    return true;
}

bool myTrailCoreInKernelAtC::populateKnotsAtBStep2(){
    map<unsigned int, KnotAtBInfo>::iterator itKnot;
    for (itKnot = knotsSetAtB.begin(); itKnot != knotsSetAtB.end(); itKnot++) {
        if ((itKnot->second).nrBitPoints >= 2) {
            itKnot->second.sliceValue = getSliceValueFromBitChain(itKnot->second.bitPointsChain);
            itKnot->second.valuePattern = getValuePatternFromSlice(itKnot->second.sliceValue);
            itKnot->second.isInKernelAtC = valuePatternInKernelAtCCheck(itKnot->second.nrBitPoints, itKnot->second.valuePattern);
        }
        else {
            cout << "Error! Less than 2 bits in one knot!" << endl;
            return false;
        }
    }
    return true;
}

bool myTrailCoreInKernelAtC::valuePatternInKernelAtCCheck(const unsigned nrBits, const ValuePatternmultiset aValuePattern){
    switch (nrBits) {
        case 2:
        {
            if ((valuePatternSet2.find(aValuePattern)) != (valuePatternSet2.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;

        case 3:
        {
            if ((valuePatternSet3.find(aValuePattern)) != (valuePatternSet3.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;

        case 4:
        {
            if ((valuePatternSet4.find(aValuePattern)) != (valuePatternSet4.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;

        case 5:
        {
            if ((valuePatternSet5.find(aValuePattern)) != (valuePatternSet5.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;

        default:
        {
            cout << "Error! The number of bits in the knot exceeds the checking bound!" << endl;
            return false;
        }
            break;
    }
}

ValuePatternmultiset myTrailCoreInKernelAtC:: getValuePatternFromSlice(const SliceValue aSliceValue){
    RowValue aRow;
    ValuePatternmultiset aValuePattern;
    for (int nrRow = 0; nrRow < 5; nrRow++) {
        aRow = getRowFromSlice(aSliceValue, nrRow);
        if (aRow) {
            aValuePattern.insert(aRow);
        }
    }
    if (aValuePattern.size() >= 2) {
        return aValuePattern;
    }
    else {
        cout << "Error! There are less than 2 active rows in the knot at B!" << endl;
        return aValuePattern;
    }
}

SliceValue myTrailCoreInKernelAtC::getSliceValueFromBitChain(vector<myBitPosition> aBitPointsChain){
    SliceValue aSliceValue = 0;
    for (int i =0; i< aBitPointsChain.size(); i++) {
        aSliceValue |= (SliceValue)1 << (aBitPointsChain[i].x + 5*aBitPointsChain[i].y);
    }
    return aSliceValue;
}

bool myTrailCoreInKernelAtC::filterOnPeerRhoOffset_test(){
    if (peerParameterOnRho.size() > 0) {
        unsigned int lastPeerParameter = peerParameterOnRho.back();
        for (int i = 0; i < peerParameterOnRho.size(); i++) {
            if (lastPeerParameter != peerParameterOnRho[i]) {
                return false;
            }
        }
        return true;
    }
    else
        return false;
}

void myTrailCoreInKernelAtC::nextStructure_test(){
    peersSetAtA.clear();
    peerParameterOnRho.clear();
    if (!isInitialStructure) {
        for (int i = 0; i < startingKnot.knotPoints.size(); i++) {
            vector<myBitPosition> aPeerAtA;
            myBitPosition pA(startingKnot.knotPoints[i]);
            pA.inverseRhoPi();
            aPeerAtA.push_back(pA);
            startingKnot.yOffset[i] = 1;
            pA.yTranslate(startingKnot.yOffset[i]);
            aPeerAtA.push_back(pA);
            peersSetAtA.push_back(aPeerAtA);
            addPeerParameterOnRho(aPeerAtA);
        }
        isInitialStructure = true;
    }
    else {
        if(recursiveYOffsetOfStartingKnot(startingKnot.yOffset)) {
            completeStructure_test();
            return;
        }
        else{
            isLastStructure = true;
            return;
        }
    }
}

void myTrailCoreInKernelAtC::completeStructure_test(){
    for (int i =0; i < startingKnot.knotPoints.size(); i++) {
        vector<myBitPosition> aPeerAtA;
        myBitPosition pA(startingKnot.knotPoints[i]);
        pA.inverseRhoPi();
        aPeerAtA.push_back(pA);
        pA.yTranslate(startingKnot.yOffset[i]);
        aPeerAtA.push_back(pA);
        peersSetAtA.push_back(aPeerAtA);
        addPeerParameterOnRho(aPeerAtA);
    }
    return;
}

bool myTrailCoreInKernelAtC::recursiveYOffsetOfStartingKnot(vector<unsigned int>& yOffset){
    if (yOffset.size() == 0) {
        return false;
    } else if((yOffset.size() >= 1) && (yOffset.back() == 4)){
        yOffset.pop_back();
        if(recursiveYOffsetOfStartingKnot(yOffset)){
            yOffset.push_back(1);
            return true;
        }
        else
            return false;
    } else if ((yOffset.size() >= 1) && (yOffset.back() < 4)){
        yOffset.back()++;
        return true;
    }
    else
        cout << "Error! Unexpected situation!" << endl;
    return true;
}

void myTrailCoreInKernelAtC::addPeerParameterOnRho(vector<myBitPosition> aPeerAtA){
    unsigned int offset[5][5] = {//[x][y] fashion, my state is [y][x]fashion
        {0, 36, 3, 41, 18},
        {1, 44, 10, 45, 2},
        {62, 6, 43, 15, 61},
        {28, 55, 25, 21, 56},
        {27, 20, 39, 8, 14}
    };
    unsigned int valueParameter;
    if (aPeerAtA.size() == 2) {
        valueParameter = (64 + offset[aPeerAtA[0].x][aPeerAtA[0].y] - offset[aPeerAtA[1].x][aPeerAtA[1].y])%64;
        peerParameterOnRho.push_back(valueParameter);
    }
    else
        cout<< "Error! The peer doesn't contain 2 bits!" << endl;
    return;
}





















