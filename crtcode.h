#ifndef CRTCODE_H
#define CRTCODE_H
#include "message.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class CRTCode
{
public:
    CRTCode();
    CRTCode(vector<int> b);
    void setbasis(vector<int> b);
    void setvals(vector<int> v);
    void encode(const Message& m);
    void encode(int m);
    bool decode(Message& m, int msgrange);
    static int hammingDist(const CRTCode& a, const CRTCode& b);
    static bool isValidBasis(vector<int> b);
    int minHammingDist(int range);
    
    vector<int> getBasis();
    vector<int> getVals();
    void printBasis();
    void printVals();
private:
    vector<int> basis;
    vector<int> vals;
    
    
    //decode help function
    void getCodeWords(int msgrange, vector<CRTCode>& codewords);
    
};

int CRT(const vector<int>& vals, const vector<int>& basis);


#endif // CRTCODE_H
