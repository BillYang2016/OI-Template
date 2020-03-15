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

struct Edge {
	int from,to,dist;
	Edge(int x=0,int y=0,int v=0):from(x),to(y),dist(v) {}
};

struct St {
	int u,v,dist;
	St(int x=0,int y=0,int va=0):u(x),v(y),dist(va) {}
};

vector<Edge> edges[maxn],tree[maxn];
vector<int> Circle[maxn];
stack<St> S;

int step=0,Lowlink[maxn],Dfn[maxn],BCC=0,New,Length[maxn],f[maxn],Belong[maxn],vst[maxn],Square[maxn];

void AddEdge(int x,int y,int v) {edges[x].push_back(Edge(x,y,v));}

void AddEdge2(int x,int y,int v) {tree[x].push_back(Edge(x,y,v));}

void Tarjan(int Now,int fa) {
	step++;
	Lowlink[Now]=Dfn[Now]=step;
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(!Dfn[Next]) {
			S.push(St(Now,Next,e.dist));
			Tarjan(Next,Now);
			Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
			if(Dfn[Now]<Lowlink[Next])AddEdge2(Now,Next,e.dist),S.pop();
			else if(Dfn[Now]==Lowlink[Next]) { //构成点双连通分量
				BCC++;
				AddEdge2(Now,++New,0);
				Square[New]=1;
				while(!S.empty()) {
					int u=S.top().u,v=S.top().v,dist=S.top().dist;S.pop();
					Length[BCC]+=dist;
					f[u]=f[v]+dist;
					if(u!=Now)Belong[u]=BCC,Circle[New].push_back(u);
					if(u==Now&&v==Next)break;
				}
				for(int Next:Circle[New])AddEdge2(New,Next,min(abs(f[Next]-f[Now]),Length[BCC]-abs(f[Next]-f[Now])));
			}
		} else if(Next!=fa&&Lowlink[Now]>Dfn[Next]) {
			Lowlink[Now]=Dfn[Next];
			S.push(St(Now,Next,e.dist));
		}
	}
}

int main() {
	
	return 0;
}