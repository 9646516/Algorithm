const int INF = 1e9;
struct MCMF {
	static const int N=7000,M=N*20;
	int n,m,fst[N],f[N],a[N],p[N],q[N],d[N];
	int _x[M],_y[M],_flow[M],_cap[M],_nxt[M],_cost[M];
	void init(int _n) {
		n=_n,m=1;
		memset(fst,0,sizeof(fst));
	}
	void add(int a,int b,int cap,int cost) {
		m++;
		_x[m]=a,_y[m]=b,_cap[m]=cap,_cost[m]=cost,_flow[m]=0;
		_nxt[m]=fst[a],fst[a]=m;
		m++;
		_x[m]=b,_y[m]=a,_cap[m]=0,_cost[m]=-cost,_flow[m]=0;
		_nxt[m]=fst[b],fst[b]=m;
		assert(a<N);
		assert(b<N);
		assert(m<M);
	}
	bool SPFA(int S,int T,int &flow,int &cost) {
		int head=0,tail=0,qmod=n+1,x,y;
		memset(f,0,sizeof f);
		for(int i=1; i<=n; i++)d[i]=1e9;
		d[S]=0,q[tail=tail%qmod+1]=S,a[S]=1e9;
		while (head!=tail) {
			f[x=q[head=head%qmod+1]]=0;
			for (int i=fst[x]; i; i=_nxt[i]) {
				y=_y[i];
				if (_flow[i]<_cap[i]&&d[x]+_cost[i]<d[y]) {
					d[y]=d[x]+_cost[i];
					a[y]=min(a[x],_cap[i]-_flow[i]);
					p[y]=i;
					if (!f[y])f[q[tail=tail%qmod+1]=y]=1;
				}
			}
		}
		if(d[T]>5e8)return 0;
		flow+=a[T],cost+=d[T]*a[T];
		for(x=T; x!=S; x=_x[p[x]])_flow[p[x]]+=a[T],_flow[p[x]^1]-=a[T];
		return 1;
	}
	int MinCost(int S,int T) {
		int flow=0,cost=0;
		while(SPFA(S,T,flow,cost));
		return cost;
	}
} MCMF;
