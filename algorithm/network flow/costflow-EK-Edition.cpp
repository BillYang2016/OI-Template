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

const int maxn=405;

struct Edge {
	int from,to,cap,flow,cost;
	Edge(int x=0,int y=0,int c=0,int f=0,int co=0):from(x),to(y),cap(c),flow(f),cost(co) {}
};

struct MinimumCost_MaximumFlow { //EK Edition
	int n,m;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool inque[maxn];
	int a[maxn],dist[maxn],path[maxn];
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,int v,int f) {
		edges.push_back(Edge(x,y,v,0,f));
		edges.push_back(Edge(y,x,0,0,-f));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool bellmanford(int s,int t,int& flow,int& cost) {
		for(int i=1; i<=n; i++)dist[i]=INT_MAX;
		queue<int> Q;
		Q.push(s);
		dist[s]=path[s]=0;
		a[s]=INT_MAX;
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			inque[Now]=0;
			for(int id:G[Now]) {
				Edge& e=edges[id];
				int Next=e.to;
				if(e.cap>e.flow&&dist[Next]>dist[Now]+e.cost) {
					dist[Next]=dist[Now]+e.cost;
					path[Next]=id;
					a[Next]=min(a[Now],e.cap-e.flow);
					if(!inque[Next]) {
						Q.push(Next);
						inque[Next]=1;
					}
				}
			}
		}
		if(dist[t]==INT_MAX)return false;
		flow+=a[t];
		cost+=dist[t]*a[t];
		for(int Now=t; Now!=s; Now=edges[path[Now]].from) {
			edges[path[Now]].flow+=a[t];
			edges[path[Now]^1].flow-=a[t];
		}
		return true;
	}
	int maxflow(int s,int t,int& cost) {
		int flow=0;
		cost=0;
		while(bellmanford(s,t,flow,cost));
		return flow;
	}
} mcmf;

int n,m;

int main() {
	n=Get_Int();
	m=Get_Int();
	mcmf.init(n);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int(),f=Get_Int();
		mcmf.AddEdge(x,y,v,f);
	}
	int flow=0,cost=0;
	flow=mcmf.maxflow(1,n,cost);
	printf("%d %d\n",flow,cost);
	return 0;
}
