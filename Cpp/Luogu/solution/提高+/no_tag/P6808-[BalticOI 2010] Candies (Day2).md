# [BalticOI 2010] Candies (Day2)

## 题目描述

给定一个长度为 $N$ 的序列 $B_1,B_2,\dots,B_N$。

一个整数 $M$ 能够被表示出来当且仅当从序列中任取 $K$ 个数 $A_1,A_2,\dots,A_K$，使得 $\sum_{i=1}^{K}A_i=M$。

你需要修改序列中的一个数 $P$，使得尽可能多的整数能够被表示出来。

## 说明/提示

对于 $100\%$ 的数据，保证 $2\le N\le 100$，$1\le B_i\le 7000$。


**题目译自 [BalticOI 2010](https://www.luogu.com.cn/problem/U126003) [Day2](https://boi.cses.fi/files/boi2010_day2.pdf) *T2 Candies***。

## 样例 #1

### 输入

```
4
1 3 4 4```

### 输出

```
4 9```

## 样例 #2

### 输入

```
5
3 3 3 3 3```

### 输出

```
3 1```

# 题解

## 作者：Getaway_Car (赞：5)

### 鲜花

校内模拟赛T3，赛时想到了正解的 $60\%$，所以就得了 $60$ 分……

赛后 T 了若干发之后终于过了。

---

本文提供一种非回退背包的解法。

在下文中，记 $k = \sum_{i = 1}^n a_i$。

### Solution 1

假设我们修改 $a_i$，设用其他数拼出的方案数为 $cnt_i$ ，那么当 $a_i'$ 足够大时，有 ${cnt_i'}_{max} = 2cnt_i + 1$。所以问题就转化到了求 $\max_{i = 1}^{n} cnt_i$ 与 $i$。

考虑枚举 $i$，并对于每个 $i$ 进行 DP 计算 $cnt_i$。求出最大值与最大值位置（即 $p$）后，需要求 $q$。

设 $f_i$ 表示是否能凑出 $i$。很容易发现，当 $\sum_{i = 1}^k [f_i = 1, f_{i + q} = 1] = 0$ 时，$q$ 合法。暴力枚举即可。

时间复杂度 $O(n ^ 2k + k ^ 2)$，完全不能接受。

### Solution 2

我们发现，在第一种解法中，对于同一个物品，进行了太多次的背包 DP。我们尝试只进行一次DP，**并标记为了凑出当前这个数，有哪些位置必须被选取**。若不需要选取第 $i$ 个数，代表当我们修改 $a_i$ 时仍然能凑出这个数。

具体地，设 $dp_{i, j}$ 表示为了凑出 $i$，是否需要 $a_j$。转移方程如下。

$$$
f_i = \mathop{bitor}\limits_{1\le k\le n} f_{i - a_k}\\
\ \\
dp_{i, j}=
\mathop{bitand}\limits_{1\le k\le n,\ f_{i - a_k} = 1}
\begin{cases}
dp_{i - a_k, j}\ (j \ne k)\\
1\ (j = k)
\end{cases}
$$$

DP 完之后统计 $cnt_i$，剩余步骤与解法一相同。

时间复杂度仍然是 $O(n ^ 2k + k ^ 2)$，但常数好得多，在洛谷上取得了 $60$ 分的好成绩！（这也是我赛时的做法，个人认为特别符合直觉。）

### Solution 3

考虑优化一下求 $q$ 的过程。前文已推得，当 $\sum_{i = 1}^k [f_i, f_{i + q}] \ne 0$，$q$ 不合法。设全集（可重集）为 $U$，此时有可重集 $S, T$ 满足 $S, T \subset U, (\sum_{i \in S} b_i) - (\sum_{i \in T} b_i) = q$。再正反做一次背包即可。总时间复杂度 $O(n^2k)$，还是卡。

### Solution 4

由于所有状态都是 $0$ 或 $1$，所以可以用 ``bitset`` 优化。最终复杂度 $O(\frac{n ^ 2k}{w})$，趋近于 $O(nk)$，可以通过。

### Code

在代码中，``dp[i][0]`` 代表文中的 $f_i$，其余的 ``dp[i][j]`` 代表文中的 $dp_{i, j}$。

