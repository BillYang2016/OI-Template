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

const int maxn=250005,maxc=26;

struct Suffix_Automaton {
	int cnt,root,last;
	int child[maxn<<1][maxc],next[maxn<<1],Max[maxn<<1];
	int buc[maxn<<1],top[maxn<<1],end_pos[maxn<<1];
	Suffix_Automaton() {init();}
	void init() {cnt=0;root=last=newnode(0);}
	int newnode(int val) {
		cnt++;
		next[cnt]=0;
		Max[cnt]=val;
		fill(child[cnt],child[cnt]+maxc,0);
		return cnt;
	}
	void insert(int data) {
		int p=last,u=newnode(Max[last]+1);
		end_pos[last=u]=1;
		for(; p&&!child[p][data]; p=next[p])child[p][data]=u;
		if(!p)next[u]=root;
		else {
			int old=child[p][data];
			if(Max[old]==Max[p]+1)next[u]=old;
			else {
				int New=newnode(Max[p]+1);
				copy(child[old],child[old]+maxc,child[New]);
				next[New]=next[old];
				next[u]=next[old]=New;
				for(; child[p][data]==old; p=next[p])child[p][data]=New;
			}
		}
	}
	void build(string s) {for(auto x:s)insert(x-'a');}
	int run(string s) {
		int p=root,len=0,ans=0;
		for(auto x:s) {
			int ch=x-'a';
			if(child[p][ch])len++,p=child[p][ch];
			else {
				while(p&&!child[p][ch])p=next[p];
				if(!p)len=0,p=root;
				else len=Max[p]+1,p=child[p][ch];
			}
			ans=max(ans,len);
		}
		return ans;
	}
	void topsort() {
		for(int i=1; i<=cnt; i++)buc[Max[i]]++;
		for(int i=1; i<=cnt; i++)buc[i]+=buc[i-1];
		for(int i=1; i<=cnt; i++)top[buc[Max[i]]--]=i;
	}
	void get_end_pos() {
		topsort();
		for(int i=cnt; i>=1; i--)end_pos[next[top[i]]]+=end_pos[top[i]];
	}
} sam;

int main() {
	
	return 0;
}
