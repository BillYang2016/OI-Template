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

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int mod=10007,inv2=5004;

struct FastWalshTransform {
	int n;
	void init(int n) {
		this->n=n;
	}
	void transform(LL *a,LL mul) {
		for(int len=2; len<=n; len<<=1) {
			int mid=len>>1;
			for(LL *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					LL x=p[i],y=p[mid+i];
					p[i]=(x+y)*mul%mod;
					p[mid+i]=(x-y+mod)*mul%mod;
				}
		}
	}
	void fwt(LL *a) {
		transform(a,1);
	}
	void ufwt(LL *a) {
		transform(a,inv2);
	}
} wtf;

int main() {
	
	return 0;
}