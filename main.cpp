#include <iostream>
#include "message.h"
using namespace std;


void testintandbinary(){
    for(int i=0; i<1024; i++){
        cout<<"i: "<<i<<" "<<"binary: "<<Message::IntToBinary(i)<<" reconvert: "<<Message::BinaryToInt(Message::IntToBinary(i))<<endl;
    }
}

int main(int argc, char *argv[])
{
    testintandbinary();
    return 0;
}
