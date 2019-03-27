template<typename base_type, base_type _MOD>
struct IntMod {
	static const int INVERSE_CACHE_SIZE = (1 << 18);
	static base_type MOD;
	static void set_mod(base_type new_mod) {
		MOD = new_mod;
	}
	base_type n;
	IntMod(long long d = 0) {
		n = (d >= 0 ? d % MOD : (d % MOD + MOD) % MOD);
	}
	virtual ~IntMod() = default;
	IntMod operator-() const {
		return build(n == 0 ? 0 : MOD - n);
	}
	IntMod& operator+=(IntMod a) {
		n = (n >= MOD - a.n ? n - MOD + a.n : n + a.n);
		return *this;
	}
	IntMod& operator-=(IntMod a) {
		n = (n >= a.n) ? n - a.n : n - a.n + MOD;
		return *this;
	}
	IntMod& operator*=(IntMod a) {
		*this = *this * a;
		return *this;
	}
	IntMod& operator/=(IntMod a) {
		*this = *this / a;
		return *this;
	}
	static IntMod build(base_type n) {
		IntMod r;
		r.n = n;
		return r;
	}
	static base_type inverse_cache[INVERSE_CACHE_SIZE];
	static bool inverse_cache_ready;
	friend IntMod inverse(IntMod n) {
		return build(inverse_internal(n.n));
	}
	static base_type inverse_internal(base_type n) {
		if (!inverse_cache_ready) {
			inverse_cache_ready=true;
			inverse_cache[0] = 0;
			inverse_cache[1] = 1;
			for (int n = 2; n < INVERSE_CACHE_SIZE; ++n) inverse_cache[n] = (MOD - (base_type)((long long)inverse_cache[MOD % n] * (MOD / n) % MOD));
		}
		return n < INVERSE_CACHE_SIZE ? inverse_cache[n] : MOD - (base_type)((long long)inverse_internal(MOD % n) * (MOD / n) % MOD);
	}
	friend bool operator==(IntMod a, IntMod b) {
		return a.n == b.n;
	}
	friend bool operator!=(IntMod a, IntMod b) {
		return a.n != b.n;
	}
	friend IntMod operator+(IntMod a, IntMod b) {
		return build(a.n >= MOD - b.n ? a.n - MOD + b.n : a.n + b.n);
	}
	friend IntMod operator-(IntMod a, IntMod b) {
		return build(a.n >= b.n ? a.n - b.n : a.n - b.n + MOD);
	}
	friend IntMod operator*(IntMod a, IntMod b) {
		return build(static_cast<base_type>(static_cast<long long>(a.n) * b.n % MOD));
	}
	friend IntMod operator/(IntMod a, IntMod b) {
		return a * inverse(b);
	}
	friend IntMod pow(IntMod p, long long e) {
		if (e <= 0) return IntMod(1);
		IntMod r = IntMod(1);
		while (1) {
			if (e & 1) r *= p;
			e /= 2;
			if (e) p = p * p;
			else break;
		}
		return r;
	}
	friend istream& operator>>(istream &stream, IntMod &a) {
		stream >> a.n;
		return stream;
	}
	friend ostream& operator<<(ostream &stream, const IntMod &a) {
		stream << a.n;
		return stream;
	}
};
template<typename base_type, base_type _MOD> base_type IntMod<base_type, _MOD>::inverse_cache[INVERSE_CACHE_SIZE];
template<typename base_type, base_type _MOD> bool IntMod<base_type, _MOD>::inverse_cache_ready;
template<typename base_type, base_type _MOD> base_type IntMod<base_type, _MOD>::MOD = _MOD;
using Int = IntMod<int, 998244353>;
