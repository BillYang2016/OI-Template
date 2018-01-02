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

struct Tree {
	int child[26],fail,next,cnt,sum;
};

struct Aho_Corasick_Automaton {
	int root,cnt;
	Tree tree[maxn];
	#define ch(x,i) tree[x].child[i]
	#define fail(x) tree[x].fail
	
	Aho_Corasick_Automaton() {
		init();
	}
	
	void init() {
		root=cnt=1;
		memset(tree,0,sizeof(tree));
	}
	
	int insert(string s) {
		int now=root;
		for(int i=0; i<s.length(); i++) {
			int j=s[i]-'a';
			if(!ch(now,j))ch(now,j)=++cnt;
			now=ch(now,j);
		}
		tree[now].cnt++;
		return now;
	}
	
	void buildfail() {
		queue<int>Q;
		Q.push(root);
		while(!Q.empty()) {
			int now=Q.front();
			Q.pop();
			for(int i=0; i<26; i++) {
				int& next=ch(now,i);
				if(!next) { //trie graph
					next=ch(fail(now),i)?ch(fail(now),i):root;
					continue;
				}
				Q.push(next);
				int p=fail(now);
				while(p&&!ch(p,i))p=fail(p);
				if(p)fail(next)=ch(p,i);
				else fail(next)=root;
				tree[next].next=tree[fail(next)].cnt?fail(next):tree[fail(next)].next;
			}
		}
	}
	
	int match(string s) {
		int now=root,ans=0;
		for(int i=0; i<s.length(); i++) {
			int j=s[i]-'a';
			now=ch(now,j);
			for(int j=now; j; j=tree[j].next) {
				tree[j].sum+=tree[j].cnt;
				tree[j].cnt=0;
			}
		}
		return ans;
	}
};

int main() {
	
	return 0;
}
