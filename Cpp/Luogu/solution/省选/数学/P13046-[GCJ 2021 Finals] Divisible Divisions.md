# [GCJ 2021 Finals] Divisible Divisions

## 题目描述

我们有一个由十进制数字组成的字符串 $\mathbf{S}$。$\mathbf{S}$ 的一个**分割**是通过将 $\mathbf{S}$ 划分为连续的若干子串得到的。例如，若 $\mathbf{S}$ 为 `0145217`，则两种可能的分割为 `014 5 21 7` 和 `0 14 52 17`。每个数字必须恰好出现在一个子串中，且每个子串必须非空。如果 $\mathbf{S}$ 有 $L$ 个数字，则它共有 $2^{L-1}$ 种可能的分割方式。

给定一个正整数 $\mathbf{D}$，若 $\mathbf{S}$ 的某个分割满足：对于任意两个相邻的子串，它们表示的十进制整数中至少有一个能被 $\mathbf{D}$ 整除，则称该分割是**可被 $\mathbf{D}$ 整除的**。若 $\mathbf{D}=7$，上述第一个示例分割是可被整除的，因为 `014`、`21` 和 `7` 表示的整数均能被 7 整除。第二个示例分割不可被整除，因为 `52` 和 `17` 是相邻子串且均不能被 7 整除。将 `0145217` 分割为 `0145217`（即不分割）对任意 $\mathbf{D}$ 都是可被整除的，因为此时不存在相邻子串对。

给定 $\mathbf{S}$ 和 $\mathbf{D}$，统计 $\mathbf{S}$ 的可被 $\mathbf{D}$ 整除的分割数量。由于结果可能非常大，只需输出其对质数 $10^{9}+7$（即 $1000000007$）取模后的余数。


## 说明/提示

**样例解释**

在样例 #1 中，$\mathbf{S}$ 的所有 16 种可被 7 整除的分割为：

- 0145217,
- 0 145217,
- 0 14 5217,
- 0 14 5 217,
- 0 14 5 21 7,
- 0 14 521 7,
- 0 145 217,
- 0 145 21 7,
- 0 14521 7,
- 014 5217,
- 014 5 217,
- 014 5 21 7,
- 014 521 7,
- 0145 217,
- 0145 21 7, 和
- 014521 7.

在样例 #2 中，共有 $2^{5}=32$ 种分割方式。若要使两个相邻子串均不被 10 整除，则这两个子串的末尾均不能为 0。唯一满足此条件的分割是 `1 001 00` 和 `1 001 0 0`，因此其余 30 种分割均是可被 10 整除的。

在样例 #3 中，没有任何子串表示的整数是偶数（即无法被 12 整除）。因此，唯一避免两个相邻子串均不被 12 整除的方式是不进行任何分割，即仅有一种分割：`5555`。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{D} \leq 10^{6}$。

**测试集 1（10 分，可见判定）**

- $1 \leq \mathbf{S}$ 的长度 $\leq 1000$。

**测试集 2（35 分，隐藏判定）**

- $1 \leq \mathbf{S}$ 的长度 $\leq 10^{5}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
0145217 7
100100 10
5555 12```

### 输出

```
Case #1: 16
Case #2: 30
Case #3: 1```

# 题解

## 作者：Purslane (赞：4)

# Solution

简单计数题。

设 $dp_{i,0/1}$ 为，将前 $i$ 个数分成若干段，且最后一段能或不能被 $D$ 整除的方案数。

考虑 $dp_j$ 往 $dp_i$ 转移。记 $pre_i$ 为前 $i$ 个数构成的字符串，那么新加的段是 $pre_i-pre_j 10^{i-j}$，尝试刻画他在模 $D$ 意义下的值。

如果 $\gcd(D,10) = 1$，那么这是简单的，因为等价于 $\dfrac{pre_i}{10^i} \equiv \dfrac{pre_j}{10^j} \pmod D$。

