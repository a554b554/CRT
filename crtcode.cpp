#include "crtcode.h"
#include <cassert>

void extgcd(int a,int b,int& d,int& x,int& y){
    if(!b){
        d=a;x=1;y=0;
    }else{
        extgcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int mod_inv(int a,int n){//inverse of a on mod n
    int d,x,y;
    extgcd(a,n,d,x,y);
    return d==1?(x+n)%n:-1;
}


int CRT(const vector<int>& vals, const vector<int>& basis){
    int mm=1;
    int ans=0;
    for(int i=0; i<basis.size(); i++){
        mm*=basis[i];
    }
    for (int i=0; i<basis.size(); i++) {
        int mdm = mm/basis[i];
        int bi=mod_inv(mdm, basis[i]);
        ans+=vals[i]*bi*mdm;
    }
    return ans%mm;
}

CRTCode::CRTCode()
{

}

CRTCode::CRTCode(vector<int> b):basis(b){
    assert(isValidBasis(b));
}

void CRTCode::setbasis(vector<int> b){
    assert(isValidBasis(b));
    basis = b;
}

void CRTCode::setvals(vector<int> v){
    assert(v.size()==basis.size());
    vals.clear();
    for (int i=0; i<basis.size(); i++) {
        assert(v[i]<basis[i]);
        vals.push_back(v[i]);
    }
}


bool CRTCode::isValidBasis(vector<int> b){
    for (int i=0; i<b.size(); i++) {
        for (int j=i+1; j<b.size(); j++) {
            if (gcd(b[i], b[j])!=1) {
                return false;
            }
        }
    }
    return true;
}

void CRTCode::encode(const Message &m){
    encode(m.getInt());
}

bool CRTCode::decode(Message &m, int msgrange){
    assert(basis.size()==vals.size());
    vector<CRTCode> codewords;
    getCodeWords(msgrange, codewords);
    int crtans = CRT(this->vals, this->basis);
    if(crtans<msgrange){
        m.setInt(crtans);
        return true;
    }
    int minhammingdist=INT_MAX;
    int minid=0;
    vector<CRTCode> mincodelist;
    for (int i=0; i<codewords.size(); i++) {
        int dist = hammingDist(codewords[i], *this);
        if (dist<minhammingdist) {
            mincodelist.clear();
            mincodelist.push_back(codewords[i]);
            minid=i;
            minhammingdist=dist;
        }
        else if(dist==minhammingdist){
            mincodelist.push_back(codewords[i]);
        }
    }
    if(mincodelist.size()==1){
        m.setInt(minid);
        return true;
    }
    m.setInt(minid);
    return false;
}

void CRTCode::encode(int m){
    assert(!basis.empty());
    vals.clear();
    for(int i=0 ;i<basis.size(); i++){
        vals.push_back(m%basis[i]);
    }
}

int CRTCode::hammingDist(const CRTCode &a, const CRTCode &b){
    assert(a.basis.size()==b.basis.size());
    int ans=0;
    for (int i=0; i<a.basis.size(); i++) {
        assert(a.basis[i]==b.basis[i]);
        if(a.vals[i]!=b.vals[i]){
            ans++;
        }
    }
    return ans;
}

void CRTCode::getCodeWords(int msgrange, vector<CRTCode> &codewords){
    codewords.clear();
    for (int i=0; i<msgrange; i++) {
        CRTCode c(this->basis);
        c.encode(i);
        codewords.push_back(c);
    }
}

int CRTCode::minHammingDist(int range){
    assert(!basis.empty());
    vector<int> sorted=basis;
    sort(sorted.begin(), sorted.end());
    int i=0;
    int mul=1;
    for (; i<basis.size(); i++) {
        mul*=basis[i];
        if(mul>=range){
            i++;
            break;
        }
    }
    assert(mul>=range);
    return basis.size()-i+1;
}


vector<int> CRTCode::getBasis(){
    return basis;
}

vector<int> CRTCode::getVals(){
    return vals;
}

void CRTCode::printBasis(){
    for (int i=0; i<basis.size(); i++) {
        cout<<basis[i]<<" ";
    }
    cout<<endl;
}

void CRTCode::printVals(){
    for (int i=0; i<vals.size(); i++) {
        cout<<vals[i]<<" ";
    }
    cout<<endl;
}

bool is_coprime(const vector<int>& input){
    for (int i=0; i<input.size(); i++) {
        for (int j=i+1; j<input.size(); j++) {
            if (input[i]==input[j]) {
                return false;
            }
            if (gcd(input[i], input[j]) != 1) {
                return false;
            }
        }
    }
    return true;
}
int evaluatecount=0;


int co_prime(const vector<int>& input, vector<int>& output){
    int max=0;
    int mid=0;
    output.clear();
    vector<int> current = input;
    vector<vector<int>> s;
    
    while (1) {
        bool flag=true;
        for (int i=0; i<current.size(); i++) {
            if (current[i]!=2) {
                flag=false;
            }
        }
        if (flag) {
            break;
        }
        current[0]--;
        for (int i=0; i<current.size(); i++) {
            if (current[i]<2) {
                current[i]=input[i];
                current[i+1]--;
            }
        }
        if(is_coprime(current)){
            s.push_back(current);
        }
    }
    
    if (s.empty()) {
        return -1;
    }
    
    for (int i=0; i<s.size(); i++) {
        int mul=1;
        for (int j=0; j<s[i].size(); j++) {
            mul*=s[i][j];
        }
        if (mul>max) {
            max = mul;
            mid = i;
        }
    }
    
    output = s[mid];
    return max;
}

