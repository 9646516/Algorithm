int a[1010];//原始输入数组
int st[1010][20];//st表
void init(int n) {
	for (int i = 0; i < n; i++)st[i][0] = a[i];
	for (int i = 1; (1 << i) <= n; i++) {
		for (int j = 0; j + (1 << i) - 1 < n; j++)
			st[j][i] = min(st[j][i - 1],st[j + (1 << (i - 1))][i - 1]);
	}
}
int search(int l, int r) {
	int k = (int)(log((double)(r - l + 1)) / log(2.0));
	return min(st[l][k],st[r - (1 << k) + 1][k]);
}
