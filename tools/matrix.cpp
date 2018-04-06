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

typedef long long LL;

struct Matrix {
	const static int maxn=5,mod=1e9+7;
	int n,m;
	LL a[maxn][maxn];
	Matrix(int n=0,int m=0,bool f=0):n(n),m(m) {
		memset(a,0,sizeof(a));
		for(int i=0; i<n; i++)a[i][i]=f;
	}
	LL* operator [] (const int x) {return a[x];}
	Matrix T() {
		Matrix c(m,n);
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)c[j][i]=a[i][j];
		return c;
	}
	Matrix operator + (Matrix b) {
		Matrix c(n,m);
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)c[i][j]=a[i][j]+b[i][j]>=mod?a[i][j]+b[i][j]-mod:a[i][j]+b[i][j];
		return c;
	}
	Matrix operator * (Matrix b) {
		Matrix c(n,b.m);
		for(int i=0; i<n; i++)
			for(int j=0; j<b.m; j++) {
				for(int k=0; k<m; k++)c[i][j]+=a[i][k]*b[k][j];
				c[i][j]%=mod;
			}
		return c;
	}
	Matrix operator ^ (LL k) {
		Matrix a=*this,c(n,m,1);
		for(; k; k>>=1,a=a*a)if(k&1)c=c*a;
		return c;
	}
};

int main() {

	return 0;
}

