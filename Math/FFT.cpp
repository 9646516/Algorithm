//注意这个板子x的系数从1开始
#include <bits/stdc++.h>
using namespace std;
const int FFTN = 1 << 21;
const int N = FFTN + 55;
struct comp {
    double r, i;
    comp(double _r = 0, double _i = 0) : r(_r), i(_i) {}
    comp operator+(const comp &x) { return comp(r + x.r, i + x.i); }
    comp operator-(const comp &x) { return comp(r - x.r, i - x.i); }
    comp operator*(const comp &x) { return comp(r * x.r - i * x.i, r * x.i + i * x.r); }
} A[N], B[N], C[N];
const double pi = acos(-1.0);
void FFT(comp *a, int t) {
    for (int i = 1, j = 0; i < FFTN - 1; i++) {
        for (int s = FFTN; j ^= s >>= 1, ~j & s;)
            ;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int d = 0; (1 << d) < FFTN; d++) {
        int m = 1 << d, m2 = m << 1;
        double o = pi / m * t;
        comp _w(cos(o), sin(o));
        for (int i = 0; i < FFTN; i += m2) {
            comp w(1, 0);
            for (int j = 0; j < m; j++) {
                comp &A = a[i + j + m], &B = a[i + j], t = w * A;
                A = B - t;
                B = B + t;
                w = w * _w;
            }
        }
    }
    if (t == -1)
        for (int i = 0; i < FFTN; i++)
            a[i].r /= FFTN;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n + 1; i++) {
        cin >> A[FFTN - i].r;
    }
    for (int i = 1; i <= m + 1; i++) {
        cin >> B[FFTN - i].r;
    }
    FFT(A, 1);
    FFT(B, 1);
    for (int i = 0; i < FFTN; i++) {
        C[i] = A[i] * B[i];
    }
    FFT(C, -1);
    for (int i = 1; i <= n + m + 1; i++) {
        cout << (int)(C[FFTN - i - 1].r + 0.5) << ' ';
    }
    cout << endl;
    return 0;
}
