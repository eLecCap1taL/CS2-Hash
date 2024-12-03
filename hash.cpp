#include <iostream>
using namespace std;
class CRC{
	typedef unsigned long long CRC64_t;
	CRC64_t pCRC64Table[256];
	void CRC64_ProcessBuffer(CRC64_t *pCRC,const char *pBytes,int len)const{
		CRC64_t nCRC=*pCRC;
		while(len>0){
			nCRC=pCRC64Table[(nCRC^(*pBytes))&0xff]^(nCRC>>8);
			pBytes++;
			len--;
		}
		*pCRC=nCRC;
	}
public:
	CRC(){
		for(int i=0;i<256;i++){
			CRC64_t &val=(pCRC64Table[i]=i);
			for(int b=0;b<8;b++,val&1?(val>>=1)^=10785157014839085493ull:val>>=1);
		}
	}
	const CRC64_t operator () (const string& s)const{
		CRC64_t ret=18446744073709551615ull;
		CRC64_ProcessBuffer(&ret,s.c_str(),s.size());
		ret^=18446744073709551615ull;
		return ret;
	}
};
int main(){
	string s;
	getline(cin,s);
	printf("%016llX",CRC{}(s));
	return 0;
}
