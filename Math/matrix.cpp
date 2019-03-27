struct Matrix {
	static const int N=105;
	Int m[N][N];
	Matrix() {
		for(int i=0; i<N; i++)for(int j=0; j<N; j++)m[i][j]=0;
	}
	friend Matrix operator *(const Matrix&a,const Matrix&b) {
		Matrix c;
		for(int i=0; i<N; i++)for(int j=0; j<N; j++)for(int k=0; k<N; k++)c.m[i][j]+=a.m[i][k]*b.m[k][j];
		return c;
	}
	friend Matrix pow(Matrix a,long long n) {
		Matrix res;
		for(int i=0; i<N; i++)res.m[i][i]=1;
		while(n>0) {
			if(n&1)res=res*a;
			n>>=1;
			a=a*a;
		}
		return res;
	}
};
