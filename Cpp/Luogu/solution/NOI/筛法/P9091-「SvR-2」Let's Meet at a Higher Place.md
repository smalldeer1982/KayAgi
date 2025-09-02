# 「SvR-2」Let's Meet at a Higher Place

## 题目背景

$$「有朝一日，让我们相逢在更高处！」$$

## 题目描述

构造一个长为 $m$ 的整数序列 $a$，使 $\forall 1 \leq i \leq m$，$a_i \in [1, n]$。

求出其前缀 $\gcd$，记为整数序列 $b$。

$f(n, m, k)$ 的值为可以通过如上方式构造出的 $b$ 序列中**相邻项相等的情况出现次数 $\leq k$** 的**不同**的 $b$ 序列的个数。

给定正整数 $n, m$，小 L 请你帮他求出 $\displaystyle\sum_{i = 1}^n \sum_{j = 1}^m \sum_{k = 0}^{j - 1} f(\lfloor \frac{n}{i} \rfloor, j, k)$ 的值。

由于结果可能很大，所以你只需要求出结果对 $2^{32}$ 取模的值。

## 说明/提示

| $\bf{Subtask}$ | $n$ | $m$ | 分值 |
| :------: | :------: | :------: | :------: |
| $1$ | $1 \leq n \leq 10^4$ | 无特殊限制 | $10 \operatorname{pts}$ |
| $2$ | $1 \leq n \leq 10^6$ | 同上 | $20 \operatorname{pts}$ |
| $3$ | $1 \leq n \leq 10^9$ | 同上 | $20 \operatorname{pts}$ |
| $4$ | 无特殊限制 | $1 \leq m \leq 25$ | $20 \operatorname{pts}$ |
| $5$ | 同上 | 无特殊限制 | $30 \operatorname{pts}$ |

对于 $100\%$ 的数据，$1 \leq n \leq 10^{10}$，$1 \leq m \leq 34$。

## 样例 #1

### 输入

```
4 2```

### 输出

```
26```

# 题解

## 作者：渐变色 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P9091)

### 前言

尝试介绍下一种容易实现且常数很小的积性函数求和法。

### Solution

