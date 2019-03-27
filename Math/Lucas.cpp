using ll = long long;
namespace Lucas {
	ll pow_m(ll a,ll k,ll p) {
		ll ans=1;
		ll tmp=a%p;
		while(k) {
			if(k&1)ans=ans*tmp%p;
			tmp=tmp*tmp%p;
			k>>=1;
		}
		return ans;
	}
	ll C(ll n,ll m,ll p) {
		if(m>n)return 0;
		ll a=1,b=1;
		for(int i=1; i<=m; i++) {
			a=a*(n+i-m)%p;
			b=b*i%p;
		}
		return a*pow_m(b,p-2,p)%p;
	}
	ll Lucas(ll n,ll m,ll p) {
		ll ans=1;
		while(n&&m) {
			ans=ans*C(n%p,m%p,p)%p;
			n/=p;
			m/=p;
		}
		return ans;
	}
}
