#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <string>
using namespace std;
class Message
{
public:
    Message();
    Message(int num);
    Message(string binary);
    static string IntToBinary(int n);
    static int BinaryToInt(string binary);
private:
    int m_int;
    string m_bin;
};

#endif // MESSAGE_H
