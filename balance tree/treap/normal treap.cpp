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
mt19937 g(rand());
 
struct Tree {
	int child[2];
	int d,val;
	int size;
};
 
struct Treap {
	Tree tree[maxn];
	int size,root;
	queue<int>Q;
#define d(x) tree[x].d
#define val(x) tree[x].val
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define root(x) tree[x].root
#define size(x) tree[x].size
	void push_up(int index) {
		int ls=ls(index),rs=rs(index);
		size(index)=size(ls)+size(rs)+1;
	}
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
	void rotate(int& index,bool side) {
		int son=tree[index].child[side^1];
		tree[index].child[side^1]=tree[son].child[side];
		tree[son].child[side]=index;
		push_up(index);
		push_up(son);
		index=son;
	}
	void insert(int& index,int val) {
		if(!index) {
			index=newnode(val);
			return;
		}
		bool side=val>val(index);
		int &son=tree[index].child[side];
		insert(son,val);
		size(index)++;
		if(d(index)<d(son))rotate(index,side^1);
	}
	int cnt,a[maxn];
	void dfs(int index) {
		if(!index)return;
		if(ls(index))dfs(ls(index));
		a[++cnt]=val(index);
		Q.push(index);
		if(rs(index))dfs(rs(index));
	}
	int build(int Left,int Right) {
		if(Left>Right)return 0;
		int mid=(Left+Right)>>1,now=newnode(a[mid]);
		ls(now)=build(Left,mid-1);
		rs(now)=build(mid+1,Right);
		push_up(now);
		return now;
	}
	int rebuild(int index) {
		cnt=0;
		dfs(ls(index));
		dfs(rs(index));
		int pos=build(1,cnt);
		return pos;
	}
	void remove(int val) {
		int now=root,father;
		bool side;
		while(val(now)!=val) {
			father=now;
			size(now)--;
			if(val<val(now))now=ls(now),side=0;
			else now=rs(now),side=1;
		}
		int pos=rebuild(now);
		if(now!=root)tree[father].child[side]=pos;
		else root=pos;
	}
	int rank(int val) {
		int now=root,ans=0;
		while(now) {
			if(val<=val(now))now=ls(now);
			else {
				ans+=size(ls(now))+1;
				now=rs(now);
			}
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
} treap;

int main() {
	
	return 0;
} 
