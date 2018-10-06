//
//  myParts.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 31/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "myParts.hpp"

unsigned int getNrActiveSlices(const vector<SliceValue>& state){
    unsigned nrSlice = 0;
    if (state.size() == 64) {
        for (int i = 0; i < 64; i++) {
            if (state[i]) {
                nrSlice++;
            }
        }
        return nrSlice;
    }
    else {
        cout << "Error in size of state!" << endl;
        return 0;
    }
}

void classifyTrailsInFile(const string& aFileName, const KeccakFPropagation::DCorLC& aDCorLC){
    string file6 = "/Users/liuguozhen/Desktop/Core6Bits.txt";
    string file8 = "/Users/liuguozhen/Desktop/Core8Bits.txt";
    string file82 = "/Users/liuguozhen/Desktop/Core8Bits2Slices.txt";
    string file83 = "/Users/liuguozhen/Desktop/Core8Bits3Slices.txt";
    string file84 = "/Users/liuguozhen/Desktop/Core8Bits4Slices.txt";
    string file10 = "/Users/liuguozhen/Desktop/Core10Bits.txt";
    string file102 = "/Users/liuguozhen/Desktop/Core10Bits2Slices.txt";
    string file103 = "/Users/liuguozhen/Desktop/Core10Bits3Slices.txt";
    string file104 = "/Users/liuguozhen/Desktop/Core10Bits4Slices.txt";
    string file105 = "/Users/liuguozhen/Desktop/Core10Bits5Slices.txt";
    string file12 = "/Users/liuguozhen/Desktop/Core12Bits.txt";
    KeccakFDCLC keccakF(1600);
    KeccakFPropagation keccakFP(keccakF,aDCorLC);
    TrailFileIterator iTrailsIn(aFileName, keccakFP);
    cout << iTrailsIn << endl;
    for (; !iTrailsIn.isEnd(); ++iTrailsIn) {
        Trail trail = (*iTrailsIn);
        if (trail.states.size() == 1) {
            unsigned int nrBits = getHammingWeight(trail.states[0]);
            unsigned int nrSlices = getNrActiveSlices(trail.states[0]);
            switch (nrBits) {
                case 6:
                {
//                    ofstream fout(file6.c_str(), ios::app);
//                    trail.save(fout);
                }
                    break;
                case 8:
                {
                    if (nrSlices == 4) {
                        ofstream fout(file84.c_str(), ios::app);
                        trail.save(fout);
                    }
                    else if (nrSlices == 3) {
                        ofstream fout(file83.c_str(), ios::app);
                        trail.save(fout);
                    }
                    else if (nrSlices == 2) {
                        ofstream fout(file82.c_str(), ios::app);
                        trail.save(fout);
                    }
                    else {
                        cout << "Error!" << endl;
                    }
//                    ofstream fout(file8.c_str(), ios::app);
//                    trail.save(fout);
                }
                    break;
                case 10:
                {
                    if (nrSlices == 5) {
                        ofstream fout(file105.c_str(), ios::app);
                        trail.save(fout);
                    }
                    else if (nrSlices == 4) {
                        ofstream fout(file104.c_str(), ios::app);
                        trail.save(fout);
                    }
                    else if (nrSlices == 3) {
                        ofstream fout(file103.c_str(), ios::app);
                        trail.save(fout);
                    }
                    else if (nrSlices == 2) {
                        ofstream fout(file102.c_str(), ios::app);
                        trail.save(fout);
                    }
                    else {
                        cout << "Error!" << endl;
                    }
//                    ofstream fout(file10.c_str(), ios::app);
//                    trail.save(fout);
                }
                    break;
                case 12:
                {
                    ofstream fout(file12.c_str(), ios::app);
                    trail.save(fout);
                }
                    break;
                default:
                {
                    cout << "Error! Need to extend the checking space!" << endl;
                }
                    break;
            }
        }
        else {
            cout << "Error!" << endl;
        }
    }
    return;
}

