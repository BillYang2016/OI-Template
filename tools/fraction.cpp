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

LL lcm(LL a,LL b) {
	return a/__gcd(a,b)*b;
}

struct Fraction {
	LL u,d;
	Fraction(LL _u=0,LL _d=1) {
		LL gcd=__gcd(_u,_d);
		u=_u/gcd;
		d=_d/gcd;
	}
	bool operator < (const Fraction& b) {
		return u*b.d<d*b.u;
	}
	bool operator == (const Fraction& b) {
		return u*b.d==d*b.u;
	}
	bool operator >= (const Fraction& b) {
		return !(*this<b);
	}
	bool operator <= (const Fraction& b) {
		return !(*this>b);
	}
	bool operator != (const Fraction& b) {
		return !(*this==b);
	}
	bool operator > (const Fraction& b) {
		return (*this>=b)&&(*this!=b);
	}
	Fraction operator + (const Fraction& b) {
		Fraction c(b.d/__gcd(b.d,d)*u+d/__gcd(b.d,d)*b.u,lcm(b.d,d));
		return c;
	}
	void operator += (const Fraction& b) {
		*this=*this+b;
	}
	Fraction operator - (const Fraction& b) {
		Fraction c(b.d/__gcd(b.d,d)*u-d/__gcd(b.d,d)*b.u,lcm(b.d,d));
		return c;
	}
	void operator -= (const Fraction& b) {
		*this=*this-b;
	}
	Fraction operator * (const Fraction& b) {
		Fraction c(u*b.u,d*b.d);
		return c;
	}
	void operator *= (const Fraction& b) {
		*this=*this*b;
	}
	Fraction operator / (const Fraction& b) {
		Fraction c(b.d,b.u);
		return *this*c;
	}
	void operator /= (const Fraction& b) {
		*this=*this/b;
	}
};
ostream& operator << (ostream& output,const Fraction& x) {
	output<<x.u<<'/'<<x.d;
	return output; 
}

int main() {

	return 0;
}