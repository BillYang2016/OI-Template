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

struct St {
	int u,v;
	St(int x=0,int y=0):u(x),v(y) {}
};

vector<int> edges[maxn],tree[maxn];
stack<St>S;

int n,m,step=0,Lowlink[maxn],Dfn[maxn],BCC=0,New,Square[maxn],Belong[maxn];

void AddEdge(int x,int y) {edges[x].push_back(y);}

void AddEdge2(int x,int y) {tree[x].push_back(y);}

void Tarjan(int Now,int fa) { //构建圆方树
	Lowlink[Now]=Dfn[Now]=++step;
	for(int Next:edges[Now]) {
		if(!Dfn[Next]) {
			S.push(St(Now,Next));
			Tarjan(Next,Now);
			Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
			if(Dfn[Now]<Lowlink[Next])AddEdge2(Now,Next),S.pop();
			else if(Dfn[Now]==Lowlink[Next]) { //构成点双连通分量
				BCC++;
				AddEdge2(Now,++New);
				Square[New]=1;
				while(!S.empty()) {
					int u=S.top().u;S.pop();
					if(u==Now)break;
					Belong[u]=BCC;
					AddEdge2(New,u);
				}
			}
		} else if(Next!=fa&&Lowlink[Now]>Dfn[Next]) {
			Lowlink[Now]=Dfn[Next];
			S.push(St(Now,Next));
		}
	}
}

int main() {
	
	return 0;
}