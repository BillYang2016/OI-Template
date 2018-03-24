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

int n;
double a[105][105];

void Gauss_Jordan(int n) {
	for(int i=1; i<=n; i++) {
		int row=i;
		for(; row<=n; row++)if(fabs(a[row][i])>eps)break;
		if(row>n)continue;
		for(int j=1; j<=n+1; j++)swap(a[i][j],a[row][j]);
		double t=a[i][i];
		for(int j=1; j<=n+1; j++)a[i][j]/=t;
		for(int j=1; j<=n; j++)
			if(j!=i) {
				t=a[j][i];
				for(int k=1; k<=n+1; k++)a[j][k]-=t*a[i][k];
			}
	}
}

int main() {
	
	return 0;
}