```cpp
int n, a[105], sum, cnt[105], mx, p;
bitset<105> dp[700005];
bitset<1400005> tmp;

int main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), sum += a[i];
	// 初始化 dp 数组
	sort(a + 1, a + 1 + n);
	dp[0] = 1, dp[1][0] = 0;
	for(int i = 1; i <= n; ++i)
		dp[1][i] = 1;
	for(int i = 2; i <= sum; ++i)
		dp[i] = dp[i - 1];
	// 计算 dp 数组
	for(int i = 1; i <= n; ++i)
		for(int j = sum; j >= a[i]; --j)
			if(dp[j - a[i]][0]) {
				dp[j] &= dp[j - a[i]];
				if(!dp[j][0]) dp[j][i] = 1;
				dp[j][0] = 1;
			}
	// 统计 cnt 并计算 p
	for(int i = 1; i <= sum; ++i)
		if(dp[i][0])
			for(int j = 1; j <= n; ++j)
				if(!dp[i][j])
					++cnt[j];
	mx = p = 0;
	for(int i = 1; i <= n; ++i)
		if(cnt[i] > mx) mx = cnt[i], p = i;
	// 计算 q
	tmp[7000 * n] = 1;
	for(int i = 1; i <= n; ++i)
		if(i != p)
			tmp = tmp | (tmp << a[i]) | (tmp >> a[i]);
	for(int i = 1; i <= sum - a[p] + 1; ++i)
		if(!tmp[7000 * n + i])
			return printf("%d %d\n", a[p], i), 0;
}
```

