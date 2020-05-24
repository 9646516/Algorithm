//https://ac.nowcoder.com/acm/contest/view-submission?submissionId=40900331
void solve(ll n,int m,int a[],int c[],int p){
    ll v[M]={1%p},u[M<<1],mask=!!n;
    for(long long i(n);i>1;i>>=1){
        mask<<=1;
    }
    for(long long x(0);mask;mask>>=1,x<<=1){
        fill_n(u,m<<1,0);
        int b(!!(n&mask));
        x|=b;
        if(x<m){
            u[x]=1%MOD;
        }else{
            for(int i(0);i<m;i++){
                for(int j(0),t(i+b);j<m;j++,t++){
                    u[t]=(u[t]+v[i]*v[j])%MOD;
                }
            }
            for(int i((m<<1)-1);i>=m;i--){
                for(int j(0),t(i-m);j<m;j++,t++){
                    u[t]=(u[t]+c[j]*u[i])%MOD;
                }
            }
        }
        copy(u,u+m,v);
    }
    for(int i(m);i<2*m;i++){
        a[i]=0;
        for(int j(0);j<m;j++){
            a[i]=(a[i]+(ll)c[j]*a[i+j-m])%MOD;
        }
    }
    ll b[M];
    for(int j(0);j<m;j++){
        b[j]=0;
        for(int i(0);i<m;i++){
            b[j]=(b[j]+v[i]*a[i+j])%MOD;
        }
    }
    for(int j(0);j<m;j++){
        a[j]=b[j];
    }
}
