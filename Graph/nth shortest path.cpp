#include <bits/stdc++.h>
using namespace std;
int op,ed,k,a,b,c,n,m,dis[1234];
struct node {
	int x;
	int d;
	friend bool operator<(node a,node b) {
		return a.d+dis[a.x]<b.d+dis[b.x];
	}
};
vector<pair<int,int> >V2[1234];
void dijk(int x) {
	multiset<pair<int,int> >Q;
	memset(dis,0x3F,sizeof(dis));
	Q.insert(make_pair(0,x));
	dis[x]=0;
	while(!Q.empty()) {
		int now=Q.begin()->second;
		Q.erase(Q.begin());
		for(auto j:V2[now]) {
			if(dis[j.first]>j.second+dis[now]) {
				Q.erase(make_pair(dis[j.first],j.first));
				dis[j.first]=j.second+dis[now];
				Q.insert(make_pair(dis[j.first],j.first));
			}
		}
	}
}
vector<pair<int,int> >V[1234];
int bfs(int x) {
	multiset<node>Q;if(op==ed)k++;
	Q.insert(node {x,0});
	while(!Q.empty()) {
		node cur=*Q.begin();
		Q.erase(Q.begin());
		if(cur.x==ed) {
			if(k>1)k--;
			else return cur.d;
		}
		for(auto i:V[cur.x])Q.insert(node {i.first,cur.d+i.second});
	}return -1;
}
int main() {
	scanf("%d%d%d%d%d",&n,&m,&k,&op,&ed);
	while(m--) {
		scanf("%d%d%d",&a,&b,&c);
		V[a].push_back(make_pair(b,c));
		V2[b].push_back(make_pair(a,c));
	}
	dijk(ed);if(dis[op]==0x3f3f3f3f){puts("-1");return 0;}
	printf("%d\n",bfs(op));
	return 0;
}