这代码截止发题解当天竟然还跑出了[洛谷最优解](https://www.luogu.com.cn/record/200199228)。（不过做这道题的人少。）

---

## 作者：zhylj (赞：3)

**先考虑 $P$ 怎么求：**

对于某一个 $P$，若不考虑 $Q$ 最小，则显然存在一种方案把这个 $P$ 改成 $+\infty$，此时能表示的数的个数是 **$B$ 除了 $P$ 以外的数能表示数的个数再乘上 $2$**，考虑 [P4141 消失之物](https://www.luogu.com.cn/problem/P4141) 的方法，我们统计表示 $i$ 的方案数 $g_i$，然后令每个 $g_i$ 都有 $g_i\leftarrow g_i - g_{i-P}$，即消去重量为 $P$ 的物品的影响，处理后不为 $0$ 的 $g_i$ 的项数乘 $2$ 就是改 $P$ 能表示到的最多的数的个数。

枚举每个 $P$，求出改掉 $P$ 能表示到的最多的数的个数。找到使其最大的 $P$ 中最小的一个即可。

注意到 $g_i$ 不能直接算，考虑 $\bmod$ 一个大素数再判断是否为 $0$，正确的概率是极高的。

**再考虑 $Q$ 怎么求：**

考虑只有选了 $Q$ 和没选 $Q$ 能凑出来的数**完全不重合**（因为一定能构造一种方案是这样的，重合了凑出来的数的个数会变少）才有可能为答案，考虑如果重合了，假如我们选的数分别是 $S_1\cup \{Q\},S_2$，则有：

$$Q+\sum_{B_i\in S_1} B_i= \sum_{B_i\in S_2} B_i$$

$$Q = \sum_{B_i\in S_2} B_i + \sum_{B_i\in S_1} (-B_i)$$

注意到，重合当且仅当 $Q$ 这个数能被 $\{B_i\}\cup\{-B_i\}$ 这些数表示，所以我们对 $\{B_i\}\cup\{-B_i\}$ 进行一次背包，找出不能被表示的最小的数就是我们要的 $Q$ 了。

后面这部分的背包可以用 bitset 优化，不过并不影响复杂度。设 $B_i$ 的值域是 $c$，这样整个算法的时间复杂度就是 $\mathcal O(n^2c)$（$\sum B_i$ 是 $\mathcal O(nc)$ 的）

**代码**

```cpp
int n, v[kN], g[kN], h[kN]; std::bitset <kN> f;
int main() { 
	int s = 0;
	rd(n);
	for(int i = 1; i <= n; ++i) rd(v[i]), s += v[i];
	std::sort(v + 1, v + n + 1);
	g[0] = 1;
	for(int i = 1; i <= n; ++i)
		for(int j = s; j >= v[i]; --j)
			g[j] = (g[j] + g[j - v[i]]) % kMod;
	int max_re = 0, a = 0, b;
	for(int i = 1; i <= n; ++i) {
		memcpy(h, g, sizeof(h));
		for(int j = v[i]; j <= s; ++j)
			h[j] = (h[j] - h[j - v[i]]) % kMod;
		int cnt = 0;
		for(int j = 0; j <= s; ++j) if(h[j]) ++cnt;
		if(cnt > max_re) {
			a = v[i]; max_re = cnt;
		}
	}
	for(int i = 1; i <= n; ++i) if(v[i] == a) { v[i] = 0; break; }
	for(int i = 1; i <= n; ++i) v[i + n] = -v[i];
	n *= 2;
	f.set(0);
	for(int i = 1; i <= n; ++i) {
		if(v[i] > 0) f |= (f << v[i]);
		else f |= (f >> -v[i]);
	}
	for(int i = 1; i <= s; ++i) if(!f[i]) {
		b = i; break;
	}
	printf("%d %d\n", a, b);
}
```


---

## 作者：JK_LOVER (赞：3)

## 题意
修改序列中的一个数，使可以表达的数字尽可能的多。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-p6808)
## 分析
考虑序列在去掉一个数时，可以表达的数字个数。这个可以用背包转移。先预处理所有数字可以表达的数字。 $f[i][j],dp[i]$ 分别表示在考虑前 $i$ 个数字表达的方案数 $j$ 和在去掉某个数之后，表达 $i$ 的方案数。
$$
f[i][j] = f[i-1][j] + f[i-1][j-a[i]] 
$$
$$
dp[j] = dp[j] - dp[j-a[pos]]
$$
$$
ans[i] = \sum_{j}^{max} [dp[j]>0]
$$
然后上面可以用滚动数组减少一维。那么我们现在就有了，去某掉一个数的方案数。那么考虑谁才是最优的。想想一下如果把这个数字修改 $a_i$ 为一个非常大的数字那么可以表达数一定是 $ans[i]\times2+1$ 。那么只需要考虑最大的 $ans[i]$ 了。考虑最小化修改后的数字，那么当一个数字加上这个数在集合中没有出现，且本身没有出现，那么这个数字就是可取的。$dp$ 一下就好了。

- 这题开了 $\text{long long}$ 就超时，所以取个 $\text{mod}$ 就好了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int a[N],dp[7100000],res[7100000],n,Max;
int mod = 4e8+7;
bitset<1400010> f;
int main()
{
	n = read();dp[0] = 1;
	for(int i = 1;i <= n;i++) {
		a[i] = read();
		for(int j = Max;j >= 0;j--) dp[j+a[i]] = (dp[j+a[i]] + dp[j] + mod)%mod;
		Max += a[i];
	}
	int ans = 0,pos = 0;
	for(int i = 1;i <= n;i++) {
		int sum = 0;
		for(int j = 0;j <= Max;j++)
		{
			res[j] = dp[j];
			if(j >= a[i]) res[j] = (res[j] - res[j-a[i]] + mod) % mod;
			if(res[j]) sum++;
		}
		if(sum > ans || (sum == ans && a[i] < a[pos])){
			ans = sum;pos = i;
		}
	}
	f[7000*n] = 1;
	for(int i = 1;i <= n;i++) {
		if(i != pos) f = f|(f<<a[i])|(f>>a[i]);
	}
	for(int i = 1;i <= Max+1;i++){
		if(!f[i+7000*n]) {
			printf("%d %d\n",a[pos],i);
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：irris (赞：1)

## Preface

背包套路二合一。

## Solution

+ 首先先做第一问：找到这个 $P$。

发现如果我们的 $Q$ 设的足够大，那么每次总有，调整后的 $ans' \gets 2\times ans + 1$，也就是说只需要注意调整前（即除了 $P$ 的所有数）能够 01 背包拼出的数的个数。

你可以前缀先做一遍背包，后缀再做一遍背包，然后拼起来。但是由于「拼起来」这个过程，最优也是 背包大小 的线性对数，复杂度为 $\mathcal O(n^2V(\log n + \log V))$，不带常数也有 $1.4\times 10^9$ 显然冲不过去。~~更别提正经人谁写 Poly 啊？~~

更优的想法是仿照 [P4141 消失之物](https://www.luogu.com.cn/problem/P4141) 形式的 **退背包**，也就是把 01 背包倒过来跑一遍以去掉某一个数。因为方案数可能很大，所以你随便设一个大一点的质数做模数就可以保证正确性，复杂度 $\mathcal O(n^2V)$。

+ 然后再做第二问：找到这个 $Q$。

第一眼的想法是 $\displaystyle\sum_{i\neq P}a_i + 1$，但是很快就被样例给叉了。事实上，这只是可行解而不是最小解。

转而考虑，一个不可行解具有什么样的特性？答案是在原来的 01 背包里存在两个数 $u, v$ 使得 $u + Q = v$。更具体地，设可重集 $S = \{a_1\dots a_n\} - \{a_P\}$，那么存在 $T_1, T_2 \subseteq S$ 使得 $\displaystyle\sum_{u\in T_1}u - \sum_{u\in T_2}u = Q$。

这时考虑左式对 $S$ 里每个数附加的系数，不难发现只有 $-1, 0, 1$ 三种。那么这其实就是问你 $S$ 里所有元素本身和相反数的任一子集能不能表示 $Q$。

直接 01 背包即可求出这个最小的不能被表示的 $Q$，注意要先把所有正数加上去再加所有负数（否则可能某些方案在中间因为减出了负数而被舍弃）。这里可以用 bitset 优化，但是反正不在复杂度瓶颈上，所以其实只是常数优化。

时间复杂度 $\mathcal O(n^2V)$。

## Code

```cpp
#include <bits/stdc++.h>

namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
}; using namespace FastIO;

constexpr int MOD = 998244353;
inline void add(int& x, int y) { (x += y) >= MOD && (x -= MOD); }
inline void del(int& x, int y) { (x -= y) < 0 && (x += MOD); }

#define MAXN 101
struct S {
	int id, v;
	S () {}
	S (int I, int V) : id(I), v(V) {}
} p[MAXN];

#define MAXM 700001
int re[MAXM];

namespace Bits {
	const int V = 10944, B = 64, R = 63, T = 6;
	struct bitset {
		private : unsigned long long a[V];
		public :
			bitset () { memset(a, 0, sizeof(a)); }
			inline int operator [] (const int& i) { return (a[i >> T] >> (i & R)) & 1; }
			inline unsigned long long get(const int& i) { return a[i]; }
			inline void set(int v, unsigned long long x = 1) { a[v >> T] ^= ((x ^ (*this)[v]) << (v & R)); }
			bitset (const std::string& S) { memset(a, 0, sizeof(a)); for (int i = 0, n = (int)S.size(); i < n; ++i) if (S[i] ^ '0') this -> set(i); }
			bitset operator & (const bitset& k) const { bitset t; for (int i = 0; i < V; i += 4) t.a[i] = a[i] & k.a[i], t.a[i | 1] = a[i | 1] & k.a[i | 1], t.a[i | 2] = a[i | 2] & k.a[i | 2], t.a[i | 3] = a[i | 3] & k.a[i | 3]; return t; }
			bitset operator &= (const bitset& k) { for (int i = 0; i < V; i += 4) a[i] &= k.a[i], a[i | 1] &= k.a[i | 1], a[i | 2] &= k.a[i | 2], a[i | 3] &= k.a[i | 3]; return *this; }
			bitset operator | (const bitset& k) const { bitset t; for (int i = 0; i < V; i += 4) t.a[i] = a[i] | k.a[i], t.a[i | 1] = a[i | 1] | k.a[i | 1], t.a[i | 2] = a[i | 2] | k.a[i | 2], t.a[i | 3] = a[i | 3] | k.a[i | 3]; return t; }
			bitset operator |= (const bitset& k) { for (int i = 0; i < V; i += 4) a[i] |= k.a[i], a[i | 1] |= k.a[i | 1], a[i | 2] |= k.a[i | 2], a[i | 3] |= k.a[i | 3]; return *this; }
			bitset operator ^ (const bitset& k) const { bitset t; for (int i = 0; i < V; i += 4) t.a[i] = a[i] ^ k.a[i], t.a[i | 1] = a[i | 1] ^ k.a[i | 1], t.a[i | 2] = a[i | 2] ^ k.a[i | 2], t.a[i | 3] = a[i | 3] ^ k.a[i | 3]; return t; }
			bitset operator ^= (const bitset& k) { for (int i = 0; i < V; i += 4) a[i] ^= k.a[i], a[i | 1] ^= k.a[i | 1], a[i | 2] ^= k.a[i | 2], a[i | 3] ^= k.a[i | 3]; return *this; }
			bitset operator <<= (int k) { if (k >= B) { int s = k >> T; for (int i = V - 1; ~i; --i) a[i] = (i + 1 > s ? a[i - s] : 0ull); k &= R; } if (!k) return *this; unsigned long long o = 0, t; for (int i = 0; i < V; ++i) t = a[i] >> (B - k), a[i] = (a[i] << k) | o, o = t; return *this; }
			bitset operator << (int k) const { bitset t = *this; return t <<= k; }
			bitset operator >>= (int k) { if (k >= B) { int s = k >> T; for (int i = 0; i < V; ++i) a[i] = (i + s < V ? a[i + s] : 0ull); k &= R; } if (!k) return *this; unsigned long long o = 0, t; for (int i = V - 1; ~i; --i) t = a[i] << (B - k), a[i] = (a[i] >> k) | o, o = t; return *this; }
			bitset operator >> (int k) const { bitset t = *this; return t >>= k; }
			const int count(int N) const { int ans = 0; for (int i = 0; i <= (N >> T); ++i) ans += __builtin_popcountll(a[i]); return ans; }
			const void debug(int N) { for (int i = 0; i < N; ++i) putchar(48 + (*this)[i]); puts(""); }
	} t;
}; using namespace Bits;

int main() {
	int N = read<int>(), M;
	for (int i = 1, v; i <= N; ++i) v = read<int>(), p[i] = S(i, v);
	std::sort(p + 1, p + N + 1, [&](S a, S b) -> bool { return a.v < b.v; }), re[0] = 1;
	for (int i = 1, sum = 0; i <= N; ++i) {
		sum += p[i].v;
		for (int j = sum, t = sum - p[i].v; ~t; --j, --t) add(re[j], re[t]);
		if (i == N) M = sum;
	}
	std::sort(p + 1, p + N + 1, [&](S a, S b) -> bool { return a.id < b.id; });
	int P = 0, Ps = 0;
	for (int i = 1, ans = 0; i <= N; ans = 0, ++i) {
		for (int j = p[i].v, t = 0; j <= M; ++j, ++t) del(re[j], re[t]);
		for (int j = 1; j <= M; ++j) ans += (re[j] > 0);
		if (ans > Ps) P = i, Ps = ans;
		for (int j = M, t = M - p[i].v; ~t; --j, --t) add(re[j], re[t]);
	}
	print<int>(p[P].v, ' ');
	t.set(0);
	for (int i = 1; i <= N; ++i) if (i != P) t |= t << p[i].v;
	for (int i = 1; i <= N; ++i) if (i != P) t |= t >> p[i].v;
	for (int i = 1; i <= M + 5; ++i) if (!t[i]) return print<int>(i, '\n'), 0;
}
```

---

## 作者：FjswYuzu (赞：0)

显然我们可以通过背包 dp 求出能组成什么值。

定义 $dp_i$ 为组成 $i$ 这个值的方案为 $dp_i$。可以发现这就是一个背包 dp，直接来就行了。

然后考虑求第一个数 $P$。对每一个数进行枚举，做一个回退的背包。具体做法是将这一个背包的转移减去就行了。具体看[P4141 天降之物](https://www.luogu.com.cn/problem/P4141)。注意顺序要倒着来，所以是逆推。然后再枚举一发，看能组成什么。能组成这个数的条件就是这个位置上的 dp 值不是 $0$。

发现当 $Q$ 取到 $∞$ 的时候一定能让当前能组成的翻倍，找最大的 $P$ 就可以了。

我们就成功找到 $P$，将其拿出来。用一个 `bitset` 维护当前能组成的数的集合。加入一个数如果使其与原来的 `bitset` 没有交集，这个 $Q$ 就是合法的。位移一下就好了。

方案比较大可以取模，反正我们只需要知道是不是 $0$ 就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int LL;
const LL MOD=1e8+7;
bitset<1400005> B;
LL n,a[105],dp[700005],tek[700005],maxn;
int main(){
	scanf("%d",&n);
	dp[0]=1;
	for(LL i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		for(LL j=maxn;j>=0;--j)	dp[j+a[i]]+=dp[j],dp[j+a[i]]%=MOD;
		maxn+=a[i];
	}
	LL ans=0,pos=0;
	tek[0]=1;
	for(LL i=1;i<=n;++i)
	{
		LL sum=0;
		for(LL j=0;j<=maxn;++j)
		{
			tek[j]=dp[j];
			if(j>=a[i])	tek[j]=(tek[j]-tek[j-a[i]]+MOD)%MOD;
			if(tek[j])	++sum;
		}
		if(sum>ans || (sum==ans && a[i]<a[pos]))	ans=sum,pos=i;
	}
	B[7000*n]=1;
	for(LL i=1;i<=n;++i)	if(i!=pos)	B=B|(B<<a[i])|(B>>a[i]);
	for(LL i=1;i<=maxn+1;++i)	if(!B[i+7000*n])	return printf("%d %d",a[pos],i)&0;
	return 0;
}
```

---

## 作者：CoronaQL (赞：0)

# 思路
显然，这道题有些深度。

我们要求这个最后剩下的数的最多方案

我们可以用 bitset 左移右移来做。

其实也比较难说清出，蒟蒻表达能力不强

二话不说，上代码

代码里注释都有
# AC代码
```cpp
#include <bits/stdc++.h>//头文件不省略真的有一大堆 
using namespace std;
int a[101], b[700001], m[700001];//如题意 
bitset<700001>dp[101];//用bitset维护 
bitset<1400001>s;
int main () 
{
	int n,ans=0,P=0,pos = 0;
	scanf ("%d", &n);//这样更快 
	for (int i = 1; i <= n; i++) //输入 
	scanf ("%d", &a[i]);
	for (int i = 1; i <= n; i++) //先来一遍 
	{
		dp[i][0] = 1;
		for (int j = 1; j <= n; j++) 
		{
			if (i == j) 
			continue;//不行就跳过 
			dp[i]=(dp[i]|(dp[i] << a[j]));// 左移右移 
		}
	}
	for (int i = 1; i <= n; i++) 
	{
		if (dp[i].count() > ans || (dp[i].count() == ans && a[i] < P)) //条件一大堆 
		{
			ans = dp[i].count();
			P = a[i];
			pos = i;
		}
	}
	int cnt=0;//计数变量 
	for (int i = 1; i <= 700001; i++) 
	{
		if (dp[pos][i]) 
		{
			b[++cnt] = i;
		}
	}
	if (cnt<=5000) 
	{
		for (int i = 1; i <= cnt; i++) 
		{
			for (int j = i + 1; j <= cnt; j++) 
			{
				m[b[j]-b[i]] = 1;
			}
		}
		int o = 700000;
		for (int i = 1; i <= 700000; i++) 
		{
			if (m[i] == 0) 
			{
				o=i;
				break;
			}
		}
		printf ("%d %d\n",P,o);	//要求换行 
		return 0;
	}
	int mx = 0;//max是关键字 
	for (int i = 700000; i >= 1; i--) 
	{
		if (dp[pos][i]) 
		{
			mx = i + 1;
			break;
		}
	}
	s[700001] = 1;//要重新赋值 
	for (int i = 1; i <= n; i++) 
	{
		if (i == pos) 
		continue;
		s=(s|(s >> a[i])|(s<< a[i])); 
	}
	for (int i=2;i <= 700000; i++) //注意！从2开始 
	{
		if (s[i+700000] == 0) 
		{
			printf ("%d %d", P, i - 1);
			return 0;//符合就直接结束 
		}
	}
	printf ("%d %d\n", P, mx);//要求换行 
	return 0;
}
```
这题还是用了比较多的行数，虽然我知道可以更短（背包DP）

但是为了大佬们的贵眼不被弄得眼花缭乱，所以用了bitset

最后求管理员通过（~~蒟蒻做了2个小时~~）

---

