void RMQ(vector<int>&mp,int n,int m) {
	//mp 0..n-1
	//dis = m
	//return min_element [max(0,i-m+1),i]
	static int q[3003];
	vector<int>ret(n);
	int l=1,r=0;
	for(int i=0; i<n; i++) {
		if(i-q[l]+1>m&&l<=r)l++;
		while(mp[i]<mp[q[r]]&&l<=r)r--;
		q[++r]=i;
		ret[i]=mp[q[l]];
	}
}
