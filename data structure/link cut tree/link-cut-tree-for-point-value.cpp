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
#include<stack>
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

//for point value

const int maxn=100005;

struct Tree {
	int father,child[2];
	bool rev;
	int max,val,sum;
};

struct Link_Cut_Tree {
	Tree tree[maxn];
	stack<int>S;
	#define fa(x) tree[x].father
	#define ls(x) tree[x].child[0]
	#define rs(x) tree[x].child[1]
	#define rev(x) tree[x].rev
	bool isroot(int index) {
		return ls(fa(index))!=index&&rs(fa(index))!=index;
	}
	bool checkson(int index) {
		return rs(fa(index))==index;
	}
	void push_down(int index) {
		if(!rev(index))return;
		swap(ls(index),rs(index));
		rev(ls(index))^=1;
		rev(rs(index))^=1;
		rev(index)=0;
	}
	void push_up(int index) {
		tree[index].max=max(max(tree[ls(index)].max,tree[rs(index)].max),tree[index].val);
		tree[index].sum=tree[ls(index)].sum+tree[rs(index)].sum+tree[index].val;
	}
	void rotate(int index) {
		int father=fa(index),grand=fa(father),side=checkson(index);
		if(!isroot(father))tree[grand].child[checkson(father)]=index;
		tree[father].child[side]=tree[index].child[side^1];
		fa(tree[father].child[side])=father;
		fa(father)=index;
		tree[index].child[side^1]=father;
		fa(index)=grand;
		push_up(father);
		push_up(index);
	}
	void splay(int index) {
		S.push(index);
		for(int i=index; !isroot(i); i=fa(i))S.push(fa(i));
		while(!S.empty())push_down(S.top()),S.pop();
		for(int father; !isroot(index); rotate(index)) {
			father=fa(index);
			if(!isroot(father))rotate(checkson(index)==checkson(father)?father:index);
		}
	}
	void access(int index) {
		for(int son=0; index; son=index,index=fa(index)) {
			splay(index);
			rs(index)=son;
			push_up(index);
		}
	}
	void reverse(int index) {
		access(index);
		splay(index);
		rev(index)^=1;
	}
	void link(int x,int y) {
		reverse(x);
		fa(x)=y;
	}
	void split(int x,int y) {
		reverse(x);
		access(y);
		splay(y);
	} 
	void cut(int x,int y) { 
		split(x,y);
		ls(y)=fa(x)=0;
	}
	void modify(int index,int val) {
		splay(index);
		tree[index].val=val;
		push_up(index);
	}
	int get_root(int index) {
		access(index);
		splay(index);
		int u=index;
		while(ls(u))u=ls(u);
		return u;
	}
};

int main() {
	
	return 0;
}
