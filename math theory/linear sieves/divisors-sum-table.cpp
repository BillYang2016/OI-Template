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

typedef long long LL;

const int maxn=1000005;

int vst[maxn],Prime[maxn],cnt=0; //prime
LL f[maxn],Min_Fac_last[maxn],Min_Fac_sum[maxn]; //divisors

void Divisors_Sum_Table(int n) {
	f[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {
			Prime[++cnt]=i;
			Min_Fac_last[i]=i;
			f[i]=Min_Fac_sum[i]=i+1;
		}
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0) {
				Min_Fac_last[i*Prime[j]]=Min_Fac_last[i]*Prime[j];
				Min_Fac_sum[i*Prime[j]]=Min_Fac_sum[i]+Min_Fac_last[i*Prime[j]];
				f[i*Prime[j]]=f[i]/Min_Fac_sum[i]*Min_Fac_sum[i*Prime[j]];
				break;
			}
			f[i*Prime[j]]=f[i]*(Prime[j]+1);
			Min_Fac_last[i*Prime[j]]=Prime[j];
			Min_Fac_sum[i*Prime[j]]=Prime[j]+1;
		}
	}
}

int main() {

	return 0;
}