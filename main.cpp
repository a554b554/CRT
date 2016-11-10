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

void testcoprime(){
    vector<int> input{10,10,10,10};
    vector<int> output;
    cout<<co_prime(input, output)<<endl;
    for (int i=0; i<output.size(); i++) {
        cout<<output[i]<<" ";
    }
    cout<<endl;
}


//please read this sample
void Sample(){
    //assume we want to encode '10110100'(8bit) to 'ABCDE'. capacity of ABCDE are '13 7 15 17 11', respectively.
    //fisrt we create a message that present the information we want to encode.
    Message m("10110100");
    
    //we can check the value in m.
    cout<<"binary m: "<<m.getBin()<<" "<<"int m: "<<m.getInt()<<endl;
    
    //if you want, you can also create m by a int value.
    // Message m(180);
    
    //then we create CRTcode for 'ABCDE'
    CRTCode code(vector<int>{13,7,15,17,11}); //must make sure basis are co-prime.
    
    
    //encoding
    code.encode(m);
    
    //we can check the encode result
    vector<int> encoderesult = code.getVals();
    for (int i=0; i<encoderesult.size(); i++) {
        cout<<m.getInt()<<" mod "<<code.getBasis()[i]<<" is "<<encoderesult[i]<<endl;
    }
    
    
    //if we want to decode, first we must know the encode range.
    //since our encode message is 8-bits, so the range is 0-255, totally 256.
    //next we create a message to store the decoded information
    Message decoded;
    
    //decoding
    code.decode(decoded, 256);
    
    //we can check the decode result.
    cout<<"origin message: "<<m.getBin()<<endl;
    cout<<"decode message: "<<decoded.getBin()<<endl;
    
    //if we have a transition error, for example
    encoderesult[0] -= 2;
    code.setvals(encoderesult);
    //we can still decode
    Message errordecode;
    code.decode(errordecode, 256);
    cout<<"error decode message: "<<errordecode.getBin()<<endl;
}




int main(int argc, char *argv[])
{
//    testintandbinary();
//    testencode();
//    testerrordecode();
//    testCRT();
    testcoprime();
//    Sample();
    return 0;
}
