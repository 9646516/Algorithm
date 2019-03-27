int fac[]={1,1,2,6,24,120,720,5040,40320};
int Cantor(int a[]) {
	int sum=0;
	for (int i=0; i<9; i++) {
		int t=0;
		for(int j=i+1; j<9; j++)if(a[j]<a[i])t++;
		sum+=t*fac[9-i-1];
	}
	return sum+1;
}
