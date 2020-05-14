//AGC031E
//AGC034D
//負辺あったら壊れるからBellman-Fordとかやるといいんじゃない？
template<class D>
struct mincf{
	using P=pair<D,int>;
	struct E{int to,rev,cap;D cost;};
	int n;
	vvc<E> g;
	vc<D> h,d;
	vi pv,pe;
	mincf(int nn):n(nn),g(n),h(n),d(n),pv(n),pe(n){}
	pi ae(int a,int b,int cap,D cost){
		pi res(a,g[a].size());
		g[a].pb({b,(int)g[b].size(),cap,cost});
		g[b].pb({a,(int)g[a].size()-1,0,-cost});
		return res;
	}
	P go(int s,int t,int f){
		priority_queue<P,vc<P>,greater<P>> q;
		fill(all(d),inf);
		d[s]=0;
		q.push(P(0,s));
		while(q.size()){
			D a;
			int v;
			tie(a,v)=q.top();q.pop();
			if(d[v]<a)continue;
			rep(i,(int)g[v].size()){
				E e=g[v][i];
				if(e.cap>0){
					D w=d[v]+e.cost+h[v]-h[e.to];
					if(w<d[e.to]){
						d[e.to]=w;
						q.push(P(w,e.to));
						pv[e.to]=v;
						pe[e.to]=i;
					}
				}
			}
		}
		if(d[t]==inf)return P(0,0);
		rep(i,n)
			h[i]=min(h[i]+d[i],inf);
		int a=f;
		for(int v=t;v!=s;v=pv[v])
			chmin(a,g[pv[v]][pe[v]].cap);
		for(int v=t;v!=s;v=pv[v]){
			E& e=g[pv[v]][pe[v]];
			e.cap-=a;
			g[e.to][e.rev].cap+=a;
		}
		return P(a*h[t],a);
	}
	D calc(int s,int t,int f){
		D res=0;
		while(f>0){
			P w=go(s,t,f);
			if(w.b==0)
				return inf;
			f-=w.b;
			res+=w.a;
		}
		return res;
	}
};
 
