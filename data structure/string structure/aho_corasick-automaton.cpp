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

const int maxn=200005;

struct Aho_Corasick_Automaton {
	struct Tree {
		int child[26];
		int fail,cnt,next;
		bool flag;
		void clear() {fill(child,child+26,0);fail=cnt=flag=next=0;}
	} tree[maxn];
	int cnt;
#define ch(x,i) tree[x].child[i]
#define fail(x) tree[x].fail
#define next(x) tree[x].next
	Aho_Corasick_Automaton() {init();}
	void init() {tree[cnt=0].clear();}
	int newnode() {tree[++cnt].clear();return cnt;}
	void insert(string s) {
		int now=0;
		for(char x:s) {
			int j=x-'a';
			if(!ch(now,j))ch(now,j)=newnode();
			now=ch(now,j);
		}
		tree[now].cnt++;
		tree[now].flag=1;
	}
	void buildfail() {
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()) {
			int now=Q.front();
			Q.pop();
			for(int i=0; i<26; i++) {
				int &son=ch(now,i);
				if(!son) {
					son=now?ch(fail(now),i):0;
					continue;
				}
				fail(son)=now?ch(fail(now),i):0;
				tree[son].flag|=tree[fail(son)].flag;
				next(son)=tree[fail(son)].cnt?fail(son):next(fail(son));
				Q.push(son);
			}
		}
	}
	int match(string s) {
		int now=0,ans=0;
		for(auto x:s) {
			int j=x-'a';
			now=ch(now,j);
			for(int j=now; j; j=next(j))ans+=tree[j].cnt,tree[j].cnt=0;
		}
		return ans;
	}
} acam;

int main() {
	
	return 0;
}
