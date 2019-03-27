vector<pair<int,int> >V2[1234];
int dis[1234];
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
