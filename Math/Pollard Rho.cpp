using LL=long long;
const LL NUM=10;//运算次数，Miller_Rabin算法为概率运算，误判率为2^(-NUM);
LL t,f[100];
LL mul_mod(LL a,LL b,LL n) { //求a*b%n，由于a和b太大，需要用进位乘法
// 	a=a%n;
// 	b=b%n;
// 	LL s=0;
// 	while(b) {
// 		if(b&1)
// 			s=(s+a)%n;
// 		a=(a<<1)%n;
// 		b=b>>1;
// 	}
// 	return s;
	return (__int128_t)a*b%n;
}
LL pow_mod(LL a,LL b,LL n) { //求a^b%n
	a=a%n;
	LL s=1;
	while(b) {
		if(b&1)
			s=mul_mod(s,a,n);
		a=mul_mod(a,a,n);
		b=b>>1;
	}
	return s;
}
bool check(LL a,LL n,LL r,LL s) {
	LL ans,p,i;
	ans=pow_mod(a,r,n);
	p=ans;
	for(i=1; i<=s; i++) {
		ans=mul_mod(ans,ans,n);
		if(ans==1&&p!=1&&p!=n-1)return true;
		p=ans;
	}
	if(ans!=1)return true;
	return false;
}
bool Miller_Rabin(LL n) { //Miller_Rabin算法，判断n是否为素数
	if(n<2)return false;
	if(n==2)return true;
	if(!(n&1))return false;
	LL i,r,s,a;
	r=n-1;
	s=0;
	while(!(r&1)) {
		r=r>>1;
		s++;
	}
	for(i=0; i<NUM; i++) {
		a=rand()%(n-1)+1;
		if(check(a,n,r,s))
			return false;
	}
	return true;
}
LL Pollard_rho(LL n,LL c) { //Pollard_rho算法，找出n的因子
	LL i=1,k=2,x,y,d,p;
	x=rand()%n;
	y=x;
	while(true) {
		i++;
		x=(mul_mod(x,x,n)+c)%n;
		if(y==x)return n;
		if(y>x)p=y-x;
		else p=x-y;
		d=__gcd(p,n);
		if(d!=1&&d!=n)return d;
		if(i==k) {
			y=x;
			k+=k;
		}
	}
}
void find(LL n) { //找出n的所有因子
	if(Miller_Rabin(n)) {
		f[t++]=n;//保存所有因子
		return;
	}
	LL p=n;
	while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);//由于p必定为合数，所以通过多次求解必定能求得答案
	find(p);
	find(n/p);
}
void gao(LL n) {//gogogogo
	t=0;
	if(n==1) {
		f[0]=1;
		t=1;
	} else {
		find (n);
		sort(f,f+t);
	}
}
