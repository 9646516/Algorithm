const int maxn=900;
unsigned long long seedx = 233;
unsigned long long seedy = 23333;
struct HashString {
	unsigned long long xp[maxn];
	unsigned long long yp[maxn];
	unsigned long long H[maxn][maxn];
	char s[maxn][maxn];
	int x,y;
	void init(int n, int m) {
		xp[0]=yp[0]=1;
		x=n,y=m;
		for(int i=1; i<=x; i++)xp[i]=xp[i-1]*seedx;
		for(int i=1; i<=y; i++)yp[i]=yp[i-1]*seedy;
	}
	void initHash() {
		for(int i=0; i<x; i++) {
			H[i][0]=s[i][0]-'a'+1;
			for(int j=1; j<y; j++)
				H[i][j]=H[i][j-1]*seedy+s[i][j]-'a'+1;
		}
		for(int i=1; i<x; i++)
			for(int j=0; j<y; j++)
				H[i][j]+=H[i-1][j]*seedx;
	}
	unsigned long long askHash(int x1, int y1, int x2, int y2) {
		unsigned long long ret=H[x2][y2];
		if(x1>0)ret-=H[x1-1][y2]*xp[x2-x1+1];
		if(y1>0)ret-=H[x2][y1-1]*yp[y2-y1+1];
		if(x1>0&&y1>0)ret+=H[x1-1][y1-1]*xp[x2-x1+1]*yp[y2-y1+1];
		returnret;
	}
}
