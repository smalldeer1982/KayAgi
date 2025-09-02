# Koishi's Unconscious Permutation

## 题目描述

> 恋便闭上了能够读心的第三只眼。虽然因此而失去了读心的能力，但相对的却可以在无意识下进行行动了。就连她本人也不可能判断自己接下来会做什么。——《东方地灵殿》

古明地恋正在无意识地排列一个长度为 $n$ 的排列。

她认为，一个排列是美丽的，当且仅当 $s=\sum \limits_{i=1}^{n-1}[p_i+1=p_{i+1}]$，其中 $[x]=1$ 当且仅当 $x$ 成立。

对于 $\forall k \in [0,n-1]$，她希望知道有多少个美丽的长度为 $n$ 排列，满足 $k=\sum \limits_{i=1}^{n-1} [p_i<p_{i+1}]$。

## 样例 #1

### 输入

```
2 0```

### 输出

```
1 0```

## 样例 #2

### 输入

```
4 1```

### 输出

```
0 3 6 0```

## 样例 #3

### 输入

```
8 3```

### 输出

```
0 0 0 35 770 980 70 0```

# 题解

## 作者：watermoon (赞：7)

[洛谷公式炸了，这里有源码](https://www.cnblogs.com/AThousandMoons/p/16366616.html)

给定正整数 $n$ 和非负整数 $s$，求对所有满足 $s=\sum_{i=1}^{n-1}[p_i+1=p_{i+1}]$ 的长为 $n$ 的排列 $p$，求 $\sum_{i=1}^{n-1}[p_i<p_{i+1}]$ 的分布，模 $998\,244\,353$。

$s<n\le 2.5\cdot 10^5$。

前置知识：欧拉数的二元 GF。

> 设 $\displaystyle\mathcal F(x,t)=\sum_{n\ge 0}\frac{x^n}{n!}\sum_{m=0}^n\left\langle\!\begin{matrix}n \\ m\end{matrix}\!\right\rangle\cdot t^m$，考虑二项式反演，$[x^nt^m]\mathcal F(xt,1+t^{-1})$ 表示对长为 $n$ 的排列钦定 $n-m$ 个上升的方案数 $/n!$，考虑这些 $p_i<p_{i+1}$ 的限制，看成边之后形成 $m$ 个连通块，每个连通块内部要求有序，相当于划分成 $m$ 个集合，不同集合之间有顺序，也就是 $[x^n](\text e^x-1)^m$（第二类斯特林数）。所以 $\mathcal F(xt,1+t^{-1})=(1-(\text e^x-1)t)^{-1}$，从而 $\mathcal F(x,t)=\dfrac{t-1}{t-\text e^{(t-1)x}}.$

首先当然是先把连续段缩一下：所有答案乘上 $\binom{n-1}s$，然后令 $n:=n-s$，$k:=k-s$，$s:=0$，容斥一下就得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/qd69vahf.png)

现在问题就是求这玩意，首先我们只用求后面和式写成 $s$ 的多项式，换成 $t$ 就是说 $s^i\to t^i(1-t)^{n-i}$，即 $(-1)^{j-i}\binom{n-i}{j-i}[s^i]\to[t^j]$，这是卷积形式。

考虑分治，设 $c_m$ 是 Stirling 数的那个系数，对区间 $(l,r]$ 计算 $\sum_{m=l+1}^rc_m\sum_{i=l+1}^ms^{m-i}(-s-l)^{\underline{i-l}}/i^{\underline{i-l}}$，分类讨论 $i,m$ 在中点的哪边，可知再算 $\sum_{i=l+1}^rs^{r-i}(-s-l)^{\underline{i-l}}/i^{\underline{i-l}}$、$\sum_{i=l+1}^rc_is^{i-l}$ 和 $(-s-l)^{\underline{r-l}}/r^{\underline{r-l}}$ 就可以了，最后特判一下 $i=0$ 的贡献。时间复杂度 $\mathcal O(n\log^2n)$。

