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
	int child[2],father;
	int key,size,cnt;
	Tree() {}
	Tree(int l,int r,int fa,int k,int s,int c):father(fa),key(k),size(s),cnt(c) {
		child[0]=l;
		child[1]=r;
	}
};

struct Splay {
	int size,root;
	Tree tree[maxn];
	#define ls(x) tree[x].child[0]
	#define rs(x) tree[x].child[1]
	#define fa(x) tree[x].father
	#define cnt(x) tree[x].cnt
	#define val(x) tree[x].key
	#define size(x) tree[x].size
	Splay() {
		tree[++size]=Tree(0,2,0,-INT_MAX,0,0);
		tree[++size]=Tree(0,0,1,INT_MAX,0,0);
		root=size;
	}
	void clear(int index) {
		tree[index]=Tree(0,0,0,0,0,0);
	}
	bool checkson(int index) {
		return rs(fa(index))==index;
	}
	void push_up(int index) {
		if(!index)return;
		size(index)=size(ls(index))+size(rs(index))+cnt(index);
	}
	void rotate(int index) {
		int father=fa(index),grand=fa(father),side=checkson(index);
		if(grand)tree[grand].child[checkson(father)]=index;
		tree[father].child[side]=tree[index].child[side^1];
		fa(tree[father].child[side])=father;
		fa(father)=index;
		tree[index].child[side^1]=father;
		fa(index)=grand;
		push_up(father);
		push_up(index);
	}
	void splay(int index,int target=0) {
		for(int father; (father=fa(index))!=target; rotate(index))
			if(fa(father)!=target)rotate(checkson(index)==checkson(father)?father:index);
		if(target==0)root=index;
	}
	int insert(int v) {
		int now=root,father=0;
		while(now&&val(now)!=v) {
			father=now;
			size(father)++;
			now=tree[now].child[val(now)<v];
		}
		if(now)cnt(now)++,size(now)++;
		else {
			tree[now=++size]=Tree(0,0,father,v,1,1);
			if(father)tree[father].child[val(father)<v]=now;
		}
		splay(now);
		return now;
	}
	void remove() {
		int now=root,pre=pre_suc(0),suc=pre_suc(1);
		splay(pre);
		splay(suc,pre);
		if(cnt(now)>1) {
			cnt(now)--;
			size(now)--;
		} else {
			clear(now);
			ls(suc)=0;
		}
		size(pre)--;
		size(suc)--;
	}
	void delete_index(int index) {
		splay(index);
		remove();
	}
	void delete_val(int v) {
		if(rank(v)==-1)return;
		remove();
	}
	int rank(int v) {
		int now=root,ans=0;
		while(now>0&&val(now)!=v) {
			if(v<val(now))now=ls(now);
			else {
				ans+=size(ls(now))+cnt(now);
				now=rs(now);
			}
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
