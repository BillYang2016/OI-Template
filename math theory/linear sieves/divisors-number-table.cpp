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

const int maxn=1000005;

int vst[maxn],Prime[maxn],cnt=0; //prime
int d[maxn],Min_Divnum[maxn]; //divisors

void Divisors_Number_Table(int n) {
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {
			Prime[++cnt]=i;
			Min_Divnum[i]=1;
			d[i]=2;
		}
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0) {
				Min_Divnum[i*Prime[j]]=Min_Divnum[i]+1;
				d[i*Prime[j]]=d[i]/(Min_Divnum[i]+1)*(Min_Divnum[i]+2);
				break;
			}
			Min_Divnum[i*Prime[j]]=1;
			d[i*Prime[j]]=d[i]*d[Prime[j]];
		}
	}
}

int main() {

	return 0;
}