因为空间复杂度 $\mathcal O(n)$ 所以空间占用排到了 rk1，不过没啥用 ![](https://啧.tk/oh)

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<int> Poly;
const int N = 1 << 19, mod = 998244353;
int ksm(int a, int b){
	int res = 1;
	for(;b;b >>= 1, a = (LL)a * a % mod)
		if(b & 1) res = (LL)res * a % mod;
	return res;
}
int n, s, fac[N], ifac[N], inv[N], w[N];
int C(int a, int b){
	if(b < 0 || a < b) return 0;
	return (LL)fac[a] * ifac[b] % mod * ifac[a - b] % mod;
}
int rev[N], lim;
void calrev(int len){
	int L = -1; lim = 1;
	while(lim <= len){lim <<= 1; ++ L;}
	for(int i = 1;i < lim;++ i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << L);
}
void NTT(int *A, bool op){
	for(int i = 0;i < lim;++ i)
		if(i < rev[i]) swap(A[i], A[rev[i]]);
	for(int md = 1;md < lim;md <<= 1)
		for(int i = 0;i < lim;i += md << 1)
			for(int j = 0;j < md;++ j){
				int y = (LL)A[md + i + j] * (op && j ? mod - w[(md << 1) - j] : w[md + j]) % mod;
				if((A[md + i + j] = A[i + j] - y) < 0) A[md + i + j] += mod;
				if((A[i + j] += y) >= mod) A[i + j] -= mod;
			}
	if(op){
		int inv = ksm(lim, mod - 2);
		for(int i = 0;i < lim;++ i) A[i] = (LL)A[i] * inv % mod;
	}
}
Poly operator + (const Poly &a, const Poly &b){
	Poly res(max(a.size(), b.size()));
	for(int i = 0;i < res.size();++ i)
		if((res[i] = (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0)) >= mod) res[i] -= mod;
	return res;
}
int A[N], B[N];
Poly operator * (const Poly &a, const Poly &b){
	Poly res(a.size() + b.size() - 1);
	if(res.size() <= 50){
		for(int i = 0;i < a.size();++ i)
			for(int j = 0;j < b.size();++ j)
				res[i + j] = (res[i + j] + (LL)a[i] * b[j]) % mod;
	} else {
		calrev(res.size());
		memset(A, 0, lim << 2);
		memset(B, 0, lim << 2);
		for(int i = 0;i < a.size();++ i) A[i] = a[i];
		for(int i = 0;i < b.size();++ i) B[i] = b[i];
		NTT(A, 0); NTT(B, 0);
		for(int i = 0;i < lim;++ i) A[i] = (LL)A[i] * B[i] % mod;
		NTT(A, 1);
		for(int i = 0;i < res.size();++ i) res[i] = A[i];
	}
	return res;
}
Poly shl(Poly a, int k){a.insert(a.begin(), k, 0); return a;}
Poly Stir2(int n){
	Poly a(n + 1), b(n + 1);
	for(int i = 0;i <= n;++ i){
		a[i] = (LL)ksm(i, n) * ifac[i] % mod;
		b[i] = (i & 1) ? mod - ifac[i] : ifac[i];
	}
	a = a * b; a.resize(n + 1);
	for(int i = 0;i <= n;++ i) a[i] = (LL)a[i] * fac[i] % mod;
	return a;
}
Poly coe;
struct Node {Poly prd, sm0, sm1, sm2;};
Node work(int l, int r){
	if(r - l == 1){
		Node ans;
		ans.prd.resize(2); ans.prd[1] = mod - inv[r]; ans.prd[0] = (LL)l * ans.prd[1] % mod;
		ans.sm0.resize(2); ans.sm0[1] = coe[r]; ans.sm1 = ans.prd;
		ans.sm2.resize(2); ans.sm2[0] = (LL)ans.prd[0] * coe[r] % mod; ans.sm2[1] = (LL)ans.prd[1] * coe[r] % mod;
		return ans;
	}
	int md = l + r >> 1;
	Node ls = work(l, md), rs = work(md, r), res;
	res.prd = ls.prd * rs.prd;
	res.sm0 = ls.sm0 + shl(rs.sm0, md - l);
	res.sm1 = shl(ls.sm1, r - md) + rs.sm1 * ls.prd;
	res.sm2 = ls.sm2 + rs.sm2 * ls.prd + ls.sm1 * rs.sm0;
	return res;
}
Poly solve(int n){
	coe = Stir2(n);
	Node $ = work(0, n);
	Poly ans = $.sm2 + $.sm0, b(n + 1);
	for(int i = 0;i <= n;++ i){
		ans[i] = (LL)ans[i] * fac[n - i] % mod;
		b[i] = (i & 1) ? mod - ifac[i] : ifac[i];
	}
	ans = ans * b; ans.resize(n + 1);
	for(int i = 0;i <= n;++ i) ans[i] = (LL)ans[i] * ifac[n - i] % mod;
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin >> n >> s; *fac = 1;
	for(int i = 1;i < N;++ i) fac[i] = (LL)fac[i - 1] * i % mod;
	ifac[N - 1] = ksm(fac[N - 1], mod - 2);
	for(int i = N - 1;i;-- i){
		ifac[i - 1] = (LL)ifac[i] * i % mod;
		inv[i] = (LL)ifac[i] * fac[i - 1] % mod;
	}
	for(int md = 1;md < N;md <<= 1){
		int Wn = ksm(3, (mod - 1) / (md << 1)); w[md] = 1;
		for(int i = 1;i < md;++ i) w[md + i] = (LL)w[md + i - 1] * Wn % mod;
	}
	int coef = C(n - 1, s); n -= s;
	if(n == 1){
		for(int i = 0;i < s;++ i){putchar('0'); putchar(' ');}
		puts("1"); return 0;
	}
	Poly ans = solve(n) + solve(n - 1);
	for(int i = 0;i < s;++ i){putchar('0'); putchar(' ');}
	for(int i = n - 1;i >= 0;-- i) printf("%lld ", (LL)ans[i] * coef % mod);
	putchar('\n');
}
```

---

## 作者：huangzirui (赞：5)

定义一个长度为 $n$ 的排列 $a$ 是优美的，当且仅当 $\sum\limits_{i=1}^{n-1} [a_i+1=a_{i+1}]=s$ ，其中 $s$ 是给定的常数。

对于所有的 $k \in [0,n-1]$ ，你需要求：

$$\sum_{\text{排列}a\text{是优美的}}[\sum_{i=1}^{n-1}[a_i<a_{i+1}]=k]$$

---

首先做一些简单的转化。

等价于钦定 $n-s$ 个数字排列，要求不存在 $[a_i+1=a_{i+1}]$，然后乘个插板的系数 $\binom{n-1}{n-s-1}$。

令 $k \leftarrow k-s,n\leftarrow n-s$ 。

我们容斥那些钦定满足 $a_i+1=a_{i+1}$ 的位置，那么答案就是：

$$
ans_k
=
\sum_{j=0}^{k}
\binom{n-1}{j}
(-1)^j
\left\langle\begin{matrix} n-j\\k-j \end{matrix}\right\rangle
$$

我们知道欧拉数的生成函数是：

$$
\left\langle\begin{matrix} n\\m \end{matrix}\right\rangle
=
[x^my^n]\dfrac{n!(x-1)}{x-e^{(x-1)y}}
$$

那么就有：

$$
ans_k
=
\sum_{j=0}^{k}
\binom{n-1}{j}
(-1)^j
\left\langle\begin{matrix} n-j\\k-j \end{matrix}\right\rangle
$$
$$
=
\sum_{j=0}^{k}
\binom{n-1}{j}
(-1)^j
\left\langle\begin{matrix} n-j\\n-k-1 \end{matrix}\right\rangle
$$
$$
=
[x^{n-k-1}]
\sum_{j=0}^{k}
\binom{n-1}{j}
(-1)^j
[y^{n-j}]\dfrac{(n-j)!(x-1)}{x-e^{(x-1)y}}
$$
$$
=
[x^{n-k-1}]
\sum_{j=0}^{k}
\dfrac{(n-1)!}{j!}
(-1)^j
(n-j)[y^{n-j}]\dfrac{x-1}{x-e^{(x-1)y}}
$$
下面积分得到

$$
ans_k=
[x^{n-k-1}]
\sum_{j=0}^{k}
\dfrac{(n-1)!}{j!}(-1)^j
[y^{n-j-1}]\dfrac{\text{d}}{\text{d}y}\dfrac{x-1}{x-e^{(x-1)y}}
$$
$$
=
[x^{n-k-1}]
\sum_{j=0}^{k}
\dfrac{(n-1)!}{j!}
(-1)^j
[y^{n-j-1}]\dfrac{\text{d}}{\text{d}y}\dfrac{x-1}{x-e^{(x-1)y}}
$$
$$
=(n-1)![x^{n-k-1}]
\sum_{j=0}^{k}
\dfrac{(-1)^j}{j!}
[y^{n-j-1}]
\dfrac{(x-1)^2e^{(x-1)y}}{(x-e^{(x-1)y})^2}
$$
$$
=(n-1)![x^{n-k-1}]
\sum_{j=0}^{k}
[y^j]e^{-y}
[y^{n-j-1}]
\dfrac{(x-1)^2e^{(x-1)y}}{(x-e^{(x-1)y})^2}
$$
$$
=(n-1)![x^{n-k-1}]
[y^{n-1}]
\dfrac{(x-1)^2e^{(x-2)y}}{(x-e^{(x-1)y})^2}
$$
$$
=(n-1)![x^{n-k-1}]
[y^{n-1}]
\dfrac{(x-1)^2e^{xy}}{(xe^y-e^{xy})^2}
$$
$$
=(n-1)![x^{n-k-1}]
[y^{n-1}]
\dfrac{(x-1)^2e^{-xy}}{(xe^{(1-x)y}-1)^2}
$$

现在考虑计算 $[y^{n-1}]
\dfrac{(x-1)^2e^{-xy}}{(xe^{(1-x)y}-1)^2}$。

换元，令 $u=(1-x)y$ 得：

$$
[y^{n-1}]
\dfrac{(x-1)^2e^{-xy}}{(xe^{(1-x)y}-1)^2}
=
(1-x)^{n+1}
[u^{n-1}]
\dfrac{e^{\frac{-xu}{1-x}}}{(xe^u-1)^2}
$$
$$
=
(1-x)^{n+1}
[u^{n-1}]
\dfrac{e^{\frac{-xu}{1-x}}}{(1-xe^u)^2}
$$

现在考虑计算 $
[u^{n-1}]
\dfrac{e^{\frac{-xu}{1-x}}}{(1-xe^u)^2}
$ 。

展开得到：

$$
[u^{n-1}]
\dfrac{e^{\frac{-xu}{1-x}}}{(1-xe^u)^2}
$$
$$=
[u^{n-1}]
\sum_{i=0}
(i+1)x^ie^{(i-\frac{x}{1-x})u}
$$
$$=
[u^{n-1}]\sum_{i=0}(i+\frac{1}{1-x}+\frac{-x}{1-x})x^ie^{(i-\frac{x}{1-x})u}
$$
$$=
[u^{n-1}]
\sum_{i=0}(i-\frac{x}{1-x})x^ie^{(i-\frac{x}{1-x})u}+
[u^{n-1}]	
\frac{1}{1-x}\sum_{i=0}x^ie^{(i-\frac{x}{1-x})u}
$$
$$=
[u^{n}]
\sum_{i=0}nx^ie^{(i-\frac{x}{1-x})u}+
[u^{n-1}]
\frac{1}{1-x}\sum_{i=0}x^ie^{(i-\frac{x}{1-x})u}
$$
$$=
[u^{n}]
\dfrac{ne^{-\frac{xu}{1-x}}}{1-xe^u}+
[u^{n-1}]
\frac{1}{1-x}
\dfrac{e^{-\frac{xu}{1-x}}}{1-xe^u}
$$

我们只关心 $[u^{n}]\dfrac{e^{-\frac{xu}{1-x}}}{1-xe^u}$。

接下来令 $w=e^u-1$ 得到：

（这里令 $w$ 没有常数项）

$$
[u^{n}]
\dfrac{(w+1)^{-\frac{x}{1-x}}}{1-x(w+1)}
$$
$$
=
\sum_{m=0}^n [u^n](e^u-1)^m[w^{m}]
\dfrac{(w+1)^{-\frac{x}{1-x}}}{1-x(w+1)}
$$
$$
=
\sum_{m=0}^n [u^n](e^u-1)^m[w^{m}]
\dfrac{\sum_{i=0}w^i\binom{-\frac{x}{1-x}}{i}}{1-x(w+1)}
$$
$$
=
\sum_{m=0}^n [u^n](e^u-1)^m[w^{m}]
\dfrac{\sum_{i=0}w^i\binom{-\frac{x}{1-x}}{i}}{1-xw-x}
$$
$$
=
\dfrac{1}{1-x}
\sum_{m=0}^n [u^n](e^u-1)^m[w^{m}]
\dfrac{\sum_{i=0}w^i\binom{-\frac{x}{1-x}}{i}}{1-\frac{x}{1-x}w}
$$
$$
=
\dfrac{1}{1-x}
\sum_{m=0}^n [u^n](e^u-1)^m
\sum_{i=0}^m
\binom{-\frac{x}{1-x}}{i}
(\dfrac{x}{1-x})^{m-i}
$$

令 $s=\dfrac{x}{1-x}$ 得到：

$$
=
\dfrac{1}{1-x}
\sum_{m=0}^n [u^n](e^u-1)^m
\sum_{i=0}^m
\binom{-s}{i}
s^{m-i}
$$

$[u^n](e^u-1)^m$ 恰好是第二类斯特林数。

用矩阵刻画后面的东西，容易构造出：

$$
\left[
\begin{matrix}
\binom{-s}{m} & \sum_{i=0}^m\binom{-s}{i}s^{m-i}
\end{matrix}
\right]
\times
\left[
\begin{matrix}
\frac{-s-m}{m+1} & \frac{-s-m}{m+1}\\
0 & s
\end{matrix}
\right]
=
\left[
\begin{matrix}
\binom{-s}{m+1} & \sum_{i=0}^{m+1}\binom{-s}{i}s^{m+1-i}
\end{matrix}
\right]
$$
我们在计算时令 $s=\dfrac{x}{1-x}$，然后算的时候，只维护当前除以 $\dfrac{1}{(1-x)^k}$ 的值，就能做到 $O(n\log^2n)$。于是我们就可以得到
$$
\dfrac{1}{1-x}
\sum_{m=0}^n [u^n](e^u-1)^m
\sum_{i=0}^m
\binom{-s}{i}
s^{m-i}
$$

即 $[u^{n}]\dfrac{e^{-\frac{xu}{1-x}}}{1-xe^u}$，于是就能得到 $[u^{n-1}]\dfrac{e^{\frac{-xu}{1-x}}}{(1-xe^u)^2}$，推到 $[y^{n-1}]\dfrac{(x-1)^2e^{-xy}}{(xe^{(1-x)y}-1)^2}$，提取系数就得解了。

---

