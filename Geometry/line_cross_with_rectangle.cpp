#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
struct node {
	int x;
	int y;
};
bool segmentsIntersect(node a,node b,node c,node d) {
	if(!(min(a.x,b.x)<=max(c.x,d.x)&&min(c.y,d.y)<=max(a.y,b.y)&&min(c.x,d.x)<=max(a.x,b.x)&&min(a.y,b.y)<=max(c.y,d.y)))
		return false;
	long long u=(c.x-a.x)*(b.y-a.y)-(b.x-a.x)*(c.y-a.y);
	long long v=(d.x-a.x)*(b.y-a.y)-(b.x-a.x)*(d.y-a.y);
	long long w=(a.x-c.x)*(d.y-c.y)-(d.x-c.x)*(a.y-c.y);
	long long z=(b.x-c.x)*(d.y-c.y)-(d.x-c.x)*(b.y-c.y);
	return (u*v<=0&&w*z<=0);
}
bool inside(node a,node b,node c,node d,node e) {
	long long u=(b.x-a.x)*(e.y-a.y)-(e.x-a.x)*(b.y-a.y);
	long long v=(d.x-c.x)*(e.y-c.y)-(e.x-c.x)*(d.y-c.y);
	long long w=(c.x-b.x)*(e.y-b.y)-(e.x-b.x)*(c.y-b.y);
	long long z=(a.x-d.x)*(e.y-d.y)-(e.x-d.x)*(a.y-d.y);
	return u*v>=0&&w*z>=0;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int cas,x1,x2,y1,y2,opx,opy,edx,edy;
	cin>>cas;
	while(cas--) {
		cin>>opx>>opy>>edx>>edy>>x1>>y1>>x2>>y2;
		node a= {x1,y1};
		node b= {x1,y2};
		node c= {x2,y2};
		node d= {x2,y1};
		node e= {opx,opy};
		node f= {edx,edy};
		bool ck=inside(a,b,c,d,e)||inside(a,b,c,d,f)||segmentsIntersect(a,b,e,f)||segmentsIntersect(b,c,e,f)||segmentsIntersect(c,d,e,f)||segmentsIntersect(a,d,e,f);
		cout<<(ck?"T":"F")<<endl;
	}
	return 0;
}