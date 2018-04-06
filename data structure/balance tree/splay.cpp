#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

struct Splay {
	struct Tree {
		int child[2],father;
		int key,size,cnt;
		Tree(int l=0,int r=0,int fa=0,int k=0,int s=0):father(fa),key(k),size(s),cnt(s) {child[0]=l,child[1]=r;}
	} tree[maxn];
	int size,root;
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define fa(x) tree[x].father
#define cnt(x) tree[x].cnt
#define val(x) tree[x].key
#define size(x) tree[x].size
	Splay() {
		tree[++size]=Tree(0,2,0,INT_MIN,0);
		tree[++size]=Tree(0,0,1,INT_MAX,0);
		root=size;
	}
	void clear(int x) {tree[x]=0;}
	bool checkson(int x) {return rs(fa(x))==x;}
	void push_up(int x) {if(x)size(x)=size(ls(x))+size(rs(x))+cnt(x);}
	void rotate(int x) {
		int f=fa(x),g=fa(f),side=checkson(x);
		if(g)tree[g].child[checkson(f)]=x;
		tree[f].child[side]=tree[x].child[side^1],fa(tree[f].child[side])=f;
		fa(f)=x,tree[x].child[side^1]=f;
		fa(x)=g;
		push_up(f),push_up(x);
	}
	void splay(int x,int tar=0) {
		for(int f; (f=fa(x))!=tar; rotate(x))if(fa(f)!=tar)rotate(checkson(x)==checkson(f)?f:x);
		if(tar==0)root=x;
	}
	int insert(int v) {
		int now=root,fa=0;
		while(now&&val(now)!=v) {
			fa=now;
			size(fa)++;
			now=tree[now].child[val(now)<v];
		}
		if(now)cnt(now)++,size(now)++;
		else {
			tree[now=++size]=Tree(0,0,fa,v,1);
			if(fa)tree[fa].child[val(fa)<v]=now;
		}
		splay(now);
		return now;
	}
	void remove() {
		int now=root,pre=pre_suc(0),suc=pre_suc(1);
		splay(pre);
		splay(suc,pre);
		if(cnt(now)>1) {cnt(now)--;size(now)--;}
		else {clear(now);ls(suc)=0;}
		size(pre)--;
		size(suc)--;
	}
	void delete_index(int x) {splay(x);remove();}
	void delete_val(int v) {if(rank(v)==-1)return;remove();}
	int rank(int v) {
		int now=root,ans=0;
		while(now>0&&val(now)!=v) {
			if(v<val(now))now=ls(now);
			else {ans+=size(ls(now))+cnt(now);now=rs(now);}
		}
		if(now<=0)return -1;
		ans+=size(ls(now));
		splay(now);
		return ans+1;
	}
	int kth(int rank) {
		int now=root;
		while(now>=0&&rank>=0) {
			if(ls(now)&&size(ls(now))>=rank)now=ls(now);
			else {
				int tmp=size(ls(now))+cnt(now);
				if(rank<=tmp)return now;
				rank-=tmp;
				now=rs(now);
			}
		}
		return -1;
	}
	int pre_suc(int bj) {
		int now=tree[root].child[bj];
		while(tree[now].child[bj^1])now=tree[now].child[bj^1];
		return now;
	}
	int pre_suc(int v,int bj) {
		if(rank(v)==-1) {
			insert(v);
			int pre=pre_suc(bj);
			delete_index(size);
			return pre;
		} else return pre_suc(bj);
	}
} splay;

int main() {
	
	return 0;
}