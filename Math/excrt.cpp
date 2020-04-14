// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 100010
#define ll long long
using namespace std;
int n;
long long a[MAXN],b[MAXN];
inline ll fmul(ll x,ll y,ll mod)
{
    ll cur_ans=0;
    while(y)
    {
        if(y&1) cur_ans=(cur_ans+x)%mod;
        x=(x+x)%mod;
        y>>=1;
    }
    return cur_ans;
}
inline ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        y=0,x=1;
        return a;
    }
    ll ans=exgcd(b,a%b,x,y);
    ll cur=x;
    x=y;
    y=cur-(a/b)*y;
    return ans;
}
inline void solve()
{
    ll ans=a[1],m=b[1],x,y;
    for(int i=2;i<=n;i++)
    {
        ll B=((a[i]-ans)%b[i]+b[i])%b[i];
        ll gcd=exgcd(m,b[i],x,y);
        x=fmul(x,B/gcd,b[i]);
        ans+=x*m;
        m*=b[i]/gcd;
        ans=(ans+m)%m;
    }
    printf("%lld\n",ans);
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("ce.in","r",stdin);
    #endif
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&b[i],&a[i]);
//  for(int i=1;i<=n;i++) printf("%lld %lld\n",a[i],b[i]);
    solve();
    return 0;
} 
