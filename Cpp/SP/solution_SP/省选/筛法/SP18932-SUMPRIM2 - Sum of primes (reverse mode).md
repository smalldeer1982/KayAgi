# SUMPRIM2 - Sum of primes (reverse mode)

## 题目描述

XerK had prepared his new problem with some sums of primes up to some bounds. His results are well here, but he forgot the bounds. Your task is to find which was the last prime in the sum. This problem is extremely simple, but you have to be extremely fast.

# 题解

## 作者：Leasier (赞：3)

前置芝士：[Meissel-Lehmer 算法](https://oi-wiki.org/math/number-theory/meissel-lehmer/)、[区间筛](https://oi-wiki.org/math/number-theory/sieve/#_6)

考虑二分答案，则我们所需的就是求出前缀质数和。这可以用 Meissel-Lehmer 算法解决。

但显然不能直接二分，所以我们可以每隔 $10^9$ 打表，则二分区间大小降至 $10^9$。

但~~显然~~还是不能直接做，所以我们可以在 $r - l \leq 2 \times 10^7$ 时停止并直接区间筛。

~~时间复杂度不会算。~~

代码：
```cpp
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;
typedef __uint128_t ulll;

typedef struct Division_tag {
	ulll a;
	ull b;
	Division_tag(){}
	Division_tag(ull b_){
		b = b_;
		a = (((ulll)1 << 64) + b - 1) / b;
	}
} Division;

const int N = 1270608 + 7, M = 2e7 + 7, K = 50, P = 2 * 3 * 5 * 7 * 11 * 13 * 17, Q = 7, R = 2e6 + 7, S = 1e3 - 1;
int sqrt_n, id, tm = 0;
ll cur_n;
int prime[N], lpf[M], pi[M], pre_phi0[K + 7][P + 7], product[Q + 7], vis[R];
ll prime_sum_list[M], prime_pow2[N], prime_pow3[N], _prime_sum_list[N], pre_phi1[K + 7][P + 7];
lll pre[N], big_prime_sum_list[R];
const char *table[S + 7] = {...};
bool p[M];
Division inv_prime[N], inv_product[Q + 7];

ull operator /(const ull &a, const Division &b){
	return a * b.a >> 64;
}

ull operator %(const ull &a, const Division &b){
	return a - b.b * (a * b.a >> 64);
}

inline ll sum1(int n){
	return (ll)n * (n + 1) / 2;
}

inline void init1(){
	int cnt = 0;
	ll sum = 0;
	p[0] = p[1] = true;
	pi[1] = 0;
	prime_sum_list[1] = 0;
	for (register int i = 2; i < M; i++){
		if (!p[i]){
			cnt++;
			prime[cnt] = i;
			prime_pow2[cnt] = (ll)i * i;
			prime_pow3[cnt] = prime_pow2[cnt] * i;
			inv_prime[cnt] = Division(i);
			sum += i;
			_prime_sum_list[cnt] = sum;
		}
		pi[i] = cnt;
		prime_sum_list[i] = sum;
		for (register int j = 1; j <= cnt && i * prime[j] < M; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i <= cnt; i++){
		pre[i] = pre[i - 1] + prime[i] * _prime_sum_list[i - 1];
	}
	for (register int i = 1; i <= P; i++){
		pre_phi0[0][i] = i;
		pre_phi1[0][i] = sum1(i);
	}
	for (register int i = 1; i <= K; i++){
		int id = i - 1;
		for (register int j = 1; j <= P; j++){
			int t = j / inv_prime[i];
			pre_phi0[i][j] = pre_phi0[id][j] - pre_phi0[id][t];
			pre_phi1[i][j] = pre_phi1[id][j] - prime[i] * pre_phi1[id][t];
		}
	}
	product[0] = 1;
	for (register int i = 1; i <= Q; i++){
		product[i] = product[i - 1] * prime[i];
		inv_product[i] = Division(product[i]);
	}
}

inline ll sqrt(ll n){
	ll ans = sqrt((double)n);
	while (ans * ans <= n) ans++;
	return ans - 1;
}

inline void init2(ll n){
	sqrt_n = sqrt(n);
	cur_n = n;
	if ((ll)sqrt_n * sqrt_n == n){
		id = sqrt_n * 2 - 1;
	} else {
		id = sqrt_n * 2;
	}
	tm++;
}

inline lll read(){
	lll ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline lll convert(const char *s){
	int len = strlen(s);
	lll ans = 0;
	for (register int i = 0; i < len; i++){
		ans = ans * 10 + (s[i] - '0');
	}
	return ans;
}

inline int get_id(ll n){
	return n <= sqrt_n ? id - n + 1 : cur_n / n;
}

inline ll cbrt(ll n){
	ll ans = cbrt((double)n);
	while (ans * ans * ans <= n) ans++;
	return ans - 1;
}

inline lll sum1(ll n){
	return (lll)n * (n + 1) / 2;
}

lll prime_sum(ll n);

inline lll p2(ll n, int m){
	int a = pi[sqrt(n)];
	lll ans = pre[m] - pre[a];
	for (register int i = m + 1; i <= a; i++){
		ans += prime[i] * prime_sum(n / inv_prime[i]);
	}
	return ans;
}

lll phi(ll n, int m){
	if (n == 0) return 0;
	if (m == 0) return sum1(n);
	if (n <= P && m <= K) return pre_phi1[m][n];
	if (m <= Q){
		ll t1 = n / inv_product[m], t2 = n % inv_product[m];
		return (ll)product[m] * pre_phi0[m][product[m]] * sum1(t1 - 1) + (lll)t1 * pre_phi1[m][product[m]] + (lll)t1 * product[m] * pre_phi0[m][t2] + pre_phi1[m][t2];
	}
	if (n < prime_pow2[m]) return prime_sum(n) - _prime_sum_list[m] + 1;
	if (n < prime_pow3[m]) return prime_sum(n) + p2(n, m) - _prime_sum_list[m] + 1;
	return phi(n, m - 1) - prime[m] * phi(n / inv_prime[m], m - 1);
}

lll prime_sum(ll n){
	if (n < M) return prime_sum_list[n];
	int id = get_id(n);
	if (vis[id] == tm) return big_prime_sum_list[id];
	int a = pi[cbrt(n)];
	vis[id] = tm;
	return big_prime_sum_list[id] = phi(n, a) - p2(n, a) + _prime_sum_list[a] - 1;
}

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

inline ll solve(ll l, ll r, lll sum, lll s){
	if (sum == s) return l - 1;
	int cnt = pi[sqrt(r)];
	ll t = r - l;
	for (register ll i = 0; i <= t; i++){
		p[i] = false;
	}
	if (l == 1) p[0] = true;
	for (register int i = 1; i <= cnt; i++){
		for (register ll j = prime[i] * max((l - 1) / prime[i] + 1, prime[i]); j <= r; j += prime[i]){
			p[j - l] = true;
		}
	}
	for (register ll i = l; i <= r; i++){
		if (!p[i - l]){
			sum += i;
			if (sum == s) return i;
		}
	}
}

int main(){
	int t = 0;
	ll l, r;
	lll s = read();
	init1();
	while (t < S && convert(table[t + 1]) < s) t++;
	l = t * 1e9;
	r = 1e9 * (t + 1) - 1;
	while (r - l >= M){
		ll mid = (l + r) >> 1;
		init2(mid);
		if (prime_sum(mid) >= s){
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	init2(l);
	printf("%lld", solve(l + 1, r, prime_sum(l), s));
	return 0;
}
```

---

## 作者：Argon_Cube (赞：1)

来一个不用二分的做法。

首先我们可以 Meissel-Lehmer 然后二分。但是我们发现这个题数据范围大得离谱，然后太多次 Meissel-Lehmer 过不去，所以我们需要分段打表，然后在二分区间长度小于 $2\times10^7$ 时直接区间筛。一般来说一段的长度为 $10^9$。

但是我们不会 Meissel-Lehmer，那么我们就考虑直接跳过二分，将区间筛加上 Wheel Factorization 优化即可在三秒之内筛完 $10^9$ 长度的区间从而通过。

但是我们不会卡常，所以我们就改成每 $4\times 10^8$ 个数分一段，这样时间上就差不多可以通过了。

然后我们发现源码长度限制 $5\times10^4\text{ Bytes}$，表太长了交不上去。那么我们就把每个数写成 $64$ 进制，这样每个数从 $22$ 位就变成了 $12$ 位，然后你去 SPOJ 上一交，过了。

但是洛谷 RemoteJudge 最大码长只有 $2^{15}\text{ Bytes}$，你还是交不上去。

这个时候我们发现好像后面每个数的第一位都差不多相同，那么我们对这个表做差分，发现还是太长了，那么我们再做一次差分，这个时候你就得到了一个大约 $30\text{ KB}$ 的表（注意第二次差分可能出现负数），此时我们发现主程序太长了，于是就用代码压行器把主程序的空格全部删掉。

这个时候你的码长应该就压进合法范围了（我的是 $31.96\text{ KB}$），交一发就可以过了。

---

