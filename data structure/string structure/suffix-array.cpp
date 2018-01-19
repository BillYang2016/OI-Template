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

const int maxn=200005;

int sa[maxn],Rank[maxn],First[maxn],Second[maxn],Bucket[maxn],tmp[maxn],Height[maxn];

void Suffix_Array(int n,int* a) {
	//calculate single alpha rank 
	fill(Bucket,Bucket+n+1,0);
	for(int i=1; i<=n; i++)Bucket[a[i]]++;
	for(int i=1; i<=n; i++)Bucket[i]+=Bucket[i-1]; 
	for(int i=1; i<=n; i++)Rank[i]=Bucket[a[i]-1]+1;
	for(int t=1; t<=n; t*=2) { 
		for(int i=1; i<=n; i++) {
			First[i]=Rank[i]; //first key 
			Second[i]=(i+t)>n?0:Rank[i+t]; //second key 
		}
		fill(Bucket,Bucket+n+1,0);
		for(int i=1; i<=n; i++)Bucket[Second[i]]++; //second key 
		for(int i=1; i<=n; i++)Bucket[i]+=Bucket[i-1];
		for(int i=1; i<=n; i++)tmp[n-(--Bucket[Second[i]])]=i; //tmp[i] record ith second key's position
		fill(Bucket,Bucket+n+1,0);
		for(int i=1; i<=n; i++)Bucket[First[i]]++; //first key 
		for(int i=1; i<=n; i++)Bucket[i]+=Bucket[i-1];
		for(int i=1; i<=n; i++)sa[Bucket[First[tmp[i]]]--]=tmp[i];
		bool unique=true;
		for(int j=1,last=0; j<=n; j++) {
			int i=sa[j];
			if(!last)Rank[i]=1;
			else if(First[i]==First[last]&&Second[i]==Second[last])Rank[i]=Rank[last],unique=false;
			else Rank[i]=Rank[last]+1; 
			last=i;
		}
		if(unique)break; //already unique 
	}
	int k=0;
	for(int i=1; i<=n; i++) {
		if(Rank[i]==1)k=0;
		else {
			if(k>0)k--; //LCP-1
			int j=sa[Rank[i]-1]; //last one 
			while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++; //enlarge 
		}
		Height[Rank[i]]=k;
	}
}

int main() {

	return 0;
}
