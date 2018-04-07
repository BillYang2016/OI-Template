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
	int ls,rs;
	int& operator [] (int x) {return d[x];}
	bool operator < (const Point& b) const {return d[D]<b.d[D];}
} p[maxn];

LL ans=0; //remember sqrt

struct KD_Tree {
#define lson p[index].ls
#define rson p[index].rs
	void push_up(int index) {
		for(int i=0; i<K; i++) {
			p[index].Min[i]=p[index].Max[i]=p[index][i];
			if(lson) {
				p[index].Min[i]=min(p[index].Min[i],p[lson].Min[i]);
				p[index].Max[i]=max(p[index].Max[i],p[lson].Max[i]);
			}
			if(rson) {
				p[index].Min[i]=min(p[index].Min[i],p[rson].Min[i]);
				p[index].Max[i]=max(p[index].Max[i],p[rson].Max[i]);
			}
		}
	}
	int build(int Left,int Right,int now) {
		int mid=(Left+Right)>>1,root=mid;
		D=now;
		nth_element(p+Left,p+mid,p+Right+1);
		if(Left<mid)p[root].ls=build(Left,mid-1,(now+1)%K);
		if(Right>mid)p[root].rs=build(mid+1,Right,(now+1)%K);
		push_up(root);
		return root;
	}
	LL sqr(LL x) {return x*x;}
	LL get_min(int index,Point P) {
		if(!index)return LLONG_MAX/2;
		LL ans=0;
		for(int i=0; i<K; i++) {
			if(p[index].Min[i]-P[i]>0)ans+=sqr(p[index].Min[i]-P[i]);
			if(P[i]-p[index].Max[i]>0)ans+=sqr(P[i]-p[index].Max[i]);
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
		LL ldist=get_min(lson,P),rdist=get_min(rson,P);
		if(ldist<rdist) {
			if(ldist<ans)find_min(lson,P,(now+1)%K);
			if(rdist<ans&&P[now]+ans>=p[index][now])find_min(rson,P,(now+1)%K);
		} else {
			if(rdist<ans)find_min(rson,P,(now+1)%K);
			if(ldist<ans&&P[now]-ans<=p[index][now])find_min(lson,P,(now+1)%K);
		}
	}
};

int main() {
	
	return 0;
}