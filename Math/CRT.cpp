#include<bits/stdc++.h>
using namespace std;
void exgcd(long long a,long long b,long long &x,long long &y) {
	if(b==0) {
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	long long t;
	t=x;
	x=y;
	y=t-a/b*y;
}
long long CRT(long long a[],long long m[],long long n,long long maxx) {
	long long M=1,ans=0;
	for(int i=1; i<=n; i++)M*=m[i];
	for(int i=1; i<=n; i++) {
		long long x,y;
		long long Mi=M/m[i];
		exgcd(Mi,m[i],x,y);
		ans=(ans+Mi*x*a[i])%M;
	}
	return ans;
}
long long a[100],b[100];
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//mod a == b 
	for(int i=1; i<=6; i++)cin>>a[i];
	for(int i=1; i<=6; i++) {
		cin>>b[i];
		b[i]%=a[i];
		if(b[i]==0)b[i]=a[i];
	}
	int res=CRT(b,a,6,maxx);
	assert(res>0);
	cout<<res<<endl;
	return 0;
}
