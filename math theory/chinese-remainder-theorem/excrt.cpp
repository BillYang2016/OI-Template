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

LL Quick_Mul(LL a,LL b,LL p) {
	LL sum=0;
	for(; b; b>>=1,a=(a<<1)%p)if(b&1)sum=(sum+a)%p;
	return sum;
}

LL Excrt(int n,LL *r,LL *m) {
	LL M=m[1],ans=r[1];
	for(int i=2; i<=n; i++) { //Mx_1+m_ix_2=a_i-ans
		LL a=M,b=m[i],x,y,c=(r[i]-ans%m[i]+m[i])%m[i],gcd;
		Exgcd(a,b,gcd,x,y);
		if(c%gcd)return -1;
		x=Quick_Mul(x,c/gcd,b/gcd);
		ans+=x*M;
		M=M/gcd*b;
		ans=(ans%M+M)%M;
	}
	return ans;
}

int main() {
	
	return 0;
}