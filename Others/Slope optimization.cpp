#include<bits/stdc++.h>
//最小值
using namespace std;
int main() {
#ifdef RINNE
	freopen("1.txt","r",stdin);
#endif
	using i32=int32_t;
	using i64=int64_t;
	using p64=tuple<i64,i64,i32>;
	auto cmp=[](const p64&a,const p64&b,const i64&c)->bool{
		i64 a1=get<0>(a)-get<0>(b);
		i64 a2=get<1>(a)-get<1>(b);
		if(a2<0) {
			a1*=-1;
			a2*=-1;
		}
		return a1<c*a2;//	a/b<c
	};
	auto cmp2=[](const p64&a,const p64&b,const i64&x,const i64&y)->bool{
		i64 a1=get<0>(a)-get<0>(b);
		i64 a2=get<1>(a)-get<1>(b);
		i64 a3=get<0>(b)-x;
		i64 a4=get<1>(b)-y;
		if(a2<0) {
			a1*=-1;
			a2*=-1;
		}
		if(a4<0) {
			a3*=-1;
			a4*=-1;
		}
		return a1*a4>a2*a3;
		//ab>bc
	};
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	static const i32 maxn=
#ifndef RINNE
	    5e4+555;
#else
	    555
#endif
	;
	static i64 a[maxn],dp[maxn];
	i32 n,k;
	cin>>n>>k;
	for(i32 i=1; i<=n; i++) {
		cin>>a[i];
		a[i]+=a[i-1];
	}
	deque<p64>Q;
	Q.push_back(make_tuple(0,0,0));
	for(i32 i=1; i<=n; i++) {
		i64 band=2*(a[i]-k+i-1);
		while(Q.size()>=2&&cmp(Q[0],Q[1],band))Q.pop_front();
		i32 good=get<2>(Q.front());
		dp[i]=dp[good]+(a[i]-a[good]+(i-good-1)-k)*(a[i]-a[good]+(i-good-1)-k);
		i64 x=dp[i]+(a[i]+i)*(a[i]+i);
		i64 y=a[i]+i;
		while(Q.size()>=2&&cmp2(Q.end()[-2],Q.end()[-1],x,y))Q.pop_back();
		Q.push_back(make_tuple(x,y,i));
	}
	cout<<dp[n]<<endl;
	return 0;
}
