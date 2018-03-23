#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<complex>
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

const int maxn=131072+5;
const LL mod=998244353;
LL g=3;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL inv(LL x) {
	return Quick_Pow(x,mod-2);
}

vector<int> ppt;

void find_root(LL x) {
	LL tmp=x-1;
	for(int i=2; i<=sqrt(tmp); i++)
		if(tmp%i==0) {
			ppt.push_back(i);
			while(tmp%i==0)tmp/=i;
		}
	for(g=2; g<x; g++) {
		bool bj=1;
		for(int t:ppt)
			if(Quick_Pow(g,(x-1)/t)==1) {
				bj=0;
				break;
			}
		if(bj)return;
	}
}

struct NumberTheoreticTransform {
	int n,rev[maxn];
	LL omega[maxn],iomega[maxn];
	void init(int n) {
		this->n=n;
		int x=Quick_Pow(g,(mod-1)/n);
		omega[0]=iomega[0]=1;
		for(int i=1; i<n; i++) {
			omega[i]=omega[i-1]*x%mod;
			iomega[i]=inv(omega[i]);
		}
		int k=log2(n);
		for(int i=0; i<n; i++) { //reverse bit position
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=1<<(k-j-1);
			rev[i]=t;
		}
	}
	void transform(LL *a,LL *omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]); //no double reversion
		for(int len=2; len<=n; len*=2) {
			int mid=len>>1;
			for(LL *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					LL t=omega[n/len*i]*p[mid+i]%mod;
					p[mid+i]=(p[i]-t+mod)%mod;
					p[i]=(p[i]+t)%mod;
				}
		}
	}
	void dft(LL *a) {
		transform(a,omega);
	}
	void idft(LL *a) {
		transform(a,iomega);
		LL x=inv(n);
		for(int i=0; i<n; i++)a[i]=a[i]*x%mod;
	}
} ntt;

void Multiply(LL* a1,const int n1,LL* a2,const int n2,LL* ans) {
	int n=1;
	while(n<n1+n2)n<<=1; //complement integer
	ntt.init(n);
	ntt.dft(a1);
	ntt.dft(a2);
	for(int i=0; i<n; i++)a1[i]=a1[i]*a2[i]%mod;
	ntt.idft(a1);
	for(int i=0; i<n1+n2-1; i++)ans[i]=a1[i];
}

int main() {
	
	return 0;
} 
