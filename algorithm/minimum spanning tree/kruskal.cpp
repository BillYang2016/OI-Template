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

const int maxn=50005;

struct Edge {
	int x,y,v;
	bool operator < (Edge b) const {
		return v<b.v;
	}
} a[maxn];

struct Kruskal {
	int n,m,ans,cnt;
	int father[maxn];
	void init(int n,int m) {
		this->n=n;
		this->m=m;
		ans=cnt=0;
	}
	void AddEdge(int from,int to,int dist) {
		a[++cnt].x=from;
		a[cnt].y=to;
		a[cnt].v=dist;
	}
	int Get_Father(int x) {
		if(father[x]==x)return x;
		return father[x]=Get_Father(father[x]);
	}
	bool main() {
		int cnt=0;
		sort(a+1,a+m+1);
		for(int i=1; i<=n; i++)father[i]=i;
		for(int i=1; i<=m; i++) {
			int f1=Get_Father(a[i].x),f2=Get_Father(a[i].y);
			if(f1!=f2) {
				father[f1]=f2;
				ans+=a[i].v;
				cnt++;
				if(cnt==n-1)break;
			}
		}
		if(cnt!=n-1)return false;
		return true;
	}
};

int main() {
	
	return 0;
}
