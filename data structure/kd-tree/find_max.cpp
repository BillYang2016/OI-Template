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
	LL get_max(int index,Point P) { 
		if(!index)return 0;
		LL ans=0;
		for(int i=0; i<K; i++)ans+=max(sqr(p[index].Max[i]-P[i]),sqr(p[index].Min[i]-P[i]));
		return ans;
	}
	LL dist(Point a,Point b) { 
		LL ans=0;
		for(int i=0; i<K; i++)ans+=sqr(a[i]-b[i]);
		return ans;
	}
	void find_max(int index,Point P) {
		if(!index)return;
		LL Dist=dist(p[index],P);
		ans=max(ans,Dist);
		LL ldist=get_max(lson,P),rdist=get_max(rson,P);
		if(ldist>rdist) {
			if(ldist>ans)find_max(lson,P);
			if(rdist>ans)find_max(rson,P);
		} else {
			if(rdist>ans)find_max(rson,P);
			if(ldist>ans)find_max(lson,P);
		}
	}
};

int main() {
	
	return 0;
}