#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<complex>
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

typedef long long LL;
typedef complex<double> cp;

const double pi=acos(-1);

struct FastFourierTransform {
	static const int BASE=10000,WIDTH=4;
	int n;
	vector<cp>omega,iomega;
	void init(int n) {
		this->n=n;
		omega.clear();
		iomega.clear();
		for(int i=0; i<n; i++) {
			omega.push_back(cp(cos(2*pi/n*i),sin(2*pi/n*i)));
			iomega.push_back(conj(omega.back())); //共轭函数取倒
		}
	}
	void transform(vector<cp>& a,const vector<cp>& omega) {
		int k=log2(n);
		for(int i=0; i<n; i++) { //二进制位翻转
			int t=0;
			for(int j=0; j<k; j++)
				if(i&(1<<j))t|=(1<<(k-j-1));
			if(i<t)swap(a[i],a[t]);
		}
		for(int len=2; len<=n; len<<=1) { //蝴蝶操作
			int mid=len>>1;
			for(int j=0; j<n; j+=len)
				for(int k=j; k<j+mid; k++) {
					complex<double>u=a[k];
					complex<double>t=omega[n/len*(k-j)]*a[k+mid];
					a[k]=u+t;
					a[k+mid]=u-t;
				}
		}
	}
	void Dft(vector<cp>& a) {
		transform(a,omega);
	}
	void iDft(vector<cp>& a) {
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
	vector<LL>s;
	int bj; //负数
	BigInteger() { //构造函数：初始赋0
		*this=0;
		bj=0;
	}
	BigInteger(const LL& num) { // 构造函数
		*this=num;
		bj=num>0?1:-1;
		if(num==0)bj=0;
	}
	//内部函数
	BigInteger abs(const BigInteger& b) {
		BigInteger a=b;
		if(a.bj==-1)a.bj=1;
		return a;
	}
	void swap(BigInteger& a,BigInteger& b) {
		BigInteger t=a;
		a=b;
		b=t;
	}
	//赋值
	BigInteger operator = (LL num) {
		s.clear();
		bj=1;
		if(num==0)bj=0;
		else if(num<0) {
			num=std::abs(num);
			bj=-1;
		}
		do {
			s.push_back(num%BASE);
			num/=BASE;
		} while(num>0);
		return *this;
	}
	BigInteger operator = (const string& str) {
		s.clear();
		LL x;
		int len=(str.length()-1)/WIDTH+1;
		for(int i=0; i<len; i++) {
			int end=str.length()-i*WIDTH;
			int start=max(0,end-WIDTH);
			sscanf(str.substr(start,end-start).c_str(),"%lld",&x);
			s.push_back(x);
		}
		if(s.size()==1&&s[0]==0)bj=0;
		return *this;
	}
	//比较
	bool operator < (const BigInteger& b) {
		if(bj<b.bj)return true;
		if(bj>b.bj)return false;
		if(bj+b.bj==-2)return abs(*this)>abs(b);
		if(s.size()<b.s.size())return true;
		if(s.size()>b.s.size())return false;
		for(int i=s.size()-1; i>=0; i--) {
			if(s[i]<b.s[i])return true;
			if(s[i]>b.s[i])return false;
		}
		return false;
	}
	bool operator >= (const BigInteger& b) {
		return !(*this<b);
	}
	bool operator <= (const BigInteger& b) {
		return !(*this>b);
	}
	bool operator == (const BigInteger& b) {
		if(bj!=b.bj)return false;
		if(s.size()!=b.s.size())return false;
		for(int i=0; i<s.size(); i++)
			if(s[i]!=b.s[i])return false;
		return true;
	}
	bool operator != (const BigInteger& b) {
		return !(*this==b);
	}
	bool operator > (const BigInteger& b) {
		return ((*this>=b)&&(*this!=b));
	}
	//+
	BigInteger operator + (BigInteger b) {
		if(bj==-1)return b-abs(*this);
		if(b.bj==-1)return *this-abs(b);
		BigInteger c;
		c.bj=1;
		if(bj==-1&&b.bj==-1)c.bj=-1;
		else if(bj==0)c.bj=b.bj;
		else if(b.bj==0)c.bj=bj;
		c.s.clear();
		LL g=0;
		for(int i=0; ; i++) {
			if(g==0&&i>=s.size()&&i>=b.s.size())break;
			LL x=g;
			if(i<s.size())x+=s[i];
			if(i<b.s.size())x+=b.s[i];
			c.s.push_back(x%BASE);
			g=x/BASE;
		}
		return c;
	}
	void operator += (BigInteger b) {
		*this=*this+b;
	}
	BigInteger operator + (const LL& b) {
		BigInteger c;
		if(b==0)return *this;
		if(b<0)return *this-abs(b);
		if(bj==0)return BigInteger(b);
		if(bj<0)return BigInteger(b)-abs(*this);
		c=b;
		c+=*this;
		return c;
	}
	void operator += (const LL& b) {
		*this=*this+b;
	}
	//-
	BigInteger operator - (BigInteger b) {
		if(bj==-1)return -(abs(*this)+b);
		if(b.bj==-1)return *this+abs(b);
		BigInteger c;
		c=*this;
		if(c==b) {
			c=0;
			return c;
		} else if(c<b) {
			BigInteger tmp=b-c;
			tmp.bj*=-1;
			return tmp;
		}
		for(int i=0; i<c.s.size(); i++) {
			LL tmp;
			if(i>=b.s.size())tmp=0;
			else tmp=b.s[i];
			if(c.s[i]<tmp) {
				c.s[i+1]-=1;
				c.s[i]+=BASE;
			}
			c.s[i]-=tmp;
		}
		while(c.s.back()==0&&c.s.size()>1)c.s.pop_back();
		return c;
	}
	void operator -= (BigInteger b) {
		*this=*this-b;
	}
	BigInteger operator - (const LL& b) {
		if(b==0)return *this;
		if(b<0)return *this+abs(b);
		if(bj==0)return -b;
		if(bj<0)return -(abs(*this)+b);
		BigInteger c,d=*this;
		c=b;
		d-=c;
		return d;
	}
	void operator -= (const LL& b) {
		*this=*this-b;
	}
	//*
	BigInteger operator * (LL b) {
		BigInteger c;
		c.bj=bj;
		if(b==0) {
			c=0;
			return c;
		} else if(b<0) {
			b=std::abs(b);
			c.bj=-bj;
		}
		c.s.clear();
		for(int i=0; i<s.size(); i++)c.s.push_back(s[i]*b);
		for(int i=0; i<c.s.size()-1; i++) {
			c.s[i+1]+=c.s[i]/BASE;
			c.s[i]%=BASE;
		}
		while(c.s.back()>=BASE) {
			LL now=c.s.back();
			c.s.back()%=BASE;
			c.s.push_back(now/BASE);
		}
		return c;
	}
	void operator *= (LL b) {
		*this=*this*b;
	}
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
		vector<cp>c1=Copy(a1),c2=Copy(a2);
		int n1=c1.size(),n2=c2.size(),n=1;
		while(n<n1+n2)n<<=1;
		c1.resize(n),c2.resize(n);
		FastFourierTransform fft;
		fft.init(n);
		fft.Dft(c1);
		fft.Dft(c2);
		for(int i=0; i<n; i++)c1[i]*=c2[i];
		fft.iDft(c1);
		BigInteger ans=Return(c1,n);
		ans.bj=a1.bj*a2.bj;
		return ans;
	}
	BigInteger Multiply(BigInteger a,BigInteger b) {
		BigInteger c;
		c.bj=bj*b.bj;
		c.s.resize(a.s.size()+b.s.size());
		for(int i=0; i<a.s.size(); i++)
			for(int j=0; j<b.s.size(); j++)c.s[i+j]+=a.s[i]*b.s[j];
		for(int i=0; i<c.s.size()-1; i++) {
			c.s[i+1]+=c.s[i]/BASE;
			c.s[i]%=BASE;
		}
		while(c.s.back()==0&&c.s.size()>1)c.s.pop_back();
		return c;
	}
	BigInteger operator * (const BigInteger& b) {
		if(s.size()*b.s.size()<=MUL_MAX)return Multiply(*this,b); //智能切换开关 
		else return FFT_Multiply(*this,b);
	}
	void operator *= (const BigInteger& b) {
		*this=*this*b;
	}
	// /
	BigInteger operator / (LL k) {
		LL d=0;
		BigInteger c;
		c=*this;
		if(k==0)throw exception();
		if(k<0) {
			k=std::abs(k);
			c.bj=-1*c.bj;
		}
		for(int i=c.s.size()-1; i>=0; i--) {
			d=d*BASE+c.s[i];
			c.s[i]=d/k;
			d%=k;
		}
		while(c.s.back()==0&&c.s.size()>1)c.s.pop_back();
		return c;
	}
	void operator /= (LL k) {
		*this=*this/k;
	}
	BigInteger Copy(const BigInteger& b,int x) {
		BigInteger t;
		t.bj=b.bj;
		t.s.resize(b.s.size()+x);
		for(int i=0; i<b.s.size(); i++)t.s[i+x]=b.s[i];
		return t;
	}
	BigInteger Divide(const BigInteger& a,const BigInteger& b,BigInteger& mod) { //'/'&'%'
		if(a.s.size()<b.s.size()) {
			mod=a;
			return BigInteger(0);
		}
		BigInteger c;
		c.s.resize(a.s.size()-b.s.size()+1);
		if(b.bj==0)throw exception();
		c.bj=a.bj*b.bj;
		mod=abs(a);
		BigInteger b0=abs(b);
		for(int i=c.s.size()-1; i>=0; i--) {
			BigInteger t;
			t=Copy(b0,i);
			if(!Pow[0]) {
				while(mod>=t) {
					(c.s[i])++;
					mod-=t;
				}
			} else {
				for(int j=log2(BASE); j>=0; j--)
					if(mod>=t*Pow[j]) {
						c.s[i]+=Pow[j];
						mod-=t*Pow[j];
					}
			}
		}
		while(c.s.back()==0&&c.s.size()>1)c.s.pop_back();
		return c;
	}
	BigInteger operator / (const BigInteger& b) {
		BigInteger c,d;
		c=Divide(*this,b,d);
		return c;
	}
	void operator /= (const BigInteger& b) {
		*this=*this/b;
	}
	//%
	BigInteger operator % (const BigInteger& b) {
		BigInteger c,d;
		c=Divide(*this,b,d);
		return d;
	}
	void operator %= (const BigInteger& b) {
		*this=*this%b;
	}
	BigInteger operator % (const LL& k) {
		LL d=0;
		BigInteger c;
		c=*this;
		for(int i=c.s.size()-1; i>=0; i--) {
			d=d*BASE+c.s[i];
			c.s[i]=d/k;
			d%=k;
		}
		return d;
	}
	void operator %= (const LL& k) {
		*this=*this%k;
	}
	//±
	BigInteger operator + () {
		return *this;
	}
	BigInteger operator - () {
		BigInteger a=*this;
		a.bj*=-1;
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
		if(s[0]=='-') {
			x.bj=-1;
			s=s.substr(1);
		} else x.bj=1;
		x=s;
		return input;
	}
	friend ostream& operator << (ostream& output,const BigInteger& x) {
		if(x.bj==-1)cout<<"-";
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

