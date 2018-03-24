#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;
typedef complex<double> cp;

const double pi=acos(-1);

struct FastFourierTransform {
	static const int BASE=10000,WIDTH=4;
	int n;
	vector<cp> omega,iomega;
	void init(int n) {
		this->n=n;
		omega.clear();
		iomega.clear();
		for(int i=0; i<n; i++) {
			omega.push_back(cp(cos(2*pi/n*i),sin(2*pi/n*i)));
			iomega.push_back(conj(omega.back()));
		}
	}
	void transform(vector<cp>& a,const vector<cp>& omega) {
		int k=log2(n);
		for(int i=0; i<n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=(1<<(k-j-1));
			if(i<t)swap(a[i],a[t]);
		}
		for(int len=2; len<=n; len<<=1) {
			int mid=len>>1;
			for(int j=0; j<n; j+=len)
				for(int k=j; k<j+mid; k++) {
					complex<double> u=a[k],t=omega[n/len*(k-j)]*a[k+mid];
					a[k]=u+t;
					a[k+mid]=u-t;
				}
		}
	}
	void dft(vector<cp>& a) {
		transform(a,omega);
	}
	void idft(vector<cp>& a) {
		transform(a,iomega);
		for(int i=0; i<n; i++)a[i]/=n;
	}
};

const int BASE=100000000,WIDTH=8,MUL_MAX=2000000; //MUL_MAX根据常数确定开关 
int Pow[(int)log2(BASE)+5];

void accelerate() {
	Pow[0]=1;
	for(int i=1; i<=log2(BASE); i++)Pow[i]=Pow[i-1]*2;
}

