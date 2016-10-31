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
    int getInt() const;
    string getBin() const;
    void setInt(int v);
    void setBin(string s);
private:
    int m_int;
    string m_bin;
};

#endif // MESSAGE_H
