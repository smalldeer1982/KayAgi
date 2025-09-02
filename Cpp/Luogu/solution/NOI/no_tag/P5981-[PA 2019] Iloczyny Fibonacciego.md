# [PA 2019] Iloczyny Fibonacciego

## 题目描述

定义斐波那契数列为 $F_1=1,F_2=2,F_i=F_{i-1}+F_{i-2}(i\ge 3)$。
对于任意一个正整数 $x$，我们总能将 $x$ 写成唯一的斐波那契表示 $(b_1,b_2,...,b_n)$，满足：

1. $b_1\times F_1+b_2\times F_2+...+b_n\times F_n=x$。
2. 对于任意的 $i(1\le i<n)$ 都有 $b_i=0$ 或 $b_i=1$；对于 $b_n$ 有 $b_n=1$。
3. 对于任意的 $i(1\le i<n)$ 都有 $b_i\times b_{i+1}=0$。

比如 $2=(0,1),4=(1,0,1),5=(0,0,0,1),20=(0,1,0,1,0,1)=F[2]+F[4]+F[6]=2+5+13$。

给定两个斐波那契表示的正整数 $A$ 和 $B$，请输出 $A\times B$ 的斐波那契表示。

## 说明/提示

对于 $100\%$ 的数据，$1\le T\le 10^3$，输入数据保证所有的 $n$ 加起来不超过 $10^6$。

## 样例 #1

### 输入

```
2
3 1 0 1
4 0 0 0 1
2 0 1
1 1```

### 输出

```
6 0 1 0 1 0 1
2 0 1```

# 题解

## 作者：Felix72 (赞：0)

这个题大概可以分成两步：先做出一个答案的**实数**斐波那契表示，再转化为题目要求的格式。

### Part I

本题不能直接卷积是因为 $f_i$ 和 $f_j$ 并不一定贡献到 $f_{i + j}$ 位。但是我们可以设法把斐波那契拆成多项式的形式。

设 $a = \frac{1 + \sqrt{5}}{2}, b = \frac{1 - \sqrt{5}}{2}$，我们有 $f_i = \frac{\sqrt{5}}{5}(a ^ i - b ^ i)$，那么 $f_if_j = \frac{1}{5}(a^{i + j} + b^{i + j} - a^ib^j - a^jb^i)$。代入 $ab = -1$ 可以通过卷积计算出最终的结果为 $\frac{1}{5}(F(a) + F(b))$，其中 $F$ 是一个多项式。但是我们最终想要的是 $\frac{\sqrt{5}}{5}(G(a) - G(b))$ 的形式，因此尝试计算 $F(a) + F(b)$ 除以 $\sqrt{5}$ 的值。我们求得 $\frac{a}{\sqrt{5}} = 0.6a + 0.4b, \frac{b}{\sqrt{5}} = -0.4a - 0.6b$，因此手动代入做多项式乘二项式就能得到一个 $\frac{\sqrt{5}}{5}(G(a) - G(b))$ 形式的答案了。

### Part II

我们先用 $f_i = f_{i - 1} + f_{i - 2}$ 消除其中的负数。这下所有系数都是**正整数**了（如果你有小数，说明你卷积部分写错了）。

然后再从高位到地位贪心，能放 $1$ 就放 $1$，检测方法就是用我们刚刚得到的结果作为被减数计算一下，看结果是否是非负数。这个高精度减法乍一看是 $O(n)$ 的，但是因为斐波那契数的增长速度关系，我们完全可以在当前值已经很大、不可能被后面的数位改变时直接剪枝。这样复杂度均摊为 $O(n\log n)$。

代码第一部分和另一篇题解不一样，第二部分是差不多的。

