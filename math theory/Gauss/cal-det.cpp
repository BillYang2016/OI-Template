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

const int maxn=205,mod=1e9+7;

LL a[maxn][maxn];

int Gauss(int n) { //n^3logn
	LL ans=1;
	int bj=1;
	for(int i=1; i<=n; i++) {
		for(int j=i+1; j<=n; j++) {
			LL A=a[i][i],B=a[j][i];
			while(B) {
				LL t=A/B;
				A%=B;
				swap(A,B);
				for(int k=i; k<=n; k++)a[i][k]=(a[i][k]-a[j][k]*t%mod+mod)%mod;
				for(int k=i; k<=n; k++)swap(a[i][k],a[j][k]);
				bj*=-1;
			}
		}
		ans=ans*a[i][i]%mod;
	}
	return (ans*bj+mod)%mod;
}

int main() {
	
	return 0;
}