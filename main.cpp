#include <iostream>
#include "crtcode.h"
#include <ctime>
using namespace std;


void testintandbinary(){
    for(int i=0; i<1024; i++){
        cout<<"i: "<<i<<" "<<"binary: "<<Message::IntToBinary(i)<<" reconvert: "<<Message::BinaryToInt(Message::IntToBinary(i))<<endl;
    }
}

void testencode(){
    int range=128;
    for (int i=0; i<range; i++) {
        Message m(i);
        CRTCode code(vector<int>{2,3,5,7,11});
        code.encode(m);
        Message de;
        code.decode(de, range);
        cout<<m.getInt()<<"  "<<de.getInt()<<endl;
        
        
    }
}

void testCRT(){
    vector<int> basis{5,7,9,11,13};
    int range=500;
    for (int i=0; i<range; i++) {
        CRTCode code(basis);
        code.encode(i);
        cout<<CRT(code.getVals(), basis)<<endl;
    }
}

void testerrordecode(){
    int origin = 198;
    int range = 256;
    vector<int> basis{5,7,9,11,13};
    Message m_origin(origin);
    CRTCode c_origin(basis);
    c_origin.encode(m_origin);
//    cout<<c_origin.minHammingDist(range);
    clock_t start=clock();
    for (int d=0; d<100; d++) {
        vector<int> received = c_origin.getVals();
        Message decoded;
        received[d%received.size()] = (received[d%received.size()]+2)%basis[d%received.size()];
//        received[0]=(received[0]+1)%basis[0];
        CRTCode receivedcode(basis);
        receivedcode.setvals(received);
        bool success=receivedcode.decode(decoded, range);
        cout<<"origin code: ";
        c_origin.printVals();
        cout<<"received code: ";
        receivedcode.printVals();
        cout<<"decode success: "<<success<<endl;
        cout<<"decode result: "<<decoded.getInt()<<endl;
    }
    clock_t end=clock();
    double time=(double)(end-start)/CLOCKS_PER_SEC;
    cout<<"time: "<<time<<endl;
}

int main(int argc, char *argv[])
{
//    testintandbinary();
//    testencode();
    testerrordecode();
//    testCRT();
    return 0;
}
