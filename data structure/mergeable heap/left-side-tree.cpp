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

struct LeftSideTree { //root is interface
	struct Tree {
		int ls,rs,val,dist;
		Tree(int l=0,int r=0,int v=0,int d=0):ls(l),rs(r),val(v),dist(d) {}
	} tree[maxn];
	int size;
	int newnode(int v) {tree[++size]=Tree(0,0,v,0);return size;}
	int merge(int x,int y) {
		if(!x||!y)return x+y;
		if(tree[x].val<tree[y].val)swap(x,y); //big root heap
		tree[x].rs=merge(tree[x].rs,y);
		if(tree[tree[x].rs].dist>tree[tree[x].ls].dist)swap(tree[x].ls,tree[x].rs);
		if(!tree[x].rs)tree[x].dist=0;
		else tree[x].dist=tree[tree[x].rs].dist+1;
		return x;
	}
	int push(int x,int v) {return merge(x,newnode(v));}
	int pop(int x) {
		int l=tree[x].ls,r=tree[x].rs;
		tree[x]=Tree();
		return merge(l,r);
	}
};

int main() {

	return 0;
}
