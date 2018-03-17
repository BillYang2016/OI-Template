#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005;

struct Tree {
	int child[2],fa;
	bool rev;
	int val,sum;
	Tree(int v=0):val(v),sum(v) {child[0]=child[1]=fa=rev=0;}
};

struct Link_Cut_Tree {
	Tree tree[maxn];
	int top,S[maxn];
#define fa(x) tree[x].fa
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define rev(x) tree[x].rev
	bool isroot(int x) {return ls(fa(x))!=x&&rs(fa(x))!=x;}
	bool checkson(int x) {return rs(fa(x))==x;}
	void reverse(int x) {swap(ls(x),rs(x));rev(x)^=1;}
	void push_down(int x) {
		if(!rev(x))return;
		reverse(ls(x)),reverse(rs(x));
		rev(x)=0;
	}
	void push_up(int x) {tree[x].sum=tree[ls(x)].sum+tree[rs(x)].sum+tree[x].val;}
	void rotate(int x) {
		int f=fa(x),g=fa(f),side=checkson(x);
		if(!isroot(f))tree[g].child[checkson(f)]=x;
		tree[f].child[side]=tree[x].child[!side],fa(tree[f].child[side])=f;
		fa(f)=x,tree[x].child[!side]=f;
		fa(x)=g;
		push_up(f),push_up(x);
	}
	void splay(int x) {
		S[++top]=x;
		for(int i=x; !isroot(i); i=fa(i))S[++top]=fa(i);
		while(top)push_down(S[top--]);
		for(int f; !isroot(x); rotate(x)) {
			f=fa(x);
			if(!isroot(f))rotate(checkson(x)==checkson(f)?f:x);
		}
	}
	void access(int x) {
		for(int son=0; x; son=x,x=fa(x)) {
			splay(x);
			rs(x)=son;
			push_up(x);
		}
	}
	void make_root(int x) {access(x);splay(x);reverse(x);}
	void split(int x,int y) {make_root(x);access(y);splay(y);}
	void link(int x,int y) {make_root(x);fa(x)=y;} //y->x
	void cut(int x,int y) {split(x,y);ls(y)=fa(x)=0;}
	int pre(int x) {x=ls(x);while(rs(x))x=rs(x);return x;}
	void modify(int x,int v) {splay(x);tree[x].val=v;push_up(x);}
	int get_root(int x) {
		access(x);
		splay(x);
		while(ls(x))x=ls(x);
		return x;
	}
} lct;

int main() {
	
	return 0;
}