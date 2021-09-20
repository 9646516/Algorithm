int dex=1,color=1,belong[101],dfs[101],low[101],in[101],out[101];
vector<int>V[101];
bool vis[101];
stack<int>S;
void tarjan(int now) {
	dfs[now]=low[now]=dex++;
	S.push(now);
	vis[now]=true;
	for(int i=0; i<(int)V[now].size(); i++) {
		int next=V[now][i];
		if(!dfs[next]) {
			tarjan(next);
			low[now]=min(low[now],low[next]);
		} else if(vis[next]) {
			low[now]=min(low[now],dfs[next]);
		}
	}
	if(low[now]==dfs[now]) {
		while(vis[now]) {
			int tp=S.top();
			S.pop();
			belong[tp]=color;
			vis[tp]=false;
		}
		color++;
	}
}
/*
for(int i=1; i<=n; i++) {
	if(!dfs[i])tarjan(i);
}
*/
