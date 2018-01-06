#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=1000005;

LL p,fac[maxn],inv[maxn],invf[maxn];

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;
	return ans;
}

LL C(LL n,LL m) {
	if(m>n)return 0;
	return fac[n]*invf[m]%p*invf[n-m]%p;
}

LL Lucas(LL n,LL m) {
	if(m==0)return 1;
	return (C(n%p,m%p)*Lucas(n/p,m/p))%p;
}

int main() {
	inv[1]=fac[0]=invf[0]=1;
	for(int i=1; i<p; i++) {
		if(i!=1)inv[i]=(p-p/i)*inv[p%i]%p;
		fac[i]=fac[i-1]*i%p;
		invf[i]=invf[i-1]*inv[i]%p;
	}
	return 0;
}