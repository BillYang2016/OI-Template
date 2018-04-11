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

namespace mod_is_prime {
	void add(LL &x,LL v) {x=x+v>=mod?x+v-mod:x+v;}
	LL Quick_Pow(LL a,LL b) {
		LL ans=1;
		for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
		return ans;
	}
	int Gauss(int n) { //n^3
		LL bj=1,ans=1;
		for(int i=1; i<=n; i++) {
			int row=i;
			for(; row<=n; row++)if(a[row][i])break;
			if(row>n)return -1;
			if(row!=i) {
				for(int j=1; j<=n; j++)swap(a[i][j],a[row][j]);
				bj*=-1;
			}
			LL inv=Quick_Pow(a[i][i],mod-2);
			for(int j=i+1; j<=n; j++) {
				LL mul=a[j][i]*inv%mod;
				for(int k=i; k<=n; k++)add(a[j][k],mod-a[i][k]*mul%mod);
			}
			ans=ans*a[i][i]%mod;
		}
		return (ans*bj+mod)%mod;
	}
}

namespace mod_is_not_prime {
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
}

int main() {
	
	return 0;
}