struct BigInteger {
	vector<LL> s;
	BigInteger(LL num=0) {*this=num;}
	//赋值
	BigInteger operator = (LL num) {
		s.clear();
		do {
			s.push_back(num%BASE);
			num/=BASE;
		} while(num);
		return *this;
	}
	BigInteger operator = (const string &str) {
		s.clear();
		LL x;
		int len=(str.length()-1)/WIDTH+1;
		for(int i=0; i<len; i++) {
			int end=str.length()-i*WIDTH,start=max(0,end-WIDTH);
			sscanf(str.substr(start,end-start).c_str(),"%lld",&x);
			s.push_back(x);
		}
		return *this;
	}
	//比较
	bool operator < (const BigInteger& b) {
		if(s.size()<b.s.size())return true;
		if(s.size()>b.s.size())return false;
		for(int i=s.size()-1; i>=0; i--) {
			if(s[i]<b.s[i])return true;
			if(s[i]>b.s[i])return false;
		}
		return false;
	}
	bool operator >= (const BigInteger& b) {return !(*this<b);}
	bool operator <= (const BigInteger& b) {return !(*this>b);}
	bool operator == (const BigInteger& b) {
		if(s.size()!=b.s.size())return false;
		for(int i=0; i<s.size(); i++)
			if(s[i]!=b.s[i])return false;
		return true;
	}
	bool operator != (const BigInteger& b) {return !(*this==b);}
	bool operator > (const BigInteger& b) {return ((*this>=b)&&(*this!=b));}
	//+
	BigInteger operator + (BigInteger b) {
		BigInteger c;c.s.clear();
		LL g=0;
		for(int i=0; g||i<s.size()||i<b.s.size(); i++) {
			g+=(i<s.size()?s[i]:0)+(i<b.s.size()?b.s[i]:0);
			c.s.push_back(g%BASE);
			g/=BASE;
		}
		return c;
	}
	void operator += (BigInteger b) {*this=*this+b;}
	BigInteger operator + (const LL &b) {
		BigInteger c=b;
		c+=*this;
		return c;
	}
	void operator += (const LL &b) {*this=*this+b;}
	//-
	BigInteger operator - (BigInteger b) {
		BigInteger a=*this;
		for(int i=0; i<a.s.size(); i++) {
			LL tmp=i<b.s.size()?b.s[i]:0;
			if(a.s[i]<tmp) {a.s[i+1]--;a.s[i]+=BASE;}
			a.s[i]-=tmp;
		}
		while(!a.s.back()&&a.s.size()>1)a.s.pop_back();
		return a;
	}
	void operator -= (BigInteger b) {*this=*this-b;}
	BigInteger operator - (const LL &b) {
		BigInteger a=*this;
		a-=BigInteger(b);
		return a;
	}
	void operator -= (const LL &b) {*this=*this-b;}
	//*
	BigInteger operator * (const LL &b) {
		if(b==0)return 0;
		BigInteger c;c.s.clear();
		for(int i=0; i<s.size(); i++)c.s.push_back(s[i]*b);
		for(int i=0; i<c.s.size()-1; i++)c.s[i+1]+=c.s[i]/BASE,c.s[i]%=BASE;
		while(c.s.back()>=BASE) {LL now=c.s.back();c.s.back()%=BASE;c.s.push_back(now/BASE);}
		return c;
	}
	void operator *= (const LL &b) {*this=*this*b;}
	int base=FastFourierTransform::BASE;
	vector<cp> Copy(const BigInteger& a) { //亿进制转万进制 
		vector<cp>tmp;
		for(vector<LL>::const_iterator it=a.s.begin(); it!=a.s.end(); it++) {
			tmp.push_back(cp(*it%base,0));
			tmp.push_back(cp(*it/base,0));
		}
		return tmp;
	}
	BigInteger Return(const vector<cp>& a,const int n) { //处理进位 
		vector<LL>c(n+1);
		for(int i=0; i<n; i++) {
			c[i]+=round(a[i].real());
			c[i+1]=c[i]/base; //进位 
			c[i]%=base;
		}
		while(!c.empty()&&c.back()>=base) { //处理多出来的 
			LL tmp=c.back();
			c.back()%=base;
			c.push_back(tmp/base);
		}
		while(!c.empty()&&!c.back())c.pop_back();
		BigInteger ans;
		ans.s.clear();
		for(vector<LL>::const_iterator it=c.begin(); it<c.end(); it+=2) { //将万进制转为亿进制 
			int tmp1=*it,tmp2=it+1==c.end()?0:*(it+1);
			ans.s.push_back(tmp1+tmp2*base);
		}
		return ans;
	}
	BigInteger FFT_Multiply(BigInteger a1,BigInteger a2) {
		vector<cp> c1=Copy(a1),c2=Copy(a2);
		int n1=c1.size(),n2=c2.size(),n=1;
		while(n<n1+n2)n<<=1;
		c1.resize(n),c2.resize(n);
		FastFourierTransform fft;
		fft.init(n);
		fft.dft(c1),fft.dft(c2);
		for(int i=0; i<n; i++)c1[i]*=c2[i];
		fft.dft(c1);
		return Return(c1,n);
	}
	BigInteger Multiply(BigInteger a,BigInteger b) {
		BigInteger c;c.s.resize(s.size()+b.s.size());
		for(int i=0; i<s.size(); i++)
			for(int j=0; j<b.s.size(); j++)c.s[i+j]+=s[i]*b.s[j];
		for(int i=0; i<c.s.size()-1; i++)c.s[i+1]+=c.s[i]/BASE,c.s[i]%=BASE;
		while(!c.s.back()&&c.s.size()>1)c.s.pop_back();
		return c;
	}
	BigInteger operator * (const BigInteger& b) {
		if(s.size()*b.s.size()<=MUL_MAX)return Multiply(*this,b); //智能切换开关 
		else return FFT_Multiply(*this,b);
	}
	void operator *= (const BigInteger &b) {*this=*this*b;}
	// /
	BigInteger Divide(BigInteger a,const LL &b,LL &d) { //'/'&'%'
		for(int i=a.s.size()-1; i>=0; i--)d=d*BASE+a.s[i],a.s[i]=d/b,d%=b;
		while(!a.s.back()&&a.s.size()>1)a.s.pop_back();
		return a;
	}
	BigInteger operator / (LL b) {LL d=0;return Divide(*this,b,d);}
	void operator /= (const LL &b) {*this=*this/b;}
	BigInteger Copy(const BigInteger& b,int x) {
		BigInteger t;
		t.s.resize(b.s.size()+x);
		for(int i=0; i<b.s.size(); i++)t.s[i+x]=b.s[i];
		return t;
	}
	BigInteger Divide(const BigInteger& a,const BigInteger& b,BigInteger& mod) { //'/'&'%'
		if(a.s.size()<b.s.size()) {mod=a;return 0;}
		BigInteger c;c.s.resize(a.s.size()-b.s.size()+1);
		mod=a;
		for(int i=c.s.size()-1; i>=0; i--) {
			BigInteger t;
			t=Copy(b,i);
			if(!Pow[0])while(mod>=t)c.s[i]++,mod-=t;
			else for(int j=log2(BASE); j>=0; j--)if(mod>=t*Pow[j])c.s[i]+=Pow[j],mod-=t*Pow[j];
		}
		while(!c.s.back()&&c.s.size()>1)c.s.pop_back();
		return c;
	}
	BigInteger operator / (const BigInteger& b) {BigInteger d;return Divide(*this,b,d);}
	void operator /= (const BigInteger& b) {*this=*this/b;}
	//%
	BigInteger operator % (const BigInteger& b) {BigInteger d;Divide(*this,b,d);return d;}
	void operator %= (const BigInteger& b) {*this=*this%b;}
	LL operator % (const LL &b) {LL d=0;Divide(*this,b,d);return d;}
	void operator %= (const LL &b) {*this=*this%b;}
	//±
	BigInteger operator + () {
		return *this;
	}
	BigInteger operator - () {
		BigInteger a=*this;
		return a;
	}
	BigInteger operator ++ () {
		*this+=1;
		return *this;
	}
	const BigInteger operator ++ (int) {
		BigInteger tmp=*this;
		*this=*this+1;
		return tmp;
	}
	BigInteger operator -- () {
		*this-=1;
		return *this;
	}
	const BigInteger operator -- (int) {
		BigInteger tmp=*this;
		*this=*this-1;
		return tmp;
	}
	friend istream& operator >> (istream& input,BigInteger& x) {
		string s;
		if(!(input>>s))return input;
		x=s;
		return input;
	}
	friend ostream& operator << (ostream& output,const BigInteger& x) {
		output<<x.s.back();
		for(int i=x.s.size()-2; i>=0; i--) {
			char buf[20];
			sprintf(buf,"%08lld",x.s[i]);
			for(int j=0; j<strlen(buf); j++)output<<buf[j];
		}
		return output;
	}
};

int main() {
	
	return 0;
}