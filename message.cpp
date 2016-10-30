#include "message.h"
#include <assert.h>

Message::Message()
{

}

Message::Message(int num):m_int(num){
    assert(m_int>0);
    m_bin = IntToBinary(num);
}

Message::Message(string binary):m_bin(binary){
    m_int = BinaryToInt(binary);
}

string Message::IntToBinary(int n){
    string ans="";
    if(n==0){
        return "0";
    }
    while(n>0){
        ans=to_string(n%2)+ans;
        n/=2;
    }
    return ans;
}

int Message::BinaryToInt(string binary){
    int ans=0;
    int n = binary.length();
    for(int i=0; i<n; i++){
        if(binary[i]=='0'){
            continue;
        }
        else if(binary[i]=='1'){
            ans+=(1<<(n-i-1));
        }
        else{
            cerr<<"invalid input message"<<endl;
            exit(0);
        }
    }
    return ans;
}
