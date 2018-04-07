#include<bits/stdc++.h>

using namespace std;

const int maxn=110005;

namespace Manacher {
	int n,f[maxn<<1];
	string s;

	int main(string tmp) {
		s.clear();
		s.push_back('#');
		for(auto x:tmp)s.push_back(x),s.push_back('#');
		n=s.length();
		int ans=0,Max=0,id=0;
		for(int i=1; i<=n-2; i++) {
			f[i]=Max>i?min(f[2*id-i],Max-i):1;
			while(i-f[i]>=0&&i+f[i]<n&&s[i-f[i]]==s[i+f[i]])f[i]++;
			if(f[i]+i>Max)Max=f[i]+i,id=i;
			ans=max(ans,f[i]-1);
		}
		return ans;
	}
}

int main() {
	
	return 0;
}