```cpp
 /* NE_Cat 4.1 */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const long double nA = (1 + sqrtl(5)) / 2, nB = (1 - sqrtl(5)) / 2;

const int N = 4000010, p = 998244353, G = 3, Gi = (p + 1) / G;
const long long INF = 10000000000000;
inline long long qpow(long long a, long long b)
{
	long long res = 1;
	while(b) {if(b & 1) res = res * a % p; b >>= 1, a = a * a % p;}
	return res;
}
int T, n, m, k;
long long fib[N];
long long h[N]; long long g[N], f[N]; bool ans[N];
int rev[N];
struct Poly
{
	vector < long long > f;
	inline void NTT(int opt, int ln)
	{
		while(f.size() < ln) f.push_back(0);
		for(int i = 0; i < ln; ++i) rev[i] = rev[i / 2] / 2 + ((i & 1) ? (ln / 2) : 0);
		for(int i = 0; i < ln; ++i) if(i > rev[i]) swap(f[i], f[rev[i]]);
		for(int i = 1; (1 << i) <= ln; ++i)
		{
			long long wn = qpow(((opt == 1) ? G : Gi), (p - 1) >> i);
			for(int j = 0; j < ln; j += (1 << i))
			{
				long long w = 1;
				for(int k = j; k < j + (1 << (i - 1)); ++k, w = w * wn % p)
				{
					long long n1 = f[k], n2 = w * f[k + (1 << (i - 1))] % p;
					f[k] = (n1 + n2) % p, f[k + (1 << (i - 1))] = (n1 - n2 + p) % p;
				}
			}
		}
		if(opt == -1)
		{
			long long iv = qpow(ln, p - 2);
			for(int i = 0; i < ln; ++i) f[i] = f[i] * iv % p;
		}
	}
	inline void output() {for(int x : f) cout << x << " "; cout << '\n';}
};
Poly operator * (Poly u, Poly v)
{
	int ln = 1, r_ln = u.f.size() + v.f.size() - 1;
	while(ln < u.f.size() + v.f.size() - 1) ln *= 2;
	u.NTT(1, ln), v.NTT(1, ln);
	Poly res;
	for(int i = 0; i < ln; ++i) res.f.push_back(u.f[i] * v.f[i] % p);
	res.NTT(-1, ln);
	while(res.f.size() > r_ln) res.f.pop_back();
	res.f.shrink_to_fit(); return res;
}
Poly operator * (Poly u, long long w)
{
	for(int i = 0; i < (int)u.f.size(); ++i) u.f[i] = u.f[i] * w;
	return u;
}
inline int get(int i) {return ((i & 1) ? -1 : 1);}
inline int check(int i)
{
	if(i < 0 && i % 2) return -1;
	return 1;
}

inline void sol()
{
	Poly A, B, rA, rB, C, D, res;
	A.f.push_back(0); A.f.push_back(0);
	B.f.push_back(0); B.f.push_back(0);
	cin >> n; for(int i = 1, x; i <= n; ++i) cin >> x, A.f.push_back(x);
	cin >> m; for(int i = 1, x; i <= m; ++i) cin >> x, B.f.push_back(x);
	for(int i = B.f.size() - 1; i >= 0; --i) rB.f.push_back(B.f[i] * get(i));
	for(int i = 0; i < (int)A.f.size(); ++i) rA.f.push_back(A.f[i]);
	C = A * B, D = rA * rB;
	for(int i = 0; i < (int)D.f.size(); ++i)
		C.f[abs(i - (int)B.f.size() + 1)] = C.f[abs(i - (int)B.f.size() + 1)] - D.f[i] * check(i - (int)B.f.size() + 1);
	for(int i = 0; i < (int)C.f.size(); ++i)
	{
		C.f[i] = (C.f[i] % p + p) % p;
		if(C.f[i] > p / 2) C.f[i] = C.f[i] - p;
	}
	C.f[1] += 2 * C.f[0]; C.f[0] = 0;
//	long double chk = 0;
//	for(int i = 0; i < (int)C.f.size(); ++i) chk += C.f[i] * (long double)(pow(nA, i) + pow(nB, i)), cout << fixed << setprecision(18) << C.f[i] << " "; cout << '\n';
//	cerr << "CHK " << (long long)chk / 5 << '\n';
	res = C * 6;
	for(int i = 3; i < (int)C.f.size(); ++i) res.f[i - 2] = res.f[i - 2] + C.f[i] * -4;
	res.f[1] = res.f[1] - C.f[1] * 4;
//	chk = 0;
//	cerr << "res : "; for(int i = 0; i < (int)res.f.size(); ++i) chk += fib[i] * res.f[i], cout << fixed << setprecision(18) << res.f[i] << " "; cout << '\n';
//	cerr << "CHK " << (long long)chk << '\n';
	k = res.f.size() - 1;
	for(int i = 1; i <= k; ++i) h[i] = res.f[i];
	long long Blo = INF;
	for(int i = k; i >= 2; --i)
	{
		if(h[i] >= 2 * Blo)
		{
			long long cur = (long long)h[i] / Blo;
			--cur;
			h[i - 1] += (h[i] - cur * Blo), h[i - 2] += (h[i] - cur * Blo);
			h[i] = cur * Blo;
		}
		else
		{
			h[i - 1] += h[i], h[i - 2] += h[i];
			h[i] = 0;
		}
	}
//	cerr << "h : "; for(int i = 1; i <= k; ++i) cerr << h[i] << " "; cerr << '\n';
	for(int i = 1; i <= k; ++i) g[i] = h[i] / 10;
	g[2] += g[1]; g[1] = 0;
	for(int i = 1; i <= k; ++i) f[i] = g[i];
//	cerr << "f : "; for(int i = 1; i <= k; ++i) cerr << f[i] << " "; cerr << '\n';
	k += 100; // should be 50 or 100
	int highbit = 0;
	for(int i = k; i >= 2; --i)
	{
		if(ans[i + 1]) continue;
		long long n1 = 1, n2 = 0; bool flag = false;
		for(int j = i; j >= 2; --j)
		{
			if(n1 > 100 * INF) break;
			n1 -= f[j];
			if(n1 <= 0 && n2 <= 0) {flag = true; break;}
			if(j == 3)
			{
				n2 += n1 * 2;
				if(n2 <= f[2]) flag = true;
				else break;
			}
			swap(n1, n2); n1 += n2;
		}
		if(flag)
		{
			highbit = max(highbit, i);
			ans[i] = true; n1 = 1, n2 = 0;
			for(int j = i; j >= 3; --j)
			{
				if(n1 <= f[j] && n2 <= f[j - 1])
				{
					f[j] -= n1, f[j - 1] -= n2; break;
				}
				n1 -= f[j]; f[j] = 0;
				if(j == 3)
				{
					n2 += n1 * 2;
					f[2] -= n2; break;
				}
				swap(n1, n2); n1 += n2;
			}
		}
	}
	cout << highbit - 1 << " "; for(int i = 2; i <= highbit; ++i) cout << ans[i] << " "; cout << '\n';
	for(int i = 1; i <= highbit; ++i) ans[i] = 0;
	for(int i = 1; i <= k; ++i) f[i] = g[i] = 0;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	fib[1] = fib[2] = 1;
	for(int i = 3; i <= 50; ++i) fib[i] = fib[i - 1] + fib[i - 2];
	cin >> T;
	while(T--) sol();
	return 0;
}
/*

*/
```

