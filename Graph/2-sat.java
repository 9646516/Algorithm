import java.io.*;
import java.util.*;
import java.math.*;
public class Main {
    InputStream is;
    PrintWriter out;
    String INPUT = "" ;
    boolean local = false;
    int inf=0x7FFFFFFF;
    int MOD=(int)(1e9+7);
    double eps=1e-5;
    double PI=Math.acos(-1);
    void solve() {
        int n=ni(),m=ni();
        TwoSatisfiability sat = new TwoSatisfiability(n+1);
        for(int i=0;i<m;i++){
            int a=ni(),b=ni(),c=ni();
            if(a==1)sat.eq(b,c);
            else sat.xor(b,c);
        }
        out.println(sat.isSatisfied()?"YES":"NO");
    }
    public static class TwoSatisfiability {
        public int[] from, to;
        public int p;
        public int n;
        public TwoSatisfiability(int n) {
            this.n = n;
            from = new int[2];
            to = new int[2];
            p = 0;
        }

        private void addEdge(int x, int y)
        {
            if(p == from.length){
                from = Arrays.copyOf(from, p*3/2);
                to = Arrays.copyOf(to, p*3/2);
            }

            from[p] = x;
            to[p] = y;
            p++;
        }

        public boolean isSatisfied()
        {
            int[][] g = packD(2*n, from, to, p);
            int[] clus = decomposeToSCC(g);
            for(int i = 0;i < n;i++){
                if(clus[i] == clus[i+n])return false;
            }
            return true;
        }

        public int[] restore()
        {
            int[][] g = packD(2*n, from, to, p);
            int[] clus = decomposeToSCC(g);
            int[] ret = new int[n];
            for(int i = 0;i < n;i++){
                if(clus[i] == clus[i+n])return null; // unsatisfied
                ret[i] = clus[i] > clus[i+n] ? -1 : 1;
            }
            return ret;
        }
        public void or2(int x, int y)
        {
            addEdge(x, y+n);
            addEdge(y, x+n);
        }
        // x or y
        // ~x->y, ~y->x
        public void or(int x, int y)
        {
            addEdge(x+n, y);
            addEdge(y+n, x);
        }

        // x = y
        // ~x -> ~y, ~y -> ~x
        // x -> y, y -> x
        public void eq(int x, int y)
        {
            addEdge(x, y);
            addEdge(y, x);
            addEdge(x+n, y+n);
            addEdge(y+n, x+n);
        }

        // x xor y
        // ~x -> y, y -> ~x
        // x -> ~y, ~y -> x
        public void xor(int x, int y)
        {
            addEdge(x+n, y);
            addEdge(y, x+n);
            addEdge(x, y+n);
            addEdge(y+n, x);
        }

        // always true
        public void t(int x)
        {
            addEdge(x+n, x);
        }

        // always false
        public void f(int x)
        {
            addEdge(x, x+n);
        }

        ////// inner utility

        public static int[][] packD(int n, int[] from, int[] to, int sup)
        {
            int[][] g = new int[n][];
            int[] p = new int[n];
            for(int i = 0;i < sup;i++)p[from[i]]++;
            for(int i = 0;i < n;i++)g[i] = new int[p[i]];
            for(int i = 0;i < sup;i++){
                g[from[i]][--p[from[i]]] = to[i];
            }
            return g;
        }

