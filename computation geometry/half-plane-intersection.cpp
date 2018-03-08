#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

//Need to reference class-Point

const int maxn=100005;

struct Line { //directed line,half plane is on left
	Point p;
	Vector v; //direction vector
	double ang;
	Line() {}
	Line(Point p,Vector v):p(p),v(v) {ang=atan2(v.y,v.x);}
	bool operator < (const Line& L) const {return ang<L.ang;}
};

bool OnLeft(Line L,Point p) {return dcmp(Cross(L.v,L.p-p))>=0;} //if you need no points on the lines,change ">=" into ">"

Point GetIntersection(Line a,Line b) {return a.p+a.v*(Cross(a.p-b.p,b.v)/Cross(a.v,b.v));}

int Unique(int n,Line *L) {
	int cnt=1;
	for(int i=2; i<=n; i++)
		if(dcmp(L[cnt].ang-L[i].ang)!=0)L[++cnt]=L[i];
		else if(OnLeft(L[cnt],L[i].p))L[cnt]=L[i];
	return cnt;
}

int HalfplaneIntersection(int n,Line *L,Point *poly) { //O(nlogn) algorithm：n is the size of lines,L is the set of lines,poly is the points of intersection,return the size of intersection
	sort(L+1,L+n+1);
	n=Unique(n,L);
	int first=1,last=1;
	static Point p[maxn+5];
	static Line q[maxn+5];
	q[last]=L[1];
	for(int i=2; i<=n; i++) {
		while(first<last&&!OnLeft(L[i],p[last-1]))last--;
		while(first<last&&!OnLeft(L[i],p[first]))first++;
		q[++last]=L[i];
		if(first<last)p[last-1]=GetIntersection(q[last-1],q[last]);
	}
	while(first<last&&!OnLeft(q[first],p[last-1]))last--;
	if(last-first<=1)return 0; //no solution
	p[last]=GetIntersection(q[last],q[first]);
	int m=0;
	for(int i=first; i<=last; i++)poly[++m]=p[i];
	return m;
}

int main() {
	
	return 0;
}