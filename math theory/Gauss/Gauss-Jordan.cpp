#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const double eps=1e-6;

int n,m;
double a[105][105];

void Gauss_Jordan(int n,int m) {
	int now=0;
	for(int i=1; i<=m; i++) {
		int row=now+1;
		for(; row<=n; row++)if(fabs(a[row][i])>eps)break;
		if(row>n)continue;
		now++;
		for(int j=1; j<=m+1; j++)swap(a[now][j],a[row][j]);
		double t=a[now][i];
		for(int j=1; j<=m+1; j++)a[now][j]/=t;
		for(int j=1; j<=n; j++)
			if(j!=now) {
				t=a[j][i];
				for(int k=1; k<=m+1; k++)a[j][k]-=t*a[now][k];
			}
	}
}

int main() {
	
	return 0;
}