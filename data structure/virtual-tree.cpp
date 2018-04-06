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

void build(vector<int> &a) {
	int tmp=a.size();
	for(int i=0; i<tmp-1; i++)a.push_back(LCA(a[i],a[i+1]));
	sort(a.begin(),a.end(),cmp);
	auto it=unique(a.begin(),a.end());
	a.erase(it,a.end());
	static int top=0,S[maxn];
	root=S[++top]=a[0];
	for(int i=1; i<a.size(); i++) {
		int now=a[i];
		while(top>=1) {
			if(First[now]>=First[S[top]]&&First[now]<=Last[S[top]]) {
				AddTreeEdge(S[top],now);
				break;
			}
			top--;
		}
		if(S[top]!=now)S[++top]=now;
	}
}

int main() {
	
	return 0;
}
