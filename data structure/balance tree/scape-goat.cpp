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

const int maxn=100005;

struct Tree {
	int child[2],father;
	int size,val;
	Tree() {}
	Tree(int l,int r,int f,int s,int v):father(f),size(s),val(v) {
		child[0]=l;
		child[1]=r;
	}
};

struct ScapeGoat_Tree {
	const double alpha=0.7;
	Tree tree[maxn];
	int root,size;
	#define ls(x) tree[x].child[0]
	#define rs(x) tree[x].child[1]
	#define fa(x) tree[x].father
	#define val(x) tree[x].val
	#define size(x) tree[x].size
	ScapeGoat_Tree() {
		tree[++size]=Tree(0,2,0,2,-INT_MAX);
		tree[++size]=Tree(0,0,1,1,INT_MAX);
		root=1;
	}
	bool balance(int index) {
		return size(index)*alpha>=max(size(ls(index)),size(rs(index)));
	}
	bool checkson(int index) {
		return rs(fa(index))==index;
	}
	void push_up(int index) {
		size(index)=size(ls(index))+1+size(rs(index));
	}
	int cnt,a[maxn];
	void dfs(int index) {
		if(ls(index))dfs(ls(index));
		a[++cnt]=index;
		if(rs(index))dfs(rs(index));
	}
	int build(int Left,int Right) {
		if(Left>Right)return 0;
		int mid=(Left+Right)>>1,pos=a[mid];
		ls(pos)=build(Left,mid-1);
		rs(pos)=build(mid+1,Right);
		fa(ls(pos))=fa(rs(pos))=pos;
		push_up(pos);
		return pos;
	}
	void rebuild(int index) {
		cnt=0;
		dfs(index);
		int father=fa(index),side=checkson(index);
		int pos=build(1,cnt);
		tree[father].child[side]=pos;
		fa(pos)=father;
		if(index==root)root=pos;
	}
	void insert(int v) {
		int now=root,father=0;
		while(now) {
			father=now;
			size(father)++;
			now=tree[now].child[val(now)<=v];
		}
		tree[now=++size]=Tree(0,0,father,1,v);
		if(father)tree[father].child[val(father)<=v]=now;
		int pos=0;
		for(int i=now; i; i=fa(i))
			if(!balance(i))pos=i;
		if(pos)rebuild(pos);
	}
	void remove(int index) {
		if(ls(index)&&rs(index)) {
			int pre=ls(index);
			while(rs(pre))pre=rs(pre);
			val(index)=val(pre); //Ç°Çý¸´ÖÆ
			index=pre; //É¾³ýÇ°Çý
		}
		int son=ls(index)?ls(index):rs(index),side=checkson(index);
		tree[fa(index)].child[side]=son;
		fa(son)=fa(index);
		for(int i=fa(index); i; i=fa(i))size(i)--;
		if(index==root)root=son;
	}
	int find(int v) {
		int now=root;
		while(now) {
			if(val(now)==v)return now;
			else now=tree[now].child[val(now)<v];
		}
		return -1;
	}
	int rank(int v) {
		int now=root,ans=0;
		while(now) {
			if(v<=val(now))now=ls(now);
			else {
				ans+=size(ls(now))+1;
				now=rs(now);
			}
		}
		return ans;
	}
	int kth(int rank) {
		rank++;
		int now=root;
		while(now>0&&rank>=0) {
			if(ls(now)&&size(ls(now))>=rank)now=ls(now);
			else {
				if(rank<=size(ls(now))+1)return now;
				rank-=size(ls(now))+1;
				now=rs(now);
			}
		}
		return -1;
	}
	int pre(int num) {
		int now=root,ans=-INT_MAX;
		while(now) {
			if(val(now)<num)ans=max(ans,val(now)),now=rs(now);
			else now=ls(now);
		}
		return ans;
	}
	int suc(int num) {
		int now=root,ans=INT_MAX;
		while(now) {
			if(val(now)>num)ans=min(ans,val(now)),now=ls(now);
			else now=rs(now);
		}
		return ans;
	}
} sgt;

int main() {
	
	return 0;
}