式子的推导请见出题人 Leasier 的[题解](https://www.luogu.com.cn/blog/Leasier/solution-P9091)，进一步转化后得到原式 $=mS_{I_{m+1}}(n)$，其中 $I_n$ 表示 $I*I\,*···*\,I$ (卷 $n$ 次)，为积性函数。

对于积性函数 $f$，构造 $g$ 满足 $g(p^k)=f(p)^k$，则 $f=g*h$，易得 $h(p^k)=f(p^k)-f(p)f(p^{k-1})$。因此我们可以先算较容易求出的 $g$，再借助 $PN$ 得到 $f$。

回忆一下 min_25 筛的第一部分，$g$ 为满足 $g(p^k)=g(p)^k$ 的任一积性函数，令 $S(n, a)=\sum\limits_{i=1}^{n}[min_i>p_a \,or\;i\in P]\,g(i)$，有 :
$$S(n,a)=S(n,a-1)-g(p_a)(S(\frac{n}{p_a},a-1)-S(p_{a-1},a-1))$$

那么其实它也能写成这样 :
$$S(n,a-1)=S(n,a)+g(p_a)(S(\frac{n}{p_a},a-1)-S(p_{a-1},a-1))$$

也就是说对于我们要求的 $g$，我们只需先求出其在素数处的和（即得到 $S(m,\pi(\sqrt{n}))$，$m=\left\lfloor\dfrac{n}{i}\right\rfloor$，$i=1,2,···,\sqrt{n}$），便可通过后一式得到 $g$ 的块筛。

之后就可以在 $O(\sqrt n)$ 内得到 $S_f(n)$，或在 $O(\sqrt{n}\log^{1+\varepsilon} n)$ 内得到 $f$ 的块筛。

### 实现

远古代码直接粘贴过来了，欠佳。
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#include <time.h>
#include <fstream>
using namespace std;
using u32 = unsigned int;
using u64 = unsigned long long;
using i64 = long long;
double inv[100005];
u32 c[70][70];
vector<int> primes;
u32 solve(i64 N, u32 k) {
	int v = log2(N) + k;
	
	const auto div = [&](i64 n, int d) -> i64 {return n * inv[d]; };
	k++;
	v = sqrt(N + 0.5);
	for (int i = 1; i <= v; ++i) inv[i] = 1.0 / i * (1 + 1e-15);
	vector<u32> s(v + 1), l(v + 1);
	for (int i = 1; i <= v; ++i) s[i] = i - 1, l[i] = div(N, i) - 1;
	for (int p = 2; p <= v; ++p)
		if (s[p] != s[p - 1]) {
			primes.push_back(p);
			i64 q = i64(p) * p, M = div(N, p);
			u32 t0 = s[p - 1];
			int t = v / p, u = min<i64>(v, div(M, p));
			for (int i = 1; i <= t; ++i) l[i] -= l[i * p] - t0;
			for (int i = t + 1; i <= u; ++i) l[i] -= s[div(M, i)] - t0;
			for (int i = v, j = t; j >= p; --j)
				for (int l = j * p; i >= l; --i)
					s[i] -= s[j] - t0;
		}
	for (int i = 1; i <= v; ++i) s[i] *= k, l[i] *= k;
	for (auto it = primes.rbegin(); it != primes.rend(); ++it) {
		int p = *it;
		i64 q = i64(p) * p, M = div(N, p);
		int t = v / p, u = min<i64>(v, div(M, p));
		u32 t0 = s[p - 1];
		if(q <= v) {
			u32 s0 = k * k;
			for (int j = p, i = q; j < t; s0 = (s[++j] - t0) * k)
				for (int l = j * p + p; i < l; ++i) s[i] += s0;
			for (int i = t * p; i <= v; ++i) s[i] += s0;
		}
		for (int i = u; i > t; --i) l[i] += (s[div(M, i)] - t0) * k;
		for (int i = t; i >= 1; --i) l[i] += (l[i * p] - t0) * k;
	}
	for (int i = 1; i <= v; ++i) s[i] += 1, l[i] += 1;
	
	k--;
	const auto divide = [](i64 n, i64 d) -> i64 {return double(n) / d; };
	function< u32(i64, int, u32)> rec = [&] (i64 n, size_t beg, u32 coeff) -> u32 {
		if (!coeff) return 0;
		u32 ret = coeff * (n > v ? l[divide(N, n)] : s[n]);
		for (size_t i = beg; i < primes.size(); ++i) {
			int p = primes[i];
			i64 q = i64(p) * p;
			if (q > n) break;
			i64 nn = divide(n, q);
			for (u32 e = 1; nn; nn = div(nn, p), ++e)
				ret += rec(nn, i + 1, -coeff * e * c[e + k][e + 1]);
		}
		return ret;
	};
	return k * rec(N, 0, 1);
}
int main() {
	i64 N;
	u32 k;
	cin >> N >> k;
	cout << solve(N, k);
	return 0;
}
```


---

## 作者：Leasier (赞：4)

~~令人遗憾的是本题唯一赛时通过者 @[Silver187](https://www.luogu.com.cn/user/154560) 写的是经过大力卡常后的算法三。~~

------------

### 算法一
容易发现前缀 $\gcd$ 的限制相当于 $\forall 2 \leq i \leq m, b_i \mid b_{i - 1}$。

枚举 $b_1$ 后记忆化搜索即可。时间复杂度为 $O(nm^2 \log n)$，可以通过 $\text{Subtask } 1$。
### 算法二
考虑 $f(n, m, k)$ 中相邻项相等出现的次数的限制实际上相当于钦定某些项，使之与后一项相等，于是我们设 $g(n, m)$ 表示以 $n$ 结尾的合法的 $m$ 项的方案数，则 $f(n, m, 0) = \displaystyle\sum_{i = 1}^n g(i, m)$。

接下来考虑 $g(n, m)$，显然可以容斥。我们希望求的是**恰好**有 $0$ 个 $1 \leq i < m, b_i = b_{i + 1}$ 的方案数，通过容斥我们可以将其转化为**至少**有 $k$ 个 $1 \leq i < m, b_i = b_{i + 1}$ 的方案数。

考虑钦定其中 $k$ 项与后一项相同，方案数是 $C_{m - 1}^k$（因为不能钦定最后一项）；对于余下的项，其可以选择与后一项相同，也可以不同，且每一项一定是后一项的因数，方案数是 $I_{m - k}(b_m)$。于是我们可以得到 $g(n, m) = \displaystyle\sum_{i = 0}^{m - 1} (-1)^i C_{m - 1}^i I_{m - i}(n)$。

注意到 $f(n, m, k) = \displaystyle\sum_{i = 0}^k C_{m - 1}^i f(n, m - i, 0)$，令 $S_f(n) = \displaystyle\sum_{i = 1}^n f(i)$，则 $f(n, m, k) = \displaystyle\sum_{i = 0}^k C_{m - 1}^i \sum_{j = 1}^n \sum_{x = 0}^{m - i - 1} (-1)^x C_{m - i - 1}^x I_{m - i - x}(j) = \sum_{i = 0}^k C_{m - 1}^i \sum_{x = 0}^{m - i - 1} (-1)^x C_{m - i - 1}^x S_{I_{m - i - x}}(n)$。

原式 $= \displaystyle\sum_{i = 1}^n \sum_{j = 1}^m \sum_{k = 0}^{j - 1} \sum_{l = 0}^k C_{j - 1}^l \sum_{x = 0}^{j - l - 1} (-1)^x C_{j - l - 1}^x S_{I_{j - l - x}}(\lfloor \frac{n}{i} \rfloor)$

$ = \displaystyle\sum_{i = 1}^n \sum_{j = 1}^m \sum_{k = 0}^{j - 1} \sum_{l = 0}^k C_{j - 1}^l \sum_{x = 0}^{j - l - 1} (-1)^x C_{j - l - 1}^{j - l - x - 1} S_{I_{j - l - x}}(\lfloor \frac{n}{i} \rfloor)$

注意到我们可以直接枚举 $T = l + x$，有：

原式 $= \displaystyle\sum_{i = 1}^n \sum_{j = 1}^m \sum_{T = 0}^{j - 1} S_{I_{j - T}}(\lfloor \frac{n}{i} \rfloor) \sum_{l = 0}^T (-1)^{T - l} C_{j - 1}^l C_{j - l - 1}^{T - l} \sum_{k = l}^{j - 1} 1$

$ = \displaystyle\sum_{i = 1}^n \sum_{j = 1}^m \sum_{T = 0}^{j - 1} S_{I_{j - T}}(\lfloor \frac{n}{i} \rfloor) \sum_{l = 0}^T (-1)^{T - l} (j - l) C_{j - 1}^l C_{j - l - 1}^{T - l}$

注意到最后一个求和符号的结果只与 $j, T$ 有关且 $m$ 很小，于是令 $g_{n, m} = \displaystyle\sum_{i = 0}^m (-1)^{m - i} (n - i) C_{n - 1}^i C_{n - i - 1}^{m - i}$，则可以在 $O(m^3)$ 的时间复杂度内预处理出。

原式 $= \displaystyle\sum_{i = 1}^n \sum_{j = 1}^m \sum_{T = 0}^{j - 1} g_{j, T} S_{I_{j - T}}(\lfloor \frac{n}{i} \rfloor)$

注意到我们可以直接枚举 $U = j - T$，有：

$ = \displaystyle\sum_{i = 1}^n \sum_{U = 1}^m S_{I_U}(\lfloor \frac{n}{i} \rfloor) \sum_{T = 0}^{m - U} g_{T + U, T}$

注意到最后一个求和符号的值只与 $T$ 有关，于是令 $h_n = \displaystyle\sum_{i = 0}^{m - n} g_{n + i, i}$，则可以在 $O(m^2)$ 的时间复杂度内预处理出。

原式 $= \displaystyle\sum_{i = 1}^n \sum_{U = 1}^m h_U S_{I_U}(\lfloor \frac{n}{i} \rfloor)$

线性筛所有 $I_i$ 即可。时间复杂度为 $O(nm + m^3)$，可以通过 $\text{Subtask } 1, 2$。
### 算法三
事实上我们只需要对于 $\forall 1 \leq i \leq m$，求出 $I_i$ 的块筛。

数论分块 + 根号分治或递推版 Min_25 筛求解即可。时间复杂度为 $O(mn^{\frac{2}{3}} + m^3)$ 或 $O(\frac{mn^{\frac{3}{4}}}{\ln n} + m^3)$，可以通过 $\text{Subtask } 1 \sim 3$。实现常数足够优秀还可以通过 $\text{Subtask } 4$。 
### 算法四
考虑 $I_i$ 在质数处的表现，我们发现 $\forall p \in \operatorname{Prime}$，$I_i(p)$ 的值**与 $p$ 具体是多少无关**。

于是不难想到 Powerful Number 筛。构造 $I_i'(p^k) = [k \leq 1] I_i(p^k)$，现在问题转变为求出 $I_i'$ 的块筛。

显然可以算贡献，可得：$S_{I_i'}(n) = \displaystyle\sum_{i = 0} I_i'(p)^i \sum_{j = 1}^n [\omega(j) = i] \mu^2(j)$，其中 $p$ 为任意质数。后半部分显然可以用类似 Min_25 筛 Part 1 的方法求出，因为 $\displaystyle\max_{i = 1}^n w(i) = O(\frac{\ln n}{\ln \ln n})$，则时间复杂度为 $O(\frac{n^{\frac{3}{4}}}{\ln \ln n})$，进而可以在 $O(\frac{m \sqrt{n} \ln n}{\ln \ln n})$ 的时间复杂度内求出块筛。

但如果此时直接像杜教筛一样根号分治，块筛部分的时间复杂度为 $O(\frac{n^{\frac{3}{4}}}{\ln \ln n} + mn^{\frac{2}{3}})$，不能通过。

考虑 Powerful Number 的性质。对于 $\lfloor \frac{n}{i} \rfloor$，当 $i \leq \sqrt[3]{n}$，显然只有 $O(\sqrt[3]{n})$ 种值；当 $i > \sqrt[3]{n}$，$\lfloor \frac{n}{i} \rfloor < n^{\frac{2}{3}}$，所以只有 $\sqrt{n^{\frac{2}{3}}} = O(\sqrt[3]{n})$ 种值。据此我们可以通过根号分治将单次求块筛的时间复杂度优化至 $O(n^{\frac{3}{5}})$。

时间复杂度为 $O(\frac{n^{\frac{3}{4}}}{\ln \ln n} + mn^{\frac{3}{5}} + m^3)$，可以通过所有数据，若实现常数过大将无法通过 $\text{Subtask } 5$。
### 算法五
感谢 @[渐变色](https://www.luogu.com.cn/user/224584) 提供本部分做法。

注意到 $h_i = [i = m] m$（具体证明略去），则原式 $= m \displaystyle\sum_{i = 1}^n S_{I_m}(\lfloor \frac{n}{i} \rfloor) = m S_{I_{m + 1}}(n)$。

于是我们只需要求 $S_{I_{m + 1}}(n)$。可以直接采用上述方法，并还可以在 $O(m \sqrt{n})$ 的时间复杂度对于 $1 \sim m$ 求解答案。

时间复杂度为 $O(m \log n + \frac{n^{\frac{3}{4}}}{\ln \ln n})$。

~~其实可以出加强版，但是懒得出了（~~

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;
typedef __uint128_t ulll;

typedef struct Division_tag {
	ulll a;
	Division_tag(){}
	Division_tag(ull mod){
		a = (((ulll)1 << 64) + mod - 1) / mod;
	}
} Division;

const int N = 1e5 + 7, M = 2e5 + 7, K = 67 + 7, P = 33 + 7, Q = 10 + 7;
int sqrt_n, prime_cnt = 0, id = 0;
ll cur_n;
int prime[N], max_prime_cnt[M];
uint c[K][P], g[M], h[Q][M], prime_power[P];
ll number[M];
bool p[N];
Division inv_prime[N];

ull operator /(const ull &a, const Division &b){
	return a * b.a >> 64;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline int log2(ll n){
    int ans = log2((double)n);
    while ((1ll << ans) <= n) ans++;
    return ans - 1;
}

inline int get_max_prime_cnt(ll n, int cnt){
    int ans = 0;
    for (register ll i = 1; i <= n && ans <= cnt; i *= prime[ans]) ans++;
    return ans - 1;
}

inline int divide(ll x, ll y){
	return 1.0 * x / y;
}

inline int get_id(ll n){
	return n <= sqrt_n ? id - n + 1 : divide(cur_n, n);
}

inline void init(ll n, int m){
	int up1 = log2(n), up2 = up1 + m - 1;
	sqrt_n = sqrt(n);
	cur_n = n;
	c[0][0] = 1;
	for (register int i = 1; i <= up2; i++){
		int t = min(i, up1);
		c[i][0] = 1;
		for (register int j = 1; j <= t; j++){
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
		}
	}
	p[0] = p[1] = true;
	for (register int i = 2; i <= sqrt_n; i++){
		if (!p[i]){
			prime_cnt++;
			prime[prime_cnt] = i;
			inv_prime[prime_cnt] = Division(i);
		}
		for (register int j = 1; j <= prime_cnt && i * prime[j] <= sqrt_n; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (register ll i = 1, j; i <= n; i = j + 1){
		ll tn = n / i;
		j = n / tn;
		id++;
		number[id] = tn;
		max_prime_cnt[id] = get_max_prime_cnt(tn, prime_cnt);
		g[id] = tn - 1;
	}
	for (register int i = 1; i <= prime_cnt; i++){
		ll t = 1ll * prime[i] * prime[i];
		for (register int j = 1; j <= id && number[j] >= t; j++){
			g[j] -= g[get_id(number[j] / inv_prime[i])] - (i - 1);
		}
	}
	for (register int i = 1; i <= id; i++){
		h[0][i] = 1;
		h[1][i] = g[i];
	}
	for (register int i = prime_cnt; i >= 1; i--){
		ll t1 = 1ll * prime[i] * prime[i];
		for (register int j = 1; j <= id && number[j] >= t1; j++){
			int cur_id = get_id(number[j] / inv_prime[i]), t2 = max_prime_cnt[j];
			h[2][j] -= i;
			for (register int k = 2; k <= t2; k++){
				h[k][j] += h[k - 1][cur_id];
			}
		}
	}
}

inline uint get_f__sum(ll n, int m){
	int id = get_id(n);
	uint ans = 0;
	for (register int i = max_prime_cnt[id]; i >= 0; i--){
		ans = ans * m + h[i][id];
	}
	return ans;
}

uint get_f_sum(int cur, int m, ll val1, uint val2){
	uint ans = val2 * get_f__sum(cur_n / val1, m);
	for (register int i = cur + 1; i <= prime_cnt && (lll)val1 * prime[i] * prime[i] <= cur_n; i++){
		int j = 2;
		for (register ll x = val1 * prime[i] * prime[i]; x <= cur_n; j++, x *= prime[i]){
			ans += get_f_sum(i, m, x, val2 * prime_power[j]);
		}
	}
	return ans;
}

int main(){
	int m, mi;
	ll n;
	scanf("%lld %d", &n, &m);
	mi = m + 1;
	init(n, mi);
	prime_power[0] = 1;
	for (register int i = 1; (1ll << i) <= n; i++){
		prime_power[i] = c[i + m][i] - mi * prime_power[i - 1];
	}
	printf("%u", m * get_f_sum(0, mi, 1, 1));
	return 0;
}
```

---

## 作者：forgive_ (赞：3)

提供一种推式子的想法。

考虑怎么刻画 $b$ 序列的样子，可以看成有若干段数，且后一段的值需要是前一段的因子，同时 $b_1\leq n$。

假设填了 $p$ 段，那么有 $p-1$ 个位置相邻项相等，在枚举 $k$ 的过程中，这种方案一共会被统计 $p$ 次，权值就是 $p$。

先考虑选哪些数，设 $d_{n,p}$ 表示在值域 $[1,n]$ 范围内选出 $p$ 个数，这些数排好序后需要满足 后一项是前一项的 **真倍数**，不能相等。

再考虑给它们排顺序，根据插板法，在 $j$ 个位置中安排 $p$ 种数的方案是 $C_{j-1}^{p-1}$。

那么我们可以写出最朴素的式子：
$$ans=\sum_{i=1}^n \sum_{j=1}^m \sum_{p=1}^j p\times C_{j-1}^{p-1}\times d_{\lfloor\frac{n}{i}\rfloor,p}$$

含 $j$ 的比较少，放到最后枚举：

$=\sum\limits_{i=1}^{n} \sum\limits_{p=1}^m d_{\lfloor\frac{n}{i}\rfloor,p}\times p \sum\limits_{j=p}^mC_{j-1}^{p-1}$

$=\sum\limits_{i=1}^{n} \sum\limits_{p=1}^m d_{\lfloor\frac{n}{i}\rfloor,p}\times p \times C_{m}^p$

根据吸收恒等式，把 $p$ 去掉：

$=m\sum\limits_{i=1}^n \sum\limits_{p=1}^mC_{m-1}^{p-1}\times d_{\lfloor\frac{n}{i}\rfloor,p}$

化不动了，想想怎么求 $d$。

朴素的想法是 $f_{i,j}$ 表示选了 $i$ 个数，最大的是 $j$，复杂度过高，无法接受。

直接分析求 $d_{n,p}$ 的过程：在 $[1,n]$ 中选出第一个数 $x_1$，接下来选 $x_1$ 的倍数，枚举倍数可以等价于在 $[2,\lfloor\frac{n}{x_1}\rfloor]$ 中选第二个数 $x_2$ ( 从 $2$ 开始是因为第一个就是 $x_1$ )。

写成式子：

$$d_{n,p}=\sum_{x_1=1}^n \sum_{x_2=2}^{\lfloor\frac{n}{x_1}\rfloor} \sum_{x_3=2}^{\lfloor\frac{n}{x_1x_2}\rfloor}...\sum_{x_p=2}^{\lfloor\frac{n}{x_1x_2..x_{p-1}}\rfloor}1$$

我们先考虑一个和它比较相似的式子：

$$h_{n,p}=\sum_{x_1=1}^n \sum_{x_2=1}^{\lfloor\frac{n}{x_1}\rfloor} \sum_{x_3=1}^{\lfloor\frac{n}{x_1x_2}\rfloor}...\sum_{x_p=1}^{\lfloor\frac{n}{x_1x_2..x_{p-1}}\rfloor}1$$

从另一个角度看，$h_{n,p}$ 可以看作 **选 $p$ 个数，使之乘积小于等于 $n$ 的数对个数**。

小于等于 $n$ 可以转化为 等于 $n$ 的前缀和，若干个数乘积等于 $n$？

考虑一个函数 $I^{p}$，意思是 $p$ 个恒等 $1$ 函数的狄利克雷卷积，那么:

$$I^p(n)=\sum_{d_1|n}\sum_{d_2|\frac{n}{d_1}}...\sum_{d_{p-1}|\frac{n}{d_1...d_{p-2}}}1$$

没错，它在 $n$ 处的函数值正是 **$p$ 个数乘积等于 $n$ 的数对个数**。

$h_{n,p}=\sum_{i=1}^nI^p(i)$

有了它怎么求 $d$ 呢？

把 $d$ 和前面的组合数放到一起看，前面的 $i$ 先不管：

$\sum_{p=1}^m C_{m-1}^{p-1}\times d_{\lfloor\frac{n}{i}\rfloor,p}$

$=\sum_{p=0}^{m-1} C_{m-1}^p \times d_{\lfloor\frac{n}{i}\rfloor,p+1}$

这个求和可以看成，我们一共要选出 $m$ 个数，每相邻两个数之间有一个“关系”，要么后一个是前一个的 **真倍数**，要么和前一个相等。

枚举 $m-1$ 个关系中的 $p$ 个，钦定这些“关系”为 **真倍数**，那么接下来 $m$ 个数会被这 $p$ 个关系划分成 $p+1$ 段，每段中数都相等，所以要在值域中选出 $p+1$ 个不同的数填进去。

**$p$ 从 $0$ 到 $m-1$ 求和，恰好枚举了所有情况**，所以上式等于：

$$h_{{\lfloor\frac{n}{i}\rfloor},m}$$

$ans=m\sum_{i=1}^{n}h_{\lfloor\frac{n}{i}\rfloor,m}$

这个求和看成是多选了一个数 $i$

$=m\times h_{n,m+1}$

$=m\sum_{i=1}^nI^{m+1}(i)$

优雅，太优雅了！

使用 Min_25 筛来求 $I^{m+1}$ 的前缀和，复杂度 $O(\frac{n^{\frac{3}{4}}}{\ln n})$

---

## 作者：ForgotMe (赞：3)

显然如果知道 $b$ 序列中不同的数的个数，就可以算出 $b$ 序列中相邻项相等的情况出现次数。可以注意到 $b_1=a_1$，不如枚举 $b_1=x$，那么后面的方案数的计算只跟 $x$ 有关。

不如设 $h(x,L)$ 表示长度为 $L$ 且满足 $b_1=x$，元素两两不同的 $b$ 序列个数。

那么就可以转化一下答案，先不管那个 $\lfloor\frac{n}{i}\rfloor$，这个可以通过整除分块一下就处理掉了。

$$
f(n,m)=\sum_{i=1}^n \sum_{L=1}^m \binom{m-1}{L-1}\times L \times h(i,L)
$$

其中那个组合数系数是经典的盒子放球问题，乘上 $L$ 是因为题目中要求的答案里枚举了 $k$。

如何快速计算 $h$ 呢？考虑求前缀 $\gcd$ 在对于一个质数来看是求其指数的前缀 $\min$，于是可以想到对 $x$ 先唯一分解，$x=\prod_{i=1}^k p_i^{\alpha_i}$ 可以发现 $h$ 只跟质数头上的指数有关，不如直接把指数拿下来记成一个 $k$ 元组 $P$。

$h(x,L)$ 则可以写为满足下列条件的 $c$ 序列（注意 $c$ 序列中的元素都是代表一个 $k$ 元组）个数：

- $c_1=P$。

- $\forall 2\le i\le L$，$\forall 1\le j\le k$，$c_{i,j}\le c_{i-1,j}$，且满足 $\exists 1\le j\le k$，$c_{i,j}\lt c_{i-1,j}$。

注意到如果说没有 $\exists 1\le j\le k$，$c_{i,j}\lt c_{i-1,j}$ 这个要求，这个东西是非常好算的，因为每一维是独立的。

不如考虑容斥，设 $h_2(x,L)$ 表示只满足 $c_1=P$，$\forall 2\le i\le L$，$\forall 1\le j\le k$，$c_{i,j}\le c_{i-1,j}$ 这两个条件的 $c$ 序列个数。

可以发现 $h_2$ 与 $h$ 的如下关系。

$$
h_2(x,L)=\sum_{i=1}^L h(x,i)\binom{L-1}{i-1}
$$

那么如果可以快速算出 $h_2$ 就可以解决掉这个问题了。

因为每一维独立，显然 $h_2(x,L)$ 是一个积性函数，$h_2(x,L)=\prod_{i=1}^k G(\alpha_i,L)$，其中 $G$ 可以通过 DP 或者组合数学预处理出来。

做 $m$ 次递推版 min_25 即可，复杂度 $\mathcal{O}(m\frac{n^{\frac{3}{4}}}{\log n})$，如果常数卡得好就可以通过此题 ~~（还可以碾压 std）~~。

有下列卡常技巧：

- 不要单独做 $m$ 次 min_25，因为 min_25 中存在大量向下整除运算求编号，非常的慢，可以开一个 $m\times \sqrt{n}$ 的 DP 数组，在最里面一起转移。

- DP 数组的第一维要开成 $\sqrt{n}$ 的大小，因为 $L$ 这一维是连续访问的，这样子会快很多。


但是还可以优化，注意到 $h_2(p,L)=L$，考虑 Powerful Number，构造 $g(p^k)=L[k\le 1]$，然后要计算 $g$ 的块筛，因为不能再去枚举 $L$ 了，所以得去枚举乘了多少次 $L$，可以得到下列柿子：

$$
\sum_{i=0} L^i\sum_{k=1}^n [w(k)=i]\mu(k)^2
$$

其中 $w(n)$ 表示 $n$ 的不同质因子个数。

这个东西可以加一维表示 $w$，然后一遍 min_25 求出来，加的那一位大小只有 $\ln \ln n$，所以复杂度是 $\mathcal{O}(\frac{n^{\frac{3}{4}}\ln\ln n}{\log n})$。

剩下就很套路了，PN 筛模板怎么做就怎么做。

复杂度变成 $\mathcal{O}(\frac{n^{\frac{3}{4}}\ln\ln n}{\log n}+mn^{\frac{3}{5}})$。

---

