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
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=200005;

namespace Suffix_Array {
	int sa[maxn],rk[maxn],fir[maxn],sec[maxn],buc[maxn],tmp[maxn],height[maxn];

	void fill_buc(int n,int *a) {
		fill(buc,buc+n+1,0);
		for(int i=1; i<=n; i++)buc[a[i]]++;
		for(int i=1; i<=n; i++)buc[i]+=buc[i-1];
	}

	void build(int n,int *a) {
		fill_buc(n,a);
		for(int i=1; i<=n; i++)rk[i]=buc[a[i]-1]+1; //calculate single alpha rank
		for(int t=1; t<=n; t<<=1) {
			for(int i=1; i<=n; i++) {
				fir[i]=rk[i]; //first key
				sec[i]=(i+t)>n?0:rk[i+t]; //second key
			}
			fill_buc(n,sec); //second key
			for(int i=1; i<=n; i++)tmp[n-(--buc[sec[i]])]=i; //tmp[i] record ith second key's position
			fill_buc(n,fir); //first key
			for(int i=1; i<=n; i++)sa[buc[fir[tmp[i]]]--]=tmp[i];
			bool unique=1;
			for(int j=1,last=0; j<=n; j++) {
				int i=sa[j];
				if(!last)rk[i]=1;
				else if(fir[i]==fir[last]&&sec[i]==sec[last])rk[i]=rk[last],unique=0;
				else rk[i]=rk[last]+1;
				last=i;
			}
			if(unique)break; //already unique
		}
		int k=0;
		for(int i=1; i<=n; i++) {
			if(rk[i]==1)k=0;
			else {
				if(k>0)k--; //LCP-1
				int j=sa[rk[i]-1]; //last one
				while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++; //enlarge
			}
			height[rk[i]]=k;
		}
	}

	void discretization(int n,int *a,int *b) {
		copy(a+1,a+n+1,b+1);
		sort(a+1,a+n+1);
		int tot=unique(a+1,a+n+1)-a-1;
		for(int i=1; i<=n; i++)b[i]=lower_bound(a+1,a+tot+1,b[i])-a;
	}
}

using namespace Suffix_Array;

int main() {
	
	return 0;
}