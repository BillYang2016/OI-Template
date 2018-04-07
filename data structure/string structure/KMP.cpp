#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1000005;

int nxt[maxn];

void Get_Next(int n,char *s) {
	nxt[1]=0;
	for(int i=2,j=0; i<=n; i++) {
		while(j&&s[i]!=s[j+1])j=nxt[j];
		if(s[i]==s[j+1])j++;
		nxt[i]=j;
	}
}

int KMP(int n,int m,char *a,char *b) {
	int ans=0;
	for(int i=1,j=0; i<=n; i++) {
		while(j&&a[i]!=b[j+1])j=nxt[j];
		if(a[i]==b[j+1])j++;
		if(j==m)ans++,j=nxt[j];
	}
	return ans;
}

int main() {
	
	return 0;
}