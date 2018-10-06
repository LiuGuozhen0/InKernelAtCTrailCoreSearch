//
//  MyTrailCoreInKernelAtC.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "translationsymmetry.h"

#include "MyTrailCoreInKernelAtC.hpp"
MyTrailCoreInKernelAtC::MyTrailCoreInKernelAtC(unsigned int aMaxWeight, KeccakFDCLC& aParent, KeccakFPropagation::DCorLC aDCorLC): InKernelAtCFilter(aMaxWeight, aParent,aDCorLC){

}

void MyTrailCoreInKernelAtC::XPeers2Slices(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);

        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                if (nextStructureOfStaringKnot()) {
                    knotsAtB.clear();
                    if (filterOnPeerRhoOffset_XPeers2Slices()) {
//                        cout << "Pass the filter on rho offsets!" << endl;
                        if (checkKnotsAtBInKernelAtC()) {
//                            cout << "Pass the filter on knots at B!" << endl;
                            if (updateSetOfMinimalStatesUpToNow()) {
//                                cout << "Pass the duplication of state B test!" << endl;
                                prepareOutputTrailCore();
                                if (workCore.back().partialWeight <= maxWeight) {
                                    outputTrailCore(fileName);
                                }
                            }
                        }
                    }
                }
            } while (!isLastStructureOfStartingKnot);
        }
    }
}

void MyTrailCoreInKernelAtC::Case422(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);

        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                nextStructureOfStaringKnot();
                                knotsAtB.clear();
                                if (filterOnPeerRhoOffset_422()) {
                                    if (checkKnotsAtBInKernelAtC()) {
                                        if (updateSetOfMinimalStatesUpToNow()) {
                                            prepareOutputTrailCore();
                                            //Deal with all such trail cores.
                                            if (workCore.back().partialWeight <= maxWeight) {
                                                outputTrailCore(fileName);
                                            }
                                        }
                                    }
                                }
            } while (!isLastStructureOfStartingKnot);
        }
    }
}

void MyTrailCoreInKernelAtC::Case532(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);

        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                nextStructureOfStaringKnot();
                                knotsAtB.clear();
                                if (filterOnPeerRhoOffset_532()) {
                                    if (checkKnotsAtBInKernelAtC()) {
                                        if (updateSetOfMinimalStatesUpToNow()) {
                                            prepareOutputTrailCore();
                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                outputTrailCore(fileName);
                                            }
                                        }
                                    }

                                }
            } while (!isLastStructureOfStartingKnot);
        }
    }
}

