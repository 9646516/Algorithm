#include<bits/stdc++.h>
#define x first
#define y second
#define PP pair<double,double>
using namespace std;
vector<PP>V;
double dis(PP a,PP b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double solve(int op,int ed) {
	if(op+1==ed)return dis(V[op],V[op+1]);
	if(op+2==ed)return min(min(dis(V[op],V[op+1]),dis(V[op],V[op+2])),dis(V[op+1],V[op+2]));
	int mid=(op+ed)/2;
	double a1=solve(op,mid),a2=solve(mid+1,ed),minn=min(a1,a2);
	vector<PP>tp;
	for(int i=op; i<=ed; i++)if(fabs(V[i].x-V[mid].x)<=minn)tp.push_back(V[i]);
	sort(tp.begin(),tp.end(),[](PP a,PP b) {
		return a.y<b.y;
	});
	for(int i=0; i<(int)tp.size(); i++) {
		for(int j=i+1; j<(int)tp.size(); j++) {
			if(fabs(tp[j].y-tp[i].y)>=minn)break;
			minn=min(minn,dis(tp[i],tp[j]));
		}
	}
	return minn;
}
int main() {
	int n;
	double a,b;
	while(scanf("%d",&n),n) {
		V.clear();
		for(int i=0; i<n; i++)scanf("%lf%lf",&a,&b),V.push_back(make_pair(a,b));
		sort(V.begin(),V.end());
		printf("%.2lf\n",solve(0,V.size()-1)/2);
	}
	return 0;
}
