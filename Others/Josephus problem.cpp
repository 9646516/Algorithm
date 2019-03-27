int dfs(int sum,int value,int n){//total sum,distance,i
	return n==1?(sum+value-1)%sum:dfs(sum-1,value,n-1)+value%sum;
}