        public static int[] decomposeToSCC(int[][] g)
        {
            int n = g.length;
            int[] stack = new int[n+1];
            int[] ind = new int[n+1];
            int[] ord = new int[n];
            Arrays.fill(ord, -1);
            int[] low = new int[n];
            Arrays.fill(low, -1);
            int sp = 0;
            int id = 0; // preorder
            int[] clus = new int[n];
            int cid = 0;
            int[] cstack = new int[n+1];
            int csp = 0;
            boolean[] incstack = new boolean[n];
            for(int i = 0;i < n;i++){
                if(ord[i] == -1){
                    ind[sp] = 0;
                    cstack[csp++] = i;
                    stack[sp++] = i;
                    incstack[i] = true;
                    while(sp > 0){
                        int cur = stack[sp-1];
                        if(ind[sp-1] == 0){
                            ord[cur] = low[cur] = id++;
                        }
                        if(ind[sp-1] < g[cur].length){
                            int nex = g[cur][ind[sp-1]];
                            if(ord[nex] == -1){
                                ind[sp-1]++;
                                ind[sp] = 0;
                                incstack[nex] = true;
                                cstack[csp++] = nex;
                                stack[sp++] = nex;
                            }else{
                                // shortcut
//								U.tr(cur, nex, incstack[nex], low[nex], stack);
                                if(incstack[nex])low[cur] = Math.min(low[cur], low[nex]);
                                ind[sp-1]++;
                            }
                        }else{
                            if(ord[cur] == low[cur]){
                                while(csp > 0){
                                    incstack[cstack[csp-1]] = false;
                                    clus[cstack[--csp]] = cid;
                                    if(cstack[csp] == cur)break;
                                }
                                cid++;
                            }
                            if(--sp >= 1)low[stack[sp-1]] = Math.min(low[stack[sp-1]], low[stack[sp]]);
                        }
                    }
                }
            }
            return clus;
        }
    }
    class Matrix {
        private final int N=2;
        public BigInteger [][]m;
        Matrix(){
            m=new BigInteger[N][N];;
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    m[i][j]=new BigInteger("0");
                }
            }
        }
        Matrix Mul(Matrix a,Matrix b) {
            Matrix c=new Matrix();
            for(int i=0; i<N; i++)for(int j=0; j<N; j++)for(int k=0; k<N; k++)c.m[i][j]=c.m[i][j].add(a.m[i][k].multiply(b.m[k][j]));
            return c;
        }
        Matrix fastm(Matrix a,long n) {
            Matrix res=new Matrix();
            for(int i=0;i<N;i++)res.m[i][i]=BigInteger.valueOf(1);
            while(n>0) {
                if((n&1)>0)res=Mul(res,a);
                n>>=1;
                a=Mul(a,a);
            }
            return res;
        }
    }
    public class Yts1999 implements Comparable{
        public long a,b;
        public Yts1999(long a,long b,long c,long d){
            this.a=a;
            this.b=b;
        }
        public int compareTo(Object o) {
            Yts1999 to=(Yts1999)o;
            if(this.b<to.b) return 1;
            else if(this.b==to.b) return 0;
            else return -1;
        }
        public void print(){
            out.printf(" %d %d",a,b);
        }
    }
    long[] exgcd(long a, long b) {
        if (b == 0) return new long[]{1,0,a};
        long[] res = exgcd(b, a%b);
        long t = res[0]; res[0] = res[1]; res[1] = t;
        res[1] -= a/b*res[0];
        return res;
    }
    long gcd(long a,long b){
        return b==0?a:gcd(b,a%b);
    }
    long lcm(long a,long b){
        return a*b/gcd(a,b);
    }
    private void run() {
        is = local? new ByteArrayInputStream(INPUT.getBytes()):System.in;
        out = new PrintWriter(System.out);
        long s = System.currentTimeMillis();
        solve();
        out.flush();
        tr(System.currentTimeMillis()-s+"ms");
    }
    public static void main(String[] args) throws Exception { new Main().run(); }
    private byte[] inbuf = new byte[1024];
    public int lenbuf = 0, ptrbuf = 0;
    private int readByte(){
        if(lenbuf == -1)throw new InputMismatchException();
        if(ptrbuf >= lenbuf){
            ptrbuf = 0;
            try { lenbuf = is.read(inbuf); } catch (IOException e) { throw new InputMismatchException(); }
            if(lenbuf <= 0)return -1;
        }
        return inbuf[ptrbuf++];
    }
    private boolean isSpaceChar(int c) { return !(c >= 33 && c <= 126); }
    private int skip() { int b; while((b = readByte()) != -1 && isSpaceChar(b)); return b; }
    private double nd() { return Double.parseDouble(ns()); }
    private char nc() { return (char)skip(); }
    private String ns(){
        int b = skip();
        StringBuilder sb = new StringBuilder();
        while(!(isSpaceChar(b))){ // when nextLine, (isSpaceChar(b) && b != ' ')
            sb.appendCodePoint(b);
            b = readByte();
        }
        return sb.toString();
    }
    private char[] ns(int n){
        char[] buf = new char[n];
        int b = skip(), p = 0;
        while(p < n && !(isSpaceChar(b))){
            buf[p++] = (char)b;
            b = readByte();
        }
        return n == p ? buf : Arrays.copyOf(buf, p);
    }
    private char[][] nm(int n, int m){
        char[][] map = new char[n][];
        for(int i = 0;i < n;i++)map[i] = ns(m);
        return map;
    }
    private int[] na(int n){
        int[] a = new int[n];
        for(int i = 0;i < n;i++)a[i] = ni();
        return a;
    }
    private int ni(){
        int num = 0, b;
        boolean minus = false;
        while((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'));
        if(b == '-'){
            minus = true;
            b = readByte();
        }
        while(true){
            if(b >= '0' && b <= '9'){
                num = num * 10 + (b - '0');
            }else{
                return minus ? -num : num;
            }
            b = readByte();
        }
    }
    private long nl(){
        long num = 0;
        int b;
        boolean minus = false;
        while((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'));
        if(b == '-'){
            minus = true;
            b = readByte();
        }
        while(true){
            if(b >= '0' && b <= '9'){
                num = num * 10 + (b - '0');
            }else{
                return minus ? -num : num;
            }
            b = readByte();
        }
    }
    private void tr(Object... o) { if(local)System.out.println(Arrays.deepToString(o)); }
}
