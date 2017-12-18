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

const int TIMES=10;

LL Quick_Mul(LL a,LL b,LL p) {
	LL tmp=(a*b-(LL)((long double)a/p*b+1e-8)*p);
	if(tmp<0)return tmp+p;
	else return tmp;
}

LL Quick_Pow(LL a,LL b,LL p) {
	LL sum=1;
	for(a%=p; b; b>>=1,a=Quick_Mul(a,a,p))if(b&1)sum=Quick_Mul(sum,a,p);
	return sum;
}

mt19937 g(rand());

bool Witness(LL a,LL n) {
	LL u=n-1,t=0;
	while(u%2==0)t++,u>>=1;
	LL x=Quick_Pow(a,u,n);
	if(x==1)return false;
	for(int i=1; i<=t; i++,x=Quick_Mul(x,x,n))
		if(x!=n-1&&x!=1&&Quick_Mul(x,x,n)==1)return true;
	return x!=1;
}

bool Miller_Rabin(LL n) {
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	for(int i=1; i<=TIMES; i++)
		if(Witness(g()%(n-1)+1,n))return false;
	return true;
}

LL Pollar_Rho(LL n) {
	if(!(n&1))return 2;
	while(true) {
		LL a=g()%(n-1)+1,b=a,c=g()%(n-1)+1;
		if(c==2)c=3;
		while(true) {
			a=(Quick_Mul(a,a,n)+c)%n;
			b=(Quick_Mul(b,b,n)+c)%n;
			b=(Quick_Mul(b,b,n)+c)%n;
			if(a==b)break; //find a circle
			LL d=__gcd(abs(b-a),n);
			if(d>1)return d;
		}
	}
}

LL Find_Fac(LL n) { //minimum factor
	if(Miller_Rabin(n))return n;
	LL p=Pollar_Rho(n);
	return min(Find_Fac(p),Find_Fac(n/p));
}

LL n;

int main() {
	
	return 0;
} 