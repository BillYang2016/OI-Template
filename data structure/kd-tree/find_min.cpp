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

int D;

struct Point {
	int d[K],Min[K],Max[K];
	int l,r;
	int& operator [] (int x) {return d[x];}
	bool operator < (const Point& b) const {return d[D]<b.d[D];}
} p[maxn];

LL ans=0; //remember sqrt

struct KD_Tree {
#define ls p[index].l
#define rs p[index].r
#define Min(i) p[index].Min[i]
#define Max(i) p[index].Max[i]
	void push_up(int index) {
		for(int i=0; i<K; i++) {
			Min(i)=Max(i)=p[index][i];
			if(ls)Min(i)=min(Min(i),p[ls].Min[i]),Max(i)=max(Max(i),p[ls].Max[i]);
			if(rs)Min(i)=min(Min(i),p[rs].Min[i]),Max(i)=max(Max(i),p[rs].Max[i]);
		}
	}
	int build(int Left,int Right,int now) {
		int mid=(Left+Right)>>1,root=mid;
		D=now;
		nth_element(p+Left,p+mid,p+Right+1);
		if(Left<mid)p[root].l=build(Left,mid-1,(now+1)%K);
		if(Right>mid)p[root].r=build(mid+1,Right,(now+1)%K);
		push_up(root);
		return root;
	}
	LL sqr(LL x) {return x*x;}
	LL get_min(int index,Point P) {
		if(!index)return LLONG_MAX/2;
		LL ans=0;
		for(int i=0; i<K; i++) {
			if(Min(i)-P[i]>0)ans+=sqr(Min(i)-P[i]);
			if(P[i]-Max(i)>0)ans+=sqr(P[i]-Max(i));
		}
		return ans;
	}
	LL dist(Point a,Point b) { 
		LL ans=0;
		for(int i=0; i<K; i++)ans+=sqr(a[i]-b[i]);
		return ans;
	}
	void find_min(int index,Point P,int now) {
		if(!index)return;
		LL Dist=dist(p[index],P);
		ans=min(ans,Dist);
		LL ldist=get_min(ls,P),rdist=get_min(rs,P);
		if(ldist<rdist) {
			if(ldist<ans)find_min(ls,P,(now+1)%K);
			if(rdist<ans&&P[now]+ans>=p[index][now])find_min(rs,P,(now+1)%K);
		} else {
			if(rdist<ans)find_min(rs,P,(now+1)%K);
			if(ldist<ans&&P[now]-ans<=p[index][now])find_min(ls,P,(now+1)%K);
		}
	}
};

int main() {
	
	return 0;
}