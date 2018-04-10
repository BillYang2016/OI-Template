#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

LL Quick_Pow(LL a,LL b,LL p) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)sum=sum*a%p;
	return sum;
}

void Exgcd(LL a,LL b,LL &gcd,LL &x,LL &y) {
	if(!b)gcd=a,x=1,y=0;
	else Exgcd(b,a%b,gcd,y,x),y-=x*(a/b);
}

LL inv(LL a,LL p) {
	// return Quick_Pow(a,p-2,p); //only when p is prime
	LL gcd,x,y;
	Exgcd(a,p,gcd,x,y);
	return (x%p+p)%p;
}

LL BSGS(LL a,LL b,LL p) {
	a%=p;
	if(a==0)return b==0?1:-1;
	static map<LL,LL> M;
	M.clear();
	LL mid=ceil(sqrt(p)),sum=1;
	for(int i=0; i<mid; i++) {
		if(!M.count(sum))M[sum]=i;
		sum=sum*a%p;
	}
	LL neg=inv(sum,p);
	sum=b;
	for(int i=0; i<mid; i++) {
		if(M.count(sum))return i*mid+M[sum];
		sum=sum*neg%p;
	}
	return -1;
}

int main() {

	return 0;
}

