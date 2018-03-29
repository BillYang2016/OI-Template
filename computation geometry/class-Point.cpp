#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const double eps=1e-8;

int dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	return x>eps?1:-1;
}

struct Point {
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	Point operator + (const Point &a) {return Point(x+a.x,y+a.y);}
	Point operator - (const Point &a) {return Point(a.x-x,a.y-y);} //attention reversed!
	Point operator * (double a) {return Point(x*a,y*a);}
	Point operator / (double a) {return Point(x/a,y/a);}
	bool operator < (const Point &b) const {return x<b.x||(x==b.x&&y<b.y);}
	bool operator == (Point b) {return dcmp(x-b.x)==0&&dcmp(y-b.y)==0;}
	double length() {return sqrt(x*x+y*y);}
	Point rotate(double rad) {return Point(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));} //anticlockwise
	Point normal(Point a) {return Point(-a.y/a.length(),a.x/a.length());} //normal vector
};

typedef Point Vector; //only for code convenience

double Cross(const Vector& a,const Vector& b) {return a.x*b.y-b.x*a.y;}
double Dot(Vector a,Vector b) {return a.x*b.x+a.y*b.y;}
double Angle(Vector a,Vector b) {return acos(Dot(a,b)/a.length()/b.length());}
double Area(Point a,Point b,Point c) {return Cross(b-a,c-a);}

bool OnSegment(Point st,Point ed,Point p) {return dcmp(Cross(st-p,ed-p))==0&&dcmp(Dot(st-p,ed-p))<0;} //if p is on segment st->ed
bool Segment_Intersection(Point a1,Point a2,Point b1,Point b2) {return dcmp(Cross(a2-a1,b1-a1))*dcmp(Cross(a2-a1,b2-a1))<0&&dcmp(Cross(b2-b1,a1-b1))*dcmp(Cross(b2-b1,a2-b1))<0;} //if segments (a1->a2,b1->b2) are intersected
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w) {return P+v*(Cross(P-Q,w)/Cross(v,w));} //get lines' (P+tv,Q+tw) intersection (need to confirm that lines are intersected)
double DistanceToLine(Point p,Point a,Point b) {Vector v1=b-a,v2=p-a;return fabs(Cross(v1,v2))/v1.length();}
double DistanceToSegment(Point p,Point a,Point b) {
	if(a==b)return (p-a).length();
	Vector v1=b-a,v2=p-a,v3=p-b;
	if(dcmp(Dot(v1,v2))<0)return v2.length();
	else if(dcmp(Dot(v1,v3))>0)return v3.length();
	else return DistanceToLine(p,a,b);
}

double Area(int n,Point* P) {
	double ans=0;
	for(int i=2; i<n; i++)ans+=Area(P[1],P[i],P[i+1]);
	return ans/2;
}

int main() {
	
	return 0;
}