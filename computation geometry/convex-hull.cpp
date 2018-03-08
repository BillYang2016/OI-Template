#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

//Need to reference class-Point

int ConvexHull(int n,Point* p,Point* ans) { //Andrew Algorithm：p[] is set of points,ans[] is set of convex-hull's points,return size of convex-hull's points
	//Need to confirm that there's no same points in p.if you need no points on edges,then change "<=" into "<"
	sort(p+1,p+n+1);
	int top=0;
	for(int i=1; i<=n; i++) { //down
		while(top>1&&dcmp(Cross(ans[top]-ans[top-1],p[i]-ans[top-1]))<=0)top--;
		ans[++top]=p[i];
	}
	int k=top;
	for(int i=n-1; i>=1; i--) { //up
		while(top>k&&dcmp(Cross(ans[top]-ans[top-1],p[i]-ans[top-1]))<=0)top--;
		ans[++top]=p[i];
	}
	if(n>1)top--;
	return top;
}

int main() {
	
	return 0;
}