void best1RForwardExtension(const string& fileName){
    cout << "Initializing..." << flush;
    KeccakFDCLC keccakF(1600);
    cout << endl;
    KeccakFPropagation keccakFTE(keccakF, KeccakFPropagation::DC);
    cout << keccakF << endl;

    cout << "Extending..." << flush;
    TrailFileIterator trailsIn(fileName, keccakFTE);
    cout << trailsIn << endl;

    stringstream oFileName;
    oFileName << fileName << string("_bestOneRoundForwardExtension");
    string outFileName = oFileName.str();
    ofstream fout(outFileName);
    TrailSaveToFile trailsOut(fout);

    ProgressMeter progress;
    progress.stack("File", trailsIn.getCount());
    for (; !trailsIn.isEnd(); ++trailsIn) {
        const vector<SliceValue>& lastStateOfTrail = (*trailsIn).states.back();
        cout << "the number of active rows: " << getNrActiveRows(lastStateOfTrail) << endl;
        unsigned int nrActiveSboxes = getNrActiveRows(lastStateOfTrail);
        if (nrActiveSboxes < 16) {
            AffineSpaceOfStates affineSpace = keccakFTE.buildStateBase(lastStateOfTrail);
            vector<SliceValue> oneOfBestCompatibleState;
            unsigned int oneBestWeight = 0xffff;
            for (SlicesAffineSpaceIterator aCompatibleState = affineSpace.getIterator(); !aCompatibleState.isEnd(); ++aCompatibleState) {
                unsigned currentWeight = keccakFTE.getWeight((*aCompatibleState));
                if (oneBestWeight > currentWeight) {
                    oneBestWeight = currentWeight;
                    oneOfBestCompatibleState = (*aCompatibleState);
                }
            }
            Trail newTrail(*trailsIn);
            newTrail.append(oneOfBestCompatibleState, oneBestWeight);
            trailsOut.fetchTrail(newTrail);
        }
        else {
            cout << "The number of active sboxes exceeds 16 !" << endl;
        }
        ++progress;
    }
    progress.unstack();
}


void chiEffectOnParity(){
    RowValue parity, row;
    inputSlicesSet possibleSliceSet;
    for (parity = 1; parity < 32; parity++) {
        for (row = 1; row < 4; row++) {
            checkParityThroughChi(parity, row, possibleSliceSet);
        }
    }
}
void checkParityThroughChi(RowValue parity, int nrRows, inputSlicesSet &possibleSliceSet){
    vector<RowValue> rows;//stores the row combinations
    RowValue currentParity;
    if (nrRows >=1 ) {
        rows.push_back(1);
        if (nrRows >=2 ) {
            rows.push_back(1);
            if (nrRows >= 3) {
                rows.push_back(1);
                if (nrRows >= 4) {
                    rows.push_back(1);
                    if (nrRows == 5) {
                        rows.push_back(1);
                    }
                }
            }
        }
    }
    if (rows.size() == nrRows) {
        do{
            if (weightCheck(rows)) {//The Hamming weight of each row should be no greater than 2
                currentParity = 0;
                for (int i=0 ; i<rows.size(); i++) {
                    currentParity ^= rows[i];
                }
                if (currentParity == parity) {
                    if (checkRepetition(rows, possibleSliceSet)) {
                        listCompatibleParity(rows);//for each right combination under the parity, compute all the output parity
                    }
                }
            }
        }while (inputPatternEnumeration(rows, nrRows));//iterate the input pattern
    }
    else
        cout << "Rows Size conflicts!" << endl;
}

bool weightCheck(vector<RowValue> &rows){
    for (int i = 0; i < rows.size(); i++) {
        if (computeHammingWeight(rows[i])>=3) {
            return false;
        }
    }
    return true;
}

int computeHammingWeight(RowValue row){
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if ((row >> i) & 0x1) {
            count ++;
        }
    }
    return count;
}

bool inputPatternEnumeration(vector<RowValue> &rows, int nrRows){
    if (rows.size() == 0) {
        return false;
    }
    else {
        if ((rows.size()>=1) && (rows.back()==31)) {
            rows.pop_back();
            if (inputPatternEnumeration(rows, nrRows)) {
                rows.push_back(1);
                return true;
            }
            else
                return false;
        }
        else if((rows.size()>=1) && (rows.back()<31)){
            rows.back()++;
            return true;
        }
        return true;
    }
}

