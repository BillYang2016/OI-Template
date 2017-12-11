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

struct SuffixAutomaton {
	int cnt,root,last;
	int next[maxn*2],Max[maxn*2],end_pos[maxn*2];
	int child[maxn*2][maxc];
	SuffixAutomaton() {
		cnt=0;
		root=last=newnode(0);
	}
	int newnode(int val) {
		cnt++;
		next[cnt]=end_pos[cnt]=0;
		Max[cnt]=val;
		memset(child[cnt],0,sizeof(child[cnt]));
		return cnt;
	}
	void insert(int data) {
		int p=last,u=newnode(Max[last]+1);
		last=u;
		end_pos[u]=1; 
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
	void build(string s) {
		for(int i=0; i<s.length(); i++)insert(s[i]-'a');
	}
	int lcs(string s) {
		int ans=0,len=0,p=root;
		for(int i=0; i<s.length(); i++) {
			int ch=s[i]-'a';
			if(child[p][ch])p=child[p][ch],len++;
			else {
				while(p&&!child[p][ch])p=next[p];
				if(!p) {
					len=0;
					p=root;
				} else {
					len=Max[p]+1;
					p=child[p][ch];
				}
			}
			ans=max(ans,len);
		}
		return ans;
	}
	void topsort() {
		for(int i=1; i<=cnt; i++)Bucket[Max[i]]++;
		for(int i=1; i<=cnt; i++)Bucket[i]+=Bucket[i-1];
		for(int i=1; i<=cnt; i++)top[Bucket[Max[i]]--]=i;
	}
	void get_end_pos() {
		topsort();
		for(int i=cnt; i>=1; i--)end_pos[next[top[i]]]+=end_pos[top[i]];
	}
} sam;

int main() {
	
	return 0;
}
