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

typedef long long LL;

const int maxn=20005,MAX_BASE=60;

struct Linear_Bases {
	LL b[MAX_BASE+5];
	Linear_Bases() {
		fill(b,b+MAX_BASE+1,0);
	}
	void add(LL num) {
		for(int j=MAX_BASE; j>=0; j--)
			if(num>>j&1) {
				if(b[j]) { //already had bases
					num^=b[j];
					continue;
				}
				b[j]=num;
				for(int k=j-1; k>=0; k--)if(b[j]>>k&1)b[j]^=b[k];
				for(int k=j+1; k<=MAX_BASE; k++)if(b[k]>>j&1)b[k]^=b[j];
				break;
			}
	}
	void build(vector<int>a) {
		for(int num:a)add(num);
	}
	void merge(const Linear_Bases& b) {
		for(int i=0; i<=MAX_BASE; i++)
			if(b.b[i])add(b.b[i]);
	}
	LL cal() { //max xor-sum
		LL ans=0;
		for(int i=0; i<=MAX_BASE; i++)ans^=b[i];
		return ans;
	}
};

int main() {

	return 0;
}