void MyTrailCoreInKernelAtC::Case332(){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = valuePatternSet3.begin(); itOneValuePattern != valuePatternSet3.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot()) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if ((yOffset.size()==1)) {
                            isLastStructureOfOtherKnot = false;
                            isInitialStructureOfOtherKnot = false;
                            do {
                                if ((peersAtA.size() == 3) && (peerParameterOnRho.size()==3)) {
                                    if (nextStructureOfOtherKnot()) {
                                        knotsAtB.clear();
                                        if (filterOnPeerRhoOffset_332()) {
                                            if (checkKnotsAtBInKernelAtC()) {
                                                if (updateSetOfMinimalStatesUpToNow()) {
                                                    prepareOutputTrailCore();
                                                    if (workCore.back().partialWeight <= maxWeight) {
                                                        outputTrailCore(fileName);
                                                    }
                                                }
                                            }
                                        }
                                        peersAtA.pop_back();
                                        peerParameterOnRho.pop_back();
                                    }
                                }
                                else {
                                    cout << "Error in size of peersAtA!" << endl;
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in size of yoffset!" << endl;
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}

void MyTrailCoreInKernelAtC::Case442(){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = valuePatternSet4.begin(); itOneValuePattern != valuePatternSet4.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot()) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        isLastStructureOfOtherKnot = false;
                        isInitialStructureOfOtherKnot = false;
                        if ((yOffset.size()==1) && (peersAtA.size()==4) && (peerParameterOnRho.size()==4)) {
                            do {
                                if (nextStructureOfOtherKnot()) {
                                    if ((yOffset.size()==2) && (peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                        knotsAtB.clear();
                                        if (filterOnPeerRhoOffset_442()) {
                                            if (checkKnotsAtBInKernelAtC()) {
                                                if (updateSetOfMinimalStatesUpToNow()) {
                                                    prepareOutputTrailCore();
                                                    if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                        outputTrailCore(fileName);
                                                    }
                                                }
                                            }
                                        }
                                        peersAtA.pop_back();
                                        peerParameterOnRho.pop_back();
                                    }
                                    else {
                                        cout << "Error in size of the other knot stage!" << endl;
                                    }
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in size of peers or yOffsets at starting knot stage!" << endl;
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}

void MyTrailCoreInKernelAtC::test(){
//    XPeers2Slices(valuePatternSet3);//Checked
//
//    XPeers2Slices(valuePatternSet4);//Searched but not Checked
//    Case422(valuePatternSet4);//Checked, Correct
//    Case332();//Checked, Correct
//    XPeers2Slices(valuePatternSet5);//Searched but not Checked//no such combination
    Case532(valuePatternSet5);
//    Case442();
//    Case433(valuePatternSet4);
//    Case4222(valuePatternSet4);
//    Case3322A(valuePatternSet3);
//    Case3322B(valuePatternSet3);
//    Case3322C(valuePatternSet3);

    cout << "Hi!" << endl;
}

void MyTrailCoreInKernelAtC::Case3322C(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if ((yOffset.size()==1) && (peersAtA.size()==3)) {
                            if (checkMappedToSameOrbitalCase3322C()){
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                isQ4Found = false;
                                BitPosition Q1B = getBitAtBFromBitAtA(peersAtA[0].back());
                                BitPosition Q4B(0, 0, Q1B.z);
                                do {
                                    if ((yOffset.size()<=2) && (peersAtA.size()==3) && (peerParameterOnRho.size()==3)) {
                                        if (nextStructureOfOtherKnot3322C(Q4B, Q1B)) {
                                            if ((peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                                if (filterOnPeerRhoOffset_3322C()) {
                                                    if (checkMappedToSameSlice3322C()) {
                                                        knotsAtB.clear();
                                                        if (checkKnotsAtBInKernelAtC()) {
                                                            if (knotsAtB.size()==4) {
                                                                if (updateSetOfMinimalStatesUpToNow()) {
                                                                    prepareOutputTrailCore();
                                                                    if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                        outputTrailCore(fileName);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }

                                                peersAtA.pop_back();//peer4
                                                peerParameterOnRho.pop_back();
                                                peersAtA.pop_back();//peer5
                                                peerParameterOnRho.pop_back();
                                            }
                                            else {
                                                cout << "Error of size on other knot stage!" << endl;
                                            }
                                        }
                                    }
                                    else {
                                        cout << "Size error in yOffset, peersAtA or peerParameterOnRho!" << endl;
                                    }
                                } while (!isLastStructureOfOtherKnot);
                            }
                        }
                        else {
                            cout << "Error in the size of yOffset and peersAtA!" << endl;
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}

void MyTrailCoreInKernelAtC::Case3322B(const multisetSet aValuePatternSet){

    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                            isInitialStructureOfOtherKnot = false;
                            isLastStructureOfOtherKnot = false;
                            do {
                                if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                    if (nextStructureOfOtherKnot3322B()) {
                                        if ((peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                            if (filterOnPeerRhoOffset_3322B()) {
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==4) {
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }
                                                    }
                                                }
                                            }

                                            peersAtA.pop_back();
                                            peersAtA.pop_back();
                                            peerParameterOnRho.pop_back();
                                            peerParameterOnRho.pop_back();
                                        }
                                        else {
                                            cout << "Error in size of other knot stage!" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << "Error in size on peersAtA!" << endl;
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in yoffset or peersAtA!" << endl;

                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}

void MyTrailCoreInKernelAtC::Case3322A(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if (checkMappedToSameKnotCase3322A()){
                            if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                do {
                                    if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                        if (nextStructureOfOtherKnot3322A()) {
                                            if ((yOffset.size()==2) && (peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                                if (filterOnPeerRhoOffset_3322A()) {
                                                    knotsAtB.clear();
                                                    if (checkKnotsAtBInKernelAtC()) {
                                                        if (knotsAtB.size()==4) {
                                                            if (updateSetOfMinimalStatesUpToNow()) {
                                                                prepareOutputTrailCore();
                                                                if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                    outputTrailCore(fileName);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                peersAtA.pop_back();
                                                peersAtA.pop_back();
                                                peerParameterOnRho.pop_back();
                                                peerParameterOnRho.pop_back();
                                            }
                                            else {
                                                cout << "Error in size of other knot stage!" << endl;
                                            }
                                        }
                                    }
                                    else {
                                        cout << "Error in size on peersAtA!" << endl;
                                    }
                                } while (!isLastStructureOfOtherKnot);
                                yOffset.pop_back();
                            }
                            else {
                                cout << "Error in yoffset or peersAtA!" << endl;

                            }
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}


void MyTrailCoreInKernelAtC::Case4222(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(4222)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if (checkMappedToSameOrbitalCase4222()){
                            if ((yOffset.size() == 1) && (peersAtA.size() == 4)) {
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                do {

                                    if (nextStructureOfOtherKnot4222()) {
                                        if ((yOffset.size()==2) && (peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                            if (filterOnPeerRhoOffset_4222()) {
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==4) {
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }

                                                    }
                                                }
                                            }
                                            peersAtA.pop_back();
                                            peerParameterOnRho.pop_back();
                                        }
                                        else {
                                            cout << "Error of size in other knot stage!" << endl;
                                        }
                                    }
                                } while (!isLastStructureOfOtherKnot);
                                yOffset.pop_back();
                            }
                            else {
                                cout << "Error in yoffset or peersAtA!" << endl;

                            }
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}


void MyTrailCoreInKernelAtC::Case433(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(433)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        knotAtB433.clear();
                        if (checkMappedToSameKnotAtBCase433(knotAtB433)){
                            if ((yOffset.size() == 1) && (peersAtA.size() == 4)) {
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                isP5Found = false;
                                BitPosition p5B(0,0,knotAtB433.back().back().z);
                                do {

                                    if (nextStructureOfOtherKnot433(p5B)) {
                                        if ((yOffset.size()==2) && (peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                            knotsAtB.clear();
                                            if (filterOnPeerRhoOffset_433()) {
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (updateSetOfMinimalStatesUpToNow()) {
                                                        prepareOutputTrailCore();
                                                        if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                            outputTrailCore(fileName);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        else {
                                            cout << "Error in size on other knot stage!" << endl;
                                        }
                                    }
                                } while (!isLastStructureOfOtherKnot);
                            }
                            else {
                                cout << "Error in yoffset or peersAtA!" << endl;
//                                return false;
                            }
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}

































