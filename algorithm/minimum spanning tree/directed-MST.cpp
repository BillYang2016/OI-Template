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

const int maxn=105;
 
struct Edge {
	int from,to;
	double dist;
	Edge(int x=0,int y=0,double v=0):from(x),to(y),dist(v) {}
};
 
double Directed_MST(int n,vector<Edge> &edges,int root) {
	double ans=0;
	static double in[maxn];
	static int id[maxn],pre[maxn],vst[maxn];
	while(true) {
		//找最小入边
		for(int i=1; i<=n; i++)in[i]=1e18;
		for(Edge &e:edges) {
			int x=e.from,y=e.to;
			if(x==y)continue;
			if(e.dist<in[y])pre[y]=x,in[y]=e.dist;
		}
		for(int i=1; i<=n; i++)if(i!=root&&in[i]==1e18)return -1; //无解
		//找环
		memset(id,0,sizeof(id));
		memset(vst,0,sizeof(vst));
		int cnt=0;
		in[root]=0;
		for(int i=1; i<=n; i++) {
			ans+=in[i];
			int now;
			for(now=i; vst[now]!=i&&!id[now]&&now!=root; now=pre[now])vst[now]=i; //找环
			if(now!=root&&!id[now]) { //缩点
				id[now]=++cnt;
				for(int p=pre[now]; p!=now; p=pre[p])id[p]=cnt;
			}
		}
		if(cnt==0)break; //无环
		for(int i=1; i<=n; i++)if(!id[i])id[i]=++cnt;
		for(Edge &e:edges) {
			int &x=e.from,&y=e.to;
			if(x!=y)e.dist-=in[y];
			x=id[x],y=id[y];
		}
		n=cnt;
		root=id[root];
	}
	return ans;
}

int main() {

	return 0;
}

