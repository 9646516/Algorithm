const int maxn=1e5+5;
char in[maxn];
int sa[maxn],x[maxn],y[maxn],c[maxn],r[maxn],height[maxn],d[maxn][40];
void build(int len) {
	int m=200;
	memset(c,0,sizeof(c));
	for(int i=0; i<len; i++)c[x[i]=in[i]]++;
	for(int i=1; i<m; i++)c[i]+=c[i-1];
	for(int i=len-1; i>=0; i--)sa[--c[x[i]]]=i;
	for(int k=1; k<=len; k*=2) {
		int p=0;
		for(int i=len-k; i<len; i++)y[p++]=i;
		for(int i=0; i<len; i++)if(sa[i]>=k)y[p++]=sa[i]-k;
		memset(c,0,sizeof(c));
		for(int i=0; i<len; i++)c[x[y[i]]]++;
		for(int i=1; i<m; i++)c[i]+=c[i-1];
		for(int i=len-1; i>=0; i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		x[sa[0]]=0;
		p=1;
		for(int i=1; i<len; i++)x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?p-1:p++;
		if(p>=len)break;
		m=p;
	}
	int k=0;
	for(int i=0; i<len; i++)r[sa[i]]=i;
	for(int i=0; i<len; i++) {
		if(k)k--;
		int j=sa[r[i]-1];
		while(in[j+k]==in[i+k])k++;
		height[r[i]]=k;
	}
	for(int i=0; i<len; i++)d[i][0]=height[i];
	for(int j=1; (1<<j)<=len; j++)for(int i=0; i+(1<<j)-1<len; i++)d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
}
int ask_rmq(int l,int r) {
	int k=0;
	while((1<<(k+1))<=r-l+1)k++;
	return min(d[l][k],d[r-(1<<k)+1][k]);
}
int lcp(int a, int b,int len) {
	if(a==b)return len-a;
	return r[a]>r[b]?ask_rmq(r[b]+1,r[a]):ask_rmq(r[a]+1,r[b]);
}
