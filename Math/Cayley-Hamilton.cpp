
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4005;
const int P = 1e9 + 7;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}
int n, k;
int a[MAXN], now[MAXN];
int res[MAXN], h[MAXN];
void times(int *x, int *y) {
	static int tmp[MAXN];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i <= k - 1; i++)
	for (int j = 0; j <= k - 1; j++)
		tmp[i + j] = (tmp[i + j] + 1ll * x[i] * y[j]) % P;
	for (int i = 2 * k - 2; i >= k; i--) {
		for (int j = 1; j <= k; j++)
			tmp[i - j] = (tmp[i - j] + 1ll * tmp[i] * a[j]) % P;
		tmp[i] = 0;
	}
	for (int i = 0; i <= k - 1; i++)
		x[i] = tmp[i];
}
int main() {
	read(n), read(k);
	for (int i = 1; i <= k; i++) {
		read(a[i]);
		if (a[i] < 0) a[i] += P;
	}
	for (int i = 0; i <= k - 1; i++) {
		read(h[i]);
		if (h[i] < 0) h[i] += P;
	}
	if (n <= k - 1) {
		writeln(h[k]);
		return 0;
	}
	n -= k - 1; res[0] = now[1] = 1;
	while (n != 0) {
		if (n & 1) times(res, now);
		n >>= 1;
		times(now, now);
	}
	for (int i = k; i <= 2 * k - 2; i++)
	for (int j = 1; j <= k; j++)
		h[i] = (h[i] + 1ll * h[i - j] * a[j]) % P;
	int ans = 0;
	for (int i = 0; i <= k - 1; i++)
		ans = (ans + 1ll * h[k - 1 + i] * res[i]) % P;
	writeln(ans);
	return 0;
}
