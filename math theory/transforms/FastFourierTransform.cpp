#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<complex>
#include<cstdlib>
#include<climits>
#include<complex>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

#define cp complex<double>

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
const double pi=acos(-1);

struct FastFourierTransform {
	int n,rev[maxn];
	cp omega[maxn],iomega[maxn];
	void init(int n) {
		this->n=n;
		for(int i=0; i<n; i++) {
			omega[i]=cp(cos(2*pi/n*i),sin(2*pi/n*i));
			iomega[i]=conj(omega[i]); //conjugate complex
		}
		int k=log2(n);
		for(int i=0; i<n; i++) { //reverse bit position
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=1<<(k-j-1);
			rev[i]=t;
		}
	}
	void transform(cp *a,cp *omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]); //no double reversion
		for(int len=2; len<=n; len*=2) {
			int mid=len>>1;
			for(cp *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					cp t=omega[n/len*i]*p[mid+i];
					p[mid+i]=p[i]-t;
					p[i]+=t;
				}
		}
	}
	void dft(cp *a) {
		transform(a,omega);
	}
	void idft(cp *a) {
		transform(a,iomega);
		for(int i=0; i<n; i++)a[i]/=n;
	}
} fft;

void Multiply(const int* a1,const int n1,const int* a2,const int n2,int* ans) {
	int n=1;
	while(n<n1+n2)n<<=1; //complement integer
	static cp c1[maxn],c2[maxn];
	for(int i=0; i<n1; i++)c1[i].real(a1[i]);
	for(int i=0; i<n2; i++)c2[i].real(a2[i]);
	fft.init(n);
	fft.dft(c1);
	fft.dft(c2);
	for(int i=0; i<n; i++)c1[i]*=c2[i];
	fft.idft(c1);
	for(int i=0; i<n1+n2-1; i++)ans[i]=round(c1[i].real());
}

int main() {
	
	return 0;
} 
