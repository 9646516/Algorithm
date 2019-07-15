#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int MOD=1e9+7;
inline ll qp(ll a,ll b) {
	ll x=1;
	a%=MOD;
	while(b) {
		if(b&1) x=x*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return x;
}
namespace Lagrange {
	ll x[23333],y[23333],a[23333],g[23333],h[23333],p[23333];
	int N;
	void work() {
		for(int i=0; i<N; ++i) a[i]=0;
		g[0]=1;
		for(int i=0; i<N; ++i) {
			for(int _=0; _<=i; ++_)h[_+1]=g[_];
			h[0]=0;
			for(int _=0; _<=i; ++_)h[_]=(h[_]-g[_]*(ll)x[i])%MOD;
			for(int _=0; _<=i+1; ++_) g[_]=h[_];
		}
		for(int i=0; i<N; ++i) {
			for(int j=0; j<=N; ++j) p[j]=g[j];
			for(int j=N; j; --j)p[j-1]=(p[j-1]+p[j]*(ll)x[i])%MOD;
			ll s=1;
			for(int j=0; j<N; ++j) if(i!=j)s=s*(x[i]-x[j])%MOD;
			s=y[i]*qp(s,MOD-2)%MOD;
			for(int _=0; _<N; ++_)a[_]=(a[_]+p[_+1]*s)%MOD;
		}
	}
	vector<int> feed(vector<int> v) {
		N=v.size();
		for(int i=0; i<N; ++i) x[i]=i,y[i]=v[i];
		work();
		v.clear();
		for(int i=0; i<N; ++i) v.push_back(a[i]);
		while(v.size()&&!v.back()) v.pop_back();
		return v;
	}
	ll calc(vector<int>&v,ll xx) {
		ll s=0,gg=1;
		xx%=MOD;
		for(int i=0; i<N; ++i)s=(s+gg*v[i])%MOD,gg=gg*xx%MOD;
		return s;
	}
}
using Lagrange::feed;
using Lagrange::calc;
//ps[k]=\sum_{i=0}^x i^k
vector<int> ps[2333];
//rs[k]=\sum_{i=0}^x ((i+1)^k-i^k)
vector<int> rs[2333];
struct arr {
	ll p[11][11];
};
ll C[233][233];
arr calc(ll a,ll b,ll c,ll n) {
	arr w;
	if(n==0) a=0;
	if(a==0||a*n+b<c) {
		for(int i=0; i<=10; ++i) {
			ll t=calc(ps[i],n),s=b/c;
			for(int j=0; i+j<=10; ++j)w.p[i][j]=t,t=t*s%MOD;
		}
		return w;
	}
	for(int i=0; i<=10; ++i)w.p[i][0]=calc(ps[i],n);
	if(a>=c||b>=c) {
		arr t=calc(a%c,b%c,c,n);
		ll p=a/c,q=b/c;
		for(int i=0; i<=10; ++i)
			for(int j=1; i+j<=10; ++j) {
				ll s=0,px=1;
				for(int x=0; x<=j; ++x,px=px*p%MOD) {
					ll qy=1;
					for(int y=0; x+y<=j; ++y,qy=qy*q%MOD) {
						//x^(i) (px)^x q^y ??^(j-x-y)
						s+=px*qy%MOD*C[j][x]%MOD*C[j-x][y]%MOD*t.p[i+x][j-x-y];
						s%=MOD;
					}
				}
				w.p[i][j]=s;
			}
		return w;
	}
	ll m=(a*n+b)/c;
	arr t=calc(c,c-b-1,a,m-1);
	for(int i=0; i<=10; ++i)
		for(int j=1; i+j<=10; ++j) {
			ll s=calc(rs[j],m-1)*calc(ps[i],n)%MOD;
			for(int p=0; p<j; ++p) {
				for(unsigned q=0; q<ps[i].size(); ++q) {
					ll v=C[j][p]*ps[i][q]%MOD;
					//v*t^p*((tc+c-b-1)/a)^q
					s-=t.p[p][q]*v;
					s%=MOD;
				}
			}
			w.p[i][j]=s%MOD;
		}
	return w;
}
int T,n,a,b,c,k1,k2;
int main() {
	for(int i=0; i<=230; ++i) {
		C[i][0]=1;
		for(int j=1; j<=i; ++j)C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
	for(int i=0; i<=10; ++i) {
		ll sp=0,sr=0;
		vector<int> p,r;
		for(int j=0; j<=20; ++j) {
			sp+=qp(j,i);
			sr+=qp(j+1,i)-qp(j,i);
			sp%=MOD;
			sr%=MOD;
			p.push_back(sp);
			r.push_back(sr);
		}
		ps[i]=feed(p);
		rs[i]=feed(r);
	}
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d%d%d%d",&n,&a,&b,&c,&k1,&k2);
		arr s=calc(a,b,c,n);
		int p=s.p[k1][k2];
		p=(p%MOD+MOD)%MOD;
		printf("%d\n",p);
	}
	return 0;
}
