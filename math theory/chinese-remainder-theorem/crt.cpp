#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

void Exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
	if(!b)d=a,x=1,y=0;
	else Exgcd(b,a%b,d,y,x),y-=(a/b)*x;
}

LL inv(LL a,LL p) {
	LL d=0,x=0,y=0;
	Exgcd(a,p,d,x,y);
	return (x%p+p)%p;
}

LL crt(int n,LL *a,LL *m) {
	LL M=1,ans=0;
	for(int i=1; i<=n; i++)M*=m[i];
	for(int i=1; i<=n; i++) {
		LL Mi=M/m[i],_Mi=inv(Mi,m[i]);
		ans=(ans+Mi*_Mi%M*a[i]%M)%M;
	}
	return ans;
}

int main() {
	
	return 0;
}