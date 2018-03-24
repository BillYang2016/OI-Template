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

int n;
double a[105][105],Ans[105];

void Simplify(int x) {
	int p=x; //choose principal element 
	double Max=abs(a[x][x]);
	for(int i=x+1; i<=n; i++)
		if(abs(a[i][x])>Max) {
			Max=abs(a[i][x]);
			p=i;
		}
	if(p!=x) //exchange
		for(int i=x; i<=n+1; i++)swap(a[x][i],a[p][i]);
	for(int i=x+1; i<=n; i++) { //simplify
		double mul=a[i][x]/a[x][x];
		for(int j=x; j<=n+1; j++)a[i][j]-=a[x][j]*mul;
	}
}

void Gauss() {
	for(int i=1; i<=n; i++)Simplify(i);
	for(int i=n; i>=1; i--) { //back substitution 
		for(int j=i+1; j<=n; j++)a[i][n+1]-=a[i][j]*Ans[j];
		Ans[i]=a[i][n+1]/a[i][i];
	}
}

int main() {

	return 0;
}