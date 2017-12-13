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
	int from,to,dist;
};

struct HeapNode {
	int d,u;
	bool operator < (HeapNode a) const {
		return d>a.d;
	}
};

struct Prim {
	int n,m,ans,dist[maxn];
	vector<Edge>edges;
	vector<int>G[maxn];
	bool vst[maxn];
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int from,int to,int dist) {
		edges.push_back((Edge) {
			from,to,dist
		});
		m=edges.size();
		G[from].push_back(m-1);
	}
	bool main(int s) {
		int cnt=0;
		for(int i=1; i<=n; i++)dist[i]=INT_MAX;
		priority_queue<HeapNode> Q;
		Q.push((HeapNode) {
			0,s
		});
		dist[s]=0;
		while(!Q.empty()&&cnt<n) {
			HeapNode Now=Q.top();
			Q.pop();
			if(vst[Now.u])continue;
			vst[Now.u]=1;
			ans+=dist[Now.u];
			cnt++;
			for(int i=0; i<G[Now.u].size(); i++) {
				Edge& e=edges[G[Now.u][i]];
				int Next=e.to,v=e.dist;
				if(!vst[Next]&&v<dist[Next]) {
					dist[Next]=v;
					Q.push((HeapNode) {
						dist[Next],Next
					});
				}
			}
		}
		if(cnt==n)return true;
		else return false;
	}
};

int main() {
	
	return 0;
}
