//
//  myParts.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 31/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef myParts_hpp
#define myParts_hpp
#include <iostream>
#include <sstream>
#include <string>
#include <set>

#include "Keccak-f.h"
#include "Keccak-fDCLC.h"
#include "Keccak-fPropagation.h"
#include "Keccak-fPositions.h"
#include "types.h"

#include "Keccak-fState.h"
#include "translationsymmetry.h"

#include "Keccak-fTrails.h"
#include "Keccak-fTrailExtensionBasedOnParity.h"
#include "progress.h"
#include "Keccak-fAffineBases.h"
using namespace std;

void classifyTrailsInFile(const string& aFileName, const KeccakFPropagation::DCorLC& aDCorLC);
unsigned int getNrActiveSlices(const vector<SliceValue>& state);
void best1RForwardExtension(const string& fileName);
typedef multiset<RowValue, greater<RowValue>> inputSlicePattern;
typedef set<inputSlicePattern> inputSlicesSet;

// The functions that help deal with properties of Keccak round functions

/**
  * This function outputs the parity corresponds to input parity through chi.
  * Note, the input rows with Hamming weight greater than 3 are not checked because generally in our check case there are at most 2 bits in each row.
  * Thus, in the actual search phase, when the rows with more than 3 bits are encountered, we should specially check it.
  */
void chiEffectOnParity();

/**
  * This function actually checks the possible cases.
  * @param  parity  the input parity pattern to be checked
  * @param  nrRows  the number of active rows for this input parity
  */
void checkParityThroughChi(RowValue parity, int nrRows, inputSlicesSet &possibleSliceSet);

/**
  * This function enumerates all the input patterns of chi under the specific parity and nrRows.
  * @param  rows    it stores all the input rows in the slice. The values of rows corresponds to the input difference of the Sbox
  * @param  nrRows  the number of active Sbox in this slice under the specific parity
  */
bool inputPatternEnumeration(vector<RowValue> &rows, int nrRows);

/**
  * For each of the input slice pattern, list all the compatible output pattersn as well as the output parities.
  * @param  rows    the input slice pattern
  */
void listCompatibleParity(vector<RowValue> rows);

/**
  * The chi operation.
  */
unsigned int Sbox(unsigned int a);

/**
  * List the DDT in the fashion of the first element stores the number(-1) of compatible output difference and other elements store all the output differences.
  */
void differential_distribution_table_dir(int DDT[32][32]);

/**
  * For each input pattern there are thousands of compatible output patterns.
  * Given one input pattern how to cover the ouput space?
  * This function traverses the output difference space recursiely.
  * @param  compatibleOutputs   it stores the compatible output difference in a 2-dimension vector
  * @param  index   it stores the pointers to the output differences, for example, the output difference to be chosen for a specific row
  * @param  depth   as the size of output difference space differs for different rows, depth is used to identify which row is pointed
  */
bool indexGeneration_recursiveSearchSpace(vector<vector<RowValue>> &compatibleOutputs, vector<int> &index, int& depth);

/**
  *
  */
bool weightCheck(vector<RowValue> &rows);

/**
  *
  */
int computeHammingWeight(RowValue row);

bool checkRepetition(vector<RowValue> rows, inputSlicesSet &possibleSliceSet);

#endif /* myParts_hpp */
