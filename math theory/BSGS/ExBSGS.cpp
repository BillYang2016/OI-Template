#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

//Need to reference BSGS

LL ExBSGS(LL a,LL b,LL p) {
	LL gcd,c=0;
	while((gcd=__gcd(a,p))!=1) {
		if(b==1)return c;
		if(b%gcd)return -1;
		p/=gcd;
		b=b/gcd*inv(a/gcd,p)%p;
		c++;
	}
	LL ans=BSGS(a,b,p);
	return ans==-1?-1:ans+c;
}

int main() {
	
	return 0;
}