#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const double eps=1e-8;

double dcmp(double x) {return fabs(x)<=eps?0:x>eps?1:-1;}

double f(double x) {} //need to fill in

double Cal(double Left,double Right) {return (Right-Left)/6*(f(Left)+4*f((Left+Right)/2)+f(Right));}

double Simpson(double Left,double Right,double ans) {
	double mid=(Left+Right)/2,ans1=Cal(Left,mid),ans2=Cal(mid,Right);
	if(dcmp(ans-ans1-ans2)==0)return ans;
	else return Simpson(Left,mid,ans1)+Simpson(mid,Right,ans2);
}

int main() {
	
	return 0;
}