---

## 作者：qiuzx (赞：0)

注意到有结论 $F_iF_j+F_{i-1}F_{j-1}=F_{i+j}$，所以发现 $F_iF_j=F_{i+j}-F_{i+j-2}+F_{i+j-4}-\cdots\pm F_{i-j}$（不妨设 $i\ge j$）。因此对这两个数的斐波那契表示做一次卷积和一次差卷积（对奇偶的系数可能有所不同，详见代码），再做一次类似后缀和的操作，即可求出它们乘积的斐波那契表示。但这个表示并不标准。首先需要把负数去掉。注意到 $F_i-F_{i-2}=F_{i-1}$，所以在卷积求出来之后贡献到答案的时候做一些微小的修改即可。

现在每个系数都是正的，但可能会很大，并且不满足斐波那契表示的要求。注意到求一个数的斐波那契表示可以从高位往低位贪心，如果当前位比整个数要小就放置一个 $1$，并将整个数减去当前位的值。所以现在我们只需要能够求出两个斐波那契表示下的数的差即可。这个可以直接不断将 $F_i$ 用 $F_{i-1},F_{i-2}$ 回代，实时只需要维护 $i,i-1$ 两位前的系数即可。但这样做复杂度是平方的。不过如果当前的 $i$ 前面的系数已经超过了一个很大的值（这道题里 $10^{12}$ 已经足够了），那么后面就无需再继续检查了。因此这样一来，一旦向后进行了检查，要么将当前维护的值翻倍了，要么抹掉了一个原数中的非零位置，所以势能分析一下即可发现复杂度为 $O(n\log n)$。

[代码](https://loj.ac/s/2170087)

---

