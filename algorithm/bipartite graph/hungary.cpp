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

const int maxn=4005;

int n,m,My[maxn];
bool vst[maxn];
vector<int>edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

bool Dfs(int Now) {
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		vst[Next]=1;
		if(My[Next]==0||Dfs(My[Next])) { //Augmentable
			My[Next]=Now;
			return true;
		}
	}
	return false;
}

int Hungary() {
	memset(My,0,sizeof(My));
	int ans=0;
	for(int i=1; i<=n; i++) {
		memset(vst,0,sizeof(vst));
		if(Dfs(i))ans++;
	}
	return ans;
}

int main() {
	
	return 0;
}
