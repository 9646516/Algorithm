#define PP pair<int,int>
#define x first
#define y second
PP cent;
inline int operator * (PP a,PP b) {
	return a.x*b.y-b.x*a.y;
}
inline PP operator - (PP a,PP b) {
	return make_pair(a.x-b.x,a.y-b.y);
}
inline double dis(PP&a,PP&b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool cmp(PP a,PP b) {
	int s=(a-cent)*(b-cent);
	return s>0||(s==0&&dis(cent,a)<dis(cent,b)) ;
}
inline double calc(vector<PP>&V,int n) {
	if(n<=1)return 0;
	if(n==2)return 2*dis(V[0],V[1]);
	vector<PP>s;
	cent= make_pair(0x7FFFFFFF,0x7FFFFFFF);
	double ret=0;
	for(int i=0; i<n; i++)if(V[i].y<cent.y||(V[i].y==cent.y&&V[i].x<cent.x))cent=V[i];
	sort(V.begin(),V.end(),cmp);
	s.push_back(V[0]);
	s.push_back(V[1]);
	s.push_back(V[2]);
	for(int i=3; i<(int)V.size(); i++) {
		while(s.size()>=2&&(s[s.size()-1]-s[s.size()-2])*(V[i]-s[s.size()-2])<=0)s.pop_back();
		s.push_back(V[i]);
	}
	s.push_back(s[0]);
	for(int i=1; i<(int)s.size(); i++)ret+=dis(s[i],s[i-1]);
	return ret;
}
