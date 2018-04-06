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

const int maxn=100005;

struct Palindsome_Automaton {
	int child[maxn][26];
	int n,size,last,s[maxn],len[maxn],next[maxn];
	Palindsome_Automaton() {
		size=-1;
		newnode(0); //even
		newnode(-1); //odd
		last=n=0;
		s[0]=-1;
		next[0]=next[1]=1;
	}
	int newnode(int v) {
		int now=++size;
		memset(child[now],0,sizeof(child[now]));
		next[now]=0;
		len[now]=v;
		return now;
	}
	void insert(int data) {
		s[++n]=data;
		int p=last;
		while(s[n-len[p]-1]!=s[n])p=next[p];
		if(!child[p][data]) {
			int now=newnode(len[p]+2),q=next[p];
			while(s[n-len[q]-1]!=s[n])q=next[q];
			next[now]=child[q][data];
			child[p][data]=now;
		}
		last=child[p][data];
	}
	void build(string s) {for(auto x:s)insert(x-'a');}
};

int main() {
	
	return 0;
} 
