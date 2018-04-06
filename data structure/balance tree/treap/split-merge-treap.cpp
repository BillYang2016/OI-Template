#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define pii pair<int,int>
mt19937 g(rand());

int max(int a,int b) {return a>b?a:b;}

const int maxn=200005;

struct Treap { //root is interface 
	struct Tree {
		int l,r,size;
		int val,max;
		Tree(int s=0,int v=0):l(0),r(0),size(s),val(v),max(v) {}
	} tree[maxn];
	int size;
#define ls(x) tree[x].l
#define rs(x) tree[x].r
#define val(x) tree[x].val
#define size(x) tree[x].size
	int newnode(int v) {tree[++size]=Tree(1,v);return size;}
	void push_up(int x) {
		size(x)=size(ls(x))+size(rs(x))+1;
		tree[x].max=max(val(x),max(tree[ls(x)].max,tree[rs(x)].max));
	}
	pii split(int x,int num) {
		if(!x)return pii(0,0);
		if(num<=size(ls(x))) {
			pii lt=split(ls(x),num);
			ls(x)=lt.second;
			push_up(x);
			return pii(lt.first,x);
		} else {
			pii rt=split(rs(x),num-size(ls(x))-1);
			rs(x)=rt.first;
			push_up(x);
			return pii(x,rt.second);
		}
	}
	int merge(int a,int b) {
		if(!a||!b)return a+b;
		if(g()%(size(a)+size(b))<size(a)) {
			rs(a)=merge(rs(a),b);
			push_up(a);
			return a;
		} else {
			ls(b)=merge(a,ls(b));
			push_up(b);
			return b;
		}
	}
	int find_rank(int x,int k) {
		if(!x)return 0;
		if(k<=size(ls(x)))return find_rank(ls(x),k);
		else if(k==size(ls(x))+1)return x;
		else return find_rank(rs(x),k-size(ls(x))-1);
	}
	int get_rank(int x,int v) {
		if(!x)return 0;
		if(v<val(x))return get_rank(ls(x),v);
		else return size(ls(x))+1+get_rank(rs(x),v);
	}
	int insert(int x,int k,int v) {
		pii tmp=split(x,k-1);
		return merge(merge(tmp.first,newnode(v)),tmp.second);
	}
	int remove(int x,int k) {return merge(split(x,k-1).first,split(x,k).second);}
} bbt;

int main() {
	
	return 0;
}
