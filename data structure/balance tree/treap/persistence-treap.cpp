#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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

#define pii pair<int,int>
#define mp make_pair
mt19937 g(rand());

int max(int a,int b) {
	return a>b?a:b;
}

const int maxn=200005;

struct Treap { //root is interface 
	struct Tree {
		int l,r,size;
		int val,max;
		Tree() {} 
		Tree(int _l,int _r,int s,int v,int m):l(_l),r(_r),size(s),val(v),max(m) {}
	} tree[maxn*100];
	int size;
#define val(x) tree[x].val
#define size(x) tree[x].size
	int newnode(int v) {
		tree[++size]=Tree(0,0,1,v,v);
		return size;
	}
	void push_up(int index) {
		int l=tree[index].l,r=tree[index].r;
		size(index)=size(l)+size(r)+1;
		tree[index].max=max(val(index),max(tree[l].max,tree[r].max));
	}
	pii split(int index,int num) {
		if(!index)return mp(0,0);
		int l=tree[index].l,r=tree[index].r;
		int now=++size;
		tree[now]=tree[index];
		if(num<=size(l)) {
			pii lt=split(l,num);
			tree[now].l=lt.second;
			push_up(now);
			return mp(lt.first,now);
		} else {
			pii rt=split(r,num-size(l)-1);
			tree[now].r=rt.first;
			push_up(now);
			return mp(now,rt.second);
		}
	}
	int merge(int a,int b) {
		if(!a||!b)return a+b;
		int now=++size;
		if(g()%(size(a)+size(b))<size(a)) {
			tree[now]=tree[a];
			tree[now].r=merge(tree[a].r,b);
		} else {
			tree[now]=tree[b];
			tree[now].l=merge(a,tree[b].l);
		}
		push_up(now);
		return now;
	}
	int find_rank(int index,int k) {
		if(!index)return 0;
		if(k<=size(tree[index].l))return find_rank(tree[index].l,k);
		else if(k==size(tree[index].l)+1)return index;
		else return find_rank(tree[index].r,k-size(tree[index].l)-1);
	}
	int get_rank(int index,int v) {
		if(!index)return 0;
		if(v<val(index))return get_rank(tree[index].l,v);
		else return size(tree[index].l)+1+get_rank(tree[index].r,v);
	}
	int insert(int index,int k,int v) {
		pii tmp=split(index,k-1);
		return merge(merge(tmp.first,newnode(v)),tmp.second);
	}
	int remove(int index,int k) {
		return merge(split(index,k-1).first,split(index,k).second);
	}
} bbt;

int main() {
	
	return 0;
}
