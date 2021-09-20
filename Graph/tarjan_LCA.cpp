#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> >V[1001];//pt dist
vector<pair<int,int> >Q[1001];//pt id
vector<pair<int,int> >Q2;
int dis[1001],father[1001],LCA[1001];
bool vis[1001];
int seek(int x) {
	return father[x]==x?x:father[x]=seek(father[x]);
}
void tarjan(int now) {
	vis[now]=true;
	for(int i=0; i<(int)Q[now].size(); i++) {
		int next=Q[now][i].first;
		if(vis[next])LCA[Q[now][i].second]=seek(next);
	}
	for(int i=0; i<(int)V[now].size(); i++) {
		int next=V[now][i].first;
		if(!vis[next]){
			dis[next]=dis[now]+V[now][i].second;
			tarjan(next);
			father[next]=now;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int pt,q,a,b,c;
	while(cin>>pt>>q) {
		for(int i=1; i<=pt; i++)father[i]=i;
		for(int i=1; i<=pt; i++)V[i].clear();
		for(int i=1; i<=pt; i++)Q[i].clear();
		memset(LCA,0,sizeof(LCA));
		memset(dis,0,sizeof(dis));
		memset(vis,false,sizeof(vis));
		Q2.clear();
		for(int i=0; i<pt-1; i++) {
			cin>>a>>b>>c;
			V[a].push_back({b,c});
			V[b].push_back({a,c});
		}
		for(int i=0; i<q; i++) {
			cin>>a>>b;
			Q[a].push_back({b,i});
			Q[b].push_back({a,i});
			Q2.push_back({a,b});
		}
		tarjan(1);
		for(int i=0;i<q;i++)cout<<dis[Q2[i].first]+dis[Q2[i].second]-2*dis[LCA[i]]<<endl;
	}
	return 0;
}
/*
INPUT FORMAT:
* Line 1: N and Q
* Lines 2..N: Ai, Bi, and Li
* Lines N+1..N+Q: p1 and p2
*/ 