否则，当 $i$ 和 $j$ 比较接近的时候可以暴力算。否则，取 $d$ 为 $D$ 除去 $2$ 和 $5$ 的结果。那么 $i-j$ 比较大，那么一定有 $\dfrac{D}{d} \mid 10^{i-j}$，那如果想让 $D$ 整除这个式子，一定也要有 $\dfrac{D}{d} \mid pre_i$，然后可以转化为 $\gcd(D,10) = 1$ 的问题。即我们只需要 $\dfrac{pre_i}{10^i} \equiv \dfrac{pre_j}{10^j} \pmod {d}$，可以预处理。

复杂度理论上是 $O(|S|)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MAXM=1e6+10,MOD=1e9+7;
int T,n,D,d1,d2,dp[MAXN][2],pre[MAXN],iv,pw[MAXN];
string S;
pair<int,int> exgcd(int a,int b) {
	if(!b) return {1,0};
	auto pr=exgcd(b,a%b);
	return {pr.second,pr.first-(a/b)*pr.second};
}
int get_inv(int x,int mod) {
	auto pr=exgcd(x,mod);
	return (pr.first%mod+mod)%mod;
}
unordered_map<int,int> ts[2];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	ffor(tc,1,T) {
		cin>>S>>D,n=S.size(),S="&"+S;
		d1=1,d2=D;
		while(d2%2==0) d1*=2,d2/=2;
		while(d2%5==0) d1*=5,d2/=5;
		pre[0]=1;
		ffor(i,1,n) pre[i]=(pre[i-1]*10+S[i]-'0')%D;
		iv=get_inv(10,d2);
		ts[0].clear(),ts[1].clear();
		dp[0][1]=1; int lpos=-1,sum1=0;
		pw[0]=1; ffor(i,1,n) pw[i]=pw[i-1]*iv%d2;
		ffor(i,1,n) {
			dp[i][0]=dp[i][1]=0;
			int mul=1;
			roff(j,i-1,max(0ll,i-20)) {
				mul=mul*10%D;
				int sum=(pre[i]-pre[j]*mul)%D;
				if(sum==0) dp[i][1]=(dp[i][1]+dp[j][0]+dp[j][1])%MOD;
				else dp[i][0]=(dp[i][0]+dp[j][1])%MOD;
			}
			int lim=max(0ll,i-20)-1;
			if(lim>=0) {
				while(lpos+1<=lim) {
					lpos++;
					sum1=(sum1+dp[lpos][1])%MOD;
					ffor(o,0,1) ts[o][pre[lpos]*pw[lpos]%d2]+=dp[lpos][o];
				}
				if(pre[i]%d1) dp[i][0]=(dp[i][0]+sum1)%MOD;
				else {
					int lhs=pre[i]*pw[i]%d2;
					dp[i][1]=(dp[i][1]+ts[0][lhs]+ts[1][lhs])%MOD;
					dp[i][0]=(dp[i][0]+sum1-ts[1][lhs])%MOD;
				}
			}
		}
		int ans=(dp[n][0]+dp[n][1])%MOD;
		cout<<"Case #"<<tc<<": "<<(ans%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}

```

---

## 作者：P2441M (赞：1)

## 题意

给定正整数 $d$ 和一个数字串 $s$，将其划分为若干连续的非空字串，求有多少种划分方案，使得对于任意两个相邻子串，它们所表示的整数至少有一个能被 $d$ 整除，答案对 $10^9+7$ 取模。多测，$1\leq T\leq 100$，$1\leq \lvert s\rvert\leq 10^5$，$1\leq d\leq 10^6$。

## 题解

随机开题，开出了远古时期 NOIP 模拟赛的 T1。

这个时限也太搞笑了，我交暴力的时候还数据分治了一下保命……

先考虑暴力 DP。令 $pre_i$ 表示 $\bmod{d}$ 意义下 $s[1,i]$ 所表示的整数，$f_{i,0/1}$ 表示划分 $s[1,i]$，$s_i$ 所在的段表示的数字能否被 $d$ 整除时的合法划分方案数。枚举最后一段为 $s[j,i]$，这一段所表示的数字就是 $pre_i-10^{i-j+1}pre_{j-1}$，那么转移即为

$$
\begin{cases}
f_{i,0}\leftarrow f_{i,0}+f_{j-1,1}&pre_i-10^{i-j+1}pre_{j-1}\not\equiv 0\pmod{d}\\
f_{i,1}\leftarrow f_{i,1}+f_{j-1,0}+f_{j-1,1}&pre_i-10^{i-j+1}pre_{j-1}\equiv 0\pmod{d}
\end{cases}
$$

这样我们就得到了 $\mathcal{O}(Tn^2)$ 的做法。

考虑如何优化。观察一个段的转移条件，以第二种转移为例，就是

$$
pre_i\equiv 10^{i-j+1}pre_{j-1}\pmod{d}
$$

不难看出，如果我们有 $\gcd(d,10)=1$，这是极好优化的。具体来说，此时 $10$ 在 $\bmod{d}$ 意义下存在逆元，那么上式化为

$$
10^{-i}pre_i\equiv 10^{-(j-1)}pre_{j-1}\pmod{d}
$$

对 $10^{-i}pre_i\bmod{d}$ 开桶即可 $\mathcal{O}(1)$ 转移。对于第一种转移，用 $\sum\limits_{0\leq j<i}{f_{j,1}}$ 减去 $\sum\limits_{0\leq j<i}[10^{-i}pre_i\equiv 10^{-(j-1)}pre_{j-1}\pmod{d}]f_{j,1}$ 即可。

尝试推广到 $\gcd(d,10)>1$ 的情况。考虑把 $d$ 的所有 $2,5$ 因子提出来，变为 $2^{c_2}5^{c_5}q$ 的形式。那么显然

$$
\begin{align*}
&pre_i\equiv 10^{i-j+1}pre_{j-1}\pmod{d}\\
\Leftrightarrow&pre_i\equiv 10^{i-j+1}pre_{j-1}\pmod{q}\land pre_i\equiv 10^{i-j+1}pre_{j-1}\pmod{2^{c_2}5^{c_5}}
\end{align*}
$$

令 $c=\max(c_2,c_5)$，显然 $c\leq \log_2d$。自然地按照 $c$ 和 $i-j+1$ 的大小关系进行分类讨论：

- $i-j+1\geq c$：这种情况下 $\bmod{2^{c_2}5^{c_5}}$ 的条件等价于 $pre_i\equiv 0\pmod{q}$，直接判就行了。对于 $\bmod{q}$ 的条件，我们有 $\gcd(q,10)=1$，按照上文的做法直接开桶做就行了。
- $i-j+1< c$：最多只有 $\mathcal{O}(\log d)$ 个这样的 $j$，暴力转移即可。

时间复杂度 $\mathcal{O}(T|s|\log{d})$。

我的实现由于边界原因，需要令 $c\leftarrow \max(c,1)$，不影响正确性。

一些警示：数据大概塞了一些 $d\leq 9$，我用了一些取模优化，忘记给 $s_i$ 模 $d$ 了，导致我一开始暴力也 WA 了。

## 代码

```cpp
#include <iostream>
#include <cstring>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 5, V = 1e6 + 5, MOD = 1e9 + 7;

inline int add(int x, int y, int p) { return x += y, x >= p ? x - p : x; }
inline int sub(int x, int y, int p) { return x -= y, x < 0 ? x + p : x; }
inline void cadd(int &x, int y, int p) { x += y, x < p || (x -= p); }
inline void csub(int &x, int y, int p) { x -= y, x < 0 && (x += p); }

int T, n, d, q, inv, pre[N], f[N][2], g[V][2], pw1[N], pw2[N];
char s[N];

inline void exgcd(int a, int b, int &x, int &y) {
	if (!b) return x = 1, y = 0, void();
	exgcd(b, a % b, y, x), y -= a / b * x;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> T;
    for (int t = 1; t <= T; ++t) {
    	cin >> s + 1 >> d, n = strlen(s + 1);
    	for (int i = 1; i <= n; ++i) s[i] -= '0', pre[i] = add(10 * pre[i - 1] % d, s[i] % d, d);
    	q = d;
    	int c2 = 0, c5 = 0, p = 1;
    	while (!(q & 1)) q >>= 1, p <<= 1, ++c2;
    	while (!(q % 5)) q /= 5, p *= 5, ++c5;
    	int c = max(max(c2, c5), 1);
    	int tmp; exgcd(10, q, inv, tmp), inv = sub(inv % q, 0, q);
    	pw1[0] = pw2[0] = 1;
    	for (int i = 1; i <= n; ++i) pw1[i] = 10 * pw1[i - 1] % d, pw2[i] = (ll)inv * pw2[i - 1] % q;
    	f[0][0] = 0, f[0][1] = 1;
    	memset(g, 0, sizeof(g));
    	int sum = 0;
    	if (c <= 1) g[0][1] = sum = 1;
    	for (int i = 1; i <= n; ++i) {
    		f[i][0] = f[i][1] = 0;
    		for (int j = max(i - c + 2, 1); j <= i; ++j) {
    			int v = sub(pre[i], (ll)pre[j - 1] * pw1[i - j + 1] % d, d);
    			if (!v) cadd(f[i][1], add(f[j - 1][0], f[j - 1][1], MOD), MOD);
    			else cadd(f[i][0], f[j - 1][1], MOD);
    		}
    		int x = (ll)pre[i] * pw2[i] % q;
    		if (!(pre[i] % p)) {
    			cadd(f[i][1], add(g[x][0], g[x][1], MOD), MOD);
    			cadd(f[i][0], sub(sum, g[x][1], MOD), MOD);
    		} else cadd(f[i][0], sum, MOD);
    		if (i - c + 1 >= 0) {
    			x = (ll)pre[i - c + 1] * pw2[i - c + 1] % q;
    			cadd(g[x][0], f[i - c + 1][0], MOD), cadd(g[x][1], f[i - c + 1][1], MOD);
    			cadd(sum, f[i - c + 1][1], MOD);
    		}
    	}
    	cout << "Case #" << t << ": " << add(f[n][0], f[n][1], MOD) << '\n';
    }
    return 0;
}
```

---

## 作者：Iniaugoty (赞：1)

看不出来这跟 CRT 有什么关系。

非常显然地，我们可以做一个 DP，设 $f _ i / g _ i$ 表示将前 $i$ 位数码分段，最后一段是（否）是 $D$ 的倍数，满足条件的方案数。

暴力转移显然，若 $(l, r]$ 段组成的数字是 $D$ 的倍数，则从 $f _ l + g _ l$ 转移到 $f _ r$，否则从 $f _ l$ 转移到 $g _ r$，时间复杂度为 $O(n ^ 2)$。

考虑如何转化这个条件。设 $s _ i$ 表示前 $i$ 位数码组成的数字，那么 $(l, r]$ 段组成的数字就是 $s _ r - 10 ^ {r - l} s _ l$。

我们要求 $10 ^ {r - l} s _ l \equiv s _ r \pmod D$。不妨假定 $D \perp 10$，则 $10$ 存在逆元，于是 $10 ^ {-l} s _ l \equiv 10 ^ {-r} s _ r$。左边只与 $l$ 相关，右边只与 $r$ 相关，而观察到 $D$ 并不大，因此用一个桶随便维护即可做到 $O(n)$。

但是有可能 $\gcd(D, 10) > 1$ 导致不存在逆元，那咋办。

不妨把 $D$ 中含 $2$ 和 $5$ 的因子去掉，即设 $D = 2 ^ {k _ 2} \cdot 5 ^ {k _ 5} \cdot D _ 0$，其中 $2 \nmid D _ 0$ 且 $5 \nmid D _ 0$。设 $k = \max(k _ 2, k _ 5)$。

要求 $10 ^ {r - l} s _ l \equiv s _ r \pmod D$，即要求其 $\bmod {2 ^ {k _ 2} \cdot 5 ^ {k _ 5}}$ 和 $\bmod {D _ 0}$ 下也同余。

- 对于 $r - l > k$，有 $10 ^ {r - l} \equiv 0 \pmod {2 ^ {k _ 2} \cdot 5 ^ {k _ 5}}$，则只有在 $s _ r \equiv 0$ 时才可能成立。剩下的 $\equiv 0 \pmod {D _ 0}$ 限制，按照上面的做法维护一个桶即可。

- 对于 $r - l \le k$，注意到 $k$ 不超过 $\log$ 级别，每个 $l$ 只需要暴力枚举后面 $k$ 个 $r$ 进行转移。

$10 ^ {r - l}s _ l \not \equiv s _ r$ 的限制显然以类似方法可以同时维护。

时间复杂度 $O(n \log n)$，常数较小。

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, LL> pii;
const int N = 1e5 + 5, K = 1e6 + 5;
const int P = 1e9 + 7;

int Add(int x, int y) { return x + y >= P ? x + y - P : x + y; }
void Cal(int &x, int y) { x = Add(x, y); }
int qPow(int x, int y, int P) {
  int res = 1;
  for (; y; x = 1ll * x * x % P, y >>= 1)
    if (y & 1) res = 1ll * res * x % P;
  return res;
}
void Exgcd(int a, int &x, int b, int &y) {
  if (!b) return x = 1, y = 0, void();
  Exgcd(b, y, a % b, x), y -= a / b * x;
}

int n, m, s[N], f[N], g[N], pq[N], qp[N], h[K], r[K]; char a[N];

void mian() {
  cin >> (a + 1) >> m, n = strlen(a + 1);
  F(i, 1, n) s[i] = (s[i - 1] * 10ll + a[i] - '0') % m;
  int m2 = 1, m5 = 1, k2 = 0, k5 = 0, m0 = m;
  while (m0 % 2 == 0) m2 <<= 1, m0 >>= 1, ++k2;
  while (m0 % 5 == 0) m5 *= 5, m0 /= 5, ++k5;
  int k = max(k2, k5), sum = 0, x, y;
  Exgcd(10, x, m0, y), x = (x % m0 + m0) % m0;
  qp[0] = pq[0] = f[0] = 1, g[0] = 0;
  F(i, 1, n) pq[i] = 1ll * pq[i - 1] * x % m;
  F(i, 1, n) qp[i] = qp[i - 1] * 10ll % m;
  F(i, 1, n) f[i] = g[i] = 0;
  F(i, 0, n - 1) {
    F(j, i + 1, min(i + k, n))
      if (1ll * s[i] * qp[j - i] % m == s[j])
        Cal(f[j], Add(f[i], g[i]));
      else Cal(g[j], f[i]);
    Cal(sum, f[i]), Cal(r[1ll * s[i] * pq[i] % m0], f[i]);
    Cal(h[1ll * s[i] * pq[i] % m0], Add(f[i], g[i]));
    int u = i + k + 1;
    if (u <= n)
      if (s[u] % m2 == 0 && s[u] % m5 == 0)
        Cal(f[u], h[1ll * s[u] * pq[u] % m0]),
        Cal(g[u], Add(sum, P - r[1ll * s[u] * pq[u] % m0]));
      else Cal(g[u], sum);
  }
  F(i, 0, m0 - 1) h[i] = r[i] = 0;
  cout << Add(f[n], g[n]);
}

int main() {
  // freopen("zyq.in", "r", stdin);
  // freopen("zyq.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int _; cin >> _;
  F(i, 1, _)
    cout << "Case #" << i << ": ",
    mian(), cout << "\n";
  return 0;
}
```

---

