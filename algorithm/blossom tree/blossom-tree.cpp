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

const int maxn=505;

int n,m,father[maxn],vst[maxn],match[maxn],pre[maxn],Type[maxn];
vector<int>edges[maxn];
queue<int>Q;

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

int LCA(int x,int y) {
	static int times=0;
	times++;
	x=father[x],y=father[y]; //circles' position 
	while(vst[x]!=times) {
		if(x) {
			vst[x]=times;
			x=father[pre[match[x]]];
		}
		swap(x,y);
	}
	return x;
}

void blossom(int x,int y,int lca) {
	while(father[x]!=lca) {
		pre[x]=y;
		y=match[x];
		if(Type[y]==1) {
			Type[y]=0;
			Q.push(y);
		}
		father[x]=father[y]=father[lca];
		x=pre[y];
	}
}

int Augument(int s) {
	for(int i=1; i<=n; i++)father[i]=i;
	memset(Type,-1,sizeof(Type));
	Q=queue<int>();
	Type[s]=0;
	Q.push(s); //only type "out" in queue
	while(!Q.empty()) {
		int Now=Q.front();
		Q.pop();
		for(int Next:edges[Now]) {
			if(Type[Next]==-1) {
				pre[Next]=Now;
				Type[Next]=1; //type "in" marked
				if(!match[Next]) {
					for(int to=Next,from=Now; to; from=pre[to]) {
						match[to]=from;
						swap(match[from],to);
					}
					return true;
				}
				Type[match[Next]]=0;
				Q.push(match[Next]);
			} else if(Type[Next]==0&&father[Now]!=father[Next]) {
				int lca=LCA(Now,Next);
				blossom(Now,Next,lca);
				blossom(Next,Now,lca);
			}
		}
	}
	return false;
}

int ans=0;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	for(int i=n; i>=1; i--)
		if(!match[i])ans+=Augument(i);
	printf("%d\n",ans);
	for(int i=1; i<=n; i++)printf("%d ",match[i]);
	return 0;
} 

