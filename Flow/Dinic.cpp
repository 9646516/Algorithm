struct dinic {
	static const int N=400,M=N*20;
	int nxt[M],head[M],list[M],cnt,w[M],w2[M],dist[N],s,e;
	void add(int a,int b,int c) {
		cnt++;
		list[cnt]=b,w[cnt]=w2[cnt]=c;
		nxt[cnt]=head[a];
		head[a]=cnt;
	}
	bool bfs() {
		memset(dist,0,sizeof(dist));
		queue<int>q;
		dist[s]=1;
		q.push(s);
		while(!q.empty()) {
			int v=q.front();
			q.pop();
			for(int i=head[v]; ~i; i=nxt[i]) {
				int u=list[i];
				if(w[i]!=0&&dist[u]==0) {
					dist[u]=dist[v]+1;
					q.push(u);
				}
			}
		}
		return dist[e]>0;
	}
	int find(int v,int low) {
		if(v==e)return low;
		int a=0;
		for(int i=head[v]; ~i&&a<low; i=nxt[i]) {
			int temp=0;
			int u=list[i];
			if(w[i]&&dist[u]==dist[v]+1&&(temp=find(u,min(low-a,w[i])))) {
				a+=temp;
				w[i]-=temp;
				w[i^1]+=temp;
			}
		}
		if(a==0)dist[v]=0;
		return a;
	}
	int calc() {
		int ans=0;
		while(bfs()) {
			int a=0;
			while((a=find(s,0x7FFFFFFF)))ans+=a;
		}
		return ans;
	}
	void init(int op,int ed) {
		memset(head,-1,sizeof(head));
		cnt=-1;
		s=op;
		e=ed;
	}
	int seek(int op,int ed) {
		for(int i=head[op]; ~i; i=nxt[i]) {
			if(list[i]==ed)return i;
		}
		assert(false);
		return -1;
	}
	void reset() {
		for(int i=0; i<=cnt; i++)w[i]=w2[i];
	}
}