void listCompatibleParity(vector<RowValue> rows){
    int DDT[32][32];
    differential_distribution_table_dir(DDT);
    vector<vector<RowValue>> compatibleOutputs;
    vector<int> index;//indicate the output slice pattern
    int depth=0;
    RowValue inputParity=0, outputParity=0;
    for (int i=0 ; i<rows.size(); i++) {//load the compatible outputs of all rows
        vector<RowValue> output;
        for (int j=1; j<DDT[rows[i]][0]; j++) {
            output.push_back(DDT[rows[i]][j]);
        }
        compatibleOutputs.push_back(output);
        index.push_back(1);
    }
    do {
        depth = 0;
        outputParity = 0;
        inputParity = 0;
//        for (int k=0; k<rows.size(); k++) {
//            bitset<5> row(rows[k]);
//            cout << row << " ";
//            inputParity ^= rows[k];
//        }
//        bitset<5> iParity(inputParity);
//        cout << " " << iParity << "  ";
        for (int i = compatibleOutputs.size()-1 ; i >= 0; i--) {
            outputParity ^= compatibleOutputs[i][index[compatibleOutputs.size()-1-i]-1];
//            bitset<5> oRow(compatibleOutputs[i][index[compatibleOutputs.size()-1-i]-1]);
//            cout << oRow << " ";
        }
        if (outputParity == 0) {
                    for (int k=0; k<rows.size(); k++) {
                        bitset<5> row(rows[k]);
                        cout << row << " ";
                        inputParity ^= rows[k];
                    }
                    bitset<5> iParity(inputParity);
                    cout << " " << iParity << "  ";
            for (int i = compatibleOutputs.size()-1 ; i >= 0; i--) {
                            bitset<5> oRow(compatibleOutputs[i][index[compatibleOutputs.size()-1-i]-1]);
                            cout << oRow << " ";
            }
                    bitset<5> oParity(outputParity);
                    cout << " " << oParity << endl;
        }
//        bitset<5> oParity(outputParity);
//        cout << " " << oParity << endl;
    } while (indexGeneration_recursiveSearchSpace(compatibleOutputs, index, depth));
}

bool indexGeneration_recursiveSearchSpace(vector<vector<RowValue>> &compatibleOutputs, vector<int> &index, int &depth){
    if (index.size()==0) {
        return false;
    }
    else {
        if ((index.back()==compatibleOutputs[depth].size()) && (depth>=0)) {
            index.pop_back();
            depth++;
            if(indexGeneration_recursiveSearchSpace(compatibleOutputs, index, depth)){
                depth--;
                index.push_back(1);//My index always starts from 1 rather than 0
                if (depth>=0) {
                    return true;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else if(index.back() < compatibleOutputs[depth].size()){
            index.back()++;
            return true;
        }
        else
            return false;
    }
}

void differential_distribution_table_dir(int DDT[32][32]){
    RowValue din, dout, x, k, index;
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            DDT[i][j] = 0;
        }
    }
    
    for (int i = 0; i < 32; i++) {
        DDT[i][0] = 1;
    }
    
    for (din = 0; din < 32; din++) {
        for (x = 0; x < 32; x++) {
            dout = Sbox(x) ^ Sbox(x^din);
            int flag = 0;
            for (k = 1; k < 32; k++) {
                if (DDT[din][k] == dout) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                index = DDT[din][0];
                DDT[din][index] = dout;
                DDT[din][0]++;
            }
        }
    }
    return;
}

unsigned int Sbox(unsigned int a){
    unsigned int res = 0;
    for (int i = 0; i < 5; i++) {
        res = res^(((a>>i)&0x1)^(~((a>>(i+1)%5)&0x1))&((a>>(i+2)%5)&0x1))<<i;
    }
    return res;
}

bool checkRepetition(vector<RowValue> rows, inputSlicesSet &possibleSliceSet){
    inputSlicePattern anInputSlice;
    for (int i=0; i < rows.size(); i++) {
        anInputSlice.insert(rows[i]);
    }
    if (possibleSliceSet.insert(anInputSlice).second == false) {
        return false;
    }
    return true;
}






















