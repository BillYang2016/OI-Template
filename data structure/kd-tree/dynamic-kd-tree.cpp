#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=50005,K=2;
const double alpha=0.78;

struct Point {
	int d[K],Min[K],Max[K];
	int l,r,size;
	Point() {l=r=size=0;}
	int& operator [] (int x) {return d[x];}
} p[maxn];

int D,n,root,cnt=0,dfn[maxn];

bool cmp(int x,int y) {return p[x][D]<p[y][D];}

struct KD_Tree {
#define ls p[index].l
#define rs p[index].r
#define Min(i) p[index].Min[i]
#define Max(i) p[index].Max[i]
	bool balance(int index) {return p[index].size*alpha>=max(p[ls].size,p[rs].size);}
	void push_up(int index) {
		for(int i=0; i<K; i++) {
			Min(i)=Max(i)=p[index][i];
			if(ls)Min(i)=min(Min(i),p[ls].Min[i]),Max(i)=max(Max(i),p[ls].Max[i]);
			if(rs)Min(i)=min(Min(i),p[rs].Min[i]),Max(i)=max(Max(i),p[rs].Max[i]);
		}
		p[index].size=p[ls].size+p[rs].size+1;
	}
	int build(int Left,int Right,int now) {
		int mid=(Left+Right)>>1;
		D=now;
		nth_element(dfn+Left,dfn+mid,dfn+Right+1,cmp);
		int root=dfn[mid];
		if(Left<mid)p[root].l=build(Left,mid-1,(now+1)%K);
		if(Right>mid)p[root].r=build(mid+1,Right,(now+1)%K);
		push_up(root);
		return root;
	}
	void dfs(int &index) {
		if(ls)dfs(ls);
		dfn[++cnt]=index;
		if(rs)dfs(rs);
		index=0;
	}
	void rebuild(int &index,int now) {
		cnt=0;
		dfs(index);
		index=build(1,cnt,now);
	}
	int tmp,prt,son,pnow;
	int insert(int index,Point P,int now) {
		if(!index) {p[++n]=P;push_up(n);return n;}
		if(P[now]<p[index][now])ls=insert(ls,P,(now+1)%K);
		else rs=insert(rs,P,(now+1)%K);
		push_up(index);
		if(!balance(index))tmp=index;
		else if(tmp)prt=index,son=tmp,pnow=(now+1)%K,tmp=0;
		return index;
	}
	void insert(Point P) {
		tmp=prt=son=0;
		root=insert(root,P,0);
		if(tmp)rebuild(root,0);
		else if(son) {
			if(p[prt].l==son)rebuild(p[prt].l,pnow);
			else rebuild(p[prt].r,pnow);
		}
	}
	LL sqr(LL x) {return x*x;}
	LL dist(int index,Point P) {
		LL ans=0;
		for(int i=0; i<K; i++)ans+=sqr(p[index][i]-P[i]);
		return ans;
	}
	LL get_max(int index,Point P) { 
		if(!index)return 0;
		LL ans=0;
		for(int i=0; i<K; i++)ans+=max(sqr(Max(i)-P[i]),sqr(Min(i)-P[i]));
		return ans;
	}
	LL get_min(int index,Point P) {
		if(!index)return LLONG_MAX/2;
		LL ans=0;
		for(int i=0; i<K; i++) {
			if(Min(i)-P[i]>0)ans+=sqr(Min(i)-P[i]);
			if(P[i]-Max(i)>0)ans+=sqr(P[i]-Max(i));
		}
		return ans;
	}
};

int main() {
	
	return 0;
}