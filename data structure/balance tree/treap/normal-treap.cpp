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
mt19937 g(rand());
 
struct Treap {
	struct Tree {
		int child[2],size;
		int d,val;
	} tree[maxn];
	int size,root;
	queue<int> Q;
#define d(x) tree[x].d
#define val(x) tree[x].val
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define size(x) tree[x].size
	void push_up(int x) {size(x)=size(ls(x))+size(rs(x))+1;}
	int newnode(int val) {
		int now;
		if(!Q.empty()) {
			now=Q.front();
			Q.pop();
			ls(now)=rs(now)=0;
		} else now=++size;
		val(now)=val;
		d(now)=g()%maxn;
		size(now)=1;
		return now;
	}
	void rotate(int& x,bool side) {
		int y=tree[x].child[side^1];
		tree[x].child[side^1]=tree[y].child[side];
		tree[y].child[side]=x;
		push_up(x),push_up(y);
		x=y;
	}
	void insert(int& x,int v) {
		if(!x) {x=newnode(v);return;}
		bool side=v>val(x);
		int &y=tree[x].child[side];
		insert(y,v);
		size(x)++;
		if(d(x)<d(y))rotate(x,side^1);
	}
	int cnt,a[maxn];
	void dfs(int x) {
		if(!x)return;
		if(ls(x))dfs(ls(x));
		a[++cnt]=val(x);
		Q.push(x);
		if(rs(x))dfs(rs(x));
	}
	int build(int Left,int Right) {
		if(Left>Right)return 0;
		int mid=(Left+Right)>>1,now=newnode(a[mid]);
		ls(now)=build(Left,mid-1);
		rs(now)=build(mid+1,Right);
		push_up(now);
		return now;
	}
	int rebuild(int x) {
		cnt=0;
		dfs(ls(x));
		dfs(rs(x));
		int pos=build(1,cnt);
		return pos;
	}
	void remove(int val) {
		int now=root,fa;
		bool side;
		while(val(now)!=val) {
			fa=now;
			size(now)--;
			if(val<val(now))now=ls(now),side=0;
			else now=rs(now),side=1;
		}
		int pos=rebuild(now);
		if(now!=root)tree[fa].child[side]=pos;
		else root=pos;
	}
	int rank(int val) {
		int now=root,ans=0;
		while(now) {
			if(val<=val(now))now=ls(now);
			else {ans+=size(ls(now))+1;now=rs(now);}
		}
		return ans+1;
	}
	int kth(int rank) {
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
} treap;

int main() {
	
	return 0;
}