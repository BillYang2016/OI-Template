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

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
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

void Exgcd(LL a,LL b,LL &gcd,LL &x,LL &y) {
	if(!b)gcd=a,x=1,y=0;
	else Exgcd(b,a%b,gcd,y,x),y-=x*(a/b);
}

LL inv(LL a,LL mod) {
	LL gcd,x,y;
	Exgcd(a,mod,gcd,x,y);
	return (x+mod)%mod;
}

LL Quick_Pow(LL a,LL b,LL mod) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

LL Fac(LL n,LL p,LL num) {
	if(n==0)return 1;
	LL sum=1;
	for(LL i=2; i<=num; i++)if(i%p)sum=sum*i%num;
	sum=Quick_Pow(sum,n/num,num);
	for(int i=2; i<=n%num; i++)if(i%p)sum=sum*i%num;
	return sum*Fac(n/p,p,num)%num;
}

LL Cal(LL n,LL p) {
	LL sum=0;
	for(LL i=n; i; i/=p)sum+=i/p;
	return sum;
}

LL C(LL n,LL m,LL p,LL num) {
	if(n<m)return 0;
	LL x=Fac(n,p,num),y=Fac(m,p,num),z=Fac(n-m,p,num);
	LL sum=Cal(n,p)-Cal(m,p)-Cal(n-m,p);
	return x*inv(y,num)%num*inv(z,num)%num*Quick_Pow(p,sum,num)%num;
}

LL ExLucas(LL n,LL m,LL mod) {
	LL x=mod,ans=0;
	for(LL i=2; i<=sqrt(mod); i++)
		if(x%i==0) {
			LL num=1;
			while(x%i==0)x/=i,num*=i;
			LL Mi=mod/num;
			ans=(ans+Mi*inv(Mi,num)%mod*C(n,m,i,num)%mod)%mod;
		}
	if(x>1)ans=(ans+mod/x*inv(mod/x,x)%mod*C(n,m,x,x)%mod)%mod;
	return ans;
}

int main() {
	
	return 0;
} 