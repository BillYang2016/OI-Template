#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct ScapeGoat_Tree {
	struct Tree {
		int child[2],father;
		int size,val;
		Tree(int l=0,int r=0,int f=0,int s=0,int v=0):father(f),size(s),val(v) {child[0]=l,child[1]=r;}
	} tree[maxn];
	const double alpha=0.7;
	int root,size;
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define fa(x) tree[x].father
#define val(x) tree[x].val
#define size(x) tree[x].size
	ScapeGoat_Tree() {
		tree[++size]=Tree(0,2,0,2,INT_MIN);
		tree[++size]=Tree(0,0,1,1,INT_MAX);
		root=1;
	}
	bool balance(int x) {return size(x)*alpha>=max(size(ls(x)),size(rs(x)));}
	bool checkson(int x) {return rs(fa(x))==x;}
	void push_up(int x) {size(x)=size(ls(x))+1+size(rs(x));}
	int cnt,a[maxn];
	void dfs(int x) {
		if(ls(x))dfs(ls(x));
		a[++cnt]=x;
		if(rs(x))dfs(rs(x));
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
	void rebuild(int x) {
		cnt=0;
		dfs(x);
		int f=fa(x),side=checkson(x);
		int pos=build(1,cnt);
		tree[f].child[side]=pos;
		fa(pos)=f;
		if(x==root)root=pos;
	}
	void insert(int v) {
		int now=root,fa=0;
		while(now) {
			fa=now;
			size(fa)++;
			now=tree[now].child[val(now)<=v];
		}
		tree[now=++size]=Tree(0,0,fa,1,v);
		if(fa)tree[fa].child[val(fa)<=v]=now;
		int pos=0;
		for(int i=now; i; i=fa(i))if(!balance(i))pos=i;
		if(pos)rebuild(pos);
	}
	void remove(int x) {
		if(ls(x)&&rs(x)) {
			int pre=ls(x);
			while(rs(pre))pre=rs(pre);
			val(x)=val(pre);
			x=pre;
		}
		int son=ls(x)?ls(x):rs(x),side=checkson(x);
		tree[fa(x)].child[side]=son;
		fa(son)=fa(x);
		for(int i=fa(x); i; i=fa(i))size(i)--;
		if(x==root)root=son;
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
			else {ans+=size(ls(now))+1;now=rs(now);}
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
		int now=root,ans=INT_